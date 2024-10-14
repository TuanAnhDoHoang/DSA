#include<iostream>
#include<cstring>
#include<algorithm>
#include<random>
#include<stack>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }
};    
class bin_tree{
public:
    Node* root;
    bin_tree(int val){
        this->root = new Node(val);
    }
    void balance_state(Node* currNode){
    }
    void pushNode(Node* currNode ,int val){
        if(currNode == NULL) {
            currNode = new Node(val);
        }
        else{
            if(val < currNode->data){
//                if(currNode->left == NULL) currNode->left = new Node(val);
//                else pushNode(currNode->left, val);
                pushNode(currNode->left, val);
            }
            else{
               // if(currNode->right == NULL) currNode->right = new Node(val);
               // else pushNode(currNode->right, val);
                pushNode(currNode->right, val);
            }
        }
    }
    void print_tree(Node* currNode){
        if(currNode == NULL) return;
        else{
            cout<<currNode->data<<" ";
            print_tree(currNode->left);
            print_tree(currNode->right);
        }
    }
    Node* findNode(int val, Node* currNode){
        if(currNode == NULL){
            cout<<"\nNot found the node has value: "<<val;
            return NULL;
        }
        if(currNode->data == val){
            printf("\nThe node value %d has been found! ", val);
            return currNode;
        }
        else{
            if(val < currNode->data ) findNode(val, currNode->left);
            else if(val > currNode->data) findNode(val, currNode->right);
        }
    }
    Node* find_parent(int val, Node* parent, Node* currNode){
        if(this->root->data == val){
            cout<<"\nThis is root which has no parent! ";
            return NULL;
        }
        else if(currNode == NULL){
            cout<<"\nThis node don't exist";
            return NULL;
        }
        else if(currNode->data == val){
            cout<<"\nParent of this node has been found! ";
            return parent;
        }
        else{
            if(val < currNode->data){
                find_parent(val, currNode, currNode->left);
            }
            else{
                find_parent(val, currNode, currNode->right);
            } 
        }
    }
    Node* delNode(int val, Node* currNode){
       if(currNode == NULL) return NULL;
       //find the match node with val
       if(val < currNode->data){
            delNode(val, currNode->left);
       }
       else if(val > currNode->data){
            delNode(val, currNode->right);
       }
       else{
            Node* p = find_parent(currNode->data, NULL, this->root);
       //if match
            if(currNode->left == NULL){
                Node*temp = currNode->right;
                //Node* p = find_parent(currNode->data, NULL, this->root);
                if(p != NULL){
                    if(currNode->data > p->data) p->right = temp;
                    else p->left = temp;
                    delete(currNode);
                    return temp;
                }
           }
            if(currNode->right == NULL){
                Node*temp = currNode->left;
                //Node* p = find_parent(currNode->data, NULL, this->root);
                if(p!= NULL){
                    if(currNode->data > p->data) p->right = temp;
                    else p->left = temp;
                    delete(currNode);
                    return temp;
                }
           }
           //Get the most left of this node's right child  
            Node* successor = currNode->right;
            while(successor != NULL && successor->left!=NULL){
                successor = successor->left;
            }
            //Node* p = find_parent(currNode->data, NULL, this->root);
            if(p != NULL){
                int t = successor->data;
                delNode(successor->data, currNode->right);
                currNode->data = t;
                //delNode(65, currNode->right);
            }
       }
    }
    void Level_print(int n){
        vector<Node*> v;
        v.push_back(this->root);
        for (int ind = 0; ind<n; ind ++){
            if(v[ind]->left  != NULL) v.push_back(v[ind]->left);
            if(v[ind]->right != NULL) v.push_back(v[ind]->right);
        }
        
        cout<<"\nLevel travelling Binary tree: ";
        for(int i=0; i<v.size(); i++){
            cout<<v[i]->data<<" ";
        }
    }
    Node* most_deep_leaf(int n, int d[]){
        vector<Node*> v;
        v.push_back(this->root);
        int level = 0;
        int state = 0;
        for (int ind = 0; ind<n; ind ++){
            if(v[ind] != NULL){
                state++;
                if(state > d[level]){
                    state = 1;
                    level++;
                }
                if(v[ind]->left  != NULL) v.push_back(v[ind]->left);
                if(v[ind]->right != NULL) v.push_back(v[ind]->right);
            }
        }
        printf("\nMost deep leaf at level %d", level);
        return v[v.size() - 1];
    }
    Node* highest_leaf(int n, int d[]){
        vector<Node*>pool;
        pool.push_back(this->root);
        int is_leaf = 0;
        int level = 0; 
        int state = 0;
        for(int ind =0 ; ind < n; ind++){
            if(pool[ind] != NULL){
                state++;
                if(state > d[level]){
                    state = 1;
                    level++;
                } 
                if(pool[ind]->left != NULL)  {
                    pool.push_back(pool[ind]->left);
                    is_leaf++;
                }
                if(pool[ind]->right != NULL) {
                    pool.push_back(pool[ind]->right);
                    is_leaf++;
                }
                if(is_leaf == 0){
                    printf("\nhighest leaf at level %d", level);
                    return pool[ind];
                }
                else is_leaf = 0;
            }
        }
    }
    void count_levelNode(int d[], int n, int level, int index, Node* currNode) {
        d[level]++;
        if(currNode->left != NULL){
            count_levelNode(d, n, level+1, index*2, currNode->left);
        }

        if(currNode->right != NULL){
            count_levelNode(d, n, level+1, index*2 + 1, currNode->right);
        }
    }
    void rotate_left(Node* node1, Node* node2){
//       Node* father_1 =  this->find_parent(node1->data, NULL, this->root);
        if(node1 == this->root){
            Node* node2_l = node2->left;
            node2->left = node1;
            node1->right = node2_l;
            this->root = node2;
        }
          else{
            Node* father_1 = this->find_parent(node1->data, NULL, this->root);
            if(father_1->right == node1){
                father_1->right = node2;
                Node* temp = node2->left;
                node2->left = node1;
                node1->right = temp;
            }
            else{
                father_1->left = node2;
                Node* temp = node2->left;
                node2->left = node1;
                node1->right = temp;
            }
        }
    }
    void rotate_right(Node* node1, Node* node2){
//       Node* father_1 =  this->find_parent(node1->data, NULL, this->root);
        if(node1 == this->root){
            Node* node2_r = node2->right;
            node2->right = node1;
            node1->left = node2_r;
            this->root = node2;
        }
          else{
            Node* father_1 = this->find_parent(node1->data, NULL, this->root);
            if(father_1->right == node1){
                father_1->right = node2;
                Node* temp = node2->right;
                node2->right = node1;
                node1->left = temp;
            }
            else{
                father_1->left = node2;
                Node* temp = node2->right;
                node2->right = node1;
                node1->left = temp;
            }
        }
    }
};

enum{
    NGHIEN_TRAI,
    NGHIEN_PHAI
};
int main(){
//=============Initialize===========//
//    int n = 20;
//    int input[] = {1,2,3,5,9,4,6,20,25,27,22,28,29,11,10,25,7,14,12};
    int n = 5;
    int input[] = {4,2,6,5,7};
    bin_tree* T = new bin_tree(input[0]);
    for(int i=1; i<=n-1; i++){
        T->pushNode(T->root,input[i]);
    }
    T->Level_print(n);
    int d[1001] = {0};
    T->count_levelNode(d, n, 0, 1, T->root);
    for(int i=0; i<=n; i++){
        if(d[i] != 0)printf("\nAt level %d has %d nodes", i, d[i]);
    }
    //==========Dont remove=================//
    return 0;
}