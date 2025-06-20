#include "log.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void log::showLog() {
    ifstream logFile(".minigit/log.txt");
    if (!logFile) {
        cout << "No commits found. Please commit something first." << endl;
        return;
    }

    string hash, madeby, timestampStr, message, line;
    while (getline(logFile, hash)) {
        getline(logFile, madeby);
        getline(logFile, timestampStr);
        getline(logFile, message);
        getline(logFile, line); // should be "---"

        time_t ts = stol(timestampStr);

        cout << "COMMIT:  " << hash << endl;
        cout << "MADE BY: " << madeby << endl;
        cout << "DATE:    " << ctime(&ts);
        cout << "MESSAGE: " << message << "\n" << endl;
    }
}
