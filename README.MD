OVERVIEW
We have tried to use a somewhat object oriented design for the application,
while keeping the overhead low. The controller and the view layers are tighly
coupled, but we found that seperating these two layers caused too much overhead
for a simple console application. The model and storage layers on the other
hand are rather decoupled from eachother, aswell as from the rest of the
application. We've adhered to best practices such as no global variables or state,
composition over inheritance, eg.


STL
Some specifics deviate slighly from the specification provided, for example
by using STL::set rather than lists eg. Since we used STL, we tried
to use the most fitting container for the task at hand, and the STL lists
are not very fitting for the operations the application required, such as 
sorting, lookups by name/id eg. while sets and maps excel at these operations.
We've tried to follow best practices, such as returning STL pairs rather than
the whole containers, and most of the code should also be const correct.
For some specific operations we have used const_cast for performance reasons,
to avoid having to remove and reinsert the elements. We are aware of the
implications caused by this, but found this to be a suitable method for these
situations.

COMMENTING
Comments follow the DoxyGen standard, making them easily viewable in any
editor supporting DoxyGen.
The .h files contain information related to the interface,
such as parameters, return values etc.
The source files has inline implementation comments where appropriate.

FILE FORMATS:

players.dat:
<ID>, <Name>, <Address>

sport.dat:
<Sport name>
<Table type>
<Number of divisions>
<Division name>
<Number of teams>
<Team name>
<Team address>
<Number of players>
<Player ID>
<Number of matches>
<Match date>, <Team A>, <Team B>, <Team A score>, <Team B score>, <Scorers>, <Extended>

division.txt
<Number of team>
<Team name>
<Team address>
<Number of players>
<Player ID> [, <Name>, <Address>] (if new player)
<Match date>, <Team A>, <Team B>

results.txt
<Sport name>
<Number of divisions>
<Division name>
<Number of matches>
<Date>, <Team A>, <Team B>, <Team A score>, <Team B score>, <Scorers>, <Extended>