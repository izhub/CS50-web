-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select
--   the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.



-- SELECT name FROM people
-- WHERE id IN (
--     SELECT DISTINCT person_id FROM stars
--     WHERE movie_id IN (
--         SELECT movie_id FROM stars
--         JOIN people ON people.id = stars.person_id
--         WHERE people.name = "Kevin Bacon" AND people.birth = 1958))
-- AND NOT (name = "Kevin Bacon" AND birth = 1958);

SELECT name FROM people
WHERE id IN (
    SELECT DISTINCT person_id FROM stars
    WHERE movie_id IN (
        SELECT movie_id FROM stars
        WHERE person_id in (
        select id from people where name = "Kevin Bacon" AND people.birth = 1958)))
AND NOT (name = "Kevin Bacon" AND birth = 1958);

