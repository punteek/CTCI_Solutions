// Chapter 2: Linked Lists

// Solutions

#include <iostream>
#include <unordered_set>
#include <stack>
#include <cmath>
using namespace std;

// Simple singly-linked list implementation

struct Node {
	int data = 0;
	Node* next = nullptr;
};

void insert(Node*& head, int value) {
	Node* toInsert = new Node;
	toInsert->data = value;
	toInsert->next = head;
	head = toInsert;
}

// to check linked list current state

void print(Node* head)
{
	while (head != nullptr) {
		cout << head->data << endl;
		head = head->next;
	}
	cout << endl;
}

/*
	2.1 Remove Dups: Write code to remove duplicates from an unsorted linked list.
*/

void removeDupes(Node* head) {
	if (head == nullptr || (head != nullptr && head->next == nullptr))
		return;

	unordered_set<int> dupes;
	unordered_set<int>::iterator it;

	dupes.insert(head->data);

	while (head->next != nullptr) {
		it = dupes.find(head->next->data);
		if (it == dupes.end()) {
			dupes.insert(head->next->data);
			head = head->next;
		}
		else {
			Node* toDelete = head->next;
			head->next = head->next->next;
			delete toDelete;
		}
	}
}

/*
	2.2 Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.
*/

int kthToLast(Node* head, int k) {
	if (head == nullptr || k < 0)
		return -1;

	Node* atK = head;
	Node* atEnd = head;

	int toMove = 0;
	while (toMove != k - 1 && atEnd != nullptr) {
		atEnd = atEnd->next;
		toMove++;
	}
	if (toMove < k - 1)
		return -1;
	while (atEnd->next != nullptr) {
		atK = atK->next;
		atEnd = atEnd->next;
	}
	return atK->data;
}

/*
	2.3 Delete Middle Node: Implement an algorithm to delete a node in the middle (i.e., any node but the
	first and last node, not necessarily the exact middle) of a singly linked list, given only access to that node.
*/

void deleteMid(Node* midNode) {
	// assume that midNode cannot be the first or last node
	Node* toDelete = midNode->next;
	midNode->next = toDelete->next;
	midNode->data = toDelete->data;
	delete toDelete;
}

/*
	2.4 Partition: Write code to partition a linked list around a value x, such that all nodes less than x come
	before all nodes greater than or equal to x. If x is contained within the list, the values of x only need to be
	after the elements less than x (see below). The partition element x can appear anywhere in the "right partition";
	it does not need to appear between the left and right partitions.
*/

void partition(Node* head, int partVal) {
	if (head == nullptr || (head != nullptr && head->next == nullptr))
		return;

	Node* swapId = head;
	Node* iter = head;

	while (swapId->data < partVal) {
		swapId = swapId->next;
		iter = iter->next;
	}

	while (swapId != nullptr && iter != nullptr) {
		if (iter->data < partVal) {
			int temp = swapId->data;
			swapId->data = iter->data;
			iter->data = temp;
			while (swapId->data < partVal) {
				swapId = swapId->next;
			}
			iter = iter->next;
		}
		else {
			iter = iter->next;
		}
	}
}

/*
	2.5 Sum Lists: You have two numbers represented by a linked list, where each node contains a single digit.
	The digits are stored in reverse order, such that the 1's digit is at the head of the list. Write a
	function that adds the two numbers and returns the sum as a linked list.
*/
// TODO: forward version
Node* sumLists(Node* num1, Node* num2) {
	if (num1 == nullptr && num2 == nullptr)
		return nullptr;
	if (num1 == nullptr && num2 != nullptr)
		return num2;
	if (num2 == nullptr && num1 != nullptr)
		return num1;

	Node* solHead = nullptr;
	int carry = 0;
	
	while (num1 != nullptr && num2 != nullptr) {
		int sum = num1->data + num2->data + carry;
		insert(solHead, sum % 10);
		if (sum > 9)
			carry = 1;
		else
			carry = 0;
		num1 = num1->next;
		num2 = num2->next;
	}

	if (carry == 1 && num1 != nullptr) {
		while (carry != 0 && num1 != nullptr) {
			int sum = num1->data + carry;
			insert(solHead, sum % 10);
			if (sum > 9)
				carry = 1;
			else
				carry = 0;
			num1 = num1->next;
		}
		if (carry == 1)
			insert(solHead, 1);
	}

	if (carry == 1 && num2 != nullptr) {
		while (carry != 0 && num2 != nullptr) {
			int sum = num2->data + carry;
			insert(solHead, sum % 10);
			if (sum > 9)
				carry = 1;
			else
				carry = 0;
			num2 = num2->next;
		}
		if (carry == 1)
			insert(solHead, 1);
	}
	return solHead;
}

