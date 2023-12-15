//bloom filter

#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int h1(string s, int arrSize) {
    ll int hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}

int h2(string s, int arrSize) {
    ll int hash = 1;
    for (int i = 0; i < s.size(); i++) {
        hash = hash + pow(19, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

int h3(string s, int arrSize) {
    ll int hash = 7;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * 31 + s[i]) % arrSize;
    }
    return hash % arrSize;
}

bool lookup(bool* bitarray, int arrSize, string s) {
    int a = h1(s, arrSize);
    int b = h2(s, arrSize);
    int c = h3(s, arrSize);

    return bitarray[a] && bitarray[b] && bitarray[c];
}

void insert(bool* bitarray, int arrSize, string s) {
    if (lookup(bitarray, arrSize, s))
        cout << s << " is Probably already present" << endl;
    else {
        int a = h1(s, arrSize);
        int b = h2(s, arrSize);
        int c = h3(s, arrSize);

        bitarray[a] = true;
        bitarray[b] = true;
        bitarray[c] = true;

        cout << s << " inserted" << endl;
    }
}

int main() {
    int arrSize;
    cout << "Enter the size of the array: ";
    cin >> arrSize;

    bool bitarray[100] = {false}; // Assuming a maximum size of 100 for simplicity

    int numStrings;
    cout << "Enter the number of strings to insert: ";
    cin >> numStrings;

    vector<string> sarray(numStrings);
    cout << "Enter the strings:\n";
    for (int i = 0; i < numStrings; ++i) {
        cout << "String " << i + 1 << ": ";
        cin >> sarray[i];
    }

    for (const string& s : sarray) {
        insert(bitarray, arrSize, s);
    }

    return 0;
}


//binomial_heap


#include <iostream>
#include <cstdlib>
using namespace std;
// Node Declaration
struct node
{
    int n;
    int degree;
    node *parent;
    node *child;
    node *sibling;
};
// Class Declaration
class BinomialHeap
{
private:
    node *H;
    node *Hr;
    int count;

public:
    node *Initializeheap();
    void Binomial_link(node *, node *);
    node *Create_node(int);
    node *Union(node *, node *);
    node *Insert(node *, node *);
    node *Merge(node *, node *);
    void Display(node *);
    node *Search(node *, int);
    BinomialHeap()
    {
        H = Initializeheap();
        Hr = Initializeheap();
        int count = 1;
    }
};
// Initialize Heap
node *BinomialHeap::Initializeheap()
{
    node *np;
    np = NULL;
    return np;
}
// Linking nodes in Binomial Heap
void BinomialHeap::Binomial_link(node *y, node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
// Create Nodes in Binomial Heap
node *BinomialHeap::Create_node(int k)
{
    node *p = new node;
    p->n = k;
    return p;
}
// Insert Nodes in Binomial Heap
node *BinomialHeap::Insert(node *H, node *x)
{
    node *H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}
// Union Nodes in Binomial Heap
node *BinomialHeap::Union(node *H1, node *H2)
{
    node *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    node *prev_x;
    node *next_x;
    node *x;

    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}
// Merge Nodes in Binomial Heap
node *BinomialHeap::Merge(node *H1, node *H2)
{
    node *H = Initializeheap();
    node *y;
    node *z;
    node *a;
    node *b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }

    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
void printTree(node *root, int depth)
{
    if (root == NULL)
        return;

    // Print the current node
    for (int i = 0; i < depth; i++)
        cout << "  "; // Adjust the spacing for each level of the tree
    cout << root->n << endl;

    // Recursively print the child and sibling nodes
    printTree(root->child, depth + 1);
    printTree(root->sibling, depth);
}

void BinomialHeap::Display(node *H)
{
    if (H == NULL)
    {
        cout << "The Heap is empty" << endl;
        return;
    }

    cout << "Binomial Heap:" << endl;
    printTree(H, 0);
    cout << endl;
}

int main()
{
    int n, m, l, i;
    BinomialHeap bh;
    node *p;

    node *H;
    H = bh.Initializeheap();
    char ch;
    while (1)
    {
        cout << "----------------------------" << endl;
        cout << " BINOMIAL HEAP" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Insert Element in the heap" << endl;
        cout << "2. Display Heap" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> l;
        switch (l)
        {
        case 1:
            cout << "Enter the element to be inserted: ";
            cin >> m;
            p = bh.Create_node(m);
            H = bh.Insert(H, p);
            break;
        case 2:
            cout << "The Heap is: " << endl;
            bh.Display(H);
            break;
        case 3:
            exit(1);
        default:
            cout << "Wrong Choice";
        }
    }
    return 0;
}


//binary_Counter

// Aggregate Method
#include <stdio.h>
#include <math.h>
void main()
{
    float tot = 0;
    int arr[4] = {0};
    printf("Enter value between 0 to %f\n", pow(2, 4));
    float n;
    scanf("%f", &n);
    printf("Counter:0, Cost:0 \n");
    for (int j = 0; j < n; j++)
    {
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4)
        {
            tot++;
            arr[i] = 1;
        }
        printf("Counter:%d, Cost:%f \n", j + 1, tot);
    }
    float avgcost = tot / n;
    printf("Avg Cost:%f \n", avgcost);
}
// Accounting method
#include <stdio.h>
#include <math.h>
void main()
{
    int size[10];
    printf("\n");
    float tot[10];
    int credit[11] = {0};
    int arr[4] = {0};
    for (int j = 0; j < 10; j++)
    {
        int total = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            total++;
            i++;
        }
        if (i < 4)
        {
            total++;
            arr[i] = 1;
        }
        credit[j + 1] = 2 - total + credit[j];
        printf("Counter:%d, ", j + 1);
        printf("Cost:%d \n", credit[j]);
    }
}

