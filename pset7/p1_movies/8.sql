-- write a SQL query to list the names of all people who starred in Toy Story.

SELECT name FROM people 
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON movies.id = stars.movie_id
WHERE movies.title = "Toy Story";
