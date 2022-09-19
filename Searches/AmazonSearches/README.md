# nmoskal2-xs2-kevingu2-smgeary2
## Team Members (Kevin Gu, Kshitij Sinha, Nathan Moskal, Sean Geary)
## Description
Our CS 225 final project aims to analyze the relationships between various products sold on Amazon. We create a graph of Amazon products based on products that are frequently bought together. We then conduct three algorithms on our data: Depth-First Search, Dijkstra's Algorithm, and Iterative Deepening Depth-First Search.

## Data
Our Amazon data is sourced from the Product co-purchasing network dataset from the Stanford Large Network Dataset. This dataset creates edges such that "if a product _i_ is frequently co-purchased with product _j_, the graph contains a directed edge from _i_ to _j_" (SNAP). To create our graphs, we use two separate data files. The first file contains a pairwise list of integers (product IDs) that each describe a directed edge from one vertex to another. The second file maps product IDs to relavent metadata (product name, SalesRank, ASIN, etc.).

### Edge Data Format
In our project, we use a small sample (85535 edges) of Amazon data from March 02, 2003 ([Original Amazon data](http://snap.stanford.edu/data/amazon0302.html)).

The file containing edge data must contain only integers. Every line of this file contains two integers separated by any number of spaces. The first integer represents the starting node and the second integer represents the destination node. Note that the data from the Stanford Database contains additional text at the top of the file (commented with a `#`). These lines must be removed before using the file with our program. See `data/amazon.txt` for reference.

### Metadata Format
In our project, we use a small sample (50000 products) of Stanford's Amazon metadata ([Amazon metadata](http://snap.stanford.edu/data/amazon-meta.html))

The file containing meta data must conform exactly to the format provided by the Stanford Database. Each entry should contain information regarding the product Id, ASIN, title, and salesrank. See `data/amazon-meta.txt` for reference.

## Our Codebase
Our `main` executable is defined in the `main.cpp` file in the project directory. Our test files are stored in the `tests` directory and the required Catch2 source files are stored in the `catch` directory. All other source code is stored in the `src` directory. A small sample of the Stanford data is provided in the `data` directory.

## Running the Project
This project can run using either the `main` executable or Catch2 tests.

### main
Our `main.cpp` file can be used to test all of our algorithms on the Stanford data. `main` takes command-line arguments to specify filepaths and then provides a command-line interface to choose which algorithms to run.

Compile the executable with the following command

```
make
```

The executable created is called `main`. To work with the Stanford Amazon data, run the following command:
```
./main amazon.txt amazon-meta.txt output.txt
```

To run our executable with any other data file, using the following template.
```
./main [edge_data.txt] [metadata.txt] [output.txt]
```

Parameter       | Details
----------------|-----------
`edge_data.txt` | File containing edge data. Use the format specified under **Edge Data Format** above. The file `data/amazon.txt` is provided as a sample
`metatdata.txt` | File containing product metadata. Use the format specified under **Metadata Format** above. The file `data/amazon-meta.txt` is provided as a sample
`output.txt`    | File path to store the output of the desired algorithm


Once the executable is running, you will be able to work with our command-line interface. You will be asked:
```
What operation would you like to perform?: Input using choices below...
 1: DFS Traversal
 2: DFS Search
 3: Dijkstra's Search
 4: IDDFS
 5: Get list of vertex names
```
Enter any number between 1 and 5. The command-line will prompt you again to specify the arguments to the corresponding algorithm. **DFS Traversal** will require one starting node; **DFS search**, **Dijkstra's Search**, and **IDDFS** will require one starting node and one ending node; and **Get list of vertex names** requires no arguments.

To specify the vertices, input any valid integer than corresponds to a product ID. A list of product ID's can be found in the `amazon-meta.txt` file. Alternatively, you can use use _Command 5: Get list of vertex names_ to print a list of product ID's and their corresponding product names.

Once the vertices are entered, the algorithm will run and the output will be printed to the specified output file. In the end, the command line should look something like this

```
Loading files...
Data: data/amazon.txt   Metadata: data/amazon-meta.txt

What operation would you like to perform?: Input using choices below...
 1: DFS Traversal
 2: DFS Search
 3: Dijkstra's Search
 4: IDDFS
 5: Get list of vertex names
3
Enter start node ID
7853
Enter end node ID
6130
Saving to file...
```

### Tests
During development, we used automated Catch2 tests to verify correctness and eliminate bugs. All our tests are stored in the `tests` directory. These tests can be compiled using the following command.
```
make test
```
Our entire test suite can then be run as follows:
```
./test
```

Every major source file in our codebase has a corresponding test file (including our data collection, Graph data structure, and algorithm files). These tests are named accordingly. Further, every major method with a non-trivial algorithm has at least one corresponding `TEST_CASE`. For example, every algorithm in the Graph class is covered in our test suite to eliminate bugs. To make testing easier, we created very small test files, which are stored in `tests/testing_data`.

### Clean
To clean all object files and executables, run the following command:
```
make clean
```
