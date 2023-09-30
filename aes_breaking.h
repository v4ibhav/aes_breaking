#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<string>
#include<bitset>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<numeric>
#include<chrono>
#define foru(i,n) for(int i = 0; i<n; i++)
#define vec2dint8 vector<vector<uint8_t>>//same as below
#define vec3dint8 vector<vec2dint8>//may not need it this time
using namespace std;



//variable and objects

vector<double> X_values(10000);
vector<double> Y_values(10000);
vector<vector<int>> Y_array(10000,(vector<int>(400,0)));

vec2dint8 dpa_matrix(10000,(vector<uint8_t>(256)));


uint8_t current_key;
//function definition
uint8_t nthstring_to_byte(uint8_t,string);
uint8_t input_xor_key(uint8_t, uint8_t);
//uint8_t xor_to_subbyte();
uint8_t hemming_x(uint8_t, uint8_t);
void filling_dpa_matrix(uint8_t,int , uint8_t);

void dpa_matrix_calc(uint8_t,int);
vector<double> dpa_linearity_calc(uint8_t,int);
void printer(int);

vector<double> power_model_X(uint8_t,int);
vector<vector<int>> power_trace_Y();
vector<double> power_trace_of_nth(int,int);

vector<uint8_t> linearity_res(uint8_t);


// double mean(vector<double>);
// void meanofX(vector<double> data);

vector<double> all_linearity_for_one_key_for_400_time_stamps(400);
vector<vector<double>> all_linearity_for_all_keys(256,(vector<double>(400)));
vector<vector<double>> for_all_keys_linearity_for_all_measurement(256,(vector<double>(10'000,0)));




///------------------------x-------------------------x-----------------------


//trying to get the efficiecnt calculation


double pearsonCorr_calc(vector<double> , vector<double>,int,int);


double meanofX;
double meanofY;
//create the function which will find it.
double finding_the_mean_of_dataset(vector<double>);
double average(vector<double> const&);


//-------------x------------------------x-----------
const vec2dint8 s_box_matrix =
{
//   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	{0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},//0
	{0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},//1
	{0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},//2
	{0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},//3
	{0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},//4
	{0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},//5
	{0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},//6
	{0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},//7
	{0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},//8
	{0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},//9
	{0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},//A
	{0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},//B
	{0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},//C
	{0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},//D
	{0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},//E
	{0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16} //F
};


uint8_t subbyte(uint8_t );
vector<string> filenames = {
        "correlation_256x400_for_1st_byte.csv",
        "correlation_256x400_for_2nd_byte.csv",
        "correlation_256x400_for_3rd_byte.csv",
        "correlation_256x400_for_4th_byte.csv",
        "correlation_256x400_for_5th_byte.csv",
        "correlation_256x400_for_6th_byte.csv",
        "correlation_256x400_for_7th_byte.csv",
        "correlation_256x400_for_8th_byte.csv",
        "correlation_256x400_for_9th_byte.csv",
        "correlation_256x400_for_10th_byte.csv",
        "correlation_256x400_for_11th_byte.csv",
        "correlation_256x400_for_12th_byte.csv",
        "correlation_256x400_for_13th_byte.csv",
        "correlation_256x400_for_14th_byte.csv",
        "correlation_256x400_for_15th_byte.csv",
        "correlation_256x400_for_16th_byte.csv"
    };

	vector<string> filenames_for_evolution = {
        "evolution_of_the_1st_byte.csv",
        "evolution_of_the_2nd_byte.csv",
        "evolution_of_the_3rd_byte.csv",
        "evolution_of_the_4th_byte.csv",
        "evolution_of_the_5th_byte.csv",
        "evolution_of_the_6th_byte.csv",
        "evolution_of_the_7th_byte.csv",
        "evolution_of_the_8th_byte.csv",
        "evolution_of_the_9th_byte.csv",
        "evolution_of_the_10th_byte.csv",
        "evolution_of_the_11th_byte.csv",
        "evolution_of_the_12th_byte.csv",
        "evolution_of_the_13th_byte.csv",
        "evolution_of_the_14th_byte.csv",
        "evolution_of_the_15th_byte.csv",
        "evolution_of_the_16th_byte.csv"
    };


void evolution_calc(vec2dint8, vec3dint8);
vector<vector<double>> evolution_matrix_for_ith_inputandtimestamp(256,(vector<double>(10'000)));
vector<double> evolution_matrix_for_ith_inputandtimestampandkey(10'000);