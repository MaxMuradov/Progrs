#include<iostream>
#include<vector>
#include <limits>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

class Water_maze
{
private:
	int maze_size;
	vector<vector<int>> maze;
	vector<vector<string>> colours;

public:

	Water_maze(int size)
	{
		maze_size = size;
		maze.resize(maze_size);
		colours.resize(maze_size);
		for (int i = 0; i < maze_size; ++i)
		{
			maze[i].resize(maze_size);
			colours[i].resize(maze_size);
		}
		for (int i = 0; i < maze_size; ++i)
		{
			for (int j = 0; j < maze_size; ++j)
			{
				maze[i][j] = rand() % 5;
				colours[i][j] = "white";
			}
		}
	}

	void refill_colours()
	{
		for (int i = 0; i < maze_size; ++i)
		{
			for (int j = 0; j < maze_size; ++j)
			{
				colours[i][j] = "white";
			}
		}
	}

	void DFS_check(int start_x, int start_y, int new_val)
	{
		int start_val = maze[start_x][start_y];
		colours[start_x][start_y] = "grey";
		if ((start_x < maze_size - 1) && (maze[start_x + 1][start_y] == start_val) && (colours[start_x + 1][start_y] == "white"))
			DFS_check(start_x + 1, start_y, new_val);
		if ((start_x > 0) && (maze[start_x - 1][start_y] == start_val) && (colours[start_x - 1][start_y] == "white"))
			DFS_check(start_x - 1, start_y, new_val);
		if ((start_y < maze_size - 1) && (maze[start_x][start_y + 1] == start_val) && (colours[start_x][start_y + 1] == "white"))
			DFS_check(start_x, start_y + 1, new_val);
		if ((start_y > 0) && (maze[start_x][start_y - 1] == start_val) && (colours[start_x][start_y - 1] == "white"))
			DFS_check(start_x, start_y - 1, new_val);

		colours[start_x][start_y] = "black";
		maze[start_x][start_y] = new_val;
	}

	int from_index_to_num(int index_x, int index_y)
	{
		return index_x * maze_size + index_y;
	}

	int from_num_to_index_y(int num)
	{
		return num / maze_size;
	}

	int from_num_to_index_x(int num)
	{
		return num % maze_size;
	}

	void BFS_check(int start_x, int start_y, int new_val)
	{
		int x = start_x, y = start_y;
		int startval = maze[start_x][start_y];
		queue<int> q;
		vector<int> neighbours;
		q.push(from_index_to_num(start_x, start_y));
		while (!q.empty())
		{
			int tmp = q.front();
			q.pop();
			x = from_num_to_index_x(tmp);
			y = from_num_to_index_y(tmp);
			colours[x][y] = "black";
			maze[x][y] = new_val;

			if (x < maze_size - 1)
				neighbours.push_back(from_index_to_num(x + 1, y));
			if (y < maze_size - 1)
				neighbours.push_back(from_index_to_num(x, y + 1));
			if (x > 0)
				neighbours.push_back(from_index_to_num(x - 1, y));
			if (y > 0)
				neighbours.push_back(from_index_to_num(x, y - 1));

			for (int neib : neighbours)
			{
				if ((maze[from_num_to_index_x(neib)][from_num_to_index_y(neib)] == startval) && (colours[from_num_to_index_x(neib)][from_num_to_index_y(neib)] == "white"))
				{
					q.push(neib);
				}
			}
		}

	}

	void print()
	{
		std::cout << "\n";
		for (int i = 0; i < maze_size; ++i, std::cout << "\n")
		{
			for (int j = 0; j < maze_size; ++j)
			{
				if (j == 0)
					std::cout << " | " << maze[i][j] << std::setw(3) << " | ";
				else
					std::cout << maze[i][j] << std::setw(3) << " | ";
			}
		}
		std::cout << "\n";
		std::cout << "\n";
	}
};

int main()
{
	int s, x, y, newval;
	cin >> s;
	Water_maze Maze(s);
	Maze.print();
	//cout << "Enter X, Y, New value\n";
	//cin >> x >> y >> newval;
	//Maze.DFS_check(y, x, newval);
	//Maze.print();
	//Maze.refill_colours();
	cout << "Enter X, Y, New value\n";
	cin >> x >> y >> newval;
	Maze.BFS_check(x, y, newval);
	Maze.print();
	return 0;
}


