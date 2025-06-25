# CS-300-DSA-Analysis-and-Design

**What was the problem you were solving in the projects for this course?**

- A university called ABCU wanted me to create an application that will allow them to search for course information within their computer science department. To do this, I had to make make sure the program could take a csv file, load the information from it into data structure, and then allow the user to search for specific courses or print out a list of all available courses.

**How did you approach the problem? Consider why data structures are important to understand.**

- For this project, I knew there were three main functions that needed to happen for it to work. The first one is that it needed to be able to take a csv file, read each line from it, and properly store the information in a data structure. For this project, my data structure of choice was a binary search tree, because of it's fast lookup time and automatic sorting. Secondly, I needed the applciation to be able to print a list of all the courses within the csv file. To do this, I created a simpe print method that read through each course in the data structure, and printed the neccesary information from it. Lastly, I needed a way to search for specific courses within the data structure. For this, I used the course number as an ID column, and had the user input the course number for the course they want to see, and then tried to match the user's course number with the courses in the data structure. If it matches one of the course numbers in the data structure, then it would print the information out, and if it didn't match any of the courses, it would display an error.

**How did you overcome any roadblocks you encountered while going through the activities or project?**

- One of the roadblocks I encountered was that I didn't have much experience on how to read through the csv file, and store it into a data structure. For this, I had to go back and reference a project that I did for another course a while back, and reuse some of the code from that since it used a similar function.

**How has your work on this project expanded your approach to designing software and developing programs?**

- This project has expanded my approach by helping me understand how important it can be to reuse code in order to speed up development. A lot of the code for this project was from assignmnets I did for other classes, or even some from this class, which ultimately helped speed up the development process for this application by quite a bit. If I would have tried to create everything from scratch, it would have taken me much longer to finish.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**

- Like I mentioned in the last point, I took a lot of inspiration from other assignments to create this application, so I think it emphasized how important it is to create modulable, reusable code, that can be implemented in other ways to create other applications later on down the road.
