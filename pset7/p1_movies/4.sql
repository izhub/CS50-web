-- write a SQL query to determine the number of movies with an IMDb rating of 10.0

SELECT COUNT(movies.title) FROM movies
INNER JOIN ratings ON ratings.movie_id = movies.id
WHERE ratings.rating = 10.0;
