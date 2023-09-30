#include"aes_breaking.h"
ofstream outfile("dummy.txt");
fstream tracesd("traces.csv",ios::in);


float average(vector<float> const& v){
    if(v.empty()){
        return 0;
    }

    auto const count = static_cast<float>(v.size());
    return accumulate(v.begin(), v.end(),0.0) / count;
}
int main()
{
    string line;
    // vector<uint8_t> y_array(10000);
    // while(getline(tracesd, line))
    // {
    //     stringstream linestream(line);
    //     int colCount = 0;
    //     string cell;
    //     while (getline(linestream, cell, ',')) {
    //             colCount++;
    //             // Check if this is the 3rd column (column index 2)
    //             if (colCount == 1) {
    //                 outfile<<cell<<" "<<endl;
    //             }
    //         }
    // }

    vector<float> v{8, 4, 2, 7, 5};
    auto const a = average(v);
    outfile << "average: " << a << "\n";

    outfile.close();
    return 0;
}

