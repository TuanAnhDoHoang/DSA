#include<iostream>
using namespace std;
class Node{
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

class avl_tree{
public:
    Node* root;
    avl_tree(int data){
        this->root = new Node(data);
    } 
    int get_Balance(Node* currNode){
        if(currNode != NULL){
            Node* l = currNode->left;
            Node* r = currNode->right;
            if(l != NULL && r!=NULL){
                return l->height - r->height;
            }
            if(l == NULL && r == NULL){
                if(l == NULL){
                    return 0 - r->height;
                }
                else return l->height;
            }
            return 0; // nút lá
        }
    }
    void push(Node* currNode, int data){
        if(currNode != NULL){
            if(data > currNode->data) 
                push(currNode->right, data);
            else if(data > currNode->data) push(currNode->right, data);
            else
                printf("\nThis data has existed!");

        }
        else{
            currNode = new Node(data);

        }
        currNode->height = 1 + max(currNode->left->height, currNode->right->height);
        int balance = get_Balance(currNode);

    }
};
int main(){
    freopen("i.inp", "r", stdin);
    freopen("o.out", "w", stdout);


    return 0;
}