previously_taken_courses=input("Please enter the courses you have taken previously with letter grades: ")
semicolons1=previously_taken_courses.count(";")
colons1=previously_taken_courses.count(":")
if colons1!=semicolons1+1:
   print("Invalid input")
else:
   modified_input_1=previously_taken_courses.replace(";", ":")
   previous_course_names_and_grades=modified_input_1.split(":")
   current_courses=input("Please enter the courses you have taken this semester with letter grades: ")
   semicolons2=current_courses.count(";")
   colons2=current_courses.count(":")
   if colons2!=semicolons2+1:
      print("Invalid input")
   else:
      modified_input_2=current_courses.replace(";", ":")
      current_course_names_and_grades=modified_input_2.split(":")
      coursename=input("Please enter the course you want to check: ")
      if coursename not in current_course_names_and_grades:
         print("You didn't take", coursename, "this semester.")
      else:
         current_idx=current_course_names_and_grades.index(coursename)
         current_grade=current_course_names_and_grades[current_idx+1].capitalize()
         if current_grade!="F":
            print("You can choose between S and", current_grade, "for", coursename+".")
         elif current_grade=="F" and coursename not in previous_course_names_and_grades:
            print("Your grade for", coursename, "is U.")
         else:
            previous_idx=previous_course_names_and_grades.index(coursename)
            previous_grade=previous_course_names_and_grades[previous_idx+1].capitalize()
            if previous_grade=="U":
               print("Your grade for", coursename, "is U.")
            else:
               print("Your grade for", coursename, "is F.")

#Deniz Muratli
