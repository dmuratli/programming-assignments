film_quota_genre=input("Please enter movie names and remaining quota: ")
modified_input=film_quota_genre.replace(",", ":")
pristine_list=modified_input.split(":")
film_names=pristine_list[0::3]
film_quotas=pristine_list[1::3]
film_genres=pristine_list[2::3]
for a in range(len(film_quotas)):
   if isinstance(film_quotas[a], str):
      film_quotas[a]=int(film_quotas[a])
   else:
      pass
for b in range(len(film_names)):
   if film_names[b]==film_names[film_names.index(film_names[b])] and b!=film_names.index(film_names[b]):
      film_quotas[film_names.index(film_names[b])]+=film_quotas[b]
   else:
      pass
requested_film=input("Please enter the movie you want to watch: ")
if requested_film in film_names:
   person_count=input("Please enter the number of tickets you want to buy: ")
   if int(person_count)<=film_quotas[film_names.index(requested_film)]:
      print("The reservation is done!")
   else:
      genre=film_genres[film_names.index(requested_film)]
      could_be_available=[]
      for c in range(len(film_genres)):
         if film_names[c]!=requested_film and film_genres[c]==genre:
            could_be_available.append(film_names[c])
         else:
            pass
      is_available=[]
      for d in range(len(could_be_available)):
         if int(person_count)<=film_quotas[film_names.index(could_be_available[d])]:
            is_available.append(could_be_available[d])
         else:
            pass
      is_available = list(dict.fromkeys(is_available))
      is_available=sorted(is_available)
      if is_available!=[]:
         print("There are not enough seats for", requested_film+"!", "But you can watch one of the following movies from the genre", genre+":")
         for e in range(len(is_available)):
             print("*", is_available[e])
      else:
         print("There are not enough seats for", requested_film, "and any other movie with the genre", genre+"!")     
else:
   print("There is no such movie in the theater.")

#Deniz Muratli
