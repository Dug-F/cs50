SELECT DISTINCT(people.name) FROM people, stars, movies
WHERE stars.movie_id = movies.id
AND people.id = stars.person_id
AND movies.year = 2004
ORDER BY birth;