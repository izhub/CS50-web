-- write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating.
-- For movies with the same rating, order them alphabetically by title.
-- Movies that do not have ratings should not be included in the result.

SELECT ratings.rating,movies.title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title;
