#include "Repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

//    ===========Constructor: loads an existing MiniGit repository===========
    Repository::Repository(const string& path, bool force) {
        worktree = path;
        gitdir = path + "/.minigit";

        // If not in force mode, ensure the .minigit folder exists
        if (!force && !fs::is_directory(gitdir)) {
            throw runtime_error("Not a MiniGit repository: " + path);
        }

        string configPath = repoFile("config");
        if (fs::exists(configPath)) {
            loadConfig(configPath);
        } else if (!force) {
            throw runtime_error("Configuration file missing");
        }

        // If not in force mode, verify version from config
        if (!force) {
            int version = stoi(config["core.repositoryformatversion"]);
            if (version != 0) {
                throw runtime_error("Unsupported repositoryformatversion: " + to_string(version));
            }
        }
    }
//==================CREATEING THE .minigit REPO======================
void Repository::init() {
        if(fs::exists(gitdir)){
            throw runtime_error(".minigit already exists");
        }
        fs::create_directory(gitdir);
        fs::create_directory(repoFile("objects"));
        fs::create_directory(repoFile("refs"));

        //WRITEING HEAD
        ofstream headFile(repoFile("HEAD"));
        if(headFile) {
            headFile<<"ref: ref/head/main"<<endl;
            headFile.close();
        }
        //WRITE CONFIG
        ofstream configFile(repoFile("config"));
        if(configFile) {
            configFile<<"[core]"<<endl;
            configFile<<"repsitoryformatversion=0"<<endl;
            configFile.close();
        }
        cout<<"Initialization Empty MiniGit Repository in"<<gitdir<<endl;
    }

//==================RESOLVING FILE PATHE IN .minigit/======================
    string Repository::repoFile(const string& relativePath) {
        return gitdir + "/" + relativePath;
    }

    // Load INI-style config file into key-value map
    void Repository::loadConfig(const string& configPath) {
        ifstream file(configPath);
        if (!file) throw runtime_error("Could not open config file");

        string line, section;
        while (getline(file, line)) {
            // Remove comments
            auto comment = line.find('#');
            if (comment != string::npos)
                line = line.substr(0, comment);

            // Trim whitespace
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty()) continue;

            // Handle section headers like [core]
            if (line.front() == '[' && line.back() == ']') {
                section = line.substr(1, line.size() - 2);
            } else {
                // Parse key=value
                auto pos = line.find('=');
                if (pos == string::npos) continue;

                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                // Trim whitespace around key and value
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                // Store in format "core.repositoryformatversion"
                config[section + "." + key] = value;
            }
        }
    }


