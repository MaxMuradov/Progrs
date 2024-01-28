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
        int left_h;
        int right_h;
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

    void push(int new_val)
    {
        if (_root == nullptr)
        {
            Node* newnode = new Node;
            newnode->value = new_val;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->left_h = 0;
            newnode->right_h = 0;
            newnode->parent = nullptr;
            _root = newnode;

            ++_tree_size;

            
        }
        else
        {
            Node* ptr = _root;
            bool flag = false;
            int counter = 0;

            if (find(new_val) != nullptr)
            {
                std::cout << "\n element is alredy exist \n";
                exit;
            }

            //проход по дереву
            while (!flag)
            {
                if (new_val > ptr->value)
                {
                    if (ptr->right != nullptr)
                    {
                        ++ptr->right_h;
                        ptr = ptr->right;
                        ++counter;
                    }
                    else
                        flag = true;
                }
                else
                {
                    if (ptr->left != nullptr)
                    {
                        ++ptr->left_h;
                        ptr = ptr->left;
                        ++counter;
                    }
                    else
                        flag = true;
                }
            }

            //добавление элемента
            Node* newnode = new Node;
            newnode->value = new_val;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->left_h = 0;
            newnode->right_h = 0;
            newnode->parent = ptr;
            if (new_val > ptr->value)
            {
                ++ptr->right_h;
                ptr->right = newnode;
            }
            else
            {
                ++ptr->left_h;
                ptr->left = newnode;
            }
                ++_tree_size;

            //балансировка если набралась критическая длинна хвоста
            if (counter > log2(_tree_size))
                balance();
        }
    }

    Node* find(int val)
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

    void balance()
    {
        std::vector<int> vec = pop_all_from_to_vec(_root);
        _root = nullptr;

        if (vec.empty())
            return;

        std::make_heap(vec.begin(), vec.end());
        for (auto i = vec.end(); i != vec.begin(); i--)
            std::pop_heap(vec.begin(), i);
        
        
        balance_rec(vec, 0, vec.size() - 1);
    
    }

    void balance_rec(std::vector<int>& vec, int left, int right)
    {
        if (left > right)
            return;

        int mid = (left + right) / 2;
        this->push(vec[mid]);

        balance_rec(vec, left, mid - 1);
        balance_rec(vec, mid + 1, right);
    }

    int pop(int value)
    {
        if (find(value) == nullptr)
        { 
            std::cout << " \nelement isn't exist in the tree \n";
        }
        else
        {
            Node* ptr = find(value);

            if (ptr->left == ptr->right)
            {
                int val = ptr->value;
                delete ptr;
                return val;
            }
            else
            {
                Node* popper;

                if (ptr->left_h > ptr->right_h)
                {
                    --ptr->left_h;
                    popper = ptr->left;
                    while (popper->right != nullptr)
                    {
                        --popper->right_h;
                        popper = popper->right;
                    }
                }
                else
                {
                    --ptr->right_h;
                    popper = ptr->right;
                    while (popper->left != nullptr)
                    {
                        --popper->left_h;
                        popper = popper->left;
                    }
                }

                if (popper->value < popper->parent->value)
                    popper->parent->left = nullptr;
                else
                    popper->parent->right = nullptr;

                std::swap(ptr->value, popper->value);

                int val;
                val = popper->value;



                delete popper;
                --_tree_size;

                while (ptr->parent != nullptr)
                {
                    if (ptr->value < ptr->parent->value)
                    { 
                        ptr = ptr->parent;
                        --ptr->left_h;
                    }
                    else
                    {
                        ptr = ptr->parent;
                        --ptr->right_h;
                    }
                }

                return val;
            }
        }
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
            {
                ptr->parent->left_h = 0;
                ptr->parent->left = nullptr;
            }
            else
            {
                ptr->parent->right_h = 0;
                ptr->parent->right = nullptr;
            }
        }

        delete ptr;
    }

    std::vector<int> pop_all_from_to_vec(Node* ptr)
    {
        std::vector<int> vec;
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

                vec.push_back(pop->value);
                delete pop;
                --_tree_size;
                pop = pop_parent;
                if (pop->parent != nullptr)
                    pop_parent = pop->parent;
            }
        }

        if (ptr->parent != nullptr)
        {
            if (ptr->value < ptr->parent->value)
            {
                ptr->parent->left_h = 0;
                ptr->parent->left = nullptr;
            }
            else
            {
                ptr->parent->right_h = 0;
                ptr->parent->right = nullptr;
            }
        }

        vec.push_back(ptr->value);
        delete ptr;
        --_tree_size;

        return vec;
    }
};



int main()
{
    Tree AVL;
    AVL.push(5);
    AVL.push(6);
    AVL.push(10);
    AVL.push(2);
    AVL.pop(6);
    AVL.push(3);
    AVL.push(13);
    AVL.push(7);

    AVL.balance();

    return 0;
}

