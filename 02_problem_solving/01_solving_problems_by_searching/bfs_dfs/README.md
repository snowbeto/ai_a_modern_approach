# Description:

	This code implements and agent who can explore the environment suing the Breadth-First Search (BFS) and Depth-First Search (DFS) methods to find targets. The search agent can perform in three different types of maps. These maps can be interpreted as follows:
		- (*) Dirt/Goal.
		- (Space) Free space.
		- (s) Initial position of the agent.
		- Any other character represents an obstacle.
		- Each character in the text file represents a cell in the map.

	The agent must follow these rules:
		- The agent can move from one cell to another at each step.
		- The agent can only move to the left, right, up or down cells from the current position. The surrounding cells should be considered as the children at the current agent’s position.
		- The agent does not have previous knowledge about the environment (such as dirt positions or obstacles) so it has to ”explore”.
		- The agent cannot move through obstacles and the map is closed.


# How to compile ? 
	1. Create a build folder and run:
		cmake ..
	2. Compile using:
		make
	3. The executable can be found in:
		../bin/
