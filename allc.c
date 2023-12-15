//binarycounter
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

//bloomfilter
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILTER_SIZE 1000

typedef struct {
    char* array;
    int size;
} BloomFilter;

// Hash functions
unsigned int hash1(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash % FILTER_SIZE;
}

unsigned int hash2(const char* str) {
    unsigned int hash = 5381;
    while (*str) {
        hash = (hash * 33) ^ (*str++);
    }
    return hash % FILTER_SIZE;
}

unsigned int hash3(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 65599) + (*str++);
    }
    return hash % FILTER_SIZE;
}

BloomFilter* initializeFilter(int size) {
    BloomFilter* filter = (BloomFilter*)malloc(sizeof(BloomFilter));
    filter->array = (char*)calloc((size + 7) / 8, sizeof(char));
    filter->size = size;
    return filter;
}

void addElement(BloomFilter* filter, const char* element) {
    unsigned int index1 = hash1(element);
    unsigned int index2 = hash2(element);
    unsigned int index3 = hash3(element);

    filter->array[index1 / 8] |= (1 << (index1 % 8));
    filter->array[index2 / 8] |= (1 << (index2 % 8));
    filter->array[index3 / 8] |= (1 << (index3 % 8));
}

bool containsElement(BloomFilter* filter, const char* element) {
    unsigned int index1 = hash1(element);
    unsigned int index2 = hash2(element);
    unsigned int index3 = hash3(element);

    return (filter->array[index1 / 8] & (1 << (index1 % 8))) &&
           (filter->array[index2 / 8] & (1 << (index2 % 8))) &&
           (filter->array[index3 / 8] & (1 << (index3 % 8)));
}

int main() {
    BloomFilter* filter = initializeFilter(FILTER_SIZE);

    addElement(filter, "apple");
    addElement(filter, "orange");
    addElement(filter, "banana");

    printf("Contains 'apple': %s\n", containsElement(filter, "apple") ? "Yes" : "No");
    printf("Contains 'grape': %s\n", containsElement(filter, "grape") ? "Yes" : "No");
    printf("Contains 'banana': %s\n", containsElement(filter, "banana") ? "Yes" : "No");

    return 0;
}

//btree
#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct btreeNode {
  int item[MAX + 1], count;
  struct btreeNode *link[MAX + 1];
};

struct btreeNode *root;

