SELECT people.name FROM movies, stars, people
WHERE stars.movie_id = movies.id
AND people.id = stars.person_id
AND movies.title = 'Toy Story';
