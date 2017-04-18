// -*- C++ -*-

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {

  ifstream indexFile("all.idx");
  ifstream dataFile("all.dta");

  int index;
  int user;
  int movie;
  int time;
  int rating;
  vector<int> users;
  vector<int> movies;
  vector<int> times;
  vector<int> ratings;
  vector<int> indices;
  vector<int> baseEntries;
  vector<int> validEntries;
  vector<int> hiddenEntries;
  vector<int> probeEntries;

  // import and store all the data
  int entry = 0;
  while (indexFile >> index){
    dataFile >> user >> movie >> time >> rating;
    users.push_back(user);
    movies.push_back(movie);
    times.push_back(time);
    ratings.push_back(rating);
    indices.push_back(index);
    if (index == 1){
      baseEntries.push_back(entry);
    }
    if (index == 2){
      validEntries.push_back(entry);
    }
    if (index == 3){
      hiddenEntries.push_back(entry);
    }
    if (index == 4){
      probeEntries.push_back(entry);
    }
    entry = entry+1;
  }
  indexFile.close();
  dataFile.close();

  ofstream baseFile;
  baseFile.open("base.dta");
  for (int baseIndex=0; baseIndex<baseEntries.size(); baseIndex++){
    int baseEntry = baseEntries[baseIndex];
    baseFile << users[baseEntry] << " " << movies[baseEntry] << " " << times[baseEntry] << " " << ratings[baseEntry] << endl;
  }
  baseFile.close();

  ofstream validFile;
  validFile.open("valid.dta");
  for (int validIndex=0; validIndex<validEntries.size(); validIndex++){
    int validEntry = validEntries[validIndex];
    validFile << users[validEntry] << " " <<  movies[validEntry] << " " << times[validEntry] << " " << ratings[validEntry] << endl;
  }
  validFile.close();

  ofstream hiddenFile;
  hiddenFile.open("hidden.dta");
  for (int hiddenIndex=0; hiddenIndex<hiddenEntries.size(); hiddenIndex++){
    int hiddenEntry = hiddenEntries[hiddenIndex];
    hiddenFile << users[hiddenEntry] << " " << movies[hiddenEntry] << " " << times[hiddenEntry] << " " << ratings[hiddenEntry] << endl;
  }
  hiddenFile.close();

  ofstream probeFile;
  probeFile.open("probe.dta");
  for (int probeIndex=0; probeIndex<probeEntries.size(); probeIndex++){
    int probeEntry = probeEntries[probeIndex];
    probeFile << users[probeEntry] << " " << movies[probeEntry] << " " << times[probeEntry] << " " << ratings[probeEntry] << endl;
  }
  probeFile.close();

  return 0;
}










