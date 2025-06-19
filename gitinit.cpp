#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>  
#include <sys/types.h>
#endif

//customHash
string customHash(const string& filecontent ){
    unsigned int hash=0;

    for(char c: filecontent){
        hash=(hash * 32) + hash + c;
    }
    char hex[9];
    snprintf(hex,9,"%08x",hash);
    return string(hex);

}

class Minigit{
private:
    string gitDir;
    string objectsDir;
    unordered_map <string,string> blob;

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

public:
    Minigit(string gitDir1){
        gitDir=gitDir1;
        objectsDir=gitDir +"/objects";

        createDirectory(gitDir);
        createDirectory(objectsDir);
        createDirectory(gitDir +"/refs");
        createDirectory(gitDir +"/refs/heads");
    }
    string createBlob(const string& content){
        string header="blob " + to_string(content.size())+'\0';
        string fileContent=header + content;
        string hash=customHash(fileContent);
        blob[hash]=content;
        return hash;
    }

    string getBlob(const string& hash){
        if(blob.count(hash)){
            return blob[hash];
        }
        cout<<"Blob not found";
    }

};


int main() {
    Minigit minigit(".minigit");

    string example=minigit.createBlob("Hello!");
    cout<<"example hashed: "<<example<<endl;
    cout<<"example originally "<<minigit.getBlob(example)<<endl;

    return 0;
    
}
    
   
