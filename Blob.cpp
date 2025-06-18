#include "Blob.h"
#include<sstream>
#include <iomanip>
#include<fstream>
#include <functional>

//================Convert byte to hex string===================
string to_hex(const unsigned char* hash, size_t length ){
  stringstream ss;
  for(size_t i=0;i<length; i++) {
    ss <<hex<< setw(2) <<setfill('0') <<(int)hash[i];
  }
  return ss.str();
}
 //========COMPUTING THE HASH===============================
  string customHash(const string& content) {
   hash<string> hasher;
  return to_string(hasher(content));
  }


