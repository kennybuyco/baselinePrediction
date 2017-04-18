// -*- C++ -*-

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

  ifstream dataFile("base.dta");

  int index;
  int user;
  int movie;
  int time;
  int rating;
  vector<int> movies;
  vector<int> ratings;

  int numberOfMovies = 17770;

  // import and store all the data, then compute global average
  int numberOfGlobalRatings = 0;
  int sumOfGlobalRatings = 0;
  while (dataFile >> user >> movie >> time >> rating){
    movies.push_back(movie);
    ratings.push_back(rating);
    numberOfGlobalRatings = numberOfGlobalRatings+1;
    sumOfGlobalRatings = sumOfGlobalRatings+rating;
  }
  double globalAverage = double(sumOfGlobalRatings)/double(numberOfGlobalRatings);

  vector<int> movieNumberOfRatings(numberOfMovies);
  vector<int> movieRatingSum(numberOfMovies);
  vector<double> movieAverage(numberOfMovies);

  //  calculate average "base set" rating for each user
  for (int dataIndex=0; dataIndex<numberOfGlobalRatings; dataIndex++){
    movie = movies[dataIndex]-1;
    rating = ratings[dataIndex];
    movieNumberOfRatings[movie] = movieNumberOfRatings[movie]+1;
    movieRatingSum[movie] = movieRatingSum[movie]+rating;
  }

  ofstream movieAveragesFile;
  movieAveragesFile.open("movieAverageRatings.dta");
  double K = 25.;
  for (int movieIndex=0; movieIndex<numberOfMovies; movieIndex++){
    movieAverage[movieIndex] = (globalAverage*K+double(movieRatingSum[movieIndex]))/(K+double(movieNumberOfRatings[movieIndex]));
    movieAveragesFile << movieAverage[movieIndex] << endl;
  } 
  movieAveragesFile.close();

  return 0;
}