// Potential Method:
#include <stdio.h>
#include <math.h>
void main()
{
    float tot = 0;
    int arr[4] = {0};
    printf("Enter value between 0 to %f\n", pow(2, 4));
    float n;
    scanf("%f", &n);
    float prev_potential = 0;
    printf("Counter:0, Cost:0\n");
    float prevones = 0;
    for (int j = 0; j < n; j++)
    {
        float currentones = 0;
        float potential = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4)
        {
            tot++;
            arr[i] = 1;
        }
        for (int k = 0; k < 4; k++)
            if (arr[k] == 1)
                currentones++;
        float current_cost = tot;
        potential = current_cost + potential - prev_potential;
        prev_potential = current_cost;
        float amort = potential + (currentones - prevones);
        prevones = currentones;
        printf("Counter:%d, Cost:%f, Current Cost:%f, amort Cost:%f\n", j + 1, current_cost, potential, amort);
    }
    float avg_cost = tot / n;
    printf("Avg Cost:%f\n", avg_cost);
}


//4 btree//

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
  int val[MAX + 1], count;
  struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;

struct BTreeNode *createNode(int val, struct BTreeNode *child);
void insertNode(int val, int pos, struct BTreeNode *node, struct BTreeNode *child);
void splitNode(int val, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode);
int setValue(int val, int *pval, struct BTreeNode *node, struct BTreeNode **child);
void insert(int val);
void search(int val, int *pos, struct BTreeNode *myNode);
void traversal(struct BTreeNode *myNode);

void displayMenu() {
    printf("B-Tree Operations:\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Display\n");
    printf("4. Exit\n");
}

