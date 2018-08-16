// Chapter 4: Trees and Graphs

// Solutions

#include <cassert>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>

/*
MY QUESTION
4.0.0 Binary Tree Implementation: Implement a binary tree
*/

struct TreeNode {
	int data = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

void printPre(TreeNode*& root) {
	TreeNode* iter = root;
	if (iter == nullptr)
		return;

	std::cout << root->data << std::endl;
	printPre(root->left);
	printPre(root->right);
}

void printIn(TreeNode*& root) {
	TreeNode* iter = root;
	if (iter == nullptr)
		return;

	printPre(root->left);
	std::cout << root->data << std::endl;
	printPre(root->right);
}

void printPost(TreeNode*& root) {
	TreeNode* iter = root;
	if (iter == nullptr)
		return;

	printPre(root->left);
	printPre(root->right);
	std::cout << root->data << std::endl;
}

/*
4.0.1 Graph Implementation: Implement a graph as an adjacency list
*/

class Graph {
public:
	Graph(int numNodes) {
		nodeSet = numNodes;
		adjList = new std::vector<int>[numNodes];
	}
	void addEdge(int from, int to) {
		adjList[from].push_back(to);
	}
	bool isRoute(int from, int to);
private:
	int nodeSet;
	std::vector<int>* adjList;
};

/*
4.1 Route Between Nodes: Given a directed graph, design an algorithm to find out whether there is
a route between two nodes.
*/

bool Graph::isRoute(int from, int to) {

	std::vector<bool> visited(nodeSet, false);
	std::queue<int> toSearch;

	toSearch.push(from);

	while (!toSearch.empty()) {
		int current = toSearch.front();
		// found it, done
		if (current == to)
			return true;

		// otherwise, search
		toSearch.pop();
		visited[current] = true;
		int neighbor_cnt = adjList[current].size();
		for (int i = 0; i < neighbor_cnt; ++i) {
			if (!visited[adjList[current][i]])
				toSearch.push(adjList[current][i]);
		}
	}
	return false;
}

/*
4.2 Minimal Tree: Given a sorted (increasing order) array with unique integer,
write an algorithm to create a binary tree with minimal height.
*/

TreeNode* createMinTree(const int* arr, int low, int high) {
	// base case
	if (low > high)
		return nullptr;

	// make the middle array value the root
	int mid = (low + high) / 2;
	TreeNode* toAdd = new TreeNode;
	toAdd->data = arr[mid];
	toAdd->left = createMinTree(arr, low, mid - 1);
	toAdd->right = createMinTree(arr, mid + 1, high);

	return toAdd;
}

// helper
TreeNode* createMinTree(const int* arr, int size) {
	if (size < 1)
		return nullptr;
	return createMinTree(arr, 0, size - 1);
}

/*
4.3 List of Depths: Given a binary tree, design an algorithm which creates a linked list of
all the nodes at each depth (e.g. if you have a tree with depth D, you'll have D linked lists).
*/

void listOfDepths(TreeNode* givenTree, std::vector<std::vector<int>>& solution, int counter) {
	// std::cout << "function is happening" << std::endl;

	TreeNode* iter = givenTree;

	if (iter == nullptr) {
		return;
	}

	// make sure the vector of vectors starts empty
	// make sure the counter always starts with 0

	// insert current
	if (counter >= solution.size()) {
		std::vector<int> newVec;
		//std::cout << "making new" << std::endl;
		solution.push_back(newVec);
	}
	solution[counter].push_back(iter->data);

	// increase counter for next level
	int nextCount = counter + 1;
	// insert left
	listOfDepths(iter->left, solution, nextCount);
	// insert right
	listOfDepths(iter->right, solution, nextCount);
}

/*
	4.4 Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of
	this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of
	any node never differ by more than one.
*/

int checkHeight(TreeNode* givenTree) {
	if (givenTree == nullptr) {
		return 0;
	}
	int leftHeight = checkHeight(givenTree->left);
	if (leftHeight == -1) {
		return -1;
	}
	int rightHeight = checkHeight(givenTree->right);
	if (rightHeight == -1) {
		return -1;
	}

	if (abs(leftHeight - rightHeight) > 1) {
		return -1;
	}
	else {
		return std::max(leftHeight, rightHeight) + 1;
	}
}

bool isBalanced(TreeNode* givenTree) {
	return (checkHeight(givenTree) != -1);
}

/*
	4.5 Validate BST: Implement a function to check if a binary tree is a binary search tree.
*/

bool isSearchTree(TreeNode* givenTree) {
	if (givenTree == nullptr)
		return true;

	if (givenTree->left == nullptr && givenTree->right == nullptr)
		return true;
		
	if (givenTree->left == nullptr && givenTree->right != nullptr)
		if (givenTree->data > givenTree->right->data)
			return false;

	if (givenTree->left != nullptr && givenTree->right == nullptr)
		if (givenTree->data < givenTree->left->data)
			return false;

	if (givenTree->left != nullptr && givenTree->right != nullptr)
		if (givenTree->data < givenTree->left->data || givenTree->data > givenTree->right->data)
			return false;

	// do for sub-trees
	int i = isSearchTree(givenTree->left);
	int j = isSearchTree(givenTree->right);
	
	if (i && j)
		return true;
	else
		return false;
}

/*
	4.6 Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of
	a given node in a binary search tree. You may assume that each node has a link to its parent.
*/


int main() {
	// Tree implementation test
	TreeNode* first = new TreeNode;
	first->data = 5;
	TreeNode* second = new TreeNode;
	second->data = 3;
	TreeNode* third = new TreeNode;
	third->data = 12;
	TreeNode* fourth = new TreeNode;
	fourth->data = 1;
	TreeNode* fifth = new TreeNode;
	fifth->data = 4;
	TreeNode* sixth = new TreeNode;
	sixth->data = 0;

	first->left = second;
	first->right = third;
	second->left = fourth;
	second->right = fifth;
	fourth->left = sixth;

	printPre(first);
	std::cout << std::endl;
	printIn(first);
	std::cout << std::endl;
	printPost(first);

	// Graph implementation test
	Graph myGraph(7);
	myGraph.addEdge(0, 1);
	myGraph.addEdge(1, 2);
	myGraph.addEdge(1, 6);
	myGraph.addEdge(2, 0);
	myGraph.addEdge(3, 0);
	myGraph.addEdge(4, 3);
	myGraph.addEdge(4, 6);
	myGraph.addEdge(5, 2);

	// Test 4.1

	assert(myGraph.isRoute(4, 1) == true);
	assert(myGraph.isRoute(5, 0) == true);
	assert(myGraph.isRoute(4, 6) == true);
	assert(myGraph.isRoute(5, 6) == true);
	assert(myGraph.isRoute(3, 2) == true);
	assert(myGraph.isRoute(1, 4) == false);

	// Test 4.2
	int sorted[] = { 1, 3, 4, 6, 23, 96, 125 };

	TreeNode* root = createMinTree(sorted, 7);
	// printPre(root);

	// Test 4.3
	std::vector<std::vector<int>> solution;
	int counter = 0;
	listOfDepths(first, solution, counter);

	// print result array of vectors
	for (unsigned int i = 0; i < solution.size(); i++) {
		for (unsigned int j = 0; j < solution[i].size(); j++) {
			std::cout << solution[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// Test 4.4
	std::cout << "isBalanced: " << isBalanced(first) << std::endl;
	
	// Test 4.5
	std::cout << "isSearchTree: " << isSearchTree(first) << std::endl;

	std::cout << "All test cases passed!" << std::endl;

	return 0;
}
