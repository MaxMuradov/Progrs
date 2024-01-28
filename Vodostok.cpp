#include<iostream>
#include<vector>
#include <fstream>


using namespace std;

class Visitor
{
private:

public:
	Visitor() = default;

	virtual void start_viertex(int value)
	{ }
	virtual void discover_vertex(int value)
	{ }
	virtual void finish_vertex(int value)
	{ }
};

class Vis : public Visitor
{
private:
	int minimal_hight;
	vector<int> same_hight;
	vector<vector<int>> res;

public:

	Vis() : minimal_hight{ 100 } {}

	void discover_vertex(int value) override;

	void finish_vertex(int value) override;

	void print_amount();

};

class Drain
{
protected:
	int drain_lenght;
	vector<vector<int>> drain_map;

	int vertex_num;
	vector<vector<int>> adj;
	vector<bool> used;
	vector<string> colours;


	bool O_check(int pos)
	{
		return (pos == 0);
	}

	bool border_check(int pos)
	{
		return (pos == drain_lenght);
	}

	void neib_push(int index, vector<int> &other)
	{
		int i = from_index_to_coord_i(index);
		int j = from_index_to_coord_j(index);

		//Заполнение по часовой от 12:00
		if (O_check(i) == false)
			other.push_back(from_coords_to_index(i - 1, j));
		if (border_check(j) == false)
			other.push_back(from_coords_to_index(i, j + 1));
		if (border_check(i) == false)
			other.push_back(from_coords_to_index(i + 1, j));
		if (O_check(j) == false)
			other.push_back(from_coords_to_index(i, j - 1));
	}

	void from_matrix_to_graph(const vector<vector<int>> &other)
	{
		vertex_num = drain_lenght * drain_lenght;
		adj.resize(vertex_num);
		for (int i = 0; i < adj.size(); ++i)
		{
			neib_push(i, adj[i]);
		}
		used.resize(vertex_num, false);
		this->refill();
	}



public:
	Drain() = default;

	virtual int find_hight(int index)
	{
		return drain_map[from_index_to_coord_i(index)][from_index_to_coord_j(index)];
	} 

	int from_coords_to_index (int i, int j)
	{
		return i* drain_lenght + j;
	}

	int from_index_to_coord_i(int index)
	{
		return index / drain_lenght;
	}

	int from_index_to_coord_j(int index)
	{
		return index % drain_lenght;
	}

	void refill()
	{
		colours.clear();
		colours.resize(vertex_num, "white");
	}

	void build_map()
	{
		int index = 0;
		int hight;
		char ch;

		ifstream file("C:\\Users\\maxim\\OneDrive\\Рабочий стол\\Учеба прога\\New\\drain.txt");
		if (file.is_open())
		{
			char buff[55];
			file >> drain_lenght;

			drain_map.resize(drain_lenght);

			for (int i = 0; i < drain_lenght; ++i)
			{
				drain_map[i].resize(drain_lenght);
				used.resize(drain_lenght);
			}

			while (!file.eof())
			{
				file >> ch;
				if (ch != ' ')
				{
					hight = static_cast<int>(ch - '0');
					drain_map[from_index_to_coord_i(index)][from_index_to_coord_j(index)] = hight;
					++index;
				}
				if (index == 25)
					break;
			}
		}
		else
		{
			cout << "file not found";
			exit;
		}

		this->from_matrix_to_graph(drain_map);
	}

	void print_map()
	{
		for (int i = 0; i < drain_lenght; ++i, cout << "\n")
			for (int j = 0; j < drain_lenght; ++j)
				cout << drain_map[i][j] << " ";
	}

	void DFS(Visitor &vis)
	{
		for(int vertex_index = 0; vertex_index < vertex_num; ++vertex_index)
			if (colours[vertex_index] == "white")
			{
				vis.start_viertex(vertex_index);
				DFS_Visit(vis, vertex_index);
			}
		this->refill();
	}

	void DFS_Visit(Visitor &vis, int vertex)
	{
		colours[vertex] = "gray";
		vis.discover_vertex(vertex);

		for (int neib : adj[vertex])
		{
			if (colours[neib] == "white" && used[neib] == false)
			{
				if (find_hight(neib) <= find_hight(vertex))
				DFS_Visit(vis, neib);
			}
		}

		colours[vertex] = "black";
		used[vertex] = true;
		vis.finish_vertex(vertex);
	}

	void Vodostok()
	{
		Vis v;
		DFS(v);
		v.print_amount();
	}



};

class Dr : public Drain, Vis
{ 
private:
	int Value;
public:
	Dr() = default;

	Dr(int value) : Value{value} {};

	int find_hight(int index) override
	{
		return drain_map[from_index_to_coord_i(index)][from_index_to_coord_j(index)];
	}
};

	void Vis :: discover_vertex(int value)
	{
		Dr K(value);
		int initial_hight = K.find_hight(value);

		if (initial_hight < minimal_hight)
		{
			minimal_hight = initial_hight;
			same_hight.clear();
			same_hight.push_back(value);
		}
		if (initial_hight == minimal_hight)
		{
			same_hight.push_back(value);
		}
	}

	void Vis :: finish_vertex(int value)
	{
		res.push_back(same_hight);
	}

	void Vis :: print_amount()
	{
		int amount = 0;
		for (int i = 0; i < res.size(); ++i )
		{
			++amount;
		}
		cout << amount;

	}


int main()
{
	Drain D;
	D.build_map();
	D.Vodostok();
	//D.print_map();
	return 0;
}



