#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <vector>
#include <string>
#include <cstdlib>
#include <shlobj.h>
#include <iostream>
#include <windows.h>
#include <filesystem>

using namespace std;
using namespace filesystem;

class Preprocess
{
public:
    void create_pixels_txt(vector<string>& folder_name, string path)
    {
        if (path!="")
        {
            for (const auto& entry : directory_iterator(path))
                if (entry.is_directory()) folder_name.push_back(entry.path().filename().string());
            for (int i = 0; i < folder_name.size(); ++i)
            {
                string folder_path  = path + "\\" + folder_name[i];
                string command = "python multiple_preprocess.py \"" + folder_path + "\" " + folder_name[i];
                int result = system(command.c_str());
                if (result != 0) cout << "Python preprocessing failed.\n";
            }
            cout << "File Created..." << endl;
        }
        else cout << "Invalid path" << endl;
    }
    
    void create_pixels_txt(string paths)
    {
        if (paths!="")
        {
            string command = "python single_preprocess.py \"" + paths;
            int result = system(command.c_str());
            if (result != 0) cout << "Python preprocessing failed.\n";
            else cout << "File Created..." << endl;
        }
        else cout << "Invalid path" << endl;
    }

    void One_Hot_Encoding(vector<vector<double>>& output,int size)
    {
        vector<double> temp;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j) temp.push_back(0);
            temp.erase(temp.begin() + i);
            temp.insert(temp.begin() + i,1);
            output.push_back(temp);
            temp.clear();
        }
    }
};
#endif