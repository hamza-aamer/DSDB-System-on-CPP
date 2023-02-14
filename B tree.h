// Deleting a key from a B-tree in C++

#include <iostream>
#include <vector>
using namespace std;

struct BTreeNode {
     node* keys;
     int t;
     BTreeNode** C;
     int n;
     bool leaf;

     BTreeNode(int _t, bool _leaf);

     void traverse();

     void BTreePointSearchID(int id);
     void BTreePointSearchDR(int id);
     void BTreePointSearchD(int id);
     void BTreePointSearchYear(int id);
     void BTreePointSearchCause(string id);
     void BTreePointSearchState(string id);

     void BTreeRangeSearchID(int idhigh,int idlow);
     void BTreeRangeSearchDR(int idhigh, int idlow);
     void BTreeRangeSearchD(int idhigh, int idlow);
     void BTreeRangeSearchYear(int idhigh, int idlow);

     void BTreePointSearchwhereYS(int key, string state)
     {
          int i;
          for (i = 0; i < n; i++) {
               if (leaf == false)
                    C[i]->BTreePointSearchwhereYS(key,state);
               if (keys[i].year == key && keys[i].state == state) {
                    cout << " " << keys[i];
               }
          }

          if (leaf == false)
               C[i]->BTreePointSearchwhereYS(key,state);
     }

     void BTreePointSearchwhereYC(int key, string state)
     {
          int i;
          for (i = 0; i < n; i++) {
               if (leaf == false)
                    C[i]->BTreePointSearchwhereYS(key, state);
               if (keys[i].year == key && keys[i].cause == state) {
                    cout << " " << keys[i];
               }
          }

          if (leaf == false)
               C[i]->BTreePointSearchwhereYS(key, state);
     }

     void BTreeUpdateQuery(int id);

     void BTreeGetNodes(vector<node>& Nodes) {
          int i;
          for (i = 0; i < n; i++) {
               if (leaf == false)
                    C[i]->BTreeGetNodes(Nodes);
               Nodes.push_back(keys[i]);
          }

          if (leaf == false)
               C[i]->BTreeGetNodes(Nodes);
     }

     void BTreeInOrderTransversal();

     int findKey(int k);
     void insertNonFull(node k);
     void splitChild(int i, BTreeNode* y);
     void deletion(int k);
     void removeFromLeaf(int idx);
     void removeFromNonLeaf(int idx);
     node getPredecessor(int idx);
     node getSuccessor(int idx);
     void fill(int idx);
     void borrowFromPrev(int idx);
     void borrowFromNext(int idx);
     void merge(int idx);
     
};

class BTree {
public:
     BTreeNode* root;
     int t;


     BTree(int _t) {
          root = NULL;
          t = _t;
     }

     void BTreeInOrderTransversal() {
          if (root != NULL)
               root->BTreeInOrderTransversal();
     }

     void insertion(node k);

     void deletion(int k);
};

// B tree node
BTreeNode::BTreeNode(int t1, bool leaf1) {
     t = t1;
     leaf = leaf1;

     keys = new node[2 * t - 1];
     C = new BTreeNode * [2 * t];

     n = 0;
}

// Find the key
int BTreeNode::findKey(int k) {
     int idx = 0;
     while (idx < n && keys[idx].id < k)
          idx++;
     return idx;
}

// Deletion operation
void BTreeNode::deletion(int k) {
     int idx = findKey(k);

     if (idx < n && keys[idx].id == k) {
          if (leaf)
               removeFromLeaf(idx);
          else
               removeFromNonLeaf(idx);
     }
     else {
          if (leaf) {
               cout << "The key " << k << " is does not exist in the tree\n";
               return;
          }

          bool flag = ((idx == n) ? true : false);

          if (C[idx]->n < t)
               fill(idx);

          if (flag && idx > n)
               C[idx - 1]->deletion(k);
          else
               C[idx]->deletion(k);
     }
     return;
}

// Remove from the leaf
void BTreeNode::removeFromLeaf(int idx) {
     for (int i = idx + 1; i < n; ++i)
          keys[i - 1] = keys[i];

     n--;

     return;
}

// Delete from non leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
     node k = keys[idx];

     if (C[idx]->n >= t) {
          node pred = getPredecessor(idx);
          keys[idx] = pred;
          C[idx]->deletion(pred.id);
     }

     else if (C[idx + 1]->n >= t) {
          node succ = getSuccessor(idx);
          keys[idx] = succ;
          C[idx + 1]->deletion(succ.id);
     }

     else {
          merge(idx);
          C[idx]->deletion(k.id);
     }
     return;
}

