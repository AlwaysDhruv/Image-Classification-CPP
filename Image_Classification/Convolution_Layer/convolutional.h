#ifndef CONVOLUTIONAL_H
#define CONVOLUTIONAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <direct.h>
#include <windows.h>

#define MAX_PATH_LEN 260

using namespace std;

class Convolution
{
public:
    void operation(vector<vector<vector<double>>>& values, vector<vector<vector<vector<double>>>>& raw_pixel, vector<vector<vector<vector<vector<int>>>>>& mask, vector<vector<double>>& kernels, vector<double> bias, int row, int stride)
    {
        string pixels_folder;
        if (!find_pixels_folder(pixels_folder)) cout << "'pixels' folder not found in current directory.\n";
        else
        {
            vector<string> txt_files = list_txt_files(pixels_folder);
            if (txt_files.empty()) cout << "No .txt files found in 'pixels' folder.\n";
            else
            {
                for (int i = 0; i < txt_files.size(); ++i)
                {
                    ifstream file(txt_files[i]);
                    if (file.is_open())
                    {
                        int ct = 0;
                        int imge = 0;
                        string line;
                        string token;
                        vector<double> pixel;
                        vector<vector<int>> temp;
                        vector<vector<double>>answer2;
                        vector<vector<double>> pixels;
                        vector<vector<vector<int>>> temp2;
                        vector<vector<vector<double>>> temp4;
                        vector<vector<vector<vector<int>>>> temp3;
                        while (getline(file, line))
                        {
                            stringstream ss(line);
                            while (getline(ss, token, ','))
                            {
                                pixel.push_back(stod(token));
                                ++ct;
                                if (ct==64)
                                {
                                    pixels.push_back(pixel);
                                    pixel.clear();
                                    ct = 0;
                                }
                            }
                            vector<double>answer;
                            temp4.push_back(pixels);
                            for (int kern = 0; kern < kernels.size(); ++kern)
                            {
                                vector<double>ans;
                                vector<vector<double>>kernal;
                                for (int j = 0; j < kernels[0].size(); ++j)
                                {
                                    ans.push_back(kernels[kern][j]);
                                    ++ct;
                                    if (ct==row)
                                    {
                                        kernal.push_back(ans);
                                        ans.clear();
                                        ct = 0;
                                    }
                                }
                                vector<vector<double>>main;
                                double sum = 0.0;
                                int cols = pixels.size() - kernal.size() + 1;
                                int rows= pixels[0].size() - kernal[0].size() + 1;
                                for (int a = 0; a < cols; ++a)
                                {
                                    for (int b = 0; b < rows; ++b)
                                    {
                                        for (int i = 0; i < kernal.size(); ++i)
                                            for (int j = 0; j < kernal[0].size(); ++j) sum += ((pixels[i + a][j + b] * kernal[i][j]) + bias[i]);
                                        ans.push_back(relu(sum));
                                        sum = 0.0;
                                    }
                                    main.push_back(ans);
                                    ans.clear();
                                }
                                temp.assign(main.size(), vector<int>(main[0].size(), 0));
                                for (int a = 0; a < main.size(); a += stride)
                                {
                                    for (int b = 0; b < main[0].size(); b += stride)
                                    {
                                        double max_val = main[a][b];
                                        int max_i = a, max_j = b;
                                        for (int i = 0; i < stride; ++i)
                                        {
                                            for (int j = 0; j < stride; ++j)
                                            {
                                                int x = a + i;
                                                int y = b + j;
                                                if (main[x][y] > max_val)
                                                {
                                                    max_val = main[x][y];
                                                    max_i = x;
                                                    max_j = y;
                                                }
                                            }
                                        }
                                        answer.push_back(max_val);
                                        temp[max_i][max_j] = 1;
                                    }
                                }
                                temp2.push_back(temp);
                                temp.clear();
                            }
                            temp3.push_back(temp2);                            
                            answer2.push_back(answer);
                            answer.clear();
                            pixels.clear();
                            temp2.clear();
                            ++imge;
                        }                        
                        mask.push_back(temp3);
                        values.push_back(answer2);
                        raw_pixel.push_back(temp4);
                        answer2.clear();
                        temp4.clear();
                        temp3.clear();
                        imge = 0;
                    }
                    else cout << "File Not Found..." << endl;
                }
            }
        }
    }

