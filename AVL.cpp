#include<iostream>
#include<vector>
#define maxn int(1e9)
using namespace std;
class Node{
    public:
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int data){
            this->value = data;
            left = NULL;
            right = NULL;
            height = 1;
        }
};
class AVL{
public:
    Node* root;
    AVL(int data){
        root = new Node(data);
    }
    int getBalance(Node* currNode){
        if(currNode == NULL)return maxn;
        Node* left = currNode->left;
        Node* right = currNode->right;

        if(left != NULL && right != NULL){
            return left->height - right->height;
        }
        else if(left == NULL && right == NULL) return 0;
        else if(left == NULL) return 0 - right->height;
        return left->height;
    }
    int getHeight(Node* x){
        if(x == NULL)return 0;
        return x->height;
    }
    Node* R_rotate(Node* x){
        Node* l_x = x->left;
        Node* temp = l_x->right;

        l_x->right = x;
        x->left = temp;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        l_x->height = 1 + max(getHeight(l_x->left), getHeight(l_x->right));
        return l_x;
    }
    Node* L_rotate(Node* x){

        Node* r_x = x->right;
        Node* temp = r_x->left;

        r_x->left = x;
        x->right = temp;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        r_x->height = 1 + max(getHeight(x->left), getHeight(x->right));

       return r_x; 
    }
    Node* AVL_action(Node* currNode, int data){
        currNode->height = 1 + max(getHeight(currNode->left) , getHeight(currNode->right));
        int balance = getBalance(currNode);
        if(currNode->left != NULL){
            if(balance > 1 && data < currNode->left->value){
                return R_rotate(currNode);
            }
            if(balance > 1 && data > currNode->left->value){
                currNode->left = L_rotate(currNode->left); 
                return R_rotate(currNode);
            }
        }
        if(currNode->right != NULL){
            if(balance < -1 && data > currNode->right->value){
                return L_rotate(currNode);
            }
            if(balance < -1 && data < currNode->left->value){
                currNode->right = R_rotate(currNode->right);
                return L_rotate(currNode);
            }
        }
    }
    Node* push(Node* currNode, int data){
        if(currNode == NULL){
            return new Node(data);
        }
        if(data > currNode->value) currNode->right = push(currNode->right, data);
        else if(data < currNode->value) currNode->left = push(currNode->left, data);
        else {
            cout << "\nData has existed: " << data;
            return currNode;
        }
        currNode->height = 1 + max(getHeight(currNode->left) , getHeight(currNode->right));
        int balance = getBalance(currNode);
        if(currNode->left != NULL){
            if(balance > 1 && data < currNode->left->value){
                return R_rotate(currNode);
            }
            if(balance > 1 && data > currNode->left->value){
                currNode->left = L_rotate(currNode->left); 
                return R_rotate(currNode);
            }
        }
        if(currNode->right != NULL){
            if(balance < -1 && data > currNode->right->value){
                return L_rotate(currNode);
            }
            if(balance < -1 && data < currNode->left->value){
                currNode->right = R_rotate(currNode->right);
                return L_rotate(currNode);
            }
        }
        return currNode;
    }
    Node* del(Node* currNode, int data){
        if(data < currNode->value){
            currNode = del(currNode->left, data); 
        }
        if(data > currNode->value){
            currNode = del(currNode->right, data);
        }
        if(data == currNode->value){
             
        }
    }  
    Node* find(int n, int data){
        if(data == this->root->value)return this->root; vector<Node*> v;
        v.push_back(this->root);
        for(int i=0; i<n; i++){
            if(v[i]->left != NULL){
                if(v[i]->left->value == data)return v[i]->left;
                v.push_back(v[i]->left);
            }
            if(v[i]->right != NULL){
                if(v[i]->right->value == data)return v[i]->right;
                v.push_back(v[i]->right);
            }
            if(v[i]->value == data)return v[i];
        } 
    }
    void print_tree(int n){
        vector<Node*> v;
        v.push_back(this->root);
        for(int i=0; i<n; i++){
            if(v[i]->left != NULL)v.push_back(v[i]->left);
            if(v[i]->right != NULL)v.push_back(v[i]->right);
            cout<<v[i]->value<<" ";
        } 
        cout<<endl;
    }
};
int main(){
    freopen("i.inp", "r", stdin);
    //freopen("o.out", "w", stdout);
    int n; cin >> n;
    int input[1001] = {0};
    for(int i=1; i<=n; i++)cin>>input[i];
    AVL* tree = new AVL(input[1]);
    for(int i = 2; i <= n; i++){
        tree->root = tree->push(tree->root, input[i]);
    }
    tree->print_tree(n); 
    return 0;
}