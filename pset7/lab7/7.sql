-- write a SQL query that returns the average energy of songs that are by Drake


SELECT AVG(songs.energy) FROM songs
INNER JOIN artists ON artist_id  = artists.id
where artists.name = "Drake";
