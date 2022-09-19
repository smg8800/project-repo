# Results
## Team Members (Kshitij Sinha, Nathan Moskal, Sean Geary, Kevin Gu)
## Algorithms
### DFS : O(|V|) for traverse and find
We created a DFS class to handle all DFS traversal related functions: traverse and find. The DFS class takes in a graph to work within upon initialization, and increments according to the DFS order -exploring all connected vertices on a branch before moving laterally. Our traverse function takes a vertex ID to start from and returns a list of vertex IDs that represents the full traversal order of the graph. The find function also returns a list of vertex IDs, however, it represents the path that DFS takes to get from a passed start ID to a passed tarted ID - if there is no path, then find returns an empty list. Implementation wise, both functions do essentially the same thing, however, in order to store the path in find, we use an unordered_map to map the current vertex to the previous, and backtrack later to build the path.
### Dijkstra's Algorithm : O(|E|) + O(|V|log(|V|))
Our Dijkstra's implementation starts at the passed start vertex, and uses a priority queue to track adjacent vertices of those seen. The priority queue sorts by distance, with the lowest distance vertex at the top of the queue. The search iterates through adjacent vertices of the top of the queue, updating distances to vertices if the path through the current vertex is shorter, and setting the previous map's values to the proper vertex. When the search reaches the destination node, it then uses the previous map to reverse the path and return a vector of ints that describes the path from source to destination.
### IDDFS : O((avg num adj Vertices)^(depth of target))
The implementation of IDDFS takes in a start node, a target node, and a maximum depth. First it checks the base cases, either the starting node is equal to the target node, or the max depth has been reached. If neither of the base cases occur, then the function is recursively called on each adjacent vertex to the start vertex with the depth limit decremented by 1. If the function returns true, each visited node will be added to a path vertex as the recursive calls unwind, leaving us with the path in reverse order.
## Algorithm Terminal Outputs
### DFS: 
Terminal output for DFS traversal:
```
./main data/amazon.txt data/amazon-meta.txt output
Loading files...
Data: data/amazon.txt   Metadata: data/amazon-meta.txt

What operation would you like to perform?: Input using choices below...
 1: DFS Traversal
 2: DFS Search
 3: Dijkstra's Search
 4: IDDFS
 5: Get list of vertex names
1
Enter start node ID
1
Saving to file...
```
Sample of DFS traversal output file:
```
1: Patterns of Preaching: A Sermon Sampler
2: Candlemas: Feast of Flames
11: Resetting the Clock : Five Anti-Aging Hormones That Improve and Extend Life
6: How the Other Half Lives: Studies Among the Tenements of New York
5: Prayers That Avail Much for Business: Executive
7: Batik
8: Losing Matt Shepard
13: Clockwork Worlds : Mechanized Environments in SF (Contributions to the Study of Science Fiction and Fantasy)
20: Computed Tomography : Fundamentals, System Technology, Image Quality, Applications
23: Strange Fire: A Novel
111: The Maine Coon Cat (Learning About Cats)
78: The Ebony Cookbook: A Date With a Dish
112: Official Microsoft Image Composer Book
182: W.C. Fields, Vol. 1 & 2
183: Funny Teddy Bear Stickers (Dover Little Activity Books)
```
Terminal output for DFS find:
```
 ./main data/amazon.txt data/amazon-meta.txt output
Loading files...
Data: data/amazon.txt   Metadata: data/amazon-meta.txt

What operation would you like to perform?: Input using choices below...
 1: DFS Traversal
 2: DFS Search
 3: Dijkstra's Search
 4: IDDFS
 5: Get list of vertex names
2
Enter start node ID
1
Enter end node ID
11
Saving to file:
```
DFS find output file:
```
1: Patterns of Preaching: A Sermon Sampler
2: Candlemas: Feast of Flames
11: Resetting the Clock : Five Anti-Aging Hormones That Improve and Extend Life
```
### Dijkstra's: 
Terminal output
```
./main data/amazon.txt data/amazon-meta.txt output
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
11
Enter end node ID
15
Saving to file:
```
Results when searching for shortest path between two Harry Potter books
```
4739: Harry Potter and the Goblet of Fire (Book 4)
190: Bob Dylan - MTV Unplugged
469: Bird Songs
774: Essential Collection
1763: Lord of Earth and Heavens Heir
6037: The French Saxophone
2936: Mix De Manuel Romero
6039: Power Animal Meditations : Shamanic Journeys with Your Spirit Allies
6958: The Travels of Sir John Mandeville (Penguin Classics)
7873: Katzung's Pharmacology: Examination and Board Review
8971: Deja Dead
14912: Portraits from the Desert: Bill Wright's Big Bend
6126: Cruciformity: Paul's Narrative Spirituality of the Cross
6130: Harry Potter and the Order of the Phoenix (Book 5, Audio)
```
### IDDFS: 
Terminal Output:
```
./main data/amazon.txt data/amazon-meta.txt output
Loading files...
Data: data/amazon.txt   Metadata: data/amazon-meta.txt

What operation would you like to perform?: Input using choices below...
 1: DFS Traversal
 2: DFS Search
 3: Dijkstra's Search
 4: IDDFS
 5: Get list of vertex names
4
Enter start node ID
1
Enter end node ID
30
Saving to file:
```
```
Start vertex:		Patterns of Preaching: A Sermon Sampler
End vertex:		Solving Statics Problems with MathCAD
Path exists?:		true
```
## Results
Our goal was to create algorithms for use on Amazon sales rank data, to see what different products were related to eachother, ie: which ones customers would be likely to purchase, given that they purchased another item. The idea behind this goal was to provide a service similar to Amazon's "purchased together" section, but with more control over what items would appear, via choosing the specific search method.

