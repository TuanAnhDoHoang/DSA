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
            if(balance < -1 && data < currNode->right->value){
                currNode->right = R_rotate(currNode->right);
                return L_rotate(currNode);
            }
        }
        return currNode;
    }
    Node* getSuccessor(Node* currNode){
        currNode = currNode->right;
        while(currNode->left != NULL && currNode != NULL){
            currNode = currNode->left;
        }
        return currNode;
    }
    Node* minValueNode(Node* node){
        Node* currNode = node;
        while(currNode != NULL && currNode->left != NULL){
            currNode = currNode->left;
        }
        return currNode;
    }
    Node* del(Node* currNode, int data){ //Nút mới thay thế cho cha của CurrNode
        if(currNode == NULL)return currNode;
        if(data < currNode->value){
            currNode->left = del(currNode->left, data); 
        }
        if(data > currNode->value){
            currNode->right = del(currNode->right, data);
        }
        if(data == currNode->value){
            if(currNode->left == nullptr && currNode->right == nullptr){
                delete(currNode);
            }
            if(currNode->left == nullptr || currNode->right == nullptr){
                if(currNode->left == nullptr){
                    Node* tmp = currNode->right;
                    *currNode = *tmp;
                    delete(tmp);
                }
                else if(currNode->right == nullptr){
                    Node* tmp = currNode->left;
                    *currNode = *tmp;
                    delete(tmp);
                }
            }
            else{
                Node* succ = getSuccessor(currNode);
                currNode->value = succ->value;
                currNode->right = del(currNode->right, succ->value);
            }
        }
        if(currNode == nullptr){
            return currNode;
        }

        currNode->height = 1+ max(getHeight(currNode->left), getHeight(currNode->right));
        int balance = getBalance(currNode);


        if(balance > 1 && getBalance(currNode->left) >= 0)// nghiên trái, trái
        {
            return R_rotate(currNode);
        }
        if(balance > 1 && getBalance(currNode->left) < 0) //Nghiên trái, phải
        {
            currNode = L_rotate(currNode->left);
            return R_rotate(currNode);
        }
        if(balance < -1 && getBalance(currNode->right) <= 0) //Phai, phai
        {
            return L_rotate(currNode);
        }
        if(balance < -1 && getBalance(currNode->right) > 0)//phai, trai
        {
            currNode = R_rotate(currNode->right);
            return L_rotate(currNode);
        }
        return currNode;
    }  
    void print_tree(int n){
        vector<Node*> v;
        v.push_back(this->root);
        for(int i=0; i<n; i++){
            if(v[i] != NULL){
                if(v[i]->left != NULL)v.push_back(v[i]->left);
                if(v[i]->right != nullptr)v.push_back(v[i]->right);
                cout<<v[i]->value<<" ";
            }
        } 
        cout<<endl;
    }
    void print_tree(Node* currNode){
        if(currNode != nullptr){
            cout<<currNode->value<<" ";
            print_tree(currNode->left);
            print_tree(currNode->right);
        }
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
    cout<<endl;
    tree->root = tree->del(tree->root, 11);
    n--;

    tree->print_tree(n); 
    return 0;
}