#include <iostream>
#include <vector>

class Heap
{
private:
	struct Node
	{
		int value;
		Node* prev_node;
		Node* next_node;
		Node* left_child;
		Node* right_child;
		Node* parent;
	};

	Node* _peak;
	Node* _last_parent;
	Node* _last_node;

	int _heap_size;

public:
	//Constructors----
	Heap() { _heap_size = 0; }

	Heap(const std::vector<int> vec)
	{
		for (int i = 0; i < vec.size(); ++i)
		{
			push_to_heap(vec[i]);
		}
		build_heap();
	}

	//Copy-constructor---
	Heap(const Heap& heap)
	{
		Node* ptr = heap._peak;
		for (int i = 0; i < heap._heap_size; ++i)
		{
			push_to_heap(ptr->value);
			ptr = ptr->next_node;
		}
	}

	//Move-copy constructor----
	Heap(Heap&& heap)
	{
		std::swap(this->_heap_size, heap._heap_size);
		std::swap(this->_peak, heap._peak);
		std::swap(this->_last_parent, heap._last_parent);
		std::swap(this->_last_node, heap._last_node);
	}

	//Destructor-----
	~Heap() {};

	//bool-------
	bool two_children(Node* ptr)
	{
		if (ptr->right_child == nullptr || ptr->left_child == nullptr)
			return false;
		else
			return true;
	}

	bool one_child(Node* ptr)
	{
		if (ptr->left_child != nullptr && ptr->right_child == nullptr)
			return true;
		else
			return false;
	}

	bool no_child(Node* ptr)
	{
		if (ptr->left_child == nullptr && ptr->right_child == nullptr)
			return true;
		else
			return false;
	}

	//sift-------
	void sift_up(Node* ptr)
	{
		if (ptr->parent != nullptr)
		{
			while (ptr->parent->value < ptr->value)
			{
				std::swap(ptr->parent->value, ptr->value);
				ptr = ptr->parent;
				if (ptr->parent == nullptr)
					break;
			}
		}
	}

	void sift_down(Node* ptr)
	{
		bool EF = false;

		while ((no_child(ptr) == false) && (EF == false))
		{
			if (two_children(ptr) == true && EF == false)
			{
				Node* max_ptr = ptr->left_child->value > ptr->right_child->value ? ptr->left_child : ptr->right_child;
				if (max_ptr->value > ptr->value)
				{
					std::swap(max_ptr->value, ptr->value);
					ptr = max_ptr;
				}
				else
					EF = true;
			}
			else if (one_child(ptr) == true && EF == false)
			{
				if (ptr->value < ptr->left_child->value)
				{
					std::swap(ptr->value, ptr->left_child->value);
					ptr = ptr->left_child;
				}
				else
					EF = true;
			}
			else
				EF = true;
		}
	}

	//main functions
	void push_to_heap(int new_value)
	{
		Node* newnode = new Node;
		newnode->value = new_value;
		if (_peak == nullptr)
		{
			_peak = newnode;
			_last_node = newnode;
			_last_parent = nullptr;

			newnode->left_child = nullptr;
			newnode->right_child = nullptr;
			newnode->next_node = nullptr;
			newnode->prev_node = nullptr;
			newnode->parent = nullptr;
		}
		else
		{

			newnode->left_child = nullptr;
			newnode->right_child = nullptr;
			newnode->next_node = nullptr;

			//
			if (_last_parent != nullptr)
			{
				if (two_children(_last_parent))
				{
					newnode->parent = _last_parent->next_node;
					_last_parent = newnode->parent;
					_last_parent->left_child = newnode;
				}
				else if (one_child(_last_parent))
				{
					_last_parent->right_child = newnode;
					newnode->parent = _last_parent;
				}
			}
			else
			{
				_last_parent = _peak;
				newnode->parent = _peak;
				_peak->left_child = newnode;
				_peak->next_node = newnode;
			}

			//


			newnode->prev_node = _last_node;
			_last_node->next_node = newnode;
			_last_node = newnode;


		}

		sift_up(_last_node);

		++_heap_size;
	}

	int extract_max()
	{
		std::swap(_peak->value, _last_node->value);
		int val = _last_node->value;
		_last_node = _last_node->prev_node;
		delete _last_node->next_node;
		--_heap_size;
		sift_down(_peak);
		return val;
	}

	void build_heap()
	{
		Node* ptr = _peak;
		for (int i = 0; i < _heap_size; ++i)
		{
			sift_up(ptr);
			ptr = ptr->next_node;
		}
	}


	void print_sort()
	{
		Node* ptr = _peak;
		for (int i = 0; i < _heap_size; ++i)
		{
			std::cout << ptr->value << " ";
			ptr = ptr->next_node;
		}
	}
};

int main()
{
	std::vector<int> vec{ 1,2,3,4,5 };
	Heap A;
	A.push_to_heap(1);
	A.push_to_heap(4);
	A.push_to_heap(9);
	A.push_to_heap(3);
	A.push_to_heap(6);
	A.push_to_heap(7);
	A.print_sort();
	std::cout << "!!!" << A.extract_max() << "!!!";
	Heap B(A);

	B.print_sort();

	return 0;
}