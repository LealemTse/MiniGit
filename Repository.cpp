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
    unordered_map<string, string> config;

    Repository(const string& path, bool force = false) {
        worktree = path;
        gitdir = path + "/.minigit";

        if (!force && !fs::is_directory(gitdir)) {
            throw runtime_error("Not a MiniGit repository: " + path);
        }

        string configPath = repo_file("config");
        if (!force && !fs::exists(configPath)) {
            throw runtime_error("Configuration file missing.");
        }

        if (fs::exists(configPath)) {
            loadConfig(configPath);
        }

        if (!force) {
            int version = stoi(config["core.repositoryformatversion"]);
            if (version != 0) {
                throw runtime_error("Unsupported repositoryformatversion: " + to_string(version));
            }
        }
    }

    string repo_file(const string& relativePath) {
        return gitdir + "/" + relativePath;
    }

    void loadConfig(const string& configPath) {
        ifstream file(configPath);
        string line, section;

        while (getline(file, line)) {
            // Remove comments and trim whitespace
            size_t comment = line.find('#');
            if (comment != string::npos) line = line.substr(0, comment);
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty()) continue;

            if (line.front() == '[' && line.back() == ']') {
                section = line.substr(1, line.size() - 2);
            } else {
                size_t equals = line.find('=');
                if (equals == string::npos) continue;

                string key = line.substr(0, equals);
                string value = line.substr(equals + 1);

                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                config[section + "." + key] = value;
            }
        }
    }
};
