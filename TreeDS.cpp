// Tree in c++
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// Tree class 
template<typename T>
class TreeNode{
    public:
        T data;
        vector<TreeNode<T>* > children;
        TreeNode(T data){
            this->data = data;
        }
        ~TreeNode(){
            for(int i=0;i<children.size();i++){
                delete(children[i]);
            }
        }
};
// input function for the Tree recursively
TreeNode<int>* TakeInput(){
    cout<<"Enter data : ";
    int rootData;
    cin>>rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);
    cout<<"Enter no of child : ";
    int childN;
    cin>>childN;
    for(int i=0;i<childN;i++){
        TreeNode<int>* child = TakeInput();
        root->children.push_back(child);
    }
    return root;
}
// input function to take input lavel wise
TreeNode<int>* takeLevelwise(){
    cout<<"Enter data : ";
    int rootData;
    cin>>rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);
    queue<TreeNode<int>*> pendingNode;
    pendingNode.push(root);
    while(pendingNode.size()!=0){
        TreeNode<int>* front = pendingNode.front();
        pendingNode.pop();
        cout<<"Enter no of child of "<<front->data <<" : ";
        int numChild;
        cin>>numChild;
        for(int i=0;i<numChild;i++){
            int childData;
            cout<<"Enter the value of "<<i<<"th child of "<<front->data<<" : ";
            cin>>childData;
            TreeNode<int>* child = new TreeNode<int>(childData);
            front->children.push_back(child);
            pendingNode.push(child);
        }
    }
    return root;
}

// print the tree function
void display(TreeNode<int> *root){
    if(!root) return;
    cout<<root->data<<" : ";
    for(int i=0;i<root->children.size();i++){
        cout<<root->children[i]->data<<", ";
    }
    cout<<endl;
    for(int i=0;i<root->children.size();i++){
        display(root->children[i]);
    }
}

// Print level wise
void printTreeLevelWise(TreeNode<int>* root){
    if(!root) return ;
    queue<TreeNode<int>*> pending;
    pending.push(root);
    while(pending.size()!=0){
        TreeNode<int>* front = pending.front();
        pending.pop();
        cout<<front->data<<" : ";
        for(int i=0;i<front->children.size();i++){
            cout<<front->children[i]->data<<", ";
            pending.push(front->children[i]);
        }
        cout<<endl;
    }
}

// finding the sum of Nodes of the tree
int findSumofNodes(TreeNode<int>* root){
    int ans = root->data;
    for(int i=0;i<root->children.size();i++){
        ans += findSumofNodes(root->children[i]);
    }
    return ans;
}
// finding max value in the tree
TreeNode<int>* findMax(TreeNode<int>* root){
    TreeNode<int>* max = new TreeNode<int>(root->data);
    for(int i = 0;i<root->children.size();i++){
        TreeNode<int>* tmp = (findMax(root->children[i]));
        if(max->data < tmp->data) {
            max = tmp;
        }
    }
    return max;
}
// Find height of the tree
int heightOfTreeNode(TreeNode<int>* root){
    if(!root) return 0;
    int ans = 0 ;
    for(int i=0;i<root->children.size();i++){
        int tmp = heightOfTreeNode(root->children[i]);
        if(ans < tmp) ans = tmp;
    }
    return ans+1;
}
// Print at level K
void PrintAtLevelK(TreeNode<int>* root, int k){
    if(root == NULL) return ;
    if(k == 0) {
        cout<<root->data<<endl;
        return;
    }
    for(int i =0;i<root->children.size();i++){
        PrintAtLevelK(root->children[i],k-1);
    }
}

// Count leaf nodes

int getLeafNodeCount(TreeNode<int>* root) {
    if(root == NULL) return 0;
    if(root->children.size() == 0) return 1;
    int ans = 0;
    for(int i=0;i<root->children.size();i++){
        ans += getLeafNodeCount(root->children[i]);
    }
    return ans;
}

// Pre Order traversal of tree
void PreOrder(TreeNode<int>* root){
    if(root == NULL) return;
    cout<<root->data<< ", ";
    for(int i = 0;i<root->children.size();i++){
        PreOrder(root->children[i]);
    }
}

// Post order traversal of tree
void postOrder(TreeNode<int>* root){
    if(root == NULL) return;
    for(int i = 0;i<root->children.size();i++){
        postOrder(root->children[i]);
    }
    cout<<root->data<<", ";
}
// Delete tree
void deleteTree(TreeNode<int>* root){
    for(int i=0;i<root->children.size();i++){
        deleteTree(root->children[i]);
    }
    delete root;
}

// if X is present in the tree
bool isPresent(TreeNode<int>* root, int x) {
    if(root == NULL) return false;
    if(root->data == x) return true;
    for(int i = 0; i<root->children.size();i++){
        if(isPresent(root->children[i],  x)) return true;
    }
    return false;
}
// Count nodes
int getLargeNodeCount(TreeNode<int>* root, int x) {
    int count;
    if(root->data > x) count = 1;
    else count = 0;
    for(int i=0;i<root->children.size();i++){
        count += getLargeNodeCount(root->children[i], x);
    }
    return count;
}

// Node with maximum child sum starting here
void helperFun(TreeNode<int>* root, TreeNode<int>** ans, int *max){
    int sum = root->data;
    for(int i = 0; i<root->children.size();i++){
        sum += root->children[i]->data;
    }
    if(sum > *max ){
        *max = sum;
        *ans = root;
    }
    for(int i=0;i<root->children.size();i++){
        helperFun(root->children[i], ans, max);
    }
}
TreeNode<int>* maxSumNode(TreeNode<int>* root) {
    // Write your code here
    if(root == NULL) return root;
    int max = 0;
    TreeNode<int> *ans = NULL;
    helperFun(root, &ans, &max);
    return ans;
}
// Node with maximum child sum ending here
int main(){
    TreeNode<int>* root =  takeLevelwise();
    printTreeLevelWise(root);
    delete(root);
    return 0;
}
