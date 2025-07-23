-- write a SQL query to list the names of all people who starred in a movie released in 2004,
--  ordered by birth year
-- People with the same birth year may be listed in any order.
-- No need to worry about people who have no birth year listed, so long as those who do have a birth year
--  are listed in order.
-- If a person appeared in more than one movie in 2004, they should only appear in your results once.

SELECT DISTINCT(people.name) FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies on movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth;
