#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

class Node {
public:
    Node *left, *right;
    int data;
};

class BreadthFirstSearch {
public:
    Node* insert(Node*, int);
    void bfs(Node*);
};

Node* BreadthFirstSearch::insert(Node* root, int data) {
    if (!root) {
        root = new Node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new Node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        } else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new Node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

void BreadthFirstSearch::bfs(Node* head) {
    queue<Node*> q;
    q.push(head);

    while (!q.empty()) {
        int qSize = q.size();
        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            Node* currNode;
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }
            #pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

int main() {
    BreadthFirstSearch bfs;
    Node* root = NULL;
    int data;
    char ans;

    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = bfs.insert(root, data);
        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "\nBreadth First Traversal: ";
    bfs.bfs(root);
    cout << endl;

    return 0;
}
