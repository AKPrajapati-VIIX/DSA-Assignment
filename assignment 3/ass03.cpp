#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int key;
    TreeNode *left;
    TreeNode *right;
    int height;
    int size;

    TreeNode(int key) {
        this->key = key;
        this->left = this->right = nullptr;
        this->height = 1;
        this->size = 1;
    }
};

class AVLTree {
private:
    TreeNode *root;

    int getHeight(TreeNode *node) {
        return node ? node->height : 0;
    }

    int getSize(TreeNode *node) {
        return node ? node->size : 0;
    }

    void updateNode(TreeNode *node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

    TreeNode* rotateRight(TreeNode *y) {
        TreeNode *x = y->left;
        TreeNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateNode(y);
        updateNode(x);
        return x;
    }

    TreeNode* rotateLeft(TreeNode *x) {
        TreeNode *y = x->right;
        TreeNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateNode(x);
        updateNode(y);
        return y;
    }

    int getBalance(TreeNode *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    TreeNode* insert(TreeNode *node, int key) {
        if (!node)
            return new TreeNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // Duplicate keys are not allowed

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* find(TreeNode *node, int key) {
        if (!node)
            return nullptr;
        if (key == node->key)
            return node;
        if (key < node->key)
            return find(node->left, key);
        return find(node->right, key);
    }

    TreeNode* minValueNode(TreeNode *node) {
        TreeNode *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    TreeNode* remove(TreeNode *node, int key) {
        if (!node)
            return node;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                TreeNode *temp = node->left ? node->left : node->right;
                if (!temp)
                    node = nullptr;
                else
                    *node = *temp;
                delete temp;
            } else {
                TreeNode *temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        if (!node)
            return node;

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    int orderOfKey(TreeNode *node, int key) {
        if (!node)
            return 0;
        if (key <= node->key)
            return orderOfKey(node->left, key);
        return 1 + getSize(node->left) + orderOfKey(node->right, key);
    }

    TreeNode* getByOrder(TreeNode *node, int k) {
        if (!node)
            return nullptr;
        int leftSize = getSize(node->left);
        if (k < leftSize)
            return getByOrder(node->left, k);
        if (k > leftSize)
            return getByOrder(node->right, k - leftSize - 1);
        return node;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    bool find(int key) {
        return find(root, key) != nullptr;
    }

    void remove(int key) {
        root = remove(root, key);
    }

    int orderOfKey(int key) {
        return orderOfKey(root, key);
    }

    int getByOrder(int k) {
        TreeNode *node = getByOrder(root, k);
        return node ? node->key : -1; 
    }

    void inorder(TreeNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    void inorder() {
        inorder(root);
    }

    int height() {
        return getHeight(root);
    }
};

int main() {
    AVLTree avlTree;

   
    int keysToInsert[] = {10, 20,22 ,30, 40, 50, 25,75,32};
    for (int key : keysToInsert) {
        avlTree.insert(key);
    }

    cout << "Inorder traversal of the constructed AVL tree: ";
    avlTree.inorder(); cout << endl;
    
    cout << "Height of the constructed AVL tree: " << avlTree.height() << endl;

    cout << "Finding keys:" << endl;
    cout << "insert 10 inorder avl tree:" <<avlTree.find(10) << endl;  
    cout <<"insert 15 inorder avl tree:" << avlTree.find(15) << endl;  

    cout << "\nRemoving key 20:" << endl;
    avlTree.remove(20);
    cout << avlTree.find(20) << endl;  

    // Get the order of a key
    cout << "\nOrder of key 25: "<< avlTree.orderOfKey(25)<< endl;
      // Return the number of keys smaller than 25

    // Get the k-th smallest element
    cout << "\nGetting the 2nd smallest element: " << endl;
    cout << avlTree.getByOrder(1) << endl;  

    cout << "\nInserting more keys and checking order:" << endl;
    avlTree.insert(5);
    avlTree.insert(15);
    avlTree.insert(35);

    cout << avlTree.orderOfKey(35) << endl; 
    cout << "\nGetting the 4th smallest element:" <<avlTree.getByOrder(3)<< endl;

    return 0;
}
