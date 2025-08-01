# a-star-pathfinder
An implementation of the A* search algorithm in C++ for navigating a grid with obstacles.

Features:
- A* search using open/closed sets
- Custom `State` enum for board representation
- Clear terminal output with emoji-based visualization
- Reads board from file

Input Format:<br/>
- The input board (`board.txt`) is a text file.
  - (With 0s for empty/navigable cells and 1s for obstacles):<br/><br/>
0,1,0,0,0,0<br/>
0,1,0,0,0,0<br/>
0,1,0,0,0,0<br/>
0,0,0,1,1,0<br/>
0,1,0,0,0,0<br/>

Output:<br/>
| 🚦 | ⛰️  | 0 | 0 | 0 | 0 |
|----|----|---|---|---|---|
| 🚗 | ⛰️  | 0 | 0 | 0 | 0 |
| 🚗 | ⛰️  | 0 | x | x | x |
| 🚗 | ⛰️  | x | 🚗 | 🚗 | 🚗 |
| 🚗 | 🚗 | 🚗 | 🚗 | ⛰️  | 🏁 |

