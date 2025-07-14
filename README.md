# Metropolitan-City-Design
A C-based interactive console application to explore the city of Mysore! 

# Features
Read and display Mysore city information from places.txt

Add and delete city-to-city road distances in distances.txt

Represent city roads using adjacency lists and matrices

Apply Prim's and Kruskal's algorithms to generate Minimum Spanning Trees (MST)

Perform DFS and BFS graph traversals

Search city names using brute-force and trie-based pattern matching

Sort cities based on population using various sorting algorithms

Use a Segment Tree to perform range minimum queries on distances

# Data Structures and Their Purpose
## Sorting Algorithms
| Algorithm      | Purpose                                                    |
| -------------- | ---------------------------------------------------------- |
| Bubble Sort    | Sorts cities in ascending order based on population        |
| Selection Sort | Sorts cities in descending order based on population       |
| Insertion Sort | Another method for sorting population in descending order  |
| Quick Sort     | Sorts edges by weight in ascending order for Kruskal's MST |

## Graph Representations
| Data Structure   | Purpose                                                       |
| ---------------- | ------------------------------------------------------------- |
| Adjacency List   | Represents the city connectivity graph for dynamic operations |
| Adjacency Matrix | Used in Prim's, BFS, and DFS for dense graph representation   |
| Distance Matrix  | Stores distances between all city pairs for segment tree ops  |

## Trie (Prefix Tree)
| Data Structure | Purpose                                                       |
| -------------- | ------------------------------------------------------------- |
| Trie           | Stores city names for lexicographic display and prefix search |

## Segment Tree
| Data Structure | Purpose                                                    |
| -------------- | ---------------------------------------------------------- |
| Segment Tree   | Efficiently finds the minimum distance between city ranges |

## Disjoint Set (Union-Find)
| Data Structure | Purpose                                    |
| -------------- | ------------------------------------------ |
| Parent Array   | Detects and avoids cycles in Kruskal’s MST |

## Graph Traversal
| Algorithm | Purpose                                              |
| --------- | ---------------------------------------------------- |
| BFS       | Traverses the graph breadth-wise from a given source |
| DFS       | Traverses the graph depth-wise from a given source   |

## String Matching
| Algorithm          | Purpose                             |
| ------------------ | ----------------------------------- |
| Brute Force Search | Searches for patterns in city names |

## How to Compile and Run
### Compile the program using a C compiler:
```gcc main.c -o main```

### Run the executable:
./main

### Follow the menu options to explore city connectivity, add/delete roads, search city names, and analyze MSTs.

## Acknowledgements
This project was developed as part of academic coursework to demonstrate the application of fundamental data structures to real-world city modeling.