int main() {
    int choice, value, pos;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(value, &pos, root);
                if (pos != -1) {
                    printf("%d is found at position %d.\n", value, pos);
                } else {
                    printf("%d is not found.\n", value);
                }
                break;

            case 3:
                printf("B-tree: ");
                traversal(root);
                printf("\n");
                break;

            case 4:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

struct BTreeNode *createNode(int val, struct BTreeNode *child) {
  struct BTreeNode *newNode;
  newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

void insertNode(int val, int pos, struct BTreeNode *node, struct BTreeNode *child) {
  int j = node->count;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}

void splitNode(int val, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  } else {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

int setValue(int val, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  if (!node) {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (val < node->val[1]) {
    pos = 0;
  } else {
    for (pos = node->count; (val < node->val[pos] && pos > 1); pos--)
      ;
    if (val == node->val[pos]) {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

void insert(int val) {
  int flag, i;
  struct BTreeNode *child;

  flag = setValue(val, &i, root, &child);
  if (flag)
    root = createNode(i, child);
}

void search(int val, int *pos, struct BTreeNode *myNode) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count; (val < myNode->val[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->val[*pos]) {
      printf("%d is found\n", val);
      return;
    }
  }
  search(val, pos, myNode->link[*pos]);

  return;
}

void traversal(struct BTreeNode *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      traversal(myNode->link[i]);
      printf("%d ", myNode->val[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}

//5cuckoo hashing

#include <algorithm>
#include <iostream>
#include <vector>

#define MAXN 11
#define ver 2

int hashtable[ver][MAXN];

int pos[ver];

void initTable()
{
    for (int j = 0; j < MAXN; j++)
        for (int i = 0; i < ver; i++)
            hashtable[i][j] = INT_MIN;
}

int hash(int function, int key)
{
    switch (function)
    {
    case 1:
        return key % MAXN;
    case 2:
        return (key / MAXN) % MAXN;
    }
}

void place(int key, int tableID, int cnt, int n)
{
    if (cnt == n)
    {
        printf("%d unpositioned\n", key);
        printf("Cycle present. REHASH.\n");
        return;
    }

    for (int i = 0; i < ver; i++)
    {
        pos[i] = hash(i + 1, key);
        if (hashtable[i][pos[i]] == key)
            return;
    }
    if (hashtable[tableID][pos[tableID]] != INT_MIN)
    {
        int dis = hashtable[tableID][pos[tableID]];
        hashtable[tableID][pos[tableID]] = key;
        place(dis, (tableID + 1) % ver, cnt + 1, n);
    }
    else
        hashtable[tableID][pos[tableID]] = key;
}

void printTable()
{
    printf("Final hash tables:\n");

    for (int i = 0; i < ver; i++, printf("\n"))
        for (int j = 0; j < MAXN; j++)
            (hashtable[i][j] == INT_MIN) ? printf("- ") : printf("%d ", hashtable[i][j]);

    printf("\n");
}

void cuckoo(std::vector<int> keys)
{
    initTable();
    for (int i = 0, cnt = 0; i < keys.size(); i++, cnt = 0)
        place(keys[i], 0, cnt, keys.size());

    printTable();
}

int main()
{
    int n;
    std::cout << "Enter the number of keys: ";
    std::cin >> n;

    std::vector<int> keys(n);
    std::cout << "Enter the keys:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "Key " << i + 1 << ": ";
        std::cin >> keys[i];
    }

    cuckoo(keys);

    return 0;
}



//6dynamic_table

#include <iostream>

#include <stack>

#include <cstdlib>

#include <ctime>
using namespace std;
class DynamicArray {
  private: int currSize;
  int capacity;
  int * a;
  int cost;

  void resizeArray() {
    if (currSize == capacity) {
      cout << "DOUBLING SIZEEEEE" << endl;
      int * temp = new int(2 * capacity);
      for (int i = 0; i < capacity; i++) {
        temp[i] = a[i];
      }
      free(a);
      a = temp;
      cost = capacity + 1;
      capacity = 2 * capacity;
    }
  }

  public: DynamicArray() {
    a = new int(1);
    cost = 1;
    currSize = 0;
    capacity = 1;
  }

  void insertAtEnd(int x) {
    if (currSize == capacity) {
      resizeArray();
    }
    else cost = 1;
    a[currSize] = x;
    currSize++;
  }

  int getArraySize() {
    return currSize;
  }
  int getCost(){
      return cost;
  }

  int getCapacity() {
    return capacity;
  }
};

int main() {
  DynamicArray a;
  int n;
  cout << "Enter the number of elements ";
  cin >> n;
  for (int i = 0; i < n; i++) {
    a.insertAtEnd(i);
    cout << "Curr Size: " << a.getArraySize() << endl;
    cout << "Capacity: " << a.getCapacity() << endl;
    cout << "Cost: "<< a.getCost()<<endl;
  }
}


//7 interval  overlapping

#include <iostream>
using namespace std;

struct Interval
{
    int low, high;
};

struct ITNode
{
    Interval *i;
    int max;
    ITNode *left, *right;
};

ITNode *newNode(Interval i)
{
    ITNode *temp = new ITNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = NULL;
    return temp;
};

ITNode *insert(ITNode *root, Interval i)
{
    if (root == NULL)
        return newNode(i);

    int l = root->i->low;

    if (i.low < l)
        root->left = insert(root->left, i);
    else
        root->right = insert(root->right, i);

    if (root->max < i.high)
        root->max = i.high;

    return root;
}

bool doOverlap(Interval i1, Interval i2)
{
    return (i1.low <= i2.high && i2.low <= i1.high);
}

Interval *overlapSearch(ITNode *root, Interval i)
{
    if (root == NULL)
        return NULL;

    if (doOverlap(*(root->i), i))
        return root->i;

    if (root->left != NULL && root->left->max >= i.low)
        return overlapSearch(root->left, i);

    return overlapSearch(root->right, i);
}

void inorder(ITNode *root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;

    inorder(root->right);
}

int main()
{
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;

    Interval *ints = new Interval[n];

    cout << "Enter intervals in the format [low high]:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Interval " << i + 1 << ": ";
        cin >> ints[i].low >> ints[i].high;
    }

    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);

    cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);

    Interval x;
    cout << "\nEnter the interval to search [low high]: ";
    cin >> x.low >> x.high;

    cout << "Searching for interval [" << x.low << ", " << x.high << "]";
    Interval *res = overlapSearch(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";

    delete[] ints;
    return 0;
}


// leftist heap

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node
{
    int element, npl;
    struct Node *left;
    struct Node *right;
};

struct LeftHeap
{
    struct Node *head;
};

struct Node *createNode(int element)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->npl = 0;
    return newNode;
}

struct LeftHeap *createLeftHeap()
{
    struct LeftHeap *heap = (struct LeftHeap *)malloc(sizeof(struct LeftHeap));
    if (heap == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    heap->head = NULL;
    return heap;
}

bool isEmpty(struct LeftHeap *heap)
{
    return heap->head == NULL;
}

void clear(struct LeftHeap *heap)
{
    heap->head = NULL;
}

struct Node *merge(struct Node *a, struct Node *b)
{
    if (a == NULL)
        return b;

    if (b == NULL)
        return a;

    if (a->element > b->element)
    {
        struct Node *temp = a;
        a = b;
        b = temp;
    }

    a->right = merge(a->right, b);

    if (a->left == NULL)
    {
        a->left = a->right;
        a->right = NULL;
    }

    else
    {

        if (a->left->npl < a->right->npl)
        {
            struct Node *temp = a->left;
            a->left = a->right;
            a->right = temp;
        }
        a->npl = a->right->npl + 1;
    }
    return a;
}

void mergeHeaps(struct LeftHeap *heap1, struct LeftHeap *heap2)
{
    if (heap1 == heap2)
        return;

    heap1->head = merge(heap1->head, heap2->head);
    heap2->head = NULL;
}

void insert(struct LeftHeap *heap, int element)
{
    heap->head = merge(createNode(element), heap->head);
}

int deleteMin(struct LeftHeap *heap)
{

    if (isEmpty(heap))
        return -1;

    int min = heap->head->element;
    heap->head = merge(heap->head->left, heap->head->right);
    return min;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->element);
    inorder(root->right);
}

int main()
{
    printf("LEFTIST HEAP\n");
    struct LeftHeap *h = createLeftHeap();
    bool askForAnother = true;
    char ch;
    while (askForAnother)
    {
        printf("Functions to do:\n1.Insert\n2.Delete minimum\n3.Checkn Empty\n4.Clear\n5.Exit\nEnter your choice:");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter integer element to insert:");
            int element;
            scanf("%d", &element);
            insert(h, element);
            break;

        case 2:
            deleteMin(h);
            break;

        case 3:
            printf("Empty status = %s\n", isEmpty(h) ? "true" : "false");
            break;

        case 4:
            clear(h);
            break;

        case 5:
            askForAnother = false;
            break;

        default:
            printf("Wrong Entry\n");
            break;
        }

        if (choice != 5)
        {
            printf("Inorder Traversal:");
            inorder(h->head);
            printf("\n");
        }
    }
    free(h);
    return 0;
}


//multistack

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements in stack: ";
    cin >> n;

    int arr[n];
    srand(time(0));

    cout << "Enter the elements of the stack:\n";
    for (int i = 0; i < n; i++) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << "--------------------\n";

    int cost = 0;
    int accountingcost = 0;
    int potentialcost = 0;

    stack<int> stk;

    for (int i = 0; i < n; i++) {
        int k; //= rand() % 3;
        cout << "Enter 1.push 2.pop 3.multipop" << " ";
        cin >> k;

        if (k == 0) {
            stk.push(arr[i]);
            cost += 1;
            accountingcost += 1;
            cout << stk.top() << " push accounting cost: " << "1" << endl;
            potentialcost += 1;
        }
        else if (k == 1) {
            if (!stk.empty()) {
                cout << stk.top() << " pop accounting cost: " << "-1" << endl;
                stk.pop();
                cost += 1;
                accountingcost -= 1;
                potentialcost -= 1;
            }
        }
        else {
            int k = rand() % 5;
            int s = stk.size();
            int minimum = min(k, s);
            for (int i = 0; i < minimum; i++) {
                cout << stk.top() << " multipop accounting cost: " << "-1" << endl;
                stk.pop();
                accountingcost -= 1;
                cost += 1;
                potentialcost -= 1;
            }
        }
    }

    cout << "\nCost: " << cost << endl;
    cout << "Aggregate cost: " << (float)cost / n << endl;
    cout << "Accounting: " << accountingcost << endl;
    cout << "Potential or Excess: " << potentialcost << endl;
    cout << "Final stack size: " << stk.size() << endl;

    return 0;
}


//perfect hashing


#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <climits>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

typedef long long int long_int;
const int max_int = 1000000001; // value, that couldn't be in the table. Analog of NULL.

// function for calculation of hash
inline int hash(long_int a_prime, long_int b_prime, int p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}

// class for mini-hash table in cells of the main hash-table class Bucket
class Bucket
{
private:

public:
    vector<int> _cells;
    int size; // the size of the mini-table should be greater than 4
    long_int hash_a;
    long_int hash_b;
    int prime;
    Bucket() {}

    void Initialize()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b = 1 + std::rand() % (prime - 1);
    }

    // construct hash table from list of elements
    void Construct(list<int> &input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        // Calculate the size of the mini-table using a power of 2
        size = std::pow( std::ceil(input.size()), 2);

        _cells.assign(size, max_int);
        Initialize();
        bool flag = true;

        // while there are no collisions in the table
        while (flag)
        {
            list<int>::iterator elem = input.begin();
            flag = false; // Assume no collision

            while (elem != input.end())
            {
                int hashKey = hash(hash_a, hash_b, prime, size, *elem);
                if (_cells[hashKey] != max_int)
                {
                    // Collision occurred, reset and break
                    flag = true;
                    _cells.assign(size, max_int);
                    Initialize();
                    break;
                }
                _cells[hashKey] = *elem;
                ++elem;
            }
        }
    }

    bool Contains(int elem)
    {
        if (size == 0)
            return false;

        int hashKey = hash(hash_a, hash_b, prime, size, elem);
        if (_cells[hashKey] == elem)
            return true;

        return false;
    }
};

// class for main hash table class FixedSet
class FixedSet
{
private:
    int _tableSize;
    long_int _hashFuncA;
    long_int _hashFuncB;
    int _primeNumber;
    vector<list<int> > _elementsInCells;
    vector<Bucket> _buckets;

public:
    FixedSet()
    {
        _primeNumber = 100013; // the maximum prime number
        _hashFuncA = std::rand() % _primeNumber;
        _hashFuncB = 1 + std::rand() % (_primeNumber - 1);
    }

    void setTableSize(int size)
    {
        _tableSize = size;
        _buckets.resize(size);
    }

    void Initialize(const vector<int> &numbers)
    {
        _tableSize = numbers.size();
        _buckets.resize(numbers.size());
        _elementsInCells.resize(numbers.size());

        for (int i = 0; i < numbers.size(); ++i)
        {
            int hashKey = hash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, numbers[i]);
            _elementsInCells[hashKey].push_back(numbers[i]);
        }

        for (int i = 0; i < numbers.size(); ++i)
        {
            _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    void PrintHashTable() const
    {
        for (int i = 0; i < _tableSize; ++i)
        {
            cout << "Hash " << i << ": ";

            if (_buckets[i].size == 0)
            {
                cout << "/" << endl;  // Print "/" for an empty bucket
            }
            else
            {
                for (int j = 0; j < _buckets[i].size; ++j)
                {
                    if (_buckets[i]._cells[j] != max_int)
                    {
                        cout << _buckets[i]._cells[j] << " ";
                    }
                    else
                    {
                        cout << "/ ";
                    }
                }
                cout << endl;
            }
        }
    }

    bool Contains(int number)
    {
        int hashKey = hash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, number);
        return _buckets[hashKey].Contains(number);
    }
};

int main(int argc, char *argv[])
{
    clock_t begin, end;
    double time_spent;
    std::srand(time(NULL));

    int numberOfElements;
    printf("Number of elements\n");
    scanf("%d", &numberOfElements);

    FixedSet fs;
    begin = clock();

    vector<int> inputVector;
    fs.setTableSize(numberOfElements);

    printf("Enter Elements\n");
    for (int i = 0; i < numberOfElements; ++i)
    {
        int elemValue;
        scanf("%d", &elemValue);
        inputVector.push_back(elemValue);
    }

    fs.Initialize(inputVector);
    end = clock();


    fs.PrintHashTable();


    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Search for an Element\n";
        cout << "2. Print Hash Table\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            int elem;
            cout << "Enter element to search: ";
            cin >> elem;
            if (fs.Contains(elem))
            {
                cout << "Element " << elem << " present in the Hash Table.\n";
            }
            else
            {
                cout << "Element " << elem << " not present in the Hash Table.\n";
            }
            break;

        case 2:
            cout << "Hash Table:\n";
            fs.PrintHashTable();
            break;

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}


//red black

#include <stdio.h>
#include <stdlib.h>

enum nodeColor
{
    RED,
    BLACK
};

struct rbNode
{
    int data, color;
    struct rbNode *link[2];
};

struct rbNode *root = NULL;

struct rbNode *createNode(int data)
{
    struct rbNode *newnode;
    newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

void insertion(int data)
{
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root)
    {
        root = createNode(data);
        return;
    }

    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            printf("Duplicates Not Allowed!!\n");
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode(data);
    while ((ht >= 3) && (stack[ht - 1]->color == RED))
    {
        if (dir[ht - 2] == 0)
        {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED)
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 0)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else
        {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED))
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 1)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}