/*
	2.6 Palindrome: Implement a function to check if a linked list is a palindrome.
*/

bool isPalindrome(Node* head) {
	if (head == nullptr || (head != nullptr && head->next == nullptr))
		return true;

	Node* toCheck = head;
	stack<int> vals;

	while (head != nullptr) {
		vals.push(head->data);
		head = head->next;
	}

	while (toCheck != nullptr) {
		if (toCheck->data != vals.top())
			return false;
		else {
			vals.pop();
			toCheck = toCheck->next;
		}
	}
	return true;
}

/*
	2.7 Intersection:  Given two (singly) linked lists, determine if the two lists intersect. Return
	the intersecting node. Note that the intersection is defined based on reference, not value. That is,
	if the kth node of the first linked list is the exact same node (by reference) as the jth node of the
	second linked list, then they are intersecting. 
*/
// UNTESTED!!!
Node* intersection(Node* list1, Node* list2) {
	if (list1 == nullptr || list2 == nullptr)
		return nullptr;
	if (list1 == nullptr || list2 == nullptr)
		return nullptr;

	int count1 = 0, count2 = 0;
	Node* temp1 = list1, *temp2 = list2;

	while (list1 != nullptr) {
		count1++;
		list1 = list1->next;
	}
	while (list2 != nullptr) {
		count2++;
		list2 = list2->next;
	}

	int diff = abs(count1 - count2);

	if (count1 < count2) {
		while (diff != 0) {
			temp2 = temp2->next;
			diff--;
		}
		while (temp2 != nullptr) {
			if (temp1 == temp2)
				return temp1;
			else {
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
	}
	else {
		while (diff != 0) {
			temp1 = temp1->next;
			diff--;
		}
		while (temp1 != nullptr) {
			if (temp1 == temp2)
				return temp2;
			else {
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
	}
	return nullptr;
}

/*
	2.8 Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
	beginning of the loop.
*/
// UNTESTED!!!
Node* detectLoop(Node* head) {
	if (head == nullptr)
		return nullptr;
	Node* slow = head;
	Node* fast = head;

	while (slow != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}
	if (fast == nullptr || fast->next == nullptr)
		return nullptr;
	slow = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

int main()
{
	// build and test basic linked list
	//
	//Node* head = nullptr;
	//insert(head, 1);
	//insert(head, 2);
	//insert(head, 10);
	//insert(head, 5);
	//insert(head, 8);
	//insert(head, 5);
	//insert(head, 3);
	//
	//print(head);
	//
	///*
	//removeDupes(head);
	//cout << "\n" << kthToLast(head, 3) << endl;
	//deleteMid(head->next->next);
	//*/
	//partition(head, 12);

	//print(head);

	/*Node* firstNum = nullptr;
	insert(firstNum, 6);
	insert(firstNum, 1);
	insert(firstNum, 7);*/
	//print(firstNum);

	/*Node* secNum = nullptr;
	insert(secNum, 9);
	insert(secNum, 7);
	insert(secNum, 4);*/
	//print(secNum);

	//print(sumLists(firstNum, secNum));

	//cout << isPalindrome(secNum) << endl;

	return 0;
}
