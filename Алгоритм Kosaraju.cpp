#include<iostream>
#include<vector>
#include <limits>
#include <list>


using namespace std;

class Graph
{
private:
	vector<vector<int>> adj;
	int vertex_num;
	vector<string> colours;
	list <int> order_vec;

public:

	Graph(int vertex_num)
	{
		this->vertex_num = vertex_num;
		adj.resize(vertex_num);
		colours.resize(vertex_num);
		for (int i = 0; i < colours.size(); ++i)
			colours[i] = "white";
	}

	void add_adj(int from, int to)
	{
		adj[from].push_back(to);
	}

	void refill()
	{
		for (int i = 0; i < colours.size(); ++i)
			colours[i] = "white";
	}

	void DFS_Top_sort(int vert)
	{
		colours[vert] = "gray";
		for (int neib : adj[vert]) {
			if (colours[neib] == "white") {
				DFS_Top_sort(neib);
			}
		}
		colours[vert] = "black";
		order_vec.push_front(vert);
	}

	vector<vector<int>> DFS(list<int> order_list)
	{
		vector<vector<int>> mat;
		mat.resize(order_list.size());
		int k = 0;
		while (!order_list.empty())
		{
			int tmp = order_list.front();
			if (colours[tmp] == "white")
			{
				DFS_Visit(tmp);
				for (int i = 0; i < vertex_num; ++i)
					if (colours[i] == "black")
					{
						mat[k].push_back(i);
						colours[i] = "none";
					}
				k++;
			}
			order_list.pop_front();
		}
		return mat;
	}

	void DFS_Visit(int vert)
	{
		colours[vert] = "gray";
		for (int neib : adj[vert]) {
			if (colours[neib] == "white") {
				DFS_Visit(neib);
			}
		}
		colours[vert] = "black";
	}

	void Trans()
	{

		vector<vector<int>> adj2;
		adj2.resize(vertex_num);
		for (int i = 0; i < adj.size(); ++i)
			for (int j = 0; j < adj[i].size(); ++j)
			{
				adj2[adj[i][j]].push_back(i);
			}

		swap(adj, adj2);
	}

	vector<vector<int>> Alg_Kosaraju(int vert)
	{
		DFS_Top_sort(vert);
		refill();
		Trans();
		return DFS(order_vec);
	}

};


int main()
{
	Graph A(7);
	A.add_adj(0, 1);

	A.add_adj(1, 2);
	A.add_adj(1, 3);

	A.add_adj(2, 0);
	A.add_adj(2, 4);
	A.add_adj(2, 6);

	A.add_adj(3, 5);

	A.add_adj(4, 6);

	A.add_adj(5, 3);

	A.Alg_Kosaraju(0);

	return 0;
}