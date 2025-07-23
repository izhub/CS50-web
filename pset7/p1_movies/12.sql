-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred


-- SELECT title FROM movies
-- WHERE id IN (
--     SELECT  movie_id FROM stars
--     JOIN people ON people.id = stars.person_id
--     WHERE name = "Helena Bonham Carter" AND movie_id IN
--         (SELECT movie_id FROM stars
--          WHERE person_id IN
--           (SELECT id FROM people
--           WHERE name = "Johnny Depp")))
-- ORDER BY title;

SELECT title FROM movies
WHERE movies.id in (
    SELECT movie_id FROM stars
    WHERE person_id =
        (SELECT id FROM people
        WHERE name = "Johnny Depp"))
and movies.id in (
    SELECT movie_id FROM stars
    WHERE person_id =
        (SELECT id FROM people
        WHERE name = "Helena Bonham Carter"));

