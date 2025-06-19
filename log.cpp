#include "log.h"
#include <iostream>
#include<ctime>

using namespace std;

void log::showLog(Repository &repo) {
  Commit* current = repo.getHead();
  if(!current) {
    cout<<"No commits found yet" <<endl;
    return;
  }
  while(current) {
    cout<<"COMMIT: "<<current->hash<<endl;
    cout<<"MADE BY: "<<current->madeby<<endl;
    cout<<"DATE: "<<ctime(&current->timestamp);
    cout<<"MESSAGE: "<<current->message<<endl;
    cout<<"FILES: "<<current->blobHashes.size()<<"\n\n";
    current=current->parent;
  }
}
