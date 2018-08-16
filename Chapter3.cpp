// Chapter 3: Stacks and Queues

// Solutions

#include <vector>
#include <stack>
#include <cassert>
#include <iostream>
using namespace std;
/*
	MY QUESTION
	3.0 Stack Implementation: Implement a stack which supports the pop(), push(), peek(), and isEmpty()
	operations.
*/

/*
	3.1 Three in One: Describe how you could use a single array to implement three stacks.
*/

/*
	Solution: If each of the stacks should only support a fixed size, then the array can just be split
	into three parts. We would need to store a start and end index for each portion of the array to be used
	as a stack. If the three stacks can be of variable length, then it is much more complicated. We could
	start off with only a single stack and then allocate another one if the user chooses, or have all of them
	start with a single element, then move the other stacks to the end of the array if any single stack becomes
	too large.
*/

/*
	3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function
	min which returns the minimum element? Push, pop, and min should all operate in O(1) time.
*/

/*
	Solution: One method is to have each element store an extra field which gives the minimum element
	at that point in the stack. If the stack is made up of ints, however, then this method doubles the
	storage space. A different method would be to create another stack of numbers that have been the minimums
	at some point and have them store how many elements to pop off of the other stack before it must be accessed.
	This way, we can keep the order of stack access consistent while also having O(1) access to the minimum,
	which will always be on top of the secondary stack.
*/

/*
	3.3 Stack of Plates:  Imagine a (literal) stack of plates. If the stack gets too high,
	it might topple. Therefore, in real life, we would likely start a new stack when the
	previous stack exceeds some threshold. Implement a data structure SetOfStacks that mimics this.
	SetOfStacks should be composed of several stacks and should create a new stack once the
	previous one exceeds capacity. SetOfStacks. push () and SetOfStacks. pop () should behave
	identically to a single stack (that is, pop ( ) should return the same values as it would
	if there were just a single stack).
*/

class PlateStack {
	public:
		// constructor
		PlateStack(int givenSize);
		// adds elment onto the stack
		void myPush(int element);
		// removes top element from the stack AND returns it
		int myPop();
		void printVals();
	
	private:
		/* vector of stack pointers*/
		stack<stack<int>> plateStackSet;
		int stackSize;
};

PlateStack::PlateStack(int givenSize) {
	stackSize = givenSize;
}

void PlateStack::myPush(int element) {
	// CASE 1: no stack exists
	// -> create first stack and add the element
	if (plateStackSet.size() == 0) {
		stack<int> singleStack;
		singleStack.push(element);
		plateStackSet.push(singleStack);
	}

	// CASE 2: some stacks exist, last one has space
	// -> push element to the last stack
	else if (plateStackSet.top().size() < stackSize) {
		plateStackSet.top().push(element);
	}

	// CASE 3: some stacks exist, but all are full
	// -> push a new stack onto the vector
	// -> push the new element onto this stack
	else {
		stack<int> singleStack;
		singleStack.push(element);
		plateStackSet.push(singleStack);
	}
}

int PlateStack::myPop() {
	// CASE 1: no stack exists
	if (plateStackSet.size() == 0)
		return -1;
	
	// CASE 2: some stacks exist, the top one is empty
	if (plateStackSet.top().size() == 0) {
		plateStackSet.pop();
		int val = plateStackSet.top().top();
		plateStackSet.top().pop();
		return val;
	}

	// CASE 3: some stacks exist, half full
	else {
		int val = plateStackSet.top().top();
		plateStackSet.top().pop();
		return val;
	}
}

void PlateStack::printVals() {
	while (plateStackSet.size() != 0) {
		while (plateStackSet.top().size() != 0) {
			cout << plateStackSet.top().top() << endl;
			plateStackSet.top().pop();
		}
		cout << endl;
		plateStackSet.pop();
	}
}

/*
	3.4: Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks.
*/
template <typename T>
class MyQueue {
	public:
		// constructor
		MyQueue();
		void myAdd(T element);
		T myRemove();
		T myPeek();
		bool myIsEmpty();
		void printQueue();

	private:
		void adjustStacks();
		stack<T> oldVals;
		stack<T> newVals;
};

template <typename T>
MyQueue<T>::MyQueue() {
	// nothing in constructor?
}

template <typename T>
void MyQueue<T>::adjustStacks() {
	// move all elements from newVals to oldVals
	while (!newVals.empty()) {
		oldVals.push(newVals.top());
		newVals.pop();
	}
}

template <typename T>
void MyQueue<T>::myAdd(T element) {
	newVals.push(element);
}

template <typename T>
T MyQueue<T>::myRemove() {
	// retrieve old elements
	if(oldVals.empty())
		adjustStacks();
	T solution = oldVals.top();
	oldVals.pop();
	return solution;
}

template <typename T>
T MyQueue<T>::myPeek() {
	if(oldVals.empty())
		adjustStacks();
	return oldVals.top();
}

template <typename T>
void MyQueue<T>::printQueue() {
	adjustStacks();
	while (!oldVals.empty()) {
		cout << oldVals.top() << endl;
		oldVals.pop();
	}
}

int main() {

	PlateStack test(2);
	test.myPush(1);
	test.myPush(2);
	test.myPush(3);
	test.myPush(4);
	test.myPush(5);
	test.myPush(6);

	/*for (int i = 0; i < 6; i++) {
		cout << "your vals are: " << test.myPop() << endl;
	}*/

	//test.printVals();

	MyQueue<int> test2;
	test2.myAdd(1);
	test2.myAdd(2);
	test2.myAdd(3);
	test2.myAdd(4);
	test2.myRemove();
	test2.myRemove();
	cout << test2.myPeek() << endl;
	test2.printQueue();

	return 0;
}