void inorderTraversal(struct rbNode *node)
{
    if (node)
    {
        inorderTraversal(node->link[0]);
        printf("%d  ", node->data);
        inorderTraversal(node->link[1]);
    }
    return;
}

int main()
{
    int ch, data;
    while (1)
    {
        printf("1.Insertion\n");
        printf("2.Traverse\n3.Exit\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the element to insert:");
            scanf("%d", &data);
            insertion(data);
            break;

        case 2:
            inorderTraversal(root);
            printf("\n");
            break;
        case 3:
            exit(0);

        default:
            printf("Not available\n");
            break;
        }
        printf("\n");
    }
    return 0;
}


//segment

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int sum;
    pair<int, int> interval;
    Node *left;
    Node *right;
};

void build(vector<int> &array, Node *cur_node, int L, int R)
{
    cur_node->interval = make_pair(L, R);
    if (L == R)
    {
        cur_node->sum = array[L];
        cur_node->left = NULL;
        cur_node->right = NULL;
        return;
    }
    cur_node->left = new Node;
    cur_node->right = new Node;

    build(array, cur_node->left, L, (L + R) / 2);
    build(array, cur_node->right, (L + R) / 2 + 1, R);

    cur_node->sum = cur_node->left->sum + cur_node->right->sum;

    return;
}

