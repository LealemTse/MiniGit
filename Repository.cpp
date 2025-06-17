#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Represents a MiniGit repository by loading config and checking validity
class Repository {
public:
    string worktree;                       // Path to working directory
    string gitdir;                         // Path to .minigit/ folder
    unordered_map<string, string> config;  // Configuration key-values

    // Constructor: loads an existing MiniGit repository
    Repository(const string& path, bool force = false) {
        worktree = path;
        gitdir = path + "/.minigit"; // <-- fixed typo here

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

    // Resolve full path to a file in .minigit/
    string repoFile(const string& relativePath) {
        return gitdir + "/" + relativePath;
    }

    // Load INI-style config file into key-value map
    void loadConfig(const string& configPath) {
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
};

// Entry point
int main() {
    try {
        Repository repo(".", false); // Will look for .minigit/config
        cout << "MiniGit repository loaded successfully!\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
