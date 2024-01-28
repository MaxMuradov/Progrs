#include<iostream>
#include<vector>
#include <limits>
#include <queue>


using namespace std;

class Graph
{
private:
	vector<vector<int>> adj;
	int vertex_num;
	vector<bool> used;
	vector<int> dist;
	vector <int> parent;
	vector<string> colours;

public:

	Graph(int vertex_number):vertex_num(vertex_number)
	{
		adj.resize(vertex_num);
		used.resize(vertex_num);
		dist.resize(vertex_num, INT_MAX);
		parent.resize(vertex_num);
		colours.resize(vertex_num, "white");
	}

	void add_adj(int from, int to)
	{
		adj[from].push_back(to);
	}

	void BFS_Visit(int vertex)
	{
		queue<int> q;
		q.push(vertex);
		dist[vertex] = 0;
		parent[vertex] = vertex;

		while (!q.empty())
		{
			int tmp = q.front();
			q.pop();
			used[tmp] = true;
			dist[tmp] = dist[parent[tmp]] + 1;

			for (int neib : adj[tmp])
			{
				if (!used[neib])
				{
					q.push(neib);
					parent[neib] = tmp;
				}
			}
		}



	}

	void DFS_Visit(int vertex)
	{
		colours[vertex] = "grey";
		for (int neib : adj[vertex])
		{
			if (colours[neib] == "white")
			{
				DFS_Visit(neib);
			}
		}
		colours[vertex] = "black";	
	}

	void DFS()
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			if (colours[i] == "white")
			{
				DFS_Visit(i);
			}
		}
	}

};


int main()
{



	return 0;
}