int query(Node *cur_node, int start, int end)
{
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (R < start || L > end)
        return 0;

    if (start <= L && end >= R)
        return cur_node->sum;

    int left_index = query(cur_node->left, start, end);
    int right_index = query(cur_node->right, start, end);

    return left_index + right_index;
}

void clearMem(Node *cur_node)
{
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (L != R)
    {
        clearMem(cur_node->left);
        clearMem(cur_node->right);
    }
    delete cur_node;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> array(n);
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> array[i];
    }

    Node *root = new Node();
    build(array, root, 0, n - 1);

    int numQueries;
    cout << "Enter the number of queries: ";
    cin >> numQueries;

    cout << "Enter the intervals for each query in the format [start end]:\n";
    for (int i = 0; i < numQueries; ++i)
    {
        int start, end;
        cout << "Query " << i + 1 << ": ";
        cin >> start >> end;

        cout << "The sum in the interval [" << start << ", " << end << "] is " << query(root, start, end) << '\n';
    }

    clearMem(root);
    return 0;
}


//tries opeations


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ALPHABET_SIZE 26

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node)
    {
        node->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}
bool isLeafNode(struct TrieNode *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i])
            return false;
    return true;
}
void insert(struct TrieNode *root, const char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->isEndOfWord = true;
}
bool search(struct TrieNode *root, const char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            return false;
        current = current->children[index];
    }
    return (current != NULL && current->isEndOfWord);
}
bool delete(struct TrieNode *root, const char *word, int depth)
{
    if (!root)
        return false;
    if (depth == strlen(word))
    {
        if (root->isEndOfWord)

        {
            root->isEndOfWord = false;
            return isLeafNode(root);
        }
        return false;
    }
    int index = word[depth] - 'a';
    if (delete (root->children[index], word, depth + 1))
    {
        free(root->children[index]);
        root->children[index] = NULL;
        return isLeafNode(root) && !root->isEndOfWord;
    }
    return false;
}
void menu()
{
    printf("\nTrie Menu:\n");
    printf("1.Insert a word\n");
    printf("2.Search for a word\n");
    printf("3.Delete a word\n");
    printf("4.Exit\n");
    printf("Enter your choice: ");
}
int main()
{
    struct TrieNode *root = createNode();
    int choice;
    char word[50];
    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a word to insert: ");
            scanf("%s", word);
            insert(root, word);
            printf("%s inserted into the Trie.\n", word);
            break;
        case 2:
            printf("Enter a word to search: ");
            scanf("%s", word);
            if (search(root, word))
                printf("%s found in the Trie.\n", word);
            else
                printf("%s not found in the Trie.\n", word);
            break;
        case 3:
            printf("Enter a word to delete: ");
            scanf("%s", word);
            if (delete (root, word, 0))
                printf("%s deleted from the Trie.\n", word);
            else
                printf("%s not found in the Trie.\n", word);
            break;
        case 4:

            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}


