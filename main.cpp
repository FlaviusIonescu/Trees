// trees.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <stack>
#include <queue>
#include <list>

using namespace std;

class Node
{

public:
    int data;
    Node* left;
    Node* right;

    Node(int newData)
            :data(newData)
    {
        left = nullptr;
        right = nullptr;
    }

    Node()
            : data(0)
    {
        left = nullptr;
        right = nullptr;
    }

    virtual void  showInfo()
    {
        cout << data << endl;
    }

};

class SpecialNode : public Node
{

public:
    SpecialNode(int data, float w)
            : Node(data)
            , weight(w)
    {

    }

    float weight;

    void showInfo()
    {
        cout << data << "  " << weight << endl;
    }

};

class BinatyTree
{
public:

    BinatyTree()
    {
        root = nullptr;
    }

    void insert(int key)
    {
        if (root != nullptr)
        {
            insert(key, root);
        }
        else
        {
            root = new Node(key);
        }
    }

    void remove(int key)
    {
        remove(key, root);
    }

    Node* find(int key)
    {
        return find(key, root);
    }

    void destroyTree()
    {
        destroyTree(root);
    }

    void traverseInorder()
    {
        traverseInorder(root);
    }

    void traversePreorder()
    {
        traversePreorder(root);
    }

    void traversePostorder()
    {
        traversePostorder(root);
    }

    void DFSIterative()
    {
        stack<Node*> dfsStack;
        DFSIterative(root, dfsStack);

    }

    void DFSRecursive()
    {
        DFSRecursive(root);
    }

    void BFSRecursive()
    {
        if (root == nullptr)
            return;

        queue<Node*> bfsQueue;
        bfsQueue.push(root);
        BFSRecursive(bfsQueue);

    }

    void BFSIterative()
    {
        BFSIterative(root);
    }

    int DeapthTree()
    {
        return DeapthTree(root);
    }

    void PrintLevels()
    {
        int deapth = DeapthTree(root);
        if (deapth > 0)
        {
            for (int i = 0; i < deapth; i++)
            {
                PrintLevel(root, i);
            }
        }
    }

private:
    void PrintLevel(Node* root, int level)
    {
        if (root != nullptr)
        {
            if (level == 0)
            {
                cout << root->data << " ";
            }
            else
            {
                PrintLevel(root->left, level - 1);
                PrintLevel(root->right, level - 1);
            }
        }
    }

    int DeapthTree(Node* node)
    {
        if (node == nullptr)
            return 0;

        return max(DeapthTree(node->left) + 1, DeapthTree(node->right) + 1);
    }

    void BFSRecursive(queue<Node*>& bfsQueue)
    {
        if (!bfsQueue.empty())
        {
            Node* cur = bfsQueue.front();
            cout << cur->data << " ";

            bfsQueue.pop();
            if (cur->left != nullptr)
                bfsQueue.push(cur->left);
            if (cur->right != nullptr)
                bfsQueue.push(cur->right);

            BFSRecursive(bfsQueue);
        }
    }

    void BFSIterative(Node* root)
    {
        queue<Node*> bfsQueue;
        if (root == nullptr)
            return;

        bfsQueue.push(root);
        while (!bfsQueue.empty())
        {
            Node* current = bfsQueue.front();
            bfsQueue.pop();
            cout << current->data << " ";
            if (current->left != nullptr)
                bfsQueue.push(current->left);
            if (current->right != nullptr)
                bfsQueue.push(current->right);
        }
    }

    void DFSRecursive(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        cout << root->data << " ";
        DFSRecursive(root->right);
        DFSRecursive(root->left);
    }

    void DFSIterative(Node* root, stack<Node*> dsfStack)
    {
        if (root == nullptr)
        {
            return;
        }

        dsfStack.push(root);
        while (!dsfStack.empty())
        {
            Node* cur = dsfStack.top();
            dsfStack.pop();

            cout << cur->data << " ";

            if (cur->left != nullptr)
                dsfStack.push(cur->left);
            if (cur->right != nullptr)
                dsfStack.push(cur->right);
        }


    }

    void insert(int key, Node* root)
    {
        if (root == nullptr)
            return;

        if (key < root->data)
        {
            if (root->left == nullptr)
            {
                auto newLeaf = new Node(key);
                root->left = newLeaf;
            }
            else
            {
                insert(key, root->left);
            }
        }
        else
        {
            if (root->right == nullptr)
            {
                auto newLeaf = new Node(key);
                root->right = newLeaf;
            }
            else
            {
                insert(key, root->right);
            }
        }
    }

    Node* remove(int key, Node* root)
    {
        if (root == nullptr)
            return nullptr;

        if (key < root->data)
        {
            root->left = remove(key, root->left);
        }
        else if(key > root->data)
        {
            root->right = remove(key, root->right);
        }
        else
        {
            //found it
            //leaf node
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }
                // right child is not null
            else if (root->left == nullptr)
            {
                Node* temp = root;
                root = root->right;
                delete temp;
            }
                // left child is not null
            else if (root->right == nullptr)
            {
                Node* temp = root;
                root = root->left;
                delete temp;
            }
                //both childs are not null
            else
            {
                //chose max from left or min from right
                Node* temp = findMin(root->right); //search in right
                root->data = temp->data;
                root->right = remove(temp->data, root->right);
            }
        }
        return root;
    }

    Node* findMin( Node* root)
    {
        if (root == nullptr)
            return nullptr;

        if (root->left != nullptr) {
            findMin( root->left);
        }

        return root;

    }

    Node* find(int key, Node* root)
    {
        if (root == nullptr)
            return nullptr;

        if (root->data == key)
            return root;

        if (root->data > key)
            return find(key, root->left);
        else
            return find(key, root->right);
    }

    void destroyTree(Node* root)
    {
        if (root != nullptr)
        {
            destroyTree(root->left);
            destroyTree(root->right);
            delete root;
        }
    }

    void traverseInorder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        traverseInorder(root->left);
        cout << root->data << " ";
        traverseInorder(root->right);
    }

    void traversePreorder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        cout << root->data << " ";
        traversePreorder(root->left);
        traversePreorder(root->right);
    }

    void traversePostorder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        traversePostorder(root->left);
        traversePostorder(root->right);
        cout << root->data << " ";
    }

    Node* root;
};

int main()
{
    BinatyTree myTree;
    myTree.insert(10);
    myTree.insert(5);
    myTree.insert(7);
    myTree.insert(15);
    myTree.insert(14);
    myTree.insert(12);
    myTree.insert(18);
    myTree.insert(19);
    myTree.insert(17);



    //Node* lala = myTree.find(11);
    //myTree.remove(10);
    //myTree.remove(13);
    cout << endl << "traverseInorder" << endl;
    myTree.traverseInorder();
    cout << endl << "traversePreorder" << endl;
    myTree.traversePreorder();
    cout << endl << "traversePostorder" << endl;
    myTree.traversePostorder();
    cout << endl << "DFSIterative" << endl;
    myTree.DFSIterative();
    cout << endl << "DFSRecursive" << endl;
    myTree.DFSRecursive();
    cout << endl << "BFSIterative" << endl;
    myTree.BFSIterative();
    cout << endl << "BFSRecursive" << endl;
    myTree.BFSRecursive();
    cout << endl << "Deapth" << endl;
    cout << myTree.DeapthTree();
    cout << endl << "BFSRecursive using DFS" << endl;
    myTree.PrintLevels();

    SpecialNode lala(5, 0.3);

    list<Node*> list;
    list.push_back(&lala);
    list.front()->showInfo();

    return 0;
}