    void operation(string name, vector<vector<double>>& values, vector<vector<double>>& kernels, vector<double>& bias, int stride)
    {
        ifstream file(name);
        if (file.is_open())
        {
            int ct = 0;
            string line;
            string token;
            vector<double> pixel;
            vector<vector<double>> pixels;
            while (getline(file, line))
            {
                stringstream ss(line);
                while (getline(ss, token, ','))
                {
                    pixel.push_back(stod(token));
                    ++ct;
                    if (ct==64)
                    {
                        pixels.push_back(pixel);
                        pixel.clear();
                        ct = 0;
                    }
                }
            }
            vector<double> answer;
            for (int kern = 0; kern < kernels.size(); ++kern)
            {
                vector<double>ans;
                vector<vector<double>>kernal;
                for (int j = 0; j < kernels[0].size(); ++j)
                {
                    ans.push_back(kernels[kern][j]);
                    ++ct;
                    if (ct==sqrt(kernels[0].size()))
                    {
                        kernal.push_back(ans);
                        ans.clear();
                        ct = 0;
                    }
                }
                vector<vector<double>>main;
                double sum = 0.0;
                int cols = pixels.size() - kernal.size() + 1;
                int rows= pixels[0].size() - kernal[0].size() + 1;
                for (int a = 0; a < cols; ++a)
                {
                    for (int b = 0; b < rows; ++b)
                    {
                        for (int i = 0; i < kernal.size(); ++i)
                            for (int j = 0; j < kernal[0].size(); ++j) sum += ((pixels[i + a][j + b] * kernal[i][j]) + bias[i]);
                        ans.push_back(relu(sum));
                        sum = 0.0;
                    }
                    main.push_back(ans);
                    ans.clear();
                }
                for (int a = 0; a < main.size(); a += stride)
                {
                    for (int b = 0; b < main[0].size(); b += stride)
                    {
                        double max_val = main[a][b];
                        for (int i = 0; i < stride; ++i)
                            for (int j = 0; j < stride; ++j)
                                max_val = max(max_val,main[a + i][a + i]);
                        answer.push_back(max_val);
                    }
                }
            }
            values.push_back(answer);
        }
        else cout << "Invalid Path " << name << endl;
    }

    bool find_pixels_folder(string& pixels_path)
    {
        char current_path[MAX_PATH_LEN];
        if (!_getcwd(current_path, MAX_PATH_LEN)) return false;

        string test_path = string(current_path) + "\\pixels";

        DWORD attribs = GetFileAttributes(test_path.c_str());
        if (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY))
        {
            pixels_path = test_path;
            return true;
        }

        return false;
    }

    bool find_pixel_folder(string& pixel_path)
    {
        char current_path[MAX_PATH_LEN];
        if (!_getcwd(current_path, MAX_PATH_LEN)) return false;

        string test_path = string(current_path) + "\\pixel";

        DWORD attribs = GetFileAttributes(test_path.c_str());
        if (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY))
        {
            pixel_path = test_path;
            return true;
        }
        return false;
    }    
    
    vector<string> list_txt_files(const string& folder_path)
    {
        vector<string> txt_files;
        string search_pattern = folder_path + "\\*.txt";

        WIN32_FIND_DATA find_data;
        HANDLE hFind = FindFirstFile(search_pattern.c_str(), &find_data);
        if (hFind == INVALID_HANDLE_VALUE) return txt_files;

        do
        {
            string full_path = folder_path + "\\" + find_data.cFileName;
            txt_files.push_back(full_path);
        } while (FindNextFile(hFind, &find_data) != 0);

        FindClose(hFind);
        return txt_files;
    }

    double relu(double x)
    {
        return max(0.0, x);
    }
};
#endif