//fibo




#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
  int key;
  int degree;
  struct _NODE *left_sibling;
  struct _NODE *right_sibling;
  struct _NODE *parent;
  struct _NODE *child;
  bool mark;
  bool visited;
} NODE;

typedef struct fibanocci_heap {
  int n;
  NODE *min;
  int phi;
  int degree;
} FIB_HEAP;

FIB_HEAP *make_fib_heap();
void insertion(FIB_HEAP *H, NODE *new, int val);
NODE *extract_min(FIB_HEAP *H);
void consolidate(FIB_HEAP *H);
void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x);
NODE *find_min_node(FIB_HEAP *H);
void decrease_key(FIB_HEAP *H, NODE *node, int key);
void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE *parent_node);
void cascading_cut(FIB_HEAP *H, NODE *parent_node);
void Delete_Node(FIB_HEAP *H, int dec_key);

FIB_HEAP *make_fib_heap() {
  FIB_HEAP *H;
  H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
  H->n = 0;
  H->min = NULL;
  H->phi = 0;
  H->degree = 0;
  return H;
}

// Printing the heap
void print_heap(NODE *n) {
  NODE *x;
  for (x = n;; x = x->right_sibling) {
    if (x->child == NULL) {
      printf("node with no child (%d) \n", x->key);
    } else {
      printf("NODE(%d) with child (%d)\n", x->key, x->child->key);
      print_heap(x->child);
    }
    if (x->right_sibling == n) {
      break;
    }
  }
}

// Inserting nodes
void insertion(FIB_HEAP *H, NODE *new, int val) {
  new = (NODE *)malloc(sizeof(NODE));
  new->key = val;
  new->degree = 0;
  new->mark = false;
  new->parent = NULL;
  new->child = NULL;
  new->visited = false;
  new->left_sibling = new;
  new->right_sibling = new;
  if (H->min == NULL) {
    H->min = new;
  } else {
    H->min->left_sibling->right_sibling = new;
    new->right_sibling = H->min;
    new->left_sibling = H->min->left_sibling;
    H->min->left_sibling = new;
    if (new->key < H->min->key) {
      H->min = new;
    }
  }
  (H->n)++;
}

