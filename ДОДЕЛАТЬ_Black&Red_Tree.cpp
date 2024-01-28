#include <iostream>
#include <math.h>
#include <vector>
#include <queue>

class Tree
{
private:

    struct Node
    {
        Node* parent;
        Node* left;
        Node* right;
        int value;
        bool isRed;
    };

    Node* _root;
    int _tree_size;

public:
    //Construction ---
    Tree()
    {
        _root = nullptr;
        _tree_size = 0;
    }

    //Copy BFS - поиск в ширину
    Tree(const Tree& other_tree)
    {
        std::queue<Node*> q;
        q.push(other_tree._root);
        while (!q.empty())
        {
            Node* head = q.front();
            q.pop();
            q.push(head->left);
            q.push(head->right);
            this->push(head->value);
        }
    }

    //Move
    Tree(Tree&& rval)
    {
        std::swap(this->_tree_size, rval._tree_size);
        std::swap(this->_root, rval._root);
    }

    //Destructor
    ~Tree()
    {
        if (_root != nullptr && _tree_size > 0)
            pop_all_from(_root);
    }

    Node* find_uncle(Node* ptr)
    {
        if (ptr->parent == nullptr)
            return nullptr;
        if (ptr->parent->parent == nullptr)
            return nullptr;

        ptr = ptr->parent;
        if (ptr->value < ptr->parent->value)
            ptr = ptr->parent->right;
        else
            ptr = ptr->parent->left;

        return ptr;
    }

    Node* find_granpa(Node* ptr)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (ptr->parent == nullptr)
                return nullptr;
            else
                ptr = ptr->parent;
        }
        return ptr;
    }

    void push(int new_val)
    {
        if (find(new_val) == nullptr)
        {
            Node* newnode = new Node;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->value = new_val;
            ++_tree_size;

            if (_root = nullptr)
            {
                newnode->isRed = false;
                newnode->parent = nullptr;
                _root = newnode;
            }
            else
            {
                //общее
                newnode->isRed = true;
                Node* ptr = _root;

                //обход
                bool Flag = false;
                while (!Flag)
                {
                    if (newnode->value < ptr->value)
                    { 
                        if (ptr->left != nullptr)
                        {
                            ptr = ptr->left;
                        }
                        else
                        {
                            Flag = true;
                        }
                    }
                    else
                    {
                        if (ptr->right != nullptr)
                        {
                            ptr = ptr->right;
                        }
                        else
                        {
                            Flag = true;
                        }
                    }
                }

                //insertion
                newnode->parent = ptr;
                if (newnode->value < ptr->value)
                    ptr->left = newnode;
                else
                    ptr->right = newnode;

                //balance
                balance(newnode);

            }
        }
        else
            std::cout << " \nElement is alredy exist \n";
    }

    int pop()
    {

    }

    void balance(Node* ptr)
    {
        if ((ptr->parent->isRed) && (find_uncle(ptr)->isRed))
            balance_uncle_red(ptr);
        else if ((ptr->parent->isRed) && (!find_uncle(ptr)->isRed))
            balance_uncle_black(ptr);
    }

    void balance_uncle_red(Node* ptr)
    {
        if (ptr == _root)
            ptr->isRed = false;
        else
        {
            Node* ptr_grandpa = find_granpa(ptr);
            if (ptr_grandpa != nullptr)
            {
                Node* ptr_uncle = find_uncle(ptr);
                Node* ptr_parent = ptr->parent;

                ptr_parent->isRed = false;
                ptr_uncle->isRed = false;
                if (ptr_grandpa != _root)
                    ptr_grandpa->isRed = true;
                else
                    ptr_grandpa->isRed = false;
               
                balance(ptr_grandpa);
            }
        }
    }

    void balance_uncle_black(Node* ptr)
    {
        //turn
        if (ptr == _root)
            ptr->isRed = false;
        else
        {
            Node* ptr_parent = ptr->parent;
            Node* ptr_grandpa = find_granpa(ptr);
            if (ptr_grandpa != nullptr)
            {
                std::swap(ptr_parent->parent, ptr_grandpa->parent);

                if (ptr_grandpa->left == ptr_parent)
                {
                    ptr_parent->right = ptr_grandpa;

                }
                else if (ptr_grandpa->right == ptr_parent)
                {
                    ptr_parent->left = ptr_grandpa;
                }

            }
        }
    }

    Node* find(int val)
    {
        if (_root != nullptr)
        {
            Node* ptr = _root;
            while (1)
            {
                if (ptr->value == val)
                    return ptr;
                else if (val > ptr->value)
                {
                    if (ptr->right != nullptr)
                        ptr = ptr->right;
                    else
                        return nullptr;
                }
                else
                {
                    if (ptr->left != nullptr)
                        ptr = ptr->left;
                    else
                        return nullptr;
                }

            }
        }
        else
            return nullptr;
    }

    void pop_all_from(Node* ptr)
    {
        Node* pop = ptr;
        Node* pop_parent = ptr;

        while (ptr->left != ptr->right)
        {
            if (pop->left != nullptr)
            {
                //step left
                pop_parent = pop;
                pop = pop->left;
            }
            else if (pop->right != nullptr)
            {
                //step right
                pop_parent = pop;
                pop = pop->right;
            }
            else
            {
                //delete
                if (pop->value < pop->parent->value)
                    pop_parent->left = nullptr;
                else
                    pop_parent->right = nullptr;


                delete pop;
                pop = pop_parent;
                if (pop->parent != nullptr)
                    pop_parent = pop->parent;
            }
        }

        if (ptr->parent != nullptr)
        {
            if (ptr->value < ptr->parent->value)
                ptr->parent->left = nullptr;
            else
                ptr->parent->right = nullptr;
        }

        delete ptr;
    }

};



int main()
{
    return 0;
}

