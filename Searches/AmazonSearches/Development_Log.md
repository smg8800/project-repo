# CS 225 Data Structures
## Development Log (nmoskal2-ksinha7-kevingu2-smgeary2)

### Week 1: April 2 - 9
We joined a shared Discord channel and discussed our general ideas for the project.
We formed our team agreement and each committed it to github. We also created a
proposal outlining our end goal for this project.

### Week 2: April 9 - 16
Set up files 'Data.cpp' and 'Data.h' to collect the data and store it as vectors.
Also created a 'driver.cpp' file to perform small tests. Also pushed dataset being used to github.
We created a rudimentary makefile with the goal of just compiling all of the files made so far
with a few error checking flags.

### Week 3: April 16 - 23
After our mid-project checkin, we collaborated to finalize the makefile, making sure it
functions as we want it but also allowing for additions to be made later on when
more files may be utilized, and briefly discussed approaches to our graph algorithms.

### Week 4: April 23 - 30
Created a catch file and a test file where we will implement more testing, discussed further on
implementations of graphs and accompanying algorithms.

### Week 5: April 30 - May 7
Working on implementing graph/graph algorithms with accompanying test cases. Created graph class, DFS class, dijkstra's 
algorithm, and metadata class (and tests). A Graph represents the directed Amazon data, the DFS class
creates a DFS traversal, dijkstra's algorithm finds the shortest distance between nodes, and 
the metadata class reads data from a file similarly to the Data class, but it reads the 
name of the products so we may display item names rather than only their product ID numbers.
Also started work on implementing IDDFS.

### Week 6: May 7 - May 12
Implemented IDDFS and tests, implements a product_utils to help handle the input data. Created a main file that takes
in a file name, metadata file name, and an output file name to run our code. There are options for which algorithm you
would like to select, and which nodes you want to start/end at. We made sure everything was functional, then got to work on our presentation, results.md, and other deliverables. We also recorded our presentation and made sure we had everything committed and
pushed to our repository on GitHub.
