#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Repository {
public:
    string worktree;
    string gitdir;
    unorded_map<string, string> config;

    Repository(const string& path, bool force=false) {
        worktree = path;

    }
};