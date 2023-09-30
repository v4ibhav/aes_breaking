#include"aes_breaking.h"
#define enable_feature_find_the_lowest_number_trace_needed
fstream output_plaintext_f("input_plaintext.txt", ios::in);
ofstream outfile("output.txt");
vector<vector<vector<uint8_t>>> dpa_3d_model(16, vector<vector<uint8_t>>(10000, vector<uint8_t>(256)));
vector<vector<int>> text_matrix(10000, vector<int>(16));
/*
    //the goal is to find the evolution graph -key256x10000-input values
    //at particular time stamp
    //the time stamp for the f
    
    key bytes -----> timestamp----------------------------------->  Keys
    1         -----> 43------------------------------------------>  0x00   
    2         -----> 43------------------------------------------>  0x01 
    3         -----> 43------------------------------------------>  0x02 
    4         -----> 43------------------------------------------>  0x03 
    5         -----> 43------------------------------------------>  0x04 
    6         -----> 43(false positive)-------------------------->  0x05 
    7         -----> 43 ----------------------------------------->  0x06 
    8         -----> 43(false positive)-------------------------->  0x07
    9         -----> 43 ----------------------------------------->  0x08 
    10        -----> 38 (negative correlation)--brute force ----->  0x09
    11        -----> 43------------------------------------------>  0x0a 
    12        -----> 43------------------------------------------>  0x0b 
    13        -----> 43------------------------------------------>  0x0b 
    14        -----> 38(negative correlation)--brute force ------>  0x0d
    15        -----> 43------------------------------------------>  0x0e 
    16        -----> 43------------------------------------------>  0x0f 
    

    //do it for first key(0x00) at the particular timestamp i have powetrace value of 10'000
    //and X_values
*/

void func_3d_dpa_model()
{
    int row = 0;
    string plain_text;

    fstream input_plaintext_f("input_plaintext.txt", ios::in);

    if(!input_plaintext_f.is_open())
    {
        outfile<<"File not opening"<<endl;
        return;
    }
    while(getline(input_plaintext_f, plain_text))
    {
        foru(i,16)
        {
            int nthstring = i*2;
            uint8_t p_text_B = nthstring_to_byte(nthstring,plain_text);
            text_matrix[row][i] = p_text_B;
        }
        // outfile<<"the plaintext for the "<<" is := "<<static_cast<int>(p_text_B)<<endl;
        row++;
        // break;
    }
    input_plaintext_f.close();
    foru(nthbyte,16)
    {
        foru(row,10000)
        {
            dpa_matrix_calc(text_matrix[row][nthbyte], row);
        }
        dpa_3d_model[nthbyte] = dpa_matrix;
    }
}
template <typename T>
void printer_nd(vector<T> Y_values_x)
{
    // if(dimension == 2)
    {
        foru(row,Y_values_x.size())
        {
            foru(col,Y_values_x[0].size())
            {
                outfile<<static_cast<double>(Y_values_x[row][col])<<", ";
            }
            outfile<<endl;
        }
        outfile<<endl;

    }
}
int main()
{
    //use current code to create 3d matrix of dpa
    Y_array = power_trace_Y(); // this is fine but the problem was reading the csv file lets just strore it first.
    func_3d_dpa_model();
    foru(thisisatrial,16)
    {
        dpa_matrix = dpa_3d_model[thisisatrial];
        for(uint16_t current_key = 0x00; current_key <= 0xff; current_key++)
        {
            all_linearity_for_all_keys[current_key]  = dpa_linearity_calc(current_key,thisisatrial);
        }
        std::ofstream out(filenames[thisisatrial]);
        //saving correlation of size 256x400 16mtimes
        for (auto& row : all_linearity_for_all_keys) 
        {
        for (auto col : row)
            out << col <<',';
        out << '\n';
        }
        out.close();
        std::ofstream output_t(filenames_for_evolution[thisisatrial]);
        //saving correlation of size 256x400 16mtimes
        for (auto& row : for_all_keys_linearity_for_all_measurement) 
        {
        for (auto col : row)
            output_t << col <<',';
        output_t << '\n';
        }
        output_t.close();
        
    }
    outfile.close();
    return 0;
}
void dpa_matrix_calc(uint8_t p_text_B, int row)
{
    uint8_t after_xor;
    uint8_t after_sub;
    uint8_t hemming_d;
    for(int i  = 0x00; i<=0xFF; i++){
        uint8_t key = i;
        after_xor = input_xor_key(p_text_B, key);
        after_sub = subbyte(after_xor);

        hemming_d = hemming_x(after_xor, p_text_B);
        filling_dpa_matrix(key,row,hemming_d);
    }    
}
void filling_dpa_matrix(uint8_t key,int row, uint8_t hemming_d)
{
    dpa_matrix[row][key] = hemming_d;
}
vector<double> dpa_linearity_calc(uint8_t key,int trial)
{
    
    X_values = power_model_X(key,10000);
    meanofX = finding_the_mean_of_dataset(X_values);
    foru(i,400)
    {
        
        int evolve = ((i==43)&(trial!=13))?1:0;
        evolve = ((trial==13) &(i==38))?1:evolve;
        Y_values = power_trace_of_nth(i,10000);
        meanofY = finding_the_mean_of_dataset(Y_values);
        all_linearity_for_one_key_for_400_time_stamps[i] = pearsonCorr_calc(X_values, Y_values,evolve,key);
    }
    return all_linearity_for_one_key_for_400_time_stamps;

} 
uint8_t nthstring_to_byte(uint8_t nth, string plain_text)
{
    uint8_t p_text_B = 0;
    string sub_str = plain_text.substr(nth, 2); //substr contains starting position and length
    p_text_B = stoi(sub_str, nullptr, 16);
    return p_text_B;
}
 
