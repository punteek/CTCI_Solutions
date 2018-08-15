// Chapter 1: Arrays and Strings

// Solutions

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
1.1 Is Unique: Implement an algorithm to determine if a string has all unique characters.
What if you cannot use additional data structures?
*/

// assume ascii characters
bool isUnique(const string& s) {
	if (s.length() > 128)
		return false;

	vector<bool> repeats(128, false);

	for (unsigned int i = 0; i < s.length(); i++) {
		int index = s[i]; // this casts the letter to corresponding ascii value
		if (repeats[index])
			return false;
		else
			repeats[index] = true;
	}
	return true;
}

// 1.2 Check Permutation: Given two strings, write a method to decide if one is a permutation of the other.

bool isPermutation(const string& s1, const string& s2)
{
	if (s1.length() != s2.length())
		return false;

	vector<int> freq(128, 0);
	for (unsigned int i = 0; i < s1.length(); i++) {
		int index = s1[i];
		freq[index]++;
	}
	for (unsigned int i = 0; i < s2.length(); i++) {
		int index = s2[i];
		freq[index]--;
		if (freq[index] < 0)
			return false;
	}
	return true;
}

/*
	1.3 URLify: Write a method to replace all spaces in a string with "%20". You may assume
	that the string has sufficient space at the end to hold the additional characters, and that
	you are given the "true" length of the string.
*/

// use cstring
void URLify(char* original, int len) {
	
	int orgSpaces = 0;
	for (int i = 0; i < len; i++){
		if (original[i] == ' ')
			orgSpaces++;
	}

	int fullLength = 2 * orgSpaces + len;
	// start at the end
	int i = fullLength - 1;

	// start at the end of the string
	for (int j = len - 1; j >= 0; j--) {
		if (original[j] != ' ')
			original[i--] = original[j];
		// the original has a space
		else {
			original[i--] = '0';
			original[i--] = '2';
			original[i--] = '%';
		}
	}
}

/*
	1.4 Palindrome Permutation: Given a string, write a function to check if it is a permutation of a
	palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation
	is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.
*/

bool isPalindrome(string s1)
{
	unordered_set<char> charSet;
	unordered_set<char>::iterator found;

	for (unsigned int i = 0; i < s1.length(); i++) {
		found = charSet.find(s1[i]);

		if (found == charSet.end())
			charSet.insert(s1[i]);
		else
			charSet.erase(s1[i]);
	}
	return charSet.size() <= 1;
}

/*
	1.5 One Away: There are three types of edits that can be performed on strings: insert a character,
	remove a character, or replace a character. Given two strings, write a function to check if they
	are one edit (or zero edits) away.
*/

bool oneAway(const string& str1, const string& str2) {
	string s1 = str1;
	string s2 = str2;

	if (str1.compare(str2) == 0)
		return true;

	if (str1.length() - str2.length() == 1) {
		for (unsigned int i = 0; i < str1.length(); i++) {
			if (str1[i] != str2[i]) {
				s2.insert(i, str1.substr(i, 1));
				if (s2.compare(str1) != 0)
					return false;
				else
					return true;
			}
		}
	}
	else if (str2.length() - str1.length() == 1) {
		for (unsigned int i = 0; i < str2.length(); i++) {
			if (str1[i] != str2[i]) {
				s1.insert(i, str2.substr(i, 1));
				if (s1.compare(str2) != 0)
					return false;
				else
					return true;
			}
		}
	}
	else if (str1.length() - str2.length() == 0) {
		for (unsigned int i = 0; i < str1.length(); i++) {
			if (str1[i] != str2[i]) {
				s1.replace(i, 1, str2.substr(i, 1));
				if (s1.compare(str2) != 0)
					return false;
				else
					return true;
			}
		}
	}
	return false;
}

/*
	1.6 String Compression: Implement a method to perform basic string compression using the counts
	of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3. If the
	"compressed" string would not become smaller than the original string, your method should return
	the original string. You can assume the string has only uppercase and lowercase letters (a-z).
*/

string squish(const string& str) {
	if (str.length() == 0 || str.length() == 1)
		return str;

	int freq = 1;
	string solution = "";
	for (unsigned int i = 0, j = 1; i < str.length();) {
		if (j == str.length()) {
			solution += str[i] + to_string(freq);
			break;
		}
		if (str[i] == str[j]) {
			freq++;
			j++;
			continue;
		}
		else {
			solution += str[i] + to_string(freq);
			i = j;
			j++;
			freq = 1;
		}
	}
	if (solution.length() < str.length())
		return solution;
	else
		return str;
}

