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

node *sort_heap(node *heap)
{
    node *left_pointer = heap, *right_pointer;

    while (left_pointer->sibling != NULL)
    {
        right_pointer = left_pointer->sibling;
        while (right_pointer != NULL && left_pointer->order <= right_pointer->order)
            right_pointer = right_pointer->sibling;

        if (right_pointer == NULL)
            left_pointer = left_pointer->sibling;
        else
        {
            node *temp_pointer = left_pointer->child;
            left_pointer->child = right_pointer->child;
            right_pointer->child = temp_pointer;

            int temp_value = left_pointer->value;
            left_pointer->value = right_pointer->value;
            right_pointer->value = temp_value;

            temp_value = left_pointer->order;
            left_pointer->order = right_pointer->order;
            right_pointer->order = temp_value;

            left_pointer = heap;
        }
    }
    return heap;
}

node *perform_union(node *heap1, node *heap2)
{
    node *pointer = heap1;

    while (pointer->sibling != NULL)
    {
        pointer = pointer->sibling;
    }

    pointer->sibling = heap2;

    node *left_pointer = heap1, *right_pointer;

    while (left_pointer != NULL)
    {
        right_pointer = left_pointer->sibling;

        while (right_pointer != NULL && left_pointer->order != right_pointer->order)
            right_pointer = right_pointer->sibling;

        if (right_pointer == NULL)
            left_pointer = left_pointer->sibling;
        else
        {
            if (left_pointer->value > right_pointer->value)
            {
                if (left_pointer == heap1)
                    heap1 = left_pointer->sibling;
                else
                {
                    node *prev_of_left;

                    prev_of_left = left_pointer;

                    while (prev_of_left->sibling != left_pointer)
                        prev_of_left = prev_of_left->sibling;
                }

                left_pointer->sibling = right_pointer->child;
                right_pointer->child = left_pointer;
                right_pointer->order++;
            }
            else
            {
                node *prev_of_right = left_pointer;

                while (prev_of_right->sibling != right_pointer)
                    prev_of_right = prev_of_right->sibling;

                prev_of_right->sibling = right_pointer->sibling;
                right_pointer->sibling = left_pointer->child;
                left_pointer->child = right_pointer;
                left_pointer->order++;
            }

            left_pointer = heap1;
        }
    }

    return heap1;
}

class binomial_heap
{
private:
    node *find_min()
    {
        node *pointer = this->start, *min_node = pointer;
        int min = 1e9;

        while (pointer != NULL)
        {
            if (min > pointer->value)
            {
                min = pointer->value;
                min_node = pointer;
            }
            pointer = pointer->sibling;
        }

        return min_node;
    }

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

    int extract_min()
    {
        node *min_node = this->find_min(), *heap1 = this->start, *heap2;

        if (min_node == heap1)
            heap1 = min_node->sibling;
        else
        {
            node *prev_of_min_node = this->start;

            while (prev_of_min_node->sibling != min_node)
                prev_of_min_node = prev_of_min_node->sibling;

            prev_of_min_node->sibling = min_node->sibling;
        }

        heap2 = min_node->child;
        this->start = perform_union(heap1, heap2);

        return min_node->value;
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

    int min_value = b_heap.extract_min();

    cout << min_value << endl;

    min_value = b_heap.extract_min();

    cout << min_value << endl;

    b_heap.traverse();

    return 0;
}