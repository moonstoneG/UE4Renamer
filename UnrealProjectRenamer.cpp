#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include <stdio.h>
#include <io.h>
#include<string>
#include<fstream>

using namespace std;

bool RemoveDir(const char* szFileDir)

{
 string strDir = szFileDir;
 if (strDir.at(strDir.length()-1) != '\\')
   strDir += '\\';
 WIN32_FIND_DATA wfd;
 HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
 if (hFind == INVALID_HANDLE_VALUE)
 return false;
 do
 {
 if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
 {
 if (stricmp(wfd.cFileName,".") != 0 &&
 stricmp(wfd.cFileName,"..") != 0)
 RemoveDir( (strDir + wfd.cFileName).c_str());
 }
 else
 {
 DeleteFile( (strDir + wfd.cFileName).c_str());
 }
 }
 while (FindNextFile(hFind,&wfd));
 FindClose(hFind);
 RemoveDirectory(szFileDir);
 return true;
}

int main()
{
   _finddata_t file;
   _finddata_t configfile;
    int k;
  long HANDLE;
  int j;
  long HANDLE1;
  string oldpathname;
  string newpathname;
  fstream f;

static char path[256];
    k = HANDLE = _findfirst("*.uproject", &file);
    j = HANDLE1 = _findfirst("Config\\DefaultEngine.ini", &configfile);
    GetCurrentDirectoryA(256,path);
    string dir(path,4);
    dir.replace(2,2,"//");
    
    if (j == -1)
    {
        cout << "cannot find config file!!!" << endl;
    }
    if (k != -1)
    {
        cout <<"Target Project found!"<< file.name << endl;
        cout <<"Target prohect config found!" <<configfile.name << endl;
        k = _findnext(HANDLE, &file);
        cout << "confirm ur project Y/N" << endl;
        static string temp = file.name;

        const char* oldname = temp.c_str();
        
        char confirmres;
        cin >> confirmres;
        static int i;
        static char p[100];

        for(int j =0;j<temp.length();j++)
        {p[j]=temp[j];};

        for(i =0;i<temp.length();i++)
        {
            if(temp[i] == '.')
            break;
        }
        static string projectrealname(p,i);
        cout<<dir;
        static  string oldprojectpath = dir + projectrealname;
        cout<<oldprojectpath<<endl;
        if (confirmres == 'y' || confirmres == 'Y')
        {
            int res;
            cout << "input new project name!!!" << endl;
            string newname;
            cin >> newname;
            static const string newprojectpath = dir + newname;
            cout<<newprojectpath<<endl;
            res = rename(oldname, (newname + ".uproject").c_str());
            string configname;
            configname = newname;
            
            WritePrivateProfileString("URL", "GameName", newname.c_str(), "Config\\DefaultEngine.ini");
            bool res3 = RemoveDir("Binaries");
            remove((temp + ".sln").c_str());
            if (res == 0)
            {
                cout << "Rename success!!!" << endl;
            }
            else
            {
                cout << "rename fail!!!" << endl;
            }
        }
        else
        {
            return 0;
        }

    }
    else
    {
        cout << "can't find uproject file!!!" << endl;
        cout << "put this program in ur project path!!!" << endl;
    }



    _findclose(HANDLE);
    _findclose(HANDLE1);
    system("pause");
    return 0;
}