/*
	1.7 Rotate Matrix: Given an NxN matrix of numbers, write a method
	to rotate the matrix by 90 degrees. Can you do this in place?
*/

// clockwise
void rotateMatrix(int** array, int n) {
	// transpose
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < i; j++) {
			int temp = array[i][j];
			array[i][j] = array[j][i];
			array[j][i] = temp;
		}
	}

	// reverse rows
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n / 2; j++) {
			int temp = array[i][j];
			array[i][j] = array[i][n - j - 1];
			array[i][n - j - 1] = temp;
		}
	}
}

/*
function to test rotate
*/

void printArr(int** toPrint) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << toPrint[i][j];
		}
		cout << endl;
	}
}

/*
	1.8 Zero Matrix: Write an algorithm such that if an element in an NxM
	matrix is 0, its entire row and column are set to 0.
*/

void zeroMatrix(int** array, int length) {
	vector<bool> rows(length, false);
	vector<bool> cols(length, false);

	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < length; j++) {
			if (array[i][j] == 0) {
				rows[i] = true;
				cols[j] = true;
			}
		}
	}

	for (size_t i = 0; i < length; i++) {
		if (rows[i]) {
			for (size_t j = 0; j < length; j++) {
				array[i][j] = 0;
			}
		}
	}

	for (size_t i = 0; i < length; i++) {
		if (cols[i]) {
			for (size_t j = 0; j < length; j++) {
				array[j][i] = 0;
			}
		}
	}
}

/*
	1.9 String Rotation: Assume you have a method isSubstring which checks if one word
	is a substring of another. Given two strings, s1 ans s2, write code to check if s2
	is a rotation of s1 using only one call to isSubstring (e.g. "waterbottle" is a
	rotation of "erbottlewat").
*/

bool isRotation(string s1, string s2)
{
	if (s2.length() == 0)
		return false;
	string test = s1 + s1;
	size_t found = test.find(s2);
	if (found != std::string::npos)
		return true;
	return false;
}

int main()
{
	// All test cases for problems in Chapter 1

	/////////////// Test 1.1 ///////////////

	assert(isUnique("hello") == false);
	assert(isUnique("bye") == true);
	assert(isUnique("llll") == false);
	assert(isUnique("abcda") == false);

	/////////////// Test 1.2 ///////////////

	assert(isPermutation("", "") == true);
	assert(isPermutation("d", "") == false);
	assert(isPermutation("", "g") == false);
	assert(isPermutation("hello", "ollhe") == true);
	assert(isPermutation("hello", "lksjd") == false);

	/////////////// Test 1.3 ///////////////

	char test1[] = "hello dude  ";
	char test2[] = "he llo man    ";

	URLify(test1, 10);
	URLify(test2, 10);

	char answer1[] = "hello%20dude";
	char answer2[] = "he%20llo%20man";

	//cout << test1 << endl << test2 << endl;

	assert(strcmp(test1, answer1) == 0);
	assert(strcmp(test2, answer2) == 0);

	/////////////// Test 1.4 ///////////////

	assert(isPalindrome("abbb") == false);
	assert(isPalindrome("abbba") == true);
	assert(isPalindrome("aabbcc") == true);
	assert(isPalindrome("aabcc") == true);
	assert(isPalindrome("abc") == false);
	assert(isPalindrome("") == true);
	assert(isPalindrome("a") == true);

	/////////////// Test 1.5 ///////////////

	assert(oneAway("pale", "ple") == true);
	assert(oneAway("pales", "pale") == true);
	assert(oneAway("pale", "bale") == true);
	assert(oneAway("pale", "bake") == false);

	/////////////// Test 1.6 ///////////////

	// solution: "a2b1c5a3"
	string sol1 = squish("aabcccccaaa");
	// solution: "a2b1c2a2" -> so return input
	string sol2 = squish("aabccaa");

	assert(sol1.compare("a2b1c5a3") == 0);
	assert(sol2.compare("aabccaa") == 0);

	/////////////// Test 1.7 ///////////////

	/////////////// Test 1.8 ///////////////

	// test the function
	// can check the output, the correct entries are zeroed out

	/////////////// Test 1.9 ///////////////
	
	assert(isRotation("erbottlewat", "waterbottle") == true);

	cout << "All test cases passed!" << endl;

	return 0;
}
