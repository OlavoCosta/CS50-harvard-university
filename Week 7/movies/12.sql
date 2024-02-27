SELECT title FROM movies WHERE id in (SELECT id FROM movies JOIN stars ON movies.id = stars.movie_id WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp') INTERSECT
SELECT id FROM movies JOIN stars ON movies.id = stars.movie_id WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter'));

