#define _NO_CPP_STD_BYTE 1
#include "Repository.h"
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <cerrno>
#endif

using namespace std;
namespace fs = std::filesystem;

//==========Hashing function===========================
string customHash(const string& filecontent) {
    unsigned int hash = 0;
    for (char c : filecontent) {
        hash = (hash * 32) + hash + c;
    }
    char hex[9];
    snprintf(hex, 9, "%08x", hash);
    return string(hex);
}

//=======================Commit===============================
Commit::Commit(string msg, string a, Commit* p)
    : message(msg), madeby(a), parent(p), timestamp(time(nullptr)) {}

void Commit::generateHash() {
    string data = message + madeby + to_string(timestamp);
    for (const auto& bh : blobHashes) data += bh;
    if (parent) data += parent->hash;
    hash = customHash(data);
}
//====================Creating the minigit repository=============================
Repository::Repository(string dir, bool force) : gitDir(dir), objectsDir(dir + "/objects") {
    if (!force && !fs::is_directory(gitDir)) {
        throw runtime_error("Not a MiniGit repository: " + dir);
    }

    string configPath = gitDir + "/config";
    if (fs::exists(configPath)) {
        loadConfig(configPath);
        loadIndex();
    } else if (!force) {
        throw runtime_error("Configuration file missing");
    }

    if (!force) {
        if (config.find("core.repositoryformatversion") == config.end()) {
            throw runtime_error("Missing 'core.repositoryformatversion' in config file");
        }
        int version = stoi(config["core.repositoryformatversion"]);
        if (version != 0) {
            throw runtime_error("Unsupported repositoryformatversion: " + to_string(version));
        }
    }
}


Repository::~Repository() {
    while (head) {
        Commit* temp = head;
        head = head->parent;
        delete temp;
    }
}
//========================minigit.init=========================================
void Repository::init() {
    initRepo();
}

void Repository::initRepo() {
    if (fs::exists(gitDir)) {
        throw runtime_error("ERROR: .minigit already exists");
    }

    createDirectory(gitDir);
    createDirectory(objectsDir);
    createDirectory(gitDir + "/refs");
    createDirectory(gitDir + "/refs/heads");

    ofstream headFile(gitDir + "/HEAD");
    headFile << "ref: refs/heads/main\n";
    headFile.close();

    ofstream configFile(gitDir + "/config");
    configFile << "[core]\n";
    configFile << "repositoryformatversion = 0\n";
    configFile.close();

    cout << "Initialized empty MiniGit repository in " << gitDir << endl;
}

void Repository::createDirectory(const string& path) {
#ifdef _WIN32
    if (!CreateDirectoryA(path.c_str(), NULL)) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            cout << "The directory " << path << " cannot be created" << endl;
        }
    }
    SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_HIDDEN);
#else
    if (mkdir(path.c_str(), 0755) != 0 && errno != EEXIST) {
        cout << "Couldn't make " << path << endl;
    }
#endif
}



void Repository::loadConfig(const string& path) {
    ifstream file(path);
    string line, section;

    while (getline(file, line)) {
        auto comment = line.find('#');
        if (comment != string::npos) line = line.substr(0, comment);

        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty()) continue;

        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
        } else {
            auto pos = line.find('=');
            if (pos == string::npos) continue;
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            config[section + "." + key] = value;
        }
    }
}

//===================Blob===============================
string Repository::createBlob(const string& content) {
    string header = "blob " + to_string(content.size()) + '\0';
    string fullContent = header + content;
    string hash = customHash(fullContent);
    blob[hash] = content;

    ofstream file(objectsDir + "/" + hash);
    if (file) file << content;
    return hash;
}
//Save Index()
void Repository::saveIndex() {
    ofstream indexFile(gitDir+"/index");
    for(const auto& [hash, content]: blob) {
        indexFile << hash << endl;
    }
}
void Repository::clearIndex() {
    ofstream indexFile(gitDir + "/index", ios::trunc);  // empties file
}


//=============minigit add======================
void Repository::addFile(const string& filepath) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        cerr << "ERROR: Cannot open file: " << filepath << endl;
        return;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    string hash = createBlob(content);
    cout << "Added file: " << filepath << " as blob " << hash << endl;
    saveIndex();
}
void Repository::loadIndex() {
    ifstream indexFile(gitDir + "/index");
    string hash;

    while (getline(indexFile, hash)) {
        string path = objectsDir + "/" + hash;
        ifstream blobFile(path);
        stringstream buffer;
        buffer << blobFile.rdbuf();
        blob[hash] = buffer.str();
    }
}

void Repository::commit(const string& message, const string& madeby) {
    if (blob.empty()) {
        cout << "No files added to commit!" << endl;
        return;
    }

    Commit* newCommit = new Commit(message, madeby, head);
    for (const auto& [hash, _] : blob) {
        newCommit->blobHashes.push_back(hash);
    }
    newCommit->generateHash();
    head = newCommit;

    cout << "Created commit: " << newCommit->hash.substr(0, 8) << "\n"
         << "Date:   " << ctime(&newCommit->timestamp)
         << "Files:  " << newCommit->blobHashes.size() << endl;

    ofstream logFile(gitDir + "/log.txt", ios::app);
        if(logFile) {
            logFile<<newCommit->hash<<"\n";
            logFile<<newCommit->madeby<<"\n";
            logFile<<newCommit->timestamp<<"\n";
            logFile<<newCommit->message<<"\n";
            logFile<<"---\n";
            logFile.close();
        }
    clearIndex();
}

string Repository::getBlob(const string& hash) {
    if (blob.count(hash)) return blob[hash];
    cout << "Blob not found";
    return "";
}