node BTreeNode::getPredecessor(int idx) {
     BTreeNode* cur = C[idx];
     while (!cur->leaf)
          cur = cur->C[cur->n];

     return cur->keys[cur->n - 1];
}

node BTreeNode::getSuccessor(int idx) {
     BTreeNode* cur = C[idx + 1];
     while (!cur->leaf)
          cur = cur->C[0];

     return cur->keys[0];
}

void BTreeNode::fill(int idx) {
     if (idx != 0 && C[idx - 1]->n >= t)
          borrowFromPrev(idx);

     else if (idx != n && C[idx + 1]->n >= t)
          borrowFromNext(idx);

     else {
          if (idx != n)
               merge(idx);
          else
               merge(idx - 1);
     }
     return;
}

// Borrow from previous
void BTreeNode::borrowFromPrev(int idx) {
     BTreeNode* child = C[idx];
     BTreeNode* sibling = C[idx - 1];

     for (int i = child->n - 1; i >= 0; --i)
          child->keys[i + 1] = child->keys[i];

     if (!child->leaf) {
          for (int i = child->n; i >= 0; --i)
               child->C[i + 1] = child->C[i];
     }

     child->keys[0] = keys[idx - 1];

     if (!child->leaf)
          child->C[0] = sibling->C[sibling->n];

     keys[idx - 1] = sibling->keys[sibling->n - 1];

     child->n += 1;
     sibling->n -= 1;

     return;
}

// Borrow from the next
void BTreeNode::borrowFromNext(int idx) {
     BTreeNode* child = C[idx];
     BTreeNode* sibling = C[idx + 1];

     child->keys[(child->n)] = keys[idx];

     if (!(child->leaf))
          child->C[(child->n) + 1] = sibling->C[0];

     keys[idx] = sibling->keys[0];

     for (int i = 1; i < sibling->n; ++i)
          sibling->keys[i - 1] = sibling->keys[i];

     if (!sibling->leaf) {
          for (int i = 1; i <= sibling->n; ++i)
               sibling->C[i - 1] = sibling->C[i];
     }

     child->n += 1;
     sibling->n -= 1;

     return;
}

// Merge
void BTreeNode::merge(int idx) {
     BTreeNode* child = C[idx];
     BTreeNode* sibling = C[idx + 1];

     child->keys[t - 1] = keys[idx];

     for (int i = 0; i < sibling->n; ++i)
          child->keys[i + t] = sibling->keys[i];

     if (!child->leaf) {
          for (int i = 0; i <= sibling->n; ++i)
               child->C[i + t] = sibling->C[i];
     }

     for (int i = idx + 1; i < n; ++i)
          keys[i - 1] = keys[i];

     for (int i = idx + 2; i <= n; ++i)
          C[i - 1] = C[i];

     child->n += sibling->n + 1;
     n--;

     delete (sibling);
     return;
}

// Insertion operation
void BTree::insertion(node k) {
     if (root == NULL) {
          root = new BTreeNode(t, true);
          root->keys[0] = k;
          root->n = 1;
     }
     else {
          if (root->n == 2 * t - 1) {
               BTreeNode* s = new BTreeNode(t, false);

               s->C[0] = root;

               s->splitChild(0, root);

               int i = 0;
               if (s->keys[0].id < k.id)
                    i++;
               s->C[i]->insertNonFull(k);

               root = s;
          }
          else
               root->insertNonFull(k);
     }
}

// Insertion non full
void BTreeNode::insertNonFull(node k) {
     int i = n - 1;

     if (leaf == true) {
          while (i >= 0 && keys[i].id > k.id) {
               keys[i + 1] = keys[i];
               i--;
          }

          keys[i + 1] = k;
          n = n + 1;
     }
     else {
          while (i >= 0 && keys[i].id > k.id)
               i--;

          if (C[i + 1]->n == 2 * t - 1) {
               splitChild(i + 1, C[i + 1]);

               if (keys[i + 1].id < k.id)
                    i++;
          }
          C[i + 1]->insertNonFull(k);
     }
}

