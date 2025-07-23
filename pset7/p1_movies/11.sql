--  write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in,
--   starting with the highest rated

SELECT movies.title FROM movies 
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating  DESC
LIMIT 5;

select movies.title from movies
join ratings on ratings.movie_id = movies.id
where movies.id in 
(select movies.id from stars where person_id = 
(select id from people where name = 'Chadwick Boseman'))
order by ratings.rating desc
limit 5;