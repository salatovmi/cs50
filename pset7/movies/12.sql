select title from movies where id in
(select distinct jd.movie_id from stars jd
join stars hbc
on
jd.movie_id = hbc.movie_id
where jd.movie_id in
(select movie_id from stars where person_id in
(select id from people where name = 'Johnny Depp'))
and hbc.movie_id in
(select movie_id from stars where person_id in
(select id from people where name = 'Helena Bonham Carter')));