SELECT songs.name FROM songs, artists
WHERE songs.artist_id = artists.id
AND songs.name LIKE '%feat.%';