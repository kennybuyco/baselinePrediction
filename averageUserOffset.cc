// -*- C++ -*-

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

  ifstream dataFile("base.dta");
  ifstream movieAverageFile("movieAverageRatings.dta");

  int index;
  int user;
  int movie;
  int time;
  int rating;
  vector<int> users;
  vector<int> movies;
  vector<int> ratings;

  int numberOfMovies = 17770;
  int numberOfUsers = 458293;

  // import and store all the data, then compute global average
  int numberOfGlobalRatings = 0;
  int sumOfGlobalRatings = 0;
  while (dataFile >> user >> movie >> time >> rating){
    users.push_back(user);
    movies.push_back(movie);
    ratings.push_back(rating);
    numberOfGlobalRatings = numberOfGlobalRatings+1;
    sumOfGlobalRatings = sumOfGlobalRatings+rating;
  }

  vector<double> movieAverageRatings;
  double movieAverageRating;
  while (movieAverageFile >> movieAverageRating){
    movieAverageRatings.push_back(movieAverageRating);
  }

  vector<int> userNumberOfRatings(numberOfUsers);
  vector<double> userOffsetSum(numberOfUsers);
  vector<double> userAverageOffset(numberOfUsers);

  //  calculate average "base set" rating for each user
  for (int dataIndex=0; dataIndex<numberOfGlobalRatings; dataIndex++){
    user = users[dataIndex]-1;
    movie = movies[dataIndex]-1;
    rating = ratings[dataIndex];
    userNumberOfRatings[user] = userNumberOfRatings[user]+1;
    userOffsetSum[user] = userOffsetSum[user]+double(rating)-movieAverageRatings[movie];
  }
  
  ofstream userAverageOffsetsFile;
  userAverageOffsetsFile.open("userAverageOffsets.dta");
  for (int userIndex=0; userIndex<numberOfUsers; userIndex++){
    userAverageOffset[userIndex] = userOffsetSum[userIndex]/double(userNumberOfRatings[userIndex]);
    userAverageOffsetsFile << userAverageOffset[userIndex] << endl;
  } 
  userAverageOffsetsFile.close();


  return 0;
}










