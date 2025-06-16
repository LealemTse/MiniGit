// does not handle conflict yet

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> readFile(const string &path)
{
    ifstream file(path);
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

void mergeFiles(const string &base, const string &branch1, const string &branch2)
{
    string basePath = ".minigit/objects/" + base;
    string branch1Path = ".minigit/objects/" + branch1;
    string branch2Path = ".minigit/objects/" + branch2;

    vector<string> baseLines = readFile(basePath);
    vector<string> branch1Lines = readFile(branch1Path);
    vector<string> branch2Lines = readFile(branch2Path);

    size_t maxSize = max(base.size(), max(branch1.size(), branch2.size()));

    vector<string> result;

    for (size_t i = 0; i < maxSize; ++i)
    {
        if (base[i] == branch1[i] && base[i] == branch2[i])
        {
            result.push_back(branch1[i]);
        }

        else if (branch1[i] == branch2[i])
        {
            result.push_back(branch1[i]);
        }

        else if (base[i] == branch1[i])
        {
            result.push_back(branch2[i]);
        }

        else if (base[i] == branch2[i])
        {
            result.push_back(branch1[i]);
        }
    }


    string mergedFile = ".minigit/merged.txt";
    ofstream out(mergedFile);
    for (size_t i = 0; i<result.size(); i++)
    {
        out << result[i] << endl;
    }
}