# baselinePrediction

The directory should have all.dta, all.idx, and qual.dta before running
After compiling all the .cc files (or should I put the compiled versions in the repo?)...
1. Run dataProcessing. This sorts all.dta and creates base.dta, valid.dta, hidden.dta, and probe.dta.
2. Run averageBaseMovieRatings. This calclates the average rating (using "BetterMean") of every movie using base.dta and stores in movieAverageRatings.dta.
3. Run averageUserOffset. This calculates the average offset for each user from the average movie rating for each movie the user rated in base.dta. Average offsets are stored in userAverageOffsets.dta.
4. Run Main. This tests the baseline prediction on probe.dta and qual.dta. It outputs the RMSE for probe.dta to the command window. It stores the predictions for qual.dta in qualPredictions.dta.
