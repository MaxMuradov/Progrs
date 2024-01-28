﻿#include <iostream>

class List
{
private:
    struct Node
    {
        int value;
        Node* next;
        Node* prev;
    };

    class Iterator
    {
    private:
        Node* ptr;

    public:
        //Constructor
        Iterator() : ptr{nullptr} {};

        //Copy-constructor
        Iterator(const Iterator& other) = default;

        //Move-constructor
        Iterator(Iterator&& other)
        {
            std::swap(other.ptr, ptr);
        }

        //Destructor
        ~Iterator() = default;

        //Operators
        Iterator& operator=(const Iterator& other) = default;

        Iterator& operator++()
        {
            if (ptr)
            {
                ptr = ptr->next;
                return *this;
            }
        }

        Iterator operator++(int)
        {
            Iterator copy(*this);
            if (ptr)
            {
                ptr = ptr->next;
            }
            return copy;
        }

        Iterator& operator--()
        {
            if (ptr)
            {
                ptr = ptr->prev;
                return *this;
            }
        }

        Iterator operator--(int)
        {
            Iterator copy(*this);
            if (ptr)
            {
                ptr = ptr->prev;
            }
            return copy;
        }
        
        //Value
        int value()
        {
            return ptr->value;
        }

        const int value() const
        {
            return ptr->value;
        }
    };

    int _size;
    Node* _head;
    Node* _tail;

public:

    //Constructor
    List() : _size{ 0 }, _head{ nullptr }, _tail{ nullptr } {};

    //Copy constructor
    List(const List& list)
    {
        copy(list);
    };

    //Move-copy constructor
    List(List&& list)
    {
        std::swap(this->_head, list._head);
        std::swap(this->_tail, list._tail);
        std::swap(this->_size, list._size);
    }

    //Destructor
    ~List()
    {
        clear();
    }

    void createIt()
    {
        Iterator A();
    }

    void push_back(int new_value)
    {
        ++_size;
        if (_head == nullptr)
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = nullptr;
            newnode->prev = nullptr;
            _head = newnode;
            _tail = newnode;
        }
        else
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = nullptr;
            newnode->prev = _tail;
            _tail->next = newnode;
            _tail = newnode;
        }
    }

    void push_front(int new_value)
    {
        ++_size;
        if (_head == nullptr)
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = nullptr;
            newnode->prev = nullptr;
            _head = newnode;
            _tail = newnode;
        }
        else
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = _head;
            newnode->prev = nullptr;
            _head = newnode;
        }
    }

    void pop_back()
    {
        if (_tail == nullptr)
        {
            std::cout << "Error";
        }
        else
        {
            Node* delete_node = _tail;
            _tail = delete_node->prev;
            if (_size > 1)
                _tail->next = nullptr;
            delete delete_node;
            --_size;
        }
    }

    void pop_front()
    {
        if (_head == nullptr)
        {
            std::cout << "Error";
        }
        else
        {
            Node* delete_node = _head;
            _head = delete_node->next;
            if (_size > 1)
                _head->prev = nullptr;
            delete delete_node;
            --_size;
        }
    }

    void print()
    {
        Node* ptr = _head;
        while (ptr != nullptr)
        {
            std::cout << ptr->value;
            ptr = ptr->next;
        }
    }

    void clear()
    {
        for (int i = _size; i > 0; --i)
        {
            pop_front();
        }
    }

    void copy(const List& list)
    {
        Node* ptr = list._tail;
        for (int i = 0; i < list._size; ++i)
        {
            push_front(ptr->value);
            ptr = ptr->prev;
        }
    }
};


int main()
{
    List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);

    
}


