#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

class Heap
{
private:
    std::vector<int> _heap;
    int _size;

public:

    Heap() { _size = 0; }

    Heap(std::vector<int> vec)
    {
        _heap = vec;
        _size = 0;
        build_heap();
    }

    //find index ----
    int left_Child(int parent_index)
    {
        return (parent_index * 2 + 1);
    }

    int right_Child(int parent_index)
    {
        return (parent_index * 2 + 2);
    }

    int parent(int child_index)
    {
        return ((child_index - 1) / 2);
    }

    //Children_Check ----
    bool two_children(int index)
    {
        if (right_Child(index) >= _size)
            return false;
        else
            return true;
    }

    bool one_child(int index)
    {
        //last child left and only one
        if (left_Child(index) == _size - 1)
            return true;
        else
            return false;

    }

    bool no_child(int index)
    {
        if (left_Child(index) >= _size)
            return false;
        else
            return true;
    }

    //sift up/down ----
    void sift_down(int index)
    {
        //re-check!!!
        bool EF = false;
        while (no_child(index) == true && (EF == false))
        {
            if (two_children(index))
            {
                int max_index = (_heap[left_Child(index)] > _heap[right_Child(index)]) ? left_Child(index) : right_Child(index);
                if (_heap[max_index] > _heap[index])
                {
                    std::swap(_heap[max_index], _heap[index]);
                    index = max_index;
                }
                else
                    EF = true;
            }
            else if (one_child(index) == true)
            {
                if (_heap[index] < _heap[left_Child(index)])
                {
                    std::swap(_heap[index], _heap[left_Child(index)]);
                    index = left_Child(index);
                }
                else
                {
                    EF = true;
                }
            }
        }

    }

    void sift_up(int index)
    {
        while (_heap[parent(index)] < _heap[index])
        {
            std::swap(_heap[parent(index)], _heap[index]);
            index = parent(index);
        }
    }


    //Push -----
    void push_num(int value)
    {
        if (_size > 0)
        {
            if (_size == _heap.size())
                push_to_heap(value);
            else
            {
                int index = _size;
                int n = _heap.size();
                _heap.push_back(value);
                for (int i = _heap.size() - 1; i > _size; )
                {
                    std::swap(_heap[i], _heap[i - 1]);
                    index = --i;
                }
                sift_up(index);
                ++_size;

                //double check
                //sift_down(index);
            }
        }
        else
        {
            this->push_back(value);
        }
    }

    void push_to_heap(int value)
    {
        _heap.push_back(value);

        sift_up(_heap.size() - 1);

        ++_size;
    }

    void push_back(int value)
    {
        _heap.push_back(value);
        ++_size;
    }

    //Rest functions ----
    int extract_max()
    {
        std::swap(_heap[0], _heap[_size - 1]);
        --_size;
        sift_down(0);
        return _heap[_size];
    }

    void build_heap()
    {
        for (int i = 0; i < _heap.size(); ++i)
        {
            sift_up(i);
            ++_size;
        }
    }

    void print()
    {
        for (int i = 0; i < _size; ++i)
            std::cout << " " << _heap[i];
    }
};

//test
void HeapSort(std::vector<int>& vector)
{
    std::make_heap(vector.begin(), vector.end());
    for (auto i = vector.end(); i != vector.begin(); i--)
    {
        std::pop_heap(vector.begin(), i);
    }

}

int main()
{
    //test
    std::cout << "Heap: \n";
    std::vector<int> v{ 7, 6, 8, 0, 2, 5, 15 };
    std::make_heap(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
        std::cout << " " << v[i];
    std::cout << "\n\n";

    std::cout << "Heap Sort: \n";
    HeapSort(v);
    for (int i = 0; i < v.size(); ++i)
        std::cout << " " << v[i];
    std::cout << "\n\n";

    std::cout << "Build_heap: ";
    std::vector<int> new_v{ 7, 6, 8, 0, 2, 5 };
    Heap A(new_v);
    A.push_num(15);
    A.print();
    std::cout << "\n\n";

    Heap heap;
    heap.push_num(7);
    heap.push_num(6);
    heap.push_num(8);
    heap.push_num(0);
    heap.push_num(2);
    heap.push_num(5);
    heap.push_num(15);
    std::cout << "\n" << heap.extract_max() << "\n";
    heap.print();
    std::cout << "\n";
    heap.push_num(20);
    heap.print();
}

