#include <iostream>
#include <cassert>
using namespace std;

struct TreeNode
{
    TreeNode *parent, *left, *right;
    int val; 

    TreeNode(int val) : val(val)
    {
        parent = left = right = nullptr;
    }
};

class Tree
{
    TreeNode* root;

    TreeNode* _insert(TreeNode* node, TreeNode* par, int& val)
    {
        if (!node)
        {
            TreeNode* newNode = new TreeNode(val);
            newNode->parent = par;
            return newNode;
        }
        
        if (val < node->val)
            node->left = _insert(node->left, node, val);
        else
            node->right = _insert(node->right, node, val);
        
        return node;
    }

    void _print(TreeNode* node)     // inorder tree walk
    {
        if (!node)
            return;
        
        _print(node->left);
        
        cout << node->val << ' ';
        
        _print(node->right);
    }

    TreeNode* _min(TreeNode* node)
    {
        if (!node->left)
            return node;
        
        return _min(node->left);
    }

    TreeNode* _max(TreeNode* node)
    {
        if (!node->right)
            return node;
        
        return _max(node->right);
    }

    TreeNode* _find(TreeNode* node, int& val)
    {
        if (!node)
            return nullptr;
        
        TreeNode* res;

        if (node->val == val)
            res = node;
        else if (val < node->val)
            res = _find(node->left, val);
        else
            res = _find(node->right, val);

        return res;
    }

public:
    Tree() : root(nullptr) {}

    void insert(int val)
    {
        root = _insert(root, nullptr, val);
    }

    void print()
    {
        _print(root);
    }

    TreeNode* min()
    {
        assert(root);
        return _min(root);
    }

    TreeNode* max()
    {
        assert(root);
        return _max(root);
    }

    TreeNode* find(int val)
    {
        return _find(root, val);
    }

    TreeNode* succesor(TreeNode* node)
    {
        if (node->right)
            return _min(node->right);
        
        TreeNode *i = node->parent, *j = node;
        
        while (i && j != i->left)   // search for any left son => it's father is greater than node => father is answer
        {
            j = i;
            i = i->parent;
        }
        
        return i;
    }

    void remove(TreeNode* node)
    {
        if (node->left && node->right)
        {
            TreeNode* succ = succesor(node);
            
            if (succ->parent)
                if (succ == succ->parent->left)
                    succ->parent->left = succ->right;
                else
                    succ->parent->right = succ->right;
            else
                root = succ->right;                    
            
            if (node->parent)
                if (node == node->parent->left)
                    node->parent->left = succ;
                else
                    node->parent->right = succ;
            else
                root = succ;
            
            node->left->parent = succ;
            node->right->parent = succ;

            succ->left = node->left;
            succ->right = node->right;

            delete node;
        }        
        else if (node->left)
        {
            if (node == node->parent->left)
                node->parent->left = node->left;
            else
                node->parent->right = node->left;
            delete node;
        }
        else if (node->right)
        {
            if (node == node->parent->left)
                node->parent->left = node->right;
            else
                node->parent->right = node->right;
            delete node;
        }
        else
        {
            if (node->parent)
                if (node == node->parent->left)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            delete node;
        }
            
    }
};

int main()
{
    Tree T;
    T.insert(10);
    T.insert(4);
    T.insert(2);
    T.insert(6);
    T.insert(5);
    T.insert(7);
    T.insert(12);
    T.insert(11);
    T.insert(15);
    T.print();
    TreeNode* node = T.find(7);
    T.remove(node);
    cout << endl;
    T.print();
}