#include <vector>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <windows.h>
#include <filesystem>
#include "Model.h"
#include "kernal.h"
#include "preprocess.h"
#include "convolutional.h"

using namespace std;

void clearScreen();
bool find_pixel_folder(string&);
bool find_pixels_folder(string&);
vector<string> list_txt_files(const string&);

int main()
{
    Model model;
    Kernal kernal;
    Preprocess pre;
    Convolution convo;
    vector<double> fc_bias;
    vector<double> convo_bias;
    vector<string> folder_name;
    vector<vector<double>> fc_weigth;
    vector<vector<double>> convo_weigth;

    while(true)
    {
        int choise;
        cout << "1. Train On New Dataset For Press [1] :- " << endl;
        cout << "2. Predict Image        For Press [2] :- " << endl;
        cout << "3. Clear Screen         For Press [3] :- " << endl;
        cout << "4. Exit                 For Press [0] :- " << endl << endl;
        cout << "Enter Your Choise :- ";
        cin >> choise;
        if (choise==1)
        {
            convo_weigth.clear();
            fc_weigth.clear();
            convo_bias.clear();
            fc_bias.clear();
            folder_name.clear();
            vector<vector<double>> labels;
            vector<vector<vector<double>>> data;
            vector<vector<vector<vector<double>>>> pixel;
            vector<vector<vector<vector<vector<int>>>>> mask;
            BROWSEINFO bi = { 0 };
            bi.lpszTitle = "Select a Dataset";
            bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
            LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
            if (pidl != nullptr)
            {
                char path[MAX_PATH];
                if (SHGetPathFromIDList(pidl, path))
                {
                    pre.create_pixels_txt(folder_name,string(path));
                    int train;
                    cout << "How Many Times To Train The Model :- ";
                    cin >> train;
                    pre.One_Hot_Encoding(labels,folder_name.size());
                    kernal.values(convo_weigth,convo_bias,5,5,1,2);
                    convo.operation(data,pixel,mask,convo_weigth,convo_bias,5,2);
                    kernal.values(fc_weigth,fc_bias,data[0][0].size(),folder_name.size());
                    model.train(data,labels,pixel,mask,fc_weigth,convo_weigth,fc_bias,convo_bias,train);
                }
                else cerr << "Failed to get folder path." << endl;
                CoTaskMemFree(pidl);
            }
            else cout << "No folder selected." << endl;
        }
        else if (choise==2)
        {
            cout << "Exit For Tyepe [exit]" << endl;
            string pixels_folder;
            while(true)
            {
                string path;
                cout << "Path :- ";
                cin >> path;
                if (path=="exit" || path=="Exit")
                {
                    string folder = pixels_folder + "\\";
                    SHFILEOPSTRUCTA fileOp = { 0 };
                    fileOp.wFunc = FO_DELETE;
                    fileOp.pFrom = folder.c_str();
                    fileOp.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION | FOF_SILENT;
                    int result = SHFileOperationA(&fileOp);;
                    break;
                }
                else
                {     
                    vector<vector<double>> data1;
                    pre.create_pixels_txt(path);
                    if (!find_pixel_folder(pixels_folder)) cout << "'pixels' folder not found in current directory.\n";
                    else
                    {
                        vector<string> txt_files = list_txt_files(pixels_folder);
                        if (txt_files.empty()) cout << "No .txt files found in 'pixels' folder.\n";
                        else
                        {
                            convo.operation(txt_files[0],data1,convo_weigth,convo_bias,2);
                            for (int i = 0; i < folder_name.size(); ++i) cout << folder_name[i] << " ";
                            cout << endl;
                            cout << folder_name[model.predict(data1,fc_weigth,fc_bias)] << endl;
                        }
                    }
                }
                string folder = pixels_folder + "\\";
                SHFILEOPSTRUCTA fileOp = { 0 };
                fileOp.wFunc = FO_DELETE;
                fileOp.pFrom = folder.c_str();
                fileOp.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION | FOF_SILENT;
                int result = SHFileOperationA(&fileOp);;                
            }
        }
        else if(choise==3) clearScreen();
        else
        {
            string pixel_folder;
            find_pixels_folder(pixel_folder);
            string folder = pixel_folder + "\\";
            SHFILEOPSTRUCTA fileOp = { 0 };
            fileOp.wFunc = FO_DELETE;
            fileOp.pFrom = folder.c_str();
            fileOp.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION | FOF_SILENT;
            int result = SHFileOperationA(&fileOp);;
            break;
        }
    }
}
void clearScreen()
{
    system("cls");
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