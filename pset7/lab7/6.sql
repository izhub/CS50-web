-- write a SQL query that lists the names of songs that are by Post Malone

SELECT songs.name FROM songs
INNER JOIN artists ON artist_id  = artists.id
where artists.name = "Post Malone";