// Find min node
NODE *find_min_node(FIB_HEAP *H) {
  if (H == NULL) {
    printf(" \n Fibonacci heap not yet created \n");
    return NULL;
  } else
    return H->min;
}

// Union operation
FIB_HEAP *unionHeap(FIB_HEAP *H1, FIB_HEAP *H2) {
  FIB_HEAP *Hnew;
  Hnew = make_fib_heap();
  Hnew->min = H1->min;

  NODE *temp1, *temp2;
  temp1 = Hnew->min->right_sibling;
  temp2 = H2->min->left_sibling;

  Hnew->min->right_sibling->left_sibling = H2->min->left_sibling;
  Hnew->min->right_sibling = H2->min;
  H2->min->left_sibling = Hnew->min;
  temp2->right_sibling = temp1;

  if ((H1->min == NULL) || (H2->min != NULL && H2->min->key < H1->min->key))
    Hnew->min = H2->min;
  Hnew->n = H1->n + H2->n;
  return Hnew;
}

// Calculate the degree
int cal_degree(int n) {
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }
  return count;
}

// Consolidate function
void consolidate(FIB_HEAP *H) {
  int degree, i, d;
  degree = cal_degree(H->n);
  NODE *A[degree], *x, *y, *z;
  for (i = 0; i <= degree; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->key > y->key) {
        NODE *exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      fib_heap_link(H, y, x);
      if (y->right_sibling == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right_sibling;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < degree; i++) {
    if (A[i] != NULL) {
      A[i]->left_sibling = A[i];
      A[i]->right_sibling = A[i];
      if (H->min == NULL) {
        H->min = A[i];
      } else {
        H->min->left_sibling->right_sibling = A[i];
        A[i]->right_sibling = H->min;
        A[i]->left_sibling = H->min->left_sibling;
        H->min->left_sibling = A[i];
        if (A[i]->key < H->min->key) {
          H->min = A[i];
        }
      }
      if (H->min == NULL) {
        H->min = A[i];
      } else if (A[i]->key < H->min->key) {
        H->min = A[i];
      }
    }
  }
}

// Linking
void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x) {
  y->right_sibling->left_sibling = y->left_sibling;
  y->left_sibling->right_sibling = y->right_sibling;

  if (x->right_sibling == x)
    H->min = x;

  y->left_sibling = y;
  y->right_sibling = y;
  y->parent = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right_sibling = x->child;
  y->left_sibling = x->child->left_sibling;
  x->child->left_sibling->right_sibling = y;
  x->child->left_sibling = y;
  if ((y->key) < (x->child->key))
    x->child = y;

  (x->degree)++;
}

// Extract min
NODE *extract_min(FIB_HEAP *H) {
  if (H->min == NULL)
    printf("\n The heap is empty");
  else {
    NODE *temp = H->min;
    NODE *pntr;
    pntr = temp;
    NODE *x = NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        pntr = x->right_sibling;
        (H->min->left_sibling)->right_sibling = x;
        x->right_sibling = H->min;
        x->left_sibling = H->min->left_sibling;
        H->min->left_sibling = x;
        if (x->key < H->min->key)
          H->min = x;
        x->parent = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->left_sibling)->right_sibling = temp->right_sibling;
    (temp->right_sibling)->left_sibling = temp->left_sibling;
    H->min = temp->right_sibling;

    if (temp == temp->right_sibling && temp->child == NULL)
      H->min = NULL;
    else {
      H->min = temp->right_sibling;
      consolidate(H);
    }
    H->n = H->n - 1;
    return temp;
  }
  return H->min;
}

void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE *parent_node) {
  NODE *temp_parent_check;

  if (node_to_be_decrease == node_to_be_decrease->right_sibling)
    parent_node->child = NULL;

  node_to_be_decrease->left_sibling->right_sibling = node_to_be_decrease->right_sibling;
  node_to_be_decrease->right_sibling->left_sibling = node_to_be_decrease->left_sibling;
  if (node_to_be_decrease == parent_node->child)
    parent_node->child = node_to_be_decrease->right_sibling;
  (parent_node->degree)--;

  node_to_be_decrease->left_sibling = node_to_be_decrease;
  node_to_be_decrease->right_sibling = node_to_be_decrease;
  H->min->left_sibling->right_sibling = node_to_be_decrease;
  node_to_be_decrease->right_sibling = H->min;
  node_to_be_decrease->left_sibling = H->min->left_sibling;
  H->min->left_sibling = node_to_be_decrease;

  node_to_be_decrease->parent = NULL;
  node_to_be_decrease->mark = false;
}

void cascading_cut(FIB_HEAP *H, NODE *parent_node) {
  NODE *aux;
  aux = parent_node->parent;
  if (aux != NULL) {
    if (parent_node->mark == false) {
      parent_node->mark = true;
    } else {
      cut(H, parent_node, aux);
      cascading_cut(H, aux);
    }
  }
}

