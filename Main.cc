// -*- C++ -*-

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
  
  int numberOfUsers = 458293;
  int numberOfMovies = 17770;

  ifstream userOffsetFile("userAverageOffsets.dta");
  ifstream movieRatingFile("movieAverageRatings.dta");

  int user;
  int movie;
  int time;
  int rating;
  double offset;
  double averageRating;
  vector<double> userOffsets(numberOfUsers);
  vector<double> movieRatings(numberOfMovies);


  // import and store all the averaged data
  user = 0;
  while (userOffsetFile >> offset){
    userOffsets[user] = offset;
    user = user+1;
  }

  movie = 0;
  while (movieRatingFile >> averageRating){
    movieRatings[movie] = averageRating;
    movie = movie+1;
  }

  userOffsetFile.close();
  movieRatingFile.close();

  // import the probe data
  vector<int> probeUsers;
  vector<int> probeMovies;
  vector<int> probeTimes;
  vector<int> probeRatings; 
  ifstream probeDataFile("probe.dta");
  while (probeDataFile >> user >> movie >> time >> rating){
    probeUsers.push_back(user);
    probeMovies.push_back(movie);
    probeTimes.push_back(time);
    probeRatings.push_back(rating);
  }
  probeDataFile.close();

  // make probe predictions and calculate rmse
  int numberOfProbeRatings = 1374739;
  double sError = 0;
  for (int probeIndex=0; probeIndex<numberOfProbeRatings; probeIndex++){
    user = probeUsers[probeIndex]-1;
    movie = probeMovies[probeIndex]-1;
    rating = probeRatings[probeIndex];
    double prediction = movieRatings[movie]+userOffsets[user];
    sError = sError + pow(prediction-double(rating),2);
  }
  double rmsError = pow(sError/double(numberOfProbeRatings),0.5);
  
  cout << "probe rmsError = " << rmsError << endl;

  // import the qual data
  vector<int> qualUsers;
  vector<int> qualMovies;
  vector<int> qualTimes;
  ifstream qualDataFile("qual.dta");
  while (qualDataFile >> user >> movie >> time){
    qualUsers.push_back(user);
    qualMovies.push_back(movie);
    qualTimes.push_back(time);
  }
  qualDataFile.close();

  // make qual predictions and write to .dta file
  ofstream qualPredictionsFile;
  qualPredictionsFile.open("qualPredictions.dta");
  int numberOfQualRatings = 2749898;
  for (int qualIndex=0; qualIndex<numberOfQualRatings; qualIndex++){
    user = qualUsers[qualIndex]-1;
    movie = qualMovies[qualIndex]-1;
    double prediction = movieRatings[movie]+userOffsets[user];
    qualPredictionsFile << fixed << setprecision(3) << prediction << endl;
  }
  qualPredictionsFile.close();
  
  return 0;
}










