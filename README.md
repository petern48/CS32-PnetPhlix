# CS32-PnetPhlix

### Video URL: https://youtu.be/sEP26hj2rCw

For this class project, I designed my own TreeMultiMap class and used it to implement Movie Database and User Database classes.
These were used by the Recommender class, which can be used to calculate movie recommendations for a particular given user based on the user's watch history.
The project was inspired by Netflix's movie recommendation system.

### MovieDatabase and ClassDatabase
These classes read files of data, create and stores Movie and User classes, 
and uses the TreeMultiMap class to efficiently sort for objects based on a variety of criteria (e.g search for movies using ID, actors, genre, etc)

### Recommender
This class uses the MovieDatabase and UserDatabase class to assign point values to each movie based on the user's watch history.
Then it can be used to return the top recommendations based on similar movies are to the movies in the user's watch history.