void decrease_key(FIB_HEAP *H, NODE *node_to_be_decrease, int new_key) {
  NODE *parent_node;
  if (H == NULL) {
    printf("\n FIbonacci heap not created ");
    return;
  }
  if (node_to_be_decrease == NULL) {
    printf("Node is not in the heap");
  }

  else {
    if (node_to_be_decrease->key < new_key) {
      printf("\n Invalid new key for decrease key operation \n ");
    } else {
      node_to_be_decrease->key = new_key;
      parent_node = node_to_be_decrease->parent;
      if ((parent_node != NULL) && (node_to_be_decrease->key < parent_node->key)) {
        printf("\n cut called");
        cut(H, node_to_be_decrease, parent_node);
        printf("\n cascading cut called");
        cascading_cut(H, parent_node);
      }
      if (node_to_be_decrease->key < H->min->key) {
        H->min = node_to_be_decrease;
      }
    }
  }
}

void *find_node(FIB_HEAP *H, NODE *n, int key, int new_key) {
  NODE *find_use = n;
  NODE *f = NULL;
  find_use->visited = true;
  if (find_use->key == key) {
    find_use->visited = false;
    f = find_use;
    decrease_key(H, f, new_key);
  }
  if (find_use->child != NULL) {
    find_node(H, find_use->child, key, new_key);
  }
  if ((find_use->right_sibling->visited != true)) {
    find_node(H, find_use->right_sibling, key, new_key);
  }

  find_use->visited = false;
}

FIB_HEAP *insertion_procedure() {
  FIB_HEAP *temp;
  int no_of_nodes, ele, i;
  NODE *new_node;
  temp = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
  temp = NULL;
  if (temp == NULL) {
    temp = make_fib_heap();
  }
  printf(" \n enter number of nodes to be insert = ");
  scanf("%d", &no_of_nodes);
  for (i = 1; i <= no_of_nodes; i++) {
    printf("\n node %d and its key value = ", i);
    scanf("%d", &ele);
    insertion(temp, new_node, ele);
  }
  return temp;
}
void Delete_Node(FIB_HEAP *H, int dec_key) {
  NODE *p = NULL;
  find_node(H, H->min, dec_key, -5000);
  p = extract_min(H);
  if (p != NULL)
    printf("\n Node deleted");
  else
    printf("\n Node not deleted:some error");
}

int main(int argc, char **argv) {
  NODE *new_node, *min_node, *extracted_min, *node_to_be_decrease, *find_use;
  FIB_HEAP *heap, *h1, *h2;
  int operation_no, new_key, dec_key, ele, i, no_of_nodes;
  heap = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
  heap = NULL;
  while (1) {
    printf(" \n Operations \n 1. Create Fibonacci heap \n 2. Insert nodes into fibonacci heap \n 3. Find min \n 4. Union \n 5. Extract min \n 6. Decrease key \n 7.Delete node \n 8. print heap \n 9. exit \n enter operation_no = ");
    scanf("%d", &operation_no);

    switch (operation_no) {
      case 1:
        heap = make_fib_heap();
        break;

      case 2:
        if (heap == NULL) {
          heap = make_fib_heap();
        }
        printf(" enter number of nodes to be insert = ");
        scanf("%d", &no_of_nodes);
        for (i = 1; i <= no_of_nodes; i++) {
          printf("\n node %d and its key value = ", i);
          scanf("%d", &ele);
          insertion(heap, new_node, ele);
        }
        break;

      case 3:
        min_node = find_min_node(heap);
        if (min_node == NULL)
          printf("No minimum value");
        else
          printf("\n min value = %d", min_node->key);
        break;

      case 4:
        if (heap == NULL) {
          printf("\n no FIbonacci heap created \n ");
          break;
        }
        h1 = insertion_procedure();
        heap = unionHeap(heap, h1);
        printf("Unified Heap:\n");
        print_heap(heap->min);
        break;

      case 5:
        if (heap == NULL)
          printf("Empty Fibonacci heap");
        else {
          extracted_min = extract_min(heap);
          printf("\n min value = %d", extracted_min->key);
          printf("\n Updated heap: \n");
          print_heap(heap->min);
        }
        break;

      case 6:
        if (heap == NULL)
          printf("Fibonacci heap is empty");
        else {
          printf(" \n node to be decreased = ");
          scanf("%d", &dec_key);
          printf(" \n enter the new key = ");
          scanf("%d", &new_key);
          find_use = heap->min;
          find_node(heap, find_use, dec_key, new_key);
          printf("\n Key decreased- Corresponding heap:\n");
          print_heap(heap->min);
        }
        break;
      case 7:
        if (heap == NULL)
          printf("Fibonacci heap is empty");
        else {
          printf(" \n Enter node key to be deleted = ");
          scanf("%d", &dec_key);
          Delete_Node(heap, dec_key);
          printf("\n Node Deleted- Corresponding heap:\n");
          print_heap(heap->min);
          break;
        }
      case 8:
        print_heap(heap->min);
        break;

      case 9:
        free(new_node);
        free(heap);
        exit(0);

      default:
        printf("Invalid choice ");
    }
  }
}
