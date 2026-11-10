#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Node Class
class Node {
public:
    int data;
    Node* l;
    Node* r;
    
    Node(int dat) {
        data = dat;
        l = r = NULL;
    }
};
// Inserting Functions
Node* insert(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }
    else if (val < root->data) {
        root->l = insert(root->l, val);
    }
    else {
        root->r = insert(root->r, val);
    }
    return root;
}
Node* makeit(Node* root, vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        root = insert(root, arr[i]);
    }
    return root;
}
 //Inorder Successor Function
Node* suc(Node* root, int val) {
    Node* successor = NULL;
    Node* current = root;

    while (current != NULL) {
        if (val < current->data) {
            successor = current; 
            current = current->l;
        } 
        else if (val > current->data) {
            current = current->r;
        } 
        else {
            if (current->r != NULL) {
                Node* temp = current->r;
                while (temp->l != NULL) {
                    temp = temp->l;
                }
                return temp;
            }
            break;
        }
    }
    return successor; 
}
Node* pred(Node* root, int val) {
    Node* predecessor = nullptr;
    
    while (root != nullptr) {
        if (root->data >= val) {
            root = root->l;
        } else {
            predecessor = root;
            root = root->r;
        }
    }
    return predecessor;
}


void range(Node*root,int &comparison){
   comparison=0;
if(root==NULL){
 return;
 }
range(root->l,comparison);
if(root->data>30 && root->data<70){
 cout<<root->data<<" ";
 comparison++;
 }
range(root->r,comparison);
comparison++;
}
void iterativerange(Node*root){
    int comparison=0;
   queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        Node*curr=q.front();
        q.pop();
        comparison++;
        if(curr->data>30 ){
            comparison++;
            if(curr->data<70){
            
            cout<<curr->data<<" ";
            }
        }
        if(curr->l!=NULL){
            q.push(curr->l);
            comparison++;
        }
        if(curr->r!=NULL){
            q.push(curr->r);
    }
    }
    cout<<endl;
    cout<<"Iterative Comparisons="<<comparison<<endl;
}
void inorder(Node*root){
    inorder(root->l);
    cout<<root->data<<" ";
    inorder(root->r);
}
int main() {
    Node* root = NULL;
    int comp=0;
    vector<int> arr = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    root = makeit(root, arr);
    Node* inord = suc(root, 40);
    Node*prede=pred(root,40);
    cout << "BST formed Successfully" << endl;
    if (inord != NULL) {
        cout << "Inorder Successor = " << inord->data << endl;
    } else {
        cout << "No successor found!" << endl;
    }
    if(prede!=NULL){
        cout<<"The Predecessor="<<prede->data<<endl;

    }
    else{
        cout<<"No Predecessor FOund"<<endl;
    }
    cout<<"\n=======Recursive Approach=======\n";
    range(root,comp);
    cout<<endl;
    cout<<"Recursive Comparisons="<<comp;
    cout<<"\n=======Iterative Approach=======\n";
    iterativerange(root);

    return 0;
}
