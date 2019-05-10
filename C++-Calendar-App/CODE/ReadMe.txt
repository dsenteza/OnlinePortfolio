Lab 5 Readme.

Group members: Zahra Lambe and Dominique Senteza


// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?
Calendar Interface


What class/classes is responsible for managing the representation and construction of the Calendar?
Calendar Builder


Which class should handle collecting information from the user about an event?
Calendar interface

Which class should handle constructing and adding the event to the Calendar?
Calendarbuilder



2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?

	We saved each event into a multimap. We used the name of each event as the key and the value was a shared pointer to the event


Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?

	Builder understands the structure of the calendar. It should be responsible for jumping.


How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?

	We only saved the events from the calendar to the file. When we restored it, we added the events from the file to the calendar.



3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 
	
	We created an enum that represented the different displays of our calendar. Based on what was currently being displayed, we passed in the corresponding
	enum value to the display function, and we forwarded to the current display's children. This allowed us to customize the display for every
	component based on the currentDisplay.



Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 
	
	One thing we changed is based off of calendar vs todo display we changed the menu options. This edit was made in CaldendarInterface.



How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.

	Everything in our project inherits from DisplayableComponent (even the added TODO list). So we have the freedom to add more children/levels to 
	our calendar if we wanted to



Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?

	The decorator pattern allows you to add additional functionality without changing a specific class as a whole
	We used the decorator pattern to add a label to calendars that were merged in from a text file



If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 



3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?

	Our ToDo list inherits from the DisplayableComponent class, as do the other Displayable objects.
	The singleton pattern made it so that there could only be one instance of the ToDo list object at a time


3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?

Testing working implementation of the code:

###################################################

H:\My Documents\332 Spring 19\lab5-dominique_and_zahra\Lab5\Debug>Lab5.exe
Calendar: test
0. 2019
1. 2020
2. 2021
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
c
Enter the name of your event (50 characters or less) and date of your event in the format 'mm/dd/yyyy'.
hello
03/23/2019
Enter the time of your event in the format 'hh:mm' using military time
02:12
Is this a recurring event? Enter yes or no
yes
Enter how often this event will occur in days (for example, if you want this event to occurr every week, enter 7
6
Enter how many times this event will repeat
8
Calendar: test
0. 2019
1. 2020
2. 2021
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
c
Enter the name of your event (50 characters or less) and date of your event in the format 'mm/dd/yyyy'.
ye
04/04/2019
Enter the time of your event in the format 'hh:mm' using military time
12:01
Is this a recurring event? Enter yes or no
no
Calendar: test
0. 2019
1. 2020
2. 2021
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
in
index? (0-2)
0
Year 2019:
0: January

1: February

2: March
     Sunday 3/23/2019 Event: hello 2:12
     Saturday 3/29/2019 Event: hello 2:12

3: April
     Friday 4/4/2019 Event: hello 2:12
     Sunday 4/4/2019 Event: ye 12:10
     Thursday 4/10/2019 Event: hello 2:12
     Wednesday 4/16/2019 Event: hello 2:12
     Tuesday 4/22/2019 Event: hello 2:12
     Monday 4/28/2019 Event: hello 2:12

4: May
     Sunday 5/4/2019 Event: hello 2:12
     Saturday 5/10/2019 Event: hello 2:12

5: June

6: July

7: August

8: September

9: October

10: November

11: December

zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
in
index? (0-11)
3
April
Sunday    Monday    Tuesday   Wednesday Thursday  Friday    Saturday
          1         2         3         4**       5         6
7         8         9         10*       11        12        13
14        15        16*       17        18        19        20
21        22*       23        24        25        26        27
28*       29        30
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
in
index? (0-29)
3
Thursday 4/4/2019
2:12 Event: hello
12:1 Event: ye
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
in
index? (0-1)
1
Sunday 4/4/2019
Event: ye
12:10
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q, delete event: d, edit event: e
d
Thursday 4/4/2019
2:12 Event: hello
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
out
April
Sunday    Monday    Tuesday   Wednesday Thursday  Friday    Saturday
          1         2         3         4*        5         6
7         8         9         10*       11        12        13
14        15        16*       17        18        19        20
21        22*       23        24        25        26        27
28*       29        30
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
s
Enter name of the event
test
Event name not found
April
Sunday    Monday    Tuesday   Wednesday Thursday  Friday    Saturday
          1         2         3         4*        5         6
7         8         9         10*       11        12        13
14        15        16*       17        18        19        20
21        22*       23        24        25        26        27
28*       29        30
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
m
Enter the name of the file you want to merge
q
Name: howdy Date: 31 2 2019 Time: 4:23
Name: howdy Date: 5 3 2019 Time: 4:23
Name: howdy Date: 10 3 2019 Time: 4:23
April
Sunday    Monday    Tuesday   Wednesday Thursday  Friday    Saturday
          1         2         3         4*        5*        6
7         8         9         10**      11        12        13
14        15        16*       17        18        19        20
21        22*       23        24        25        26        27
28*       29        30
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
out
Year 2019:
0: January

1: February

2: March
     Sunday 3/23/2019 Event: hello 2:12
     Saturday 3/29/2019 Event: hello 2:12
     Sunday 3/31/2019 Event: howdy 4:23

3: April
     Friday 4/4/2019 Event: hello 2:12
     Sunday 4/5/2019 Event: howdy 4:23
     Thursday 4/10/2019 Event: hello 2:12
     Sunday 4/10/2019 Event: howdy 4:23
     Wednesday 4/16/2019 Event: hello 2:12
     Tuesday 4/22/2019 Event: hello 2:12
     Monday 4/28/2019 Event: hello 2:12

4: May
     Sunday 5/4/2019 Event: hello 2:12
     Saturday 5/10/2019 Event: hello 2:12

5: June

6: July

7: August

8: September

9: October

10: November

11: December

zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q
s
Enter name of the event
howdy
1: howdy
2: howdy
3: howdy
Input the number of the event you want to view
1
Sunday 3/31/2019
Event: howdy
4:23
zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q, delete event: d, edit event: e