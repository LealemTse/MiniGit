#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <ctime>

#include "Repository.h"
#include "log.h"
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

class Commit{
public:
    string hash;
    string message;
    string madeby;
    time_t timestamp;
    vector<string>blobHashes;
    Commit* parent;

    Commit(string msg,string a,Commit* p=nullptr)
        :message(msg),madeby(a),parent(p),timestamp(time(nullptr)){}
    

    void generateHash(){
        string data= message + madeby +to_string(timestamp);
        for(const auto& bh:blobHashes){
            data+=bh;
        }
        if(parent){
            data+= parent->hash;
        }
        hash=customHash(data);
    
    }

};

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
        //cout<<"Directory "<<path<<" was created! "<<endl;  

    }

class Minigit{
    string gitDir;
    string objectsDir;
    unordered_map<string, string> blob;
    Commit* head = nullptr;

    void initRepo(){
        createDirectory(gitDir);
        createDirectory(objectsDir);
        createDirectory(gitDir +"/refs");
        createDirectory(gitDir +"/refs/heads");
        
        commit("Initial commit","System");
        cout<<"Initialized empty MiniGit repository in ./"<<gitDir<<endl;
    }
    
public:
    Minigit(string dir):gitDir(dir),objectsDir(dir+"/objects"){};
    
    ~Minigit(){
        while(head){
            Commit* temp=head;
            head=head->parent;
            delete temp;
        }
    }
    void init(){
        initRepo();
    }
    
    string createBlob(const string& content){
        string header="blob " + to_string(content.size())+'\0';
        string fileContent=header + content;
        string hash=customHash(fileContent);
        blob[hash]=content;

        ofstream blobFile(objectsDir + "/" + hash);
        if(blobFile){
            blobFile<<content;
        }
        return hash;
    }

    void commit(const string& message,const string& madeby){
        if (blob.empty()) {
        cout << "No files added to commit!"<<endl;
        return;
        }

        Commit* newCommit= new Commit(message,madeby,head);
        for(const auto& pair:blob){
            newCommit->blobHashes.push_back(pair.first);
        }
        newCommit->generateHash();
        head=newCommit;
        cout<<"Created commit: "<<newCommit->hash.substr(0,8)<<"\n"
            << "Date:   " << ctime(&newCommit->timestamp) 
            << "Files:  " << newCommit->blobHashes.size() << endl;
        
    }

    string getBlob(const string& hash){
        if(blob.count(hash)){
            return blob[hash];
        }
        cout<<"Blob not found";
    }

};

int main(int argc,char* argv[]) {
    if(argc<2){
        cout<<"Usage: "<<argv[0]<<"<command>[options]"<<endl;
        cout<<"Commands: init,commit -m <message>"<<endl;
        return 1;
    }
    string command=argv[1];
    Minigit minigit(".minigit");
    if(command=="init"){
        minigit.init();
    }else if (command == "add") {
        if (argc < 3) {
            cerr << "Usage: minigit add <file>" << endl;
            return 1;
        }
        Repository repo;
        repo.addFile(argv[2]);
    }
    else if(command=="commit"){
        if(argc<4 || string(argv[2]) !="-m"){
            cout<<"Usage: "<<argv[0]<<"commit -m \"<message>\"" << endl;
            return 1;
        }
        string message=argv[3];
        minigit.commit(message,"User");
    }
    else if(command =="log") {
        Repository repo;
        log::showLog(repo);
    }
    else{
        if (fs::exists(".minigit")) {
            cout << "MiniGit Repository Loaded Successfully" << endl;
        } else {
            cerr << "ERROR: No MiniGit repository found. Run 'minigit init' first." << endl;
        }
    }

    return 0; 
}

    
   
