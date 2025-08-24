#include <iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

// 前序遍历
void preOrder(TreeNode* node) {
    if (node) {
        std::cout << node->value << " "; // 访问根节点
        preOrder(node->left);              // 遍历左子树
        preOrder(node->right);             // 遍历右子树
    }
}

// 中序遍历
void inOrder(TreeNode* node) {
    if (node) {
        inOrder(node->left);               // 遍历左子树
        std::cout << node->value << " ";  // 访问根节点
        inOrder(node->right);              // 遍历右子树
    }
}

// 后序遍历
void postOrder(TreeNode* node) {
    if (node) {
        postOrder(node->left);             // 遍历左子树
        postOrder(node->right);            // 遍历右子树
        std::cout << node->value << " ";   // 访问根节点
    }
}

int main() {
    // 示例二叉树构建
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    std::cout << "前序遍历: ";
    preOrder(root);
    std::cout << "\n中序遍历: ";
    inOrder(root);
    std::cout << "\n后序遍历: ";
    postOrder(root);
    
    return 0;
}
