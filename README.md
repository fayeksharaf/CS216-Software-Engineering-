# CS216 – Introduction to Software Engineering
### University of Kentucky | Fall 2023 | C++

A collection of four progressively complex C++ projects built throughout the semester. Each project introduces a new data structure or algorithm, building on the last — from STL containers to graph traversal with BFS.

---

## Projects at a Glance

| # | Project | Core Concepts | Key Files |
|---|---------|--------------|-----------|
| 1 | [IMDB Movie Database](#project-1-imdb-movie-database) | `map`, `set`, case-insensitive search | `PA1.cpp`, `imdb.h`, `imdb.cpp` |
| 2 | [Autocomplete Search Engine](#project-2-autocomplete-search-engine) | Binary search, merge sort, templates | `Project2.cpp`, `term.cpp`, `autocomplete.cpp`, `SortingList.cpp` |
| 3a | [Graph – Shortest Path (BFS)](#project-3-part-1-graph--shortest-path) | Graph, BFS, adjacency map | `PA3Part1.cpp`, `Graph.h`, `Graph.cpp` |
| 3b | [Word Ladder Game](#project-3-part-2-word-ladder-game) | Template class, Word Buckets, BFS | `PA3Part2.cpp`, `Graph.h`, `Graph.cpp` |

---

## Project 1: IMDB Movie Database

**What it does:** Reads a dataset of actors and their movies, then lets the user query the database in two ways — searching for actors by movie, or finding co-actors for a given actor name.

**What I built:** The complete `IMDB` class (`imdb.cpp`), including both private data structures and all member functions. The main driver (`PA1.cpp`) handles the interactive menu and all three set-operation searches.

**Key features:**
- Stores data in two parallel `map<string, set<string>>` structures — one keyed by movie, one by actor — for efficient lookup in both directions
- Case-insensitive movie title matching using C++ `<regex>`
- Three set operations implemented manually (no STL `set_union` etc.): union, intersection, and symmetric difference of actor sets
- Sub-menu loop for repeated searches without reloading data

**How to compile and run:**
```bash
cd Project1-IMDB
g++ PA1.cpp imdb.cpp -o Project1
./Project1 actor_movies.txt
```

**Example interaction:**
```
This application stores information about Actors and their Movies,
please choose your option (Enter Q or q to quit):
1. Actors in Movies
2. Actors and co-actors
```

---

## Project 2: Autocomplete Search Engine

**What it does:** Given a large dataset of query terms and weights (e.g., 80,000+ IMDB movies or 100,000 actors), finds all terms matching a user-typed prefix and returns the top N results ranked by weight — just like Google's search suggestions.

**What I built:** The `Term` class (`term.cpp`), the `Autocomplete` class (`autocomplete.cpp`), and the main driver (`Project2.cpp`). The `SortingList` template class was provided by the instructor.

**Key features:**
- Binary search to efficiently find prefix-matched terms in a sorted sequence (O(log n) lookup)
- Merge sort used to rank matched results in descending order by weight
- Template class `SortingList<T>` stores terms generically — works with any comparable type
- Timed benchmarking: the program measures and prints how long sorting and searching take
- Handles datasets of 80,000+ entries with measurable sub-second response times

**How to compile and run:**
```bash
cd Project2-Autocomplete
make
./Project2 imdb.txt 5       # search IMDB movies, show top 5 matches
./Project2 actors.txt 3     # search actors, show top 3 matches
./Project2 fortune.txt 10   # search Fortune 1000 companies, show top 10
```

**Example interaction:**
```
Time for sorting all terms: 0.42 seconds.
Please input the search query (type "exit" to quit):
> the god
98234    The Godfather (1972)
45123    The Godfather: Part II (1974)
12300    The Godfather: Part III (1990)
```

---

## Project 3 Part 1: Graph – Shortest Path

**What it does:** Builds an undirected graph from a fixed set of vertices and edges, then lets the user pick any two vertices and finds the shortest path between them using Breadth-First Search (BFS).

**What I built:** The complete `Graph` class (`Graph.cpp`) — the `addEdge()`, `hasEdge()`, and `BFS()` member functions. The main driver and header were provided by the instructor.

**Key features:**
- Adjacency map representation: `map<char, set<char>>` maps each vertex to its set of neighbors
- BFS using a queue, tracking both distance and the path taken via a `go_through` map
- Handles both connected and disjoint graphs — correctly reports "no path" when vertices are in separate components
- Returns special constants `NOPATH` (-1) and `INVALID_VERTEX` (-2) for clean error handling

**How to compile and run:**
```bash
cd Project3-Part1-Graph
g++ Graph.cpp PA3Part1.cpp -o testConnectedGraph
./testConnectedGraph
```

**Example interaction:**
```
Please choose the vertex as the source: A
Please choose the vertex as the destination: H

The distance from A to H is 3-edge away.
The path back to the source vertex:
H ---> F ---> E ---> A
```

---

## Project 3 Part 2: Word Ladder Game

**What it does:** Reads a dictionary of 4-letter words, builds a graph where words are connected if they differ by exactly one letter, then finds the shortest "word ladder" between any two words using BFS.

**What I built:** Upgraded `Graph` into a C++ template class (`Graph<T>`) so it works with `string` vertices instead of just `char`. Implemented the `WordBuckets_addEdges()` function for efficient edge-building, and completed the main BFS path-display logic.

**Key features:**
- Generic template class `Graph<T>` works with any vertex type (chars, strings, etc.)
- Word Buckets approach for O(n) edge-building instead of O(n²) brute-force comparison — each word generates patterns like `"c??l"`, `"?o?l"`, and words sharing a pattern are connected
- Uses a `stack` to reverse the BFS path and display it forward (source → destination)
- Tested on both a 15-word sample and a full 7,186-word dictionary

**How to compile and run:**
```bash
cd Project3-Part2-WordLadder
g++ PA3Part2.cpp Graph.cpp -o PA3Part2
./PA3Part2 FourLetterWords_simple.txt   # 15-word demo
./PA3Part2 FourLetterWords.txt          # full 7,186-word dictionary
```

**Example interaction:**
```
Please type the FIRST four-letter word: fool
Please type the SECOND four-letter word: sage

The ladder distance from [fool] to [sage] is 6-step away.
A ladder from [fool] to [sage]:
fool -> pool -> poll -> pall -> pale -> page -> sage
```

---

## Concepts Demonstrated Across All Projects

| Concept | Where Used |
|---------|-----------|
| STL `map` and `set` | Projects 1, 3a, 3b |
| Template classes | Projects 2, 3b |
| Binary search | Project 2 |
| Merge sort | Project 2 |
| Object-oriented design (classes, friend functions, operator overloading) | Projects 1, 2 |
| Graph data structure (adjacency map) | Projects 3a, 3b |
| Breadth-First Search (BFS) | Projects 3a, 3b |
| Algorithm efficiency (O(n²) vs O(n) Word Buckets) | Project 3b |
| File I/O and command-line arguments | Projects 1, 2, 3b |

---

## Author
**Md Fayek Sharaf**  
CS216 – Introduction to Software Engineering Techniques  
University of Kentucky, Fall 2023
