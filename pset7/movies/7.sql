select m.title, r.rating from movies m, ratings r where m.id = r.movie_id and m.year = 2010 order by r.rating desc, m.title asc;