uint8_t input_xor_key(uint8_t p_text_B, uint8_t key)
{

    uint8_t after_xor;
    after_xor = p_text_B ^ key;
    return after_xor ;
}
uint8_t subbyte(uint8_t state_prev)
{
    uint8_t state_row = state_prev&0x0f;
    uint8_t state_col = state_prev>>4;
    uint8_t state_value = s_box_matrix[state_row][state_col];
    return state_value;
}
uint8_t hemming_x(uint8_t after_xor, uint8_t p_text_B)
{

    uint8_t hemming_d = 0;
    while(after_xor)
    {
        if(after_xor & 1)
        {
            hemming_d++;

        }
        after_xor >>=1;

    }
    return hemming_d;
 
}
void printer(int val)
{
   if(val == 2)
   {
        

        foru(i,all_linearity_for_all_keys.size())
        {
            outfile<<all_linearity_for_one_key_for_400_time_stamps[i]<<" ";
        }
        outfile<<endl;

   }

    else if(val == 1)
    {
        foru(i,10000)
        {
            outfile<<static_cast<double>(Y_values[i])<<" ";
        }
        outfile<<endl;

    }
    else if(val == 3)
    {
        foru(i,10)
        {
            foru(j,dpa_matrix[i].size())
            {
                outfile<<hex<<static_cast<int>(dpa_matrix[i][j])<<" ";
            }
            outfile<<endl;
        }
    }
    else{
        foru(i,10000)
        {
            outfile<<static_cast<double>(X_values[i])<<" ";
        }
        outfile<<endl;

    }

    // 
    

}

vector<double> power_model_X(uint8_t key,int numberofrows)
{
    vector<double> x_array(10000);
    foru(row,numberofrows)
    {

        x_array[row] = dpa_matrix[row][key];
        // outfile<<hex<<static_cast<int>(dpa_matrix[row][key])<<endl;
        
    }
    return x_array;
}
vector<vector<int>> power_trace_Y() //this opening and storing the values inside an 2darray now in the form of int.
{
    
    ifstream file("traces.csv");
    vector<vector<int>> data(10000,(vector<int>(400,0)));
    for(int row = 0; row < 10000; row++)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() ) 
            break;

        std::stringstream iss(line);

        for (int col = 0; col < 400; col++)
        {
            std::string val;
            std::getline(iss, val, ',');
            std::stringstream convertor(val);
            convertor >> data[row][col];
            
        }
        // Clear the newline character from the input stream
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    file.close();
    return data;
}
double finding_the_mean_of_dataset(vector<double> set)
{
    if(set.empty()){
        return 0;
    }

    auto const count = static_cast<double>(set.size());
    return accumulate(set.begin(), set.end(),0.0) / count;
}
vector<double> power_trace_of_nth(int timestamp, int range)
{
    vector<double> return_vector(10000);
    foru(i,range)
    {
        return_vector[i] = Y_array[i][timestamp];
    }
    return return_vector;
}
double pearsonCorr_calc(const std::vector<double> x, const std::vector<double> y,int evolve,int key) {
    if (x.size() != y.size()) {
        std::cerr << "Error: Arrays must have the same length." << std::endl;
        return 0.0f; // Return an error value or handle the error as appropriate
    }


    double sumXY = 0.0f;
    double sumX2 = 0.0f;
    double sumY2 = 0.0f;
    double correlation_for_time_index;

    int measurement_counter =0;

    for (size_t i = 0; i < x.size(); i++) {

        double deltaX = x[i] - meanofX;
        double deltaY = y[i] - meanofY;
        sumXY += deltaX * deltaY;
        sumX2 += deltaX * deltaX;
        sumY2 += deltaY * deltaY;
        if(evolve == 1)
        {
            correlation_for_time_index = sumXY / (sqrt(sumX2) * sqrt(sumY2));
            for_all_keys_linearity_for_all_measurement[key][i] = correlation_for_time_index;
            //findthehighestcorrelation for the correct key guess
        }

    }
        double correlation = sumXY / (sqrt(sumX2) * sqrt(sumY2));
    return correlation;
}
