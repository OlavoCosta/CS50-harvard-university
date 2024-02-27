-- Taking into account that we should not make assumptions about Post Malone's artist_id,
-- a table with a single column for the name of each of the artist's songs was generated.
-- By selecting the name column in the songs table where artist_id gets the id selected in the artistis table, we find the name 'Post Malone'.
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');
