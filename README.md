# maze_solver
Graphical maze creator and solver- GUI implemented in Python and maze search algorithms using DFS and BFS implemented in C.
### Usage
Steps:  
1. Steps 2 to 5 are meant to show the user the operation of this program. **Steps 6 onward are for custom made mazes.**
2. Compile and execute maze_solver_main.c.  
3. Enter maze number 1-3 to illustrate pre made examples, 4 to solve custom example (steps 6 onward).  
4. Enter 0 to display unsolved maze and close when ready to see the solution.  
5. Observe output of terminal/execution environment. If 'Path Found!' message appears, the solution image, where path is shown with a red line, appears.  
6. To solve your own maze, go to maze_solver.py and under `def custom_maze():`, after the comment [INSERT YOUR MAZE BELOW](https://github.com/sriramcu/maze_solver/blob/a75250dce4f4be18d231cc208eaa510a38410c75/maze_solver.py#L192), create your maze as follows:  
7. **As of now, this program is constrained to 10 X 5 mazes.** The x coordinate of a line can vary from 0 to 10 whereas the y coordinate of a line can vary from 0 to 5. The cartesian axes are as per conventions. **Source (entry) must be at (0,5) i.e. top left corner. Final point (destination/exit) must be at (10,0), i.e. bottom right corner**. 
Thus the empty lines(where 'ph' (see step 8) is not allowed) are between (0,5) and (1,5) as well as between (9,0) and (10,0).

8. Use the ph(x,xn,y) function to plot a maze wall/line horizontally from x to xn, with y constant (since it is a horizontal line).  
9. Use the pv(x,y,yn) function to plot a maze wall/line vertically from y to yn, with x constant (since it is a vertical line).  
10. Follow steps 2 to 5 to obtain solution.


