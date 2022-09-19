# CS 225 Data Structures
## Project Proposal (nmoskal2-xs2-kevingu2-smgeary2)

1. **Leading Question** Given a product, we would like to find if there are any cycles in the related products graph in order to advertise a bundle of related products back to the buyer. We would like to display the results as a ranked list. We would also like to implement a function that takes two products and returns a measurement of how closely related they are.
2. **Dataset Acquistion and Processing** The dataset we will be using comes from the Stanford Network Analysis Platform. We will be focusing on the Product Co-purchasing Networks data based on the *Customers Who Bought This Item Also Bought* feature on the Amazon website. As the description suggests, the data is a graph of products with edges connecting products that are frequently co-purchased with said product. This data comes in .txt format and we will cite it using the provided BibTex citation.  
We plan loading this data into an array format. We propose that our graph structure will consist of nodes of product ID#s and edges will connect nodes that represent co-purchased products. Additionally, each node will store a weighting representing the distance away from a target node -- this field will remain empty until a target node is specified. If there are any issues missing or malformed data, we will omit that record.  

3. **Graph Algorithms** We propose to implement a simple DFS using an iterator as our graph traversal. Our traversal iterator would take a product ID node as a starting point and will update its internal position to the next co-purchased product ID node everytime it is incremented until there are no more remaining nodes or a cycle has been detected.  
 Building off this idea, we propose to implement Iteratively Deepening DFS (IDDFS) in order to find the most related cycle to the target product ID node. Since this algorithm slowly increments away from the starting product ID node, any cycles that it discovers should be the “optimal bundle” of related products for a buyer to view.  
 For our final algorithm, we propose to use Dijikstra’s Algorithm to receive two product ID nodes and find the shortest path between them. This represents the smallest sequence of connections needed to reach a certain product given an initial product. This algorithm could possibly come into play for checking whether our IDDFS really works or help us with visualizing our graph.

4. **Timeline**  
  April 7 - sync to complete project proposal and team contract  
  April 9 - submit project proposal and team contract  
  April 12 - set up initial repository and Makefile  
  April 15 - finish reading in data into array format and write simple tests to verify correctness  
  April 19 through 23 - Mid-project check ins  
  April 19 - convert array format into graph format and pass simple tests  
  April 22 - write DFS iterator and verify with tests  
  April 29 - write IDDFS and verify with tests  
  May 5 - write Dijikstra’s Algorithm and verify with tests  
  May 7 - finish report  
  May 9 - sync to record final presentation  
  May 11 - finish editing presentation and submit  
