#include <iostream>
#include <vector>

struct Node
{
    int value;
    Node* next;
    Node* prev;
};

class Queue
{
private:

    int _size;
    Node* _head;
    Node* _tail;
    Node* _midLeft;
    Node* _midRight;

public:

    Queue() : _size{ 0 }, _head{ nullptr }, _tail{ nullptr }, _midLeft{ nullptr }, _midRight{ nullptr } {};

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
            _midLeft = newnode;
            _midRight = newnode;
        }
        else
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = nullptr;
            newnode->prev = _tail;
            _tail->next = newnode;
            _tail = newnode;


            if (_size % 2 == 0)
            {
                _midRight = _midRight->next;
            }
            else
            {
                _midLeft = _midLeft->next;
            }
        }
    }

    int pop_front()
    {
        int del_value;
        --_size;

        if (_size == 0)
        {
            Node* delete_node = _head;
            del_value = delete_node->value;
            _head = nullptr;
            _tail = nullptr;
            _midLeft = nullptr;
            _midRight = nullptr;
            delete delete_node;
        }
        else
        {
            Node* delete_node = _head;
            del_value = delete_node->value;
            _head = _head->next;
            _head->prev = nullptr;
            delete delete_node;

            if (_size % 2 == 0)
            {
                _midRight = _midRight->next;
            }
            else
            {
                _midLeft = _midLeft->next;
            }
        }
        return del_value;
    }

    void push_mid(int new_value)
    {
        if (_head == nullptr || _size == 1)
            push_back(new_value);
        else
        {
            ++_size;
            Node* newnode = new Node;
            newnode->value = new_value;

            if (_midLeft == _midRight)
            {
                Node* ptr = _midLeft->next;
                _midLeft->next = newnode;
                newnode->prev = _midLeft;
                ptr->prev = newnode;
                newnode->next = ptr;
                _midRight = newnode;
            }
            else
            {
                _midRight->prev = newnode;
                _midLeft->next = newnode;
                newnode->next = _midRight;
                newnode->prev = _midLeft;
                _midRight = newnode;
                _midLeft = newnode;
            }
        }
    }
};


int main()
{
    std::vector <int> goblinarr;
    Queue queue;

    char sign;
    int n, goblin;
    std::cin >> n;


    for (int i = 0; i < n; ++i)
    {
        std::cin >> sign;
        if (sign == '-')
        {
            goblinarr.push_back(queue.pop_front());
        }
        else if (sign == '+')
        {
            std::cin >> goblin;
            queue.push_back(goblin);
        }
        else if (sign == '*')
        {
            std::cin >> goblin;
            queue.push_mid(goblin);
        }
    }

    for (int i = 0; i < goblinarr.size(); ++i)
    {
        std::cout << goblinarr[i] << "\n";
    }
}


