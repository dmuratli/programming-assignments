#Get the input values
quota=float(input("Please enter your internet quota (GB): "))
time_spent_watching=float(input("Please enter your total video viewing time in minutes: "))
number_of_messages_sent=int(input("Please enter the number of messages you send: "))

#Do the calculations
quota_spent_watching=time_spent_watching*7.7
quota_spent_messaging=number_of_messages_sent*1.7
a=quota_spent_watching/1024
b=quota_spent_messaging/(1024*1024)
c=quota-a-b
X=format(c, '.2f')
more_videos_in_minutes=(c*1024)/7.7
h=int(more_videos_in_minutes//60)
m=int(more_videos_in_minutes%60)
s=format((more_videos_in_minutes*60)%60, '.2f')

#Display the outputs
print("Your remaining internet quota is", X, "GB(s).")
print("You can watch video for", h, "hour(s),", m, "minute(s) and", s, "second(s).")

#Deniz Muratli
