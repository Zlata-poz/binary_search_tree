#include <iostream>

using namespace std;

struct TreeNode {
	int value;
	TreeNode* right;
	TreeNode* left;
	TreeNode* parent;
	TreeNode(int value) : value(value), right(nullptr), left(nullptr), parent(nullptr){}
};
class BinarySearchTree {
	TreeNode* root;
	int height(TreeNode* ptr) {
		if (ptr == nullptr) return 0;
		return max(height(ptr->left), height(ptr->right)) + 1;
	}

	int balanceFactor(TreeNode* ptr) {
		if (ptr == nullptr) return 0;
		return height(ptr->left) - height(ptr->right);
	}

	void LL_rotation(TreeNode* ptr) {
		TreeNode* child = ptr->right;
		ptr->right = child->left; 
		if (child->left != nullptr) child->left->parent = ptr;
		child->parent = ptr->parent; 
		child->left = ptr;
		if (ptr->parent == nullptr) { 
			root = child;}
		else if (ptr == ptr->parent->left) { 
			ptr->parent->left = child;}
		else ptr->parent->right = child;
		ptr->parent = child;
	}

	void RR_rotation(TreeNode* ptr) {
		TreeNode* child = ptr->left; 
		ptr->left = child->right; 
		if (child->right != nullptr) child->right->parent = ptr;
		child->parent = ptr->parent; 
		child->right = ptr; 
		if (ptr->parent == nullptr) { 
			root = child;}
		else if (ptr == ptr->parent->left) {
			ptr->parent->left = child;}
		else ptr->parent->right = child;
		ptr->parent = child;
	}

public: 
	
	BinarySearchTree() : root(nullptr){}

	void addElem(int value) {
		TreeNode* ptr = root;
		if (root == nullptr) {
			root = new TreeNode(value);
		}
		else {
			while (true) {
				if (value < ptr->value) {
					if (ptr->left) {
						ptr = ptr->left;
					}
					else {
						ptr->left = new TreeNode(value);
						ptr->left->parent = ptr;
						break;
					}
				}
				else {
					if (ptr->right) {
						ptr = ptr->right;
					}
					else {
						ptr->right = new TreeNode(value);
						ptr->right->parent = ptr;
						break;
					}
				}

			}
		}


	}

	TreeNode findElem(int value) {
		TreeNode* ptr = root;
		if (root == nullptr) {
			cout << "Element " << value << " is not found" << endl;
		}
		else {
			while (ptr != nullptr) {
				if (value < ptr->value) {
					ptr = ptr->left;
				}
				else if (value > ptr->value) {
					ptr = ptr->right;
				}
				else if (value = ptr->value) {
					cout << "Element " << value << " is found" << endl;
					return *ptr;
					break;
				}
				if (ptr == nullptr) {
					cout << "Element " << value << " is not found" << endl;
				}
			}

		}
	}

	void removeElemHelp(TreeNode*& ptr, int value) {
		if (ptr == nullptr) {
			return;
		}
		else {
			if (value < ptr->value) {
				removeElemHelp(ptr->left, value);
			}
			else if (value > ptr->value) {
				removeElemHelp(ptr->right, value);
			}
			else {
				if (ptr->left == nullptr && ptr->right == nullptr) {
					TreeNode* toDel = ptr;
					ptr = nullptr;
					delete toDel;
				}
				else if (ptr->left == nullptr || ptr->right == nullptr) {
					TreeNode* child = (ptr->left != nullptr ? ptr->left : ptr->right);
					TreeNode* toDel = ptr;
					ptr = child;
					delete toDel;
				}
				else { 
					if ((ptr->left->left == nullptr && ptr->left->right == nullptr) || ptr->left->left != nullptr && ptr->left->right == nullptr) {
						TreeNode* child = ptr->left; 
						child->parent = ptr->parent;
						child->right = ptr->right;
						TreeNode* toDel = ptr;
						ptr = child;
						delete toDel;
					}
					else if ((ptr->left->right != nullptr && ptr->left->left == nullptr) || ptr->left->left != nullptr && ptr->left->right != nullptr) { 
						TreeNode* temp = ptr->left;
						while (temp->right != nullptr) {
							temp = temp->right; 
						}

						ptr->value = temp->value;
						temp->parent->right = NULL;
						
					}
				}
			}
		}
	}
	void inOrder(TreeNode* ptr) {
		if (ptr == NULL) return;
		inOrder(ptr->left);
		cout << ptr->value << " ";
		inOrder(ptr->right);
	}

	void printTree() {
		inOrder(root);
	}
	
	void removeEl(int value) {
		removeElemHelp(root, value);
	}
	

	
	void balance(TreeNode* ptr) {
		int balance = balanceFactor(ptr);

		if (balance > 1) {
			if (balanceFactor(ptr->left) >= 0) {
				RR_rotation(ptr);
			}
			else {
				LL_rotation(ptr->left);
				RR_rotation(ptr);
			}
		}
		else if (balance < -1) {
			if (balanceFactor(ptr->right) <= 0) {
				LL_rotation(ptr);
			}
			else {
				RR_rotation(ptr->right);
				LL_rotation(ptr);
			}
		}
	}

	void forcedBalanscingHelp(TreeNode* ptr) {
		if (ptr == nullptr) return;
		forcedBalanscingHelp(ptr->left);
		forcedBalanscingHelp(ptr->right);
		balance(ptr);
	}

	void forcedBalancing() {
		forcedBalanscingHelp(root);
	}

	void printTreeHelper(TreeNode* node, string indent, bool last) {
		if (node != nullptr) {
			cout << indent;
			if (last) {
				cout << "R----";  // Если это правый потомок
				indent += "   ";
			}
			else {
				cout << "L----";  // Если это левый потомок
				indent += "|  ";
			}
			cout << node->value << endl;

			// Рекурсивно выводим правое и левое поддерево
			printTreeHelper(node->right, indent, false);  // Печатаем правое поддерево (справа)
			printTreeHelper(node->left, indent, true);   // Печатаем левое поддерево (слева)
		}
	}

	void printTree_2() {
		if (root == nullptr) {
			cout << "Tree is empty." << endl;
		}
		else {
			printTreeHelper(root, "", true);  // Запускаем рекурсию с корня дерева
		}
	}
};

int main() {
	BinarySearchTree tree;
	for (int i = 0; i < 25; i++) {
		tree.addElem(i);
	}

	tree.findElem(23);
	tree.printTree_2();
	tree.removeEl(20);
	tree.printTree();
	cout << endl;
	tree.printTree_2();
	tree.forcedBalancing();
	cout << endl;
	tree.printTree_2();
}