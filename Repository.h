#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
using namespace std;

class Commit {
public:
  string hash;
  string message;
  string madeby;
  time_t timestamp;
  vector<std::string> blobHashes;
  Commit* parent;


  Commit(string msg, string a, Commit* p = nullptr);
  void generateHash();
};
string customHash(const string& filecontent);

class Repository {
private:
  string gitDir;
  string objectsDir;
  unordered_map<string, string> blob;
  unordered_map<string, string> config;
  Commit* head = nullptr;

  void initRepo();
  void createDirectory(const string& path);
  void loadConfig(const string& configPath);
  void saveIndex();
  void loadIndex();
  void clearIndex();

public:
  Repository(string dir = ".minigit", bool force =false);
  ~Repository();
  void init();
  std::string createBlob(const string& content);
  void commit(const string& message, const std::string& madeby);
  std::string getBlob(const string& hash);
  void addFile(const string& filepath);
  Commit* getHead() const {return head;}
};

#endif