// Node creation
struct btreeNode *createNode(int item, struct btreeNode *child) {
  struct btreeNode *newNode;
  newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  newNode->item[1] = item;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert
void insertValue(int item, int pos, struct btreeNode *node,
          struct btreeNode *child) {
  int j = node->count;
  while (j > pos) {
    node->item[j + 1] = node->item[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->item[j + 1] = item;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int item, int *pval, int pos, struct btreeNode *node,
         struct btreeNode *child, struct btreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->item[j - median] = node->item[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertValue(item, pos, node, child);
  } else {
    insertValue(item, pos - median, *newNode, child);
  }
  *pval = node->item[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value of node
int setNodeValue(int item, int *pval,
           struct btreeNode *node, struct btreeNode **child) {
  int pos;
  if (!node) {
    *pval = item;
    *child = NULL;
    return 1;
  }

  if (item < node->item[1]) {
    pos = 0;
  } else {
    for (pos = node->count;
       (item < node->item[pos] && pos > 1); pos--)
      ;
    if (item == node->item[pos]) {
      printf("Duplicates not allowed\n");
      return 0;
    }
  }
  if (setNodeValue(item, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertValue(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insertion(int item) {
  int flag, i;
  struct btreeNode *child;

  flag = setNodeValue(item, &i, root, &child);
  if (flag)
    root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct btreeNode *myNode, int pos) {
  struct btreeNode *dummy;
  dummy = myNode->link[pos];

  for (; dummy->link[0] != NULL;)
    dummy = dummy->link[0];
  myNode->item[pos] = dummy->item[1];
}

// Do rightshift
void rightShift(struct btreeNode *myNode, int pos) {
  struct btreeNode *x = myNode->link[pos];
  int j = x->count;

  while (j > 0) {
    x->item[j + 1] = x->item[j];
    x->link[j + 1] = x->link[j];
  }
  x->item[1] = myNode->item[pos];
  x->link[1] = x->link[0];
  x->count++;

  x = myNode->link[pos - 1];
  myNode->item[pos] = x->item[x->count];
  myNode->link[pos] = x->link[x->count];
  x->count--;
  return;
}

// Do leftshift
void leftShift(struct btreeNode *myNode, int pos) {
  int j = 1;
  struct btreeNode *x = myNode->link[pos - 1];

  x->count++;
  x->item[x->count] = myNode->item[pos];
  x->link[x->count] = myNode->link[pos]->link[0];

  x = myNode->link[pos];
  myNode->item[pos] = x->item[1];
  x->link[0] = x->link[1];
  x->count--;

  while (j <= x->count) {
    x->item[j] = x->item[j + 1];
    x->link[j] = x->link[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void mergeNodes(struct btreeNode *myNode, int pos) {
  int j = 1;
  struct btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

  x2->count++;
  x2->item[x2->count] = myNode->item[pos];
  x2->link[x2->count] = myNode->link[0];

  while (j <= x1->count) {
    x2->count++;
    x2->item[x2->count] = x1->item[j];
    x2->link[x2->count] = x1->link[j];
    j++;
  }

  j = pos;
  while (j < myNode->count) {
    myNode->item[j] = myNode->item[j + 1];
    myNode->link[j] = myNode->link[j + 1];
    j++;
  }
  myNode->count--;
  free(x1);
}

// Adjust the node
void adjustNode(struct btreeNode *myNode, int pos) {
  if (!pos) {
    if (myNode->link[1]->count > MIN) {
      leftShift(myNode, 1);
    } else {
      mergeNodes(myNode, 1);
    }
  } else {
    if (myNode->count != pos) {
      if (myNode->link[pos - 1]->count > MIN) {
        rightShift(myNode, pos);
      } else {
        if (myNode->link[pos + 1]->count > MIN) {
          leftShift(myNode, pos + 1);
        } else {
          mergeNodes(myNode, pos);
        }
      }
    } else {
      if (myNode->link[pos - 1]->count > MIN)
        rightShift(myNode, pos);
      else
        mergeNodes(myNode, pos);
    }
  }
}

// Traverse the tree
void traversal(struct btreeNode *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      traversal(myNode->link[i]);
      printf("%d ", myNode->item[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}

int main() {
  int item, ch;

  insertion(5);
  insertion(3);
  insertion(21);
  insertion(9);
  insertion(1);
  insertion(13);
  insertion(2);
  insertion(7);
  insertion(10);
  insertion(12);
  insertion(4);
  insertion(8);

  traversal(root);
}

//cuckoohashing
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 11  // Choose a prime number for better performance

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry* table1;
    Entry* table2;
    int size;
} CuckooHashTable;

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Initialize cuckoo hash table
CuckooHashTable* initCuckooHashTable(int size) {
    CuckooHashTable* cuckooTable = (CuckooHashTable*)malloc(sizeof(CuckooHashTable));
    cuckooTable->size = size;
    cuckooTable->table1 = (Entry*)calloc(size, sizeof(Entry));
    cuckooTable->table2 = (Entry*)calloc(size, sizeof(Entry));
    return cuckooTable;
}

// Insert key-value pair into the cuckoo hash table
bool insert(CuckooHashTable* cuckooTable, int key, int value);

// Search for a key in the cuckoo hash table
int search(CuckooHashTable* cuckooTable, int key);

// Print the cuckoo hash table
void printCuckooTable(CuckooHashTable* cuckooTable);

// Main function
int main() {
    CuckooHashTable* cuckooTable = initCuckooHashTable(TABLE_SIZE);

    // Example usage
    insert(cuckooTable, 5, 50);
    insert(cuckooTable, 2, 20);
    insert(cuckooTable, 8, 80);
    insert(cuckooTable, 9, 90);

    printCuckooTable(cuckooTable);

    int searchResult = search(cuckooTable, 2);
    if (searchResult != -1) {
        printf("Value for key 2: %d\n", searchResult);
    } else {
        printf("Key 2 not found.\n");
    }

    // Clean up
    free(cuckooTable->table1);
    free(cuckooTable->table2);
    free(cuckooTable);

    return 0;
}

bool insert(CuckooHashTable* cuckooTable, int key, int value) {
    int currentKey = key;
    int currentValue = value;

    for (int i = 0; i < cuckooTable->size; i++) {
        // Try inserting into the first table
        int hashIndex1 = hash1(currentKey);
        if (cuckooTable->table1[hashIndex1].key == 0) {
            cuckooTable->table1[hashIndex1].key = currentKey;
            cuckooTable->table1[hashIndex1].value = currentValue;
            return true;
        }

        // Swap with the current table entry and move to the other table
        Entry temp = cuckooTable->table1[hashIndex1];
        cuckooTable->table1[hashIndex1].key = currentKey;
        cuckooTable->table1[hashIndex1].value = currentValue;

        currentKey = temp.key;
        currentValue = temp.value;

        // Try inserting into the second table
        int hashIndex2 = hash2(currentKey);
        if (cuckooTable->table2[hashIndex2].key == 0) {
            cuckooTable->table2[hashIndex2].key = currentKey;
            cuckooTable->table2[hashIndex2].value = currentValue;
            return true;
        }

        // Swap with the current table entry and move to the other table
        temp = cuckooTable->table2[hashIndex2];
        cuckooTable->table2[hashIndex2].key = currentKey;
        cuckooTable->table2[hashIndex2].value = currentValue;

        currentKey = temp.key;
        currentValue = temp.value;
    }

    // Rehash and try again if insertion fails
    return false;
}

int search(CuckooHashTable* cuckooTable, int key) {
    int hashIndex1 = hash1(key);
    if (cuckooTable->table1[hashIndex1].key == key) {
        return cuckooTable->table1[hashIndex1].value;
    }

    int hashIndex2 = hash2(key);
    if (cuckooTable->table2[hashIndex2].key == key) {
        return cuckooTable->table2[hashIndex2].value;
    }

    return -1;  // Key not found
}

void printCuckooTable(CuckooHashTable* cuckooTable) {
    printf("Table 1:\n");
    for (int i = 0; i < cuckooTable->size; i++) {
        printf("[%d] -> %d\n", cuckooTable->table1[i].key, cuckooTable->table1[i].value);
    }

    printf("Table 2:\n");
    for (int i = 0; i < cuckooTable->size; i++) {
        printf("[%d] -> %d\n", cuckooTable->table2[i].key, cuckooTable->table2[i].value);
    }
}

//fibonacciheap
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

//interval tree
#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int low;
    int high;
} Interval;

typedef struct Node {
    Interval *interval;
    int max;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(Interval *interval) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->interval = interval;
    node->max = interval->high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, Interval *interval) {
    if (root == NULL) {
        return newNode(interval);
    }
    int low = root->interval->low;
    if (interval->low < low) {
        root->left = insert(root->left, interval);
    } else {
        root->right = insert(root->right, interval);
    }
    if (root->max < interval->high) {
        root->max = interval->high;
    }
    return root;
}

void overlapSearch(Node *root, Interval *interval) {
    if (root == NULL) {
        return;
    }
    if (root->interval->low <= interval->high && interval->low <= root->interval->high) {
        printf("Overlapping interval: [%d, %d]\n", root->interval->low, root->interval->high);
    }
    if (root->left != NULL && root->left->max >= interval->low) {
        overlapSearch(root->left, interval);
    }
    overlapSearch(root->right, interval);
}

int main() {
    Interval intervals[] = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};
    int n = sizeof(intervals) / sizeof(intervals[0]);
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, &intervals[i]);
    }
    Interval x = {6, 7};
    overlapSearch(root, &x);
    return 0;
}

//leftistheap
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

//rbt
#include <stdio.h>
#include <stdlib.h>

enum nodeColor {
  RED,
  BLACK
};

struct rbNode {
  int data, color;
  struct rbNode *link[2];
};

struct rbNode *root = NULL;

// Create a red-black tree
struct rbNode *createNode(int data) {
  struct rbNode *newnode;
  newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
  newnode->data = data;
  newnode->color = RED;
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}

// Insert an node
void insertion(int data) {
  struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
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
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
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
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Print the inorder traversal of the tree
void inorderTraversal(struct rbNode *node) {
  if (node) {
    inorderTraversal(node->link[0]);
    printf("%d  ", node->data);
    inorderTraversal(node->link[1]);
  }
  return;
}

// Driver code
int main() {
  int ch, data;
  while (1) {
    printf("1. Insertion\t2. Traverse\t3. Exit\n");
    printf("Enter your choice:");
    scanf("%d", &ch);
    switch (ch) {
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

//segment tree
#include <stdio.h>
#include <limits.h>

#define MAX 1000

int segmentTreeSum[MAX];
int segmentTreeMin[MAX];
int segmentTreeMax[MAX];

void buildSegmentTree(int arr[], int node, int start, int end) {
    if (start == end) {
        segmentTreeSum[node] = arr[start];
        segmentTreeMin[node] = arr[start];
        segmentTreeMax[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(arr, 2 * node, start, mid);
        buildSegmentTree(arr, 2 * node + 1, mid + 1, end);
        segmentTreeSum[node] = segmentTreeSum[2 * node] + segmentTreeSum[2 * node + 1];
        segmentTreeMin[node] = (segmentTreeMin[2 * node] < segmentTreeMin[2 * node + 1]) ? segmentTreeMin[2 * node] : segmentTreeMin[2 * node + 1];
        segmentTreeMax[node] = (segmentTreeMax[2 * node] > segmentTreeMax[2 * node + 1]) ? segmentTreeMax[2 * node] : segmentTreeMax[2 * node + 1];
    }
}

int querySum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return segmentTreeSum[node];
    }
    int mid = (start + end) / 2;
    return querySum(2 * node, start, mid, l, r) + querySum(2 * node + 1, mid + 1, end, l, r);
}

int queryMin(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MAX;
    }
    if (l <= start && end <= r) {
        return segmentTreeMin[node];
    }
    int mid = (start + end) / 2;
    return (queryMin(2 * node, start, mid, l, r) < queryMin(2 * node + 1, mid + 1, end, l, r)) ? queryMin(2 * node, start, mid, l, r) : queryMin(2 * node + 1, mid + 1, end, l, r);
}

int queryMax(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MIN;
    }
    if (l <= start && end <= r) {
        return segmentTreeMax[node];
    }
    int mid = (start + end) / 2;
    return (queryMax(2 * node, start, mid, l, r) > queryMax(2 * node + 1, mid + 1, end, l, r)) ? queryMax(2 * node, start, mid, l, r) : queryMax(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = 6;

    buildSegmentTree(arr, 1, 0, n - 1);

    printf("Sum of elements in range [2, 3] is %d\n", querySum(1, 0, n - 1, 2, 3));
    printf("Minimum of elements in range [1, 3] is %d\n", queryMin(1, 0, n - 1, 1, 3));
    printf("Maximum of elements in range [1, 5] is %d\n", queryMax(1, 0, n - 1, 1, 5));

    return 0;
}

//standard trie
#include <stdio.h>
#include <stdlib.h>
struct trie
{
	struct trie *alpha[26];
	int wordflag;
};
typedef struct trie trie;
trie *root;
trie *createnode()
{
	trie *node = (trie *)malloc(sizeof(trie));

	for (int i = 0; i < 26; i++)
		node->alpha[i] = NULL;
		node->wordflag = 0;
	return node;
}
int search_insert_delete(trie *node, char *word, char mode)
{
	if (!node)
	{
		if (mode == 'i')
		{
			printf("\nCreating root node...");
			node = createnode();
			root = node;
		}
		else if(mode == 's' || mode == 'd')
		{
			printf("\nRoot node does not exist.");
			return 1;
		}
	}
	while (*word)
	{
		int index = (*word | ('A' ^ 'a')) - 'a';
		if (!node->alpha[index])
		{
			if (mode == 'i')
			{
				printf("\nCreating node for character '%c'...", *word);
				node->alpha[index] = createnode();
			}
			else if(mode == 's' || mode == 'd')
			{
				printf("\nNo node found for character '%c'.", *word);
				return 1;
			}
		}
		node = node->alpha[index];
		word++;
	}
	if (!node->wordflag)
	{
		if (mode == 'i')
		{
			printf("\nSetting wordflag...");
			node->wordflag = 1;
			return 0;
		}
		else if(mode == 's' || mode == 'd')
		{
			printf("\nWordflag not set.");
			return 1;
		}
	}
	else if(mode == 'd')
	{
		printf("\nResetting wordflag...");
		node->wordflag = 0;
		return 0;
	}
	else return 0;
}
void main()
{
	int ch;
	do
	{
		char word[10];
		int result;
		printf("\n\n1. Enter into trie \n2. Search from trie \n3. Delete from trie \n4. Exit \n\nEnter your choice: ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("\nEnter the word to be inserted: ");
			scanf("%s", word);
			result = search_insert_delete(root, word, 'i');
			if (!result)
			{
				printf("\nInsertion successful!");
			}
			break;
		case 2:
			printf("\nEnter the word to be searched: ");
			scanf("%s", word);
			result = search_insert_delete(root, word, 's');
			if (result == 0)
				printf("\nSearchsuccessful!\nThe word is present in the trie.");
			else
				printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
			break;
		case 3:
			printf("\nEnter the word to be deleted: ");
			scanf("%s", word);
			result = search_insert_delete(root, word, 'd');
			if (result == 0)
				printf("\nDeletion successful!");
			else printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (ch != 4);
}