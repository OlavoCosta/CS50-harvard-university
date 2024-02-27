-- The LIKE operator is used in a WHERE clause to search for a specified pattern in a column.
-- Generating a table with only one column, displaying all the songs that are by other artists.
SELECT name FROM songs WHERE name LIKE '%feat.%';