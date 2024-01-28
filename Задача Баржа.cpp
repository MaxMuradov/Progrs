#include <iostream>
#include <vector>

using namespace std;

//описание Node
struct Node
{
    Node* next;
    int value;
};

//описание stack
struct Stack
{
    int _size;
    Node* _head;
    Node* _tail;

    //construct
    Stack() : _size{ 0 }, _head{ nullptr }, _tail{ nullptr } {}

    void size_check()
    {
        if (_size < 0)
        {
            cout << "Error";
        }
    }

    void push_front(int new_value)
    {
        size_check();
        ++_size;
        if (_head == nullptr)
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = nullptr;
            _head = newnode;
            _tail = newnode;
        }
        else
        {
            Node* newnode = new Node;
            newnode->value = new_value;
            newnode->next = _head;
            _head = newnode;
        }
    }

    void pop_front(int& pop_value)
    {
        --_size;
        size_check();
        if (_head == nullptr)
        {
            cout << "Error";
        }
        else
        {
            Node* delete_node = _head;
            _head = delete_node->next;
            pop_value = delete_node->value;
            delete delete_node;
        }
    }
};



int main()
{
    //1-st line
    int amountOfActs, amountOfTanks, maxBarrels;
    cin >> amountOfActs >> amountOfTanks >> maxBarrels;

    vector<Stack> ship;

    char sign;
    int tank, box;

    int ship_capacity = 0;
    int max_ship_capacity = 0;

    //push стэков
    for (int i = 0; i < amountOfTanks; ++i)
    {
        Stack stack;
        ship.push_back(stack);
    }

    //main
    for (int i = 0; i < amountOfActs; ++i)
    {
        cin >> sign >> tank >> box;

        if (sign == '+')
        {
            ++ship_capacity;
            if (ship_capacity > maxBarrels)
            {
                cout << "Error";
                return 0;
            }
            if (ship_capacity > max_ship_capacity)
                max_ship_capacity = ship_capacity;
            ship[--tank].push_front(box);
        }
        else if (sign == '-')
        {
            --ship_capacity;
            int box_from_tank = 0;
            ship[--tank].pop_front(box_from_tank);
            if (box_from_tank != box)
            {
                cout << "Error";
                return 0;
            }
        }
    }

    //return
    if (ship_capacity == 0)
        cout << max_ship_capacity;
    else
        cout << "Error";

    return 0;

}


