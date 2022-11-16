SELECT movies.title from movies
WHERE id IN (
SELECT movie_id FROM people, stars WHERE name = 'Johnny Depp' AND stars.person_id = people.id
INTERSECT
SELECT movie_id FROM people, stars WHERE name = 'Helena Bonham Carter' AND stars.person_id = people.id
);