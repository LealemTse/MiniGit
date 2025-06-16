#include <iostream>
#include <string>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>  
#include <sys/types.h>
#endif





void createDirectory(const string& path) {

#ifdef _WIN32           //for windows
    CreateDirectoryA(path.c_str(),NULL);

    if(!CreateDirectoryA(path.c_str(),NULL)){
            if(GetLastError() !=ERROR_ALREADY_EXISTS){
                cout<<"The directory "<<path<<" cannot created"<<endl;
                return;
            }
    }
    SetFileAttributesA(path.c_str(),FILE_ATTRIBUTE_HIDDEN);
        
#else
    if(mkdir(path.c_str(),0755)!=0 && errno !=EEXIST){
        cout<<"Couldn't make "<<path<<endl;

    }
#endif
    cout<<"Directory "<<path<<" was created! "<<endl;  

}
int main() {
    string parentDir = ".minigit";  

    createDirectory(parentDir);
    

    string subDirs[] = {
        parentDir + "/objects",
        parentDir + "/refs",
        parentDir + "/refs/heads"
    };
   
    for (const auto& dir : subDirs) {
        createDirectory(dir);
            
    }
    cout << "Directory tree created successfully!" << endl;
    return 0;
}