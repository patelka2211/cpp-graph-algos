#include <bits/stdc++.h>
using namespace std;
#define flash                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(NULL);
#define int long long
#define frl(i, a, b) for (i = a; i < b; i++)
#define rfrl(i, a, b) for (i = b; i > a; i--)
#define MOD 1000000007
#define pi (3.141592653589)
#define min3(a, b, c) min(c, min(a, b))
#define min4(a, b, c, d) min(d, min(c, min(a, b)))
#define rev(s) reverse(s.begin(), s.end())

class node
{
private:
public:
    int value, order;
    node *sibling, *child;
    node(int value)
    {
        this->value = value;
        this->order = 0;
        this->sibling = this->child = NULL;
    }
};

class binomial_heap
{
private:
public:
    node *start;
    binomial_heap()
    {
        this->start = NULL;
    };

    void add_node(int value)
    {
        if (this->start == NULL)
        {
            this->start = new node(value);
            return;
        }

        node *new_node = new node(value);

        new_node->sibling = this->start;
        this->start = new_node;

        node *start = this->start, *sibling = this->start->sibling;

        while (start != NULL && sibling != NULL && start->order == sibling->order)
        {

            if (start->value >= sibling->value)
            {
                start->sibling = sibling->child;
                sibling->child = start;
                this->start = sibling;
                sibling->order++;
            }
            else
            {
                start->sibling = sibling->sibling;
                sibling->sibling = start->child;
                start->child = sibling;
                start->order++;
            }

            start = this->start;
            sibling = this->start->sibling;
        }
    }

    void traverse()
    {
        node *pointer = this->start;
        do
        {
            cout << pointer->value << " : " << pointer->order << ", ";
            pointer = pointer->sibling;
        } while (pointer != NULL);
        cout << endl;
    }
};

int32_t main()
{
    flash;

    binomial_heap b_heap = binomial_heap();

    b_heap.add_node(7);
    b_heap.add_node(2);
    b_heap.add_node(4);
    b_heap.add_node(17);
    b_heap.add_node(1);
    b_heap.add_node(11);
    b_heap.add_node(6);
    b_heap.add_node(8);
    b_heap.add_node(15);
    b_heap.add_node(10);
    b_heap.add_node(20);

    b_heap.traverse();

    return 0;
}