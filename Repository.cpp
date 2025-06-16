#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Repository {
public:
    string worktree;
    string gitdir;
    unorderd_map<string, string> config;

    Repository(const string& path, bool force=false) {
        worktree = path;
        gitdir = path+"/.minigti";

        if(!force && !fs::is_directory(gitdir)) {
            throw runtime_error("Not a MiniGit repository: "+ path);
        }

        string configPath = repoFile("config");
        if(fs::exists(configPath)) {
            loadConfig(configPath);
        }else if(!force) {
            throw runtime_error("Configuration FIle Missing");
        }
        if(!force) {
            //stoi converst a string in to int.
            int version = stoi(config["core.repositoryformatversion"]);
            if(version!=0) {
                throw runtime_error("Unsupported repositoryformatversion: "+ to_string(version));
            }
        }
    }

    string repoFile(const string& relativePath) {
        return gitdir + "/" + relativePath;
    }
    void loadConfig(const string& configPath) {
        ifstream file(configPath);
        if(!file) throw runtime_error("Could not open config file");

        string line, section;
        while(getline(file,line)) {
            auto comment = line.find('#');
            if(comment != string::npos) line=line.substr(0,comment);

            line.erase(0,line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n")+1);

            if(line.empty()) continue;

            if(line.front()=='[' && line.back()==']') {
                section=line.substr(1,line.size()-2);
            } else {
                auto pos = line.find('=');
                if(pos==string::npos) continue;

                string key = line.substr(0,pos);
                string value= line.substr(pos+1);

                key.erase(0,key.find_first_not_of(" \t"));
                key.erase(0,key.find_last_not_of(" \t"));
                value.erase(0,value.find_first_not_of(" \t"));
                value.erase(0,value.find_last_not_of(" \t"));

                config[section+"."+key]=value
            }
        }
    }
};

int main() {
    try {
        GitRepository repo(".", false);
        cout << "MiniGit repository loaded successfully!\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
}