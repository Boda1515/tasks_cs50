-- In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT title
FROM movies
JOIN stars AS s1 ON s1.movie_id = movies.id
JOIN people AS p1 ON p1.id = s1.person_id
JOIN stars AS s2 ON s2.movie_id = movies.id
JOIN people AS p2 ON p2.id = s2.person_id
WHERE p1.name = "Bradley Cooper" AND p2.name = "Jennifer Lawrence";
