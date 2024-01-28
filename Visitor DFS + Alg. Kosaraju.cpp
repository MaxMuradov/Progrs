#include<iostream>
#include<vector>
#include <limits>
#include <list>


using namespace std;

class Visitor
{
private:

public:
	void start_vertex(int value)
	{	}

	void discover_vertex(int value)
	{	}

	void finish_vertex(int value)
	{	}


};

class Top_Sort_Visitor : public Visitor
{
private:
	list<int> order_list;

public:

	Top_Sort_Visitor() = default;

	void finish_vertex(int value)
	{
		order_list.push_front(value);
	}

	list<int> get_list()
	{
		return order_list;
	}
};

class SCC_Visitor : public Visitor
{
private:
	vector<vector<int>> SCC_vec;
	int index_scc;

public:
	SCC_Visitor(int num_vertex)
	{
		SCC_vec.resize(num_vertex);
		index_scc = -1;
	}

	void start_vertex(int value)
	{
		index_scc++;
	}

	void discover_vertex(int value)
	{
		SCC_vec[index_scc].push_back(value);
	}

	void finish_vertex(int value)
	{	}

	void print()
	{
		for (const auto& invec : SCC_vec)
		{
			for (const auto vertex : invec)
				cout << vertex << " ";
			cout << "\n";
		}
	}
};

class Graph
{
private:
	vector<vector<int>> adj;
	int vertex_num;
	vector<string> colours;

public:

	Graph(int vertex_number) :vertex_num(vertex_number)
	{
		adj.resize(vertex_num);
		colours.resize(vertex_num, "white");
	}

	Graph(const Graph& other)
	{
		vertex_num = other.vertex_num;
		adj.resize(vertex_num);
		for (int i = 0; i < other.adj.size(); ++i)
		{
			for (int j = 0; j < other.adj[i].size(); ++j)
			{
				adj[i].push_back(other.adj[i][j]);
			}
		}
		colours.resize(vertex_num, "white");
	}

	void refill()
	{
		for (int i = 0; i < colours.size(); ++i)
		{
			colours[i] = "white";
		}
	}

	void add_adj(int from, int to)
	{
		adj[from].push_back(to);
	}

	template <typename Visitor>
	void DFS_Visit(Visitor& vis, int vertex)
	{
		colours[vertex] = "grey";
		vis.discover_vertex(vertex);

		for (int neib : adj[vertex])
		{
			if (colours[neib] == "white")
			{
				DFS_Visit(vis, neib);
			}
		}

		colours[vertex] = "black";
		vis.finish_vertex(vertex);
	}

	template <typename Visitor>
	void DFS(Visitor& vis, const list<int>& order = list<int>())
	{
		if (order.empty())
		{
			for (int vertex = 0; vertex < vertex_num; ++vertex)
			{
				if (colours[vertex] == "white")
				{
					vis.start_vertex(vertex);
					DFS_Visit(vis, vertex);
				}
			}
		}
		else
		{
			for (auto vertex : order)
			{
				if (colours[vertex] == "white")
				{
					vis.start_vertex(vertex);
					DFS_Visit(vis, vertex);
				}
			}
		}
		refill();
	}

	//Trans const переделать чтобы не менял изначальный граф
	void Trans()
	{
		//Graph G(*this);
		vector<vector<int>> adj2;
		adj2.resize(vertex_num);
		for (int i = 0; i < this->adj.size(); ++i)
			for (int j = 0; j < this->adj[i].size(); ++j)
			{
				adj2[this->adj[i][j]].push_back(i);
			}

		//swap(G.adj, adj2);
		swap(adj, adj2);

		//return G;
	}

	void Kosoraju()
	{
		Graph Rep(*this);
		Top_Sort_Visitor TPS;
		Rep.DFS<Top_Sort_Visitor>(TPS);
		Rep.Trans();
		SCC_Visitor SCC(vertex_num);
		Rep.DFS<SCC_Visitor>(SCC, TPS.get_list());
		SCC.print();
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

	A.Kosoraju();


	return 0;
}