// Split child
void BTreeNode::splitChild(int i, BTreeNode* y) {
     BTreeNode* z = new BTreeNode(y->t, y->leaf);
     z->n = t - 1;

     for (int j = 0; j < t - 1; j++)
          z->keys[j] = y->keys[j + t];

     if (y->leaf == false) {
          for (int j = 0; j < t; j++)
               z->C[j] = y->C[j + t];
     }

     y->n = t - 1;

     for (int j = n; j >= i + 1; j--)
          C[j + 1] = C[j];

     C[i + 1] = z;

     for (int j = n - 1; j >= i; j--)
          keys[j + 1] = keys[j];

     keys[i] = y->keys[t - 1];

     n = n + 1;
}

// Traverse
void BTreeNode::traverse() {
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->traverse();
          cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->traverse();
}

// Delete Operation
void BTree::deletion(int k) {
     if (!root) {
          cout << "The tree is empty\n";
          return;
     }

     root->deletion(k);

     if (root->n == 0) {
          BTreeNode* tmp = root;
          if (root->leaf)
               root = NULL;
          else
               root = root->C[0];

          delete tmp;
     }
     return;
}


//Point searchs
void BTreeNode::BTreePointSearchID(int key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchID(key);
          if (keys[i].id == key) {
               cout << " " << keys[i];
          }
     }

     if (leaf == false)
          C[i]->BTreePointSearchID(key);
}

void BTreeNode::BTreePointSearchDR(int key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchDR(key);
          if (keys[i].DR == key)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreePointSearchDR(key);
}

void BTreeNode::BTreePointSearchYear(int key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchYear(key);
          if (keys[i].year == key)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreePointSearchYear(key);
}

void BTreeNode::BTreePointSearchD(int key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchD(key);
          if (keys[i].deaths == key)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreePointSearchD(key);
}

void BTreeNode::BTreePointSearchState(string key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchState(key);
          if (keys[i].cause == key)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreePointSearchState(key);
}

void BTreeNode::BTreePointSearchCause(string key)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreePointSearchCause(key);
          if (keys[i].cause == key)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreePointSearchCause(key);
}

//Ranger searchs
void BTreeNode::BTreeRangeSearchID(int high,int low)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeRangeSearchID(high,low);
          if (keys[i].id >= low && keys[i].id<=high)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreeRangeSearchID(high, low);
}

void BTreeNode::BTreeRangeSearchDR(int high, int low)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeRangeSearchDR(high, low);
          if (keys[i].DR >= low && keys[i].DR <= high)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreeRangeSearchDR(high, low);
}

void BTreeNode::BTreeRangeSearchYear(int high, int low)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeRangeSearchYear(high, low);
          if (keys[i].year >= low && keys[i].year <= high)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreeRangeSearchYear(high, low);
}

void BTreeNode::BTreeRangeSearchD(int high, int low)
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeRangeSearchD(high, low);
          if (keys[i].deaths >= low && keys[i].deaths <= high)
               cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreeRangeSearchD(high, low);
}


//Triversals
void BTreeNode::BTreeInOrderTransversal()
{
     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeInOrderTransversal();
          cout << " " << keys[i];
     }

     if (leaf == false)
          C[i]->BTreeInOrderTransversal();
}

//Update Query
void BTreeNode::BTreeUpdateQuery(int ID)
{
     string cause;
     string state;

     int i;
     for (i = 0; i < n; i++) {
          if (leaf == false)
               C[i]->BTreeUpdateQuery(ID);
          if (keys[i].id == ID) {
               int temp;
               cout << keys[i];
               cout << "Select Query to Update:\n\t1-Year Of Death\n\t2-Cause of Death\n\t3-State\n\t4-No of Deaths\n\t5-Death Rate\n\t6-Go Back\nEnter Your Choice : ";
               cin >> temp;
               switch (temp) {
               case 1:
                    int year;
                    cout << "Enter New Year of Death : ";
                    cin >> year;
                    keys[i].year = year;
                    break;
               case 2:
                    cout << "Enter New Cause of Death : ";
                    cin >> cause;
                    keys[i].cause = cause;
                    break;
               case 3:
                    cout << "Enter New State of Death : ";
                    cin >> state;
                    keys[i].state= state;
                    break;
               case 4:
                    int deaths;
                    cout << "Enter New No of Death : ";
                    cin >> deaths;
                    keys[i].deaths = deaths;
                    break;
               case 5:
                    int DR;
                    cout << "Enter New Death Rate of Deaths : ";
                    cin >> DR;
                    keys[i].DR = DR;
                    break;
               case 6:
                    return;
                    break;
               }


               return;
          }
     }

     if (leaf == false)
          C[i]->BTreeUpdateQuery(ID);
}

