# C Recursive Grid Pathfinder & Statistical Search

A performance-oriented C application implementing recursive matrix pathfinding algorithms and recursive binary search with dynamic 2D pointer management.

## Key Features
- **Max-Cost Path Finding**: Recursive traversal algorithm finding optimal paths through $M \times N$ dynamic matrices.
- **Dynamic 2D Pointer Allocation**: Pointer-of-pointers (`int **`) heap allocation and deallocation to prevent stack overflow.
- **Recursive Array Analytics**: Recursive sum calculation, statistical metrics (Mean, Standard Deviation), and $O(\log n)$ Recursive Binary Search.

## How to Run

1. Compile:
   ```bash
   gcc main.c -o pathfinder_stats