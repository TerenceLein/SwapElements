/* 
 * File:   main.cpp
 * Author: Terence Lein
 *
 * Created on April 18, 2014, 6:39 PM
 */

/****
 * Swap Elements : a simple Code Eval challenge
 * 
 * A set of integers is given followed by set of element swap operations
 * <input file> :: <test> \n <test> \n ...
 * <test> :: <elements> : <operations>
 * <elements> :: <integer0> <integer1> ...
 * <operations> :: <operation>, <operation>, ...
 * <operation> :: <element1> - <element2>
 ****/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cerrno>
#include <vector>

// getList - given a string of integers, parse into a set (vector container) of elements
void getList (std::vector<int>& list, std::string str) {
	int num;
	std::istringstream is (str);
	while(is >> num){
		list.push_back(num);
	}
}

// OPERATION - basic operation type which contains the two element positions to swap
typedef struct {
	int first;
	int second;
} OPERATION;

// getOperation - given a string of two hyphen separated integers, parse into an element swap operation
void getOperation (OPERATION& op, std::string str){
	std::istringstream is(str);
	char hyphen;
	is >> op.first;
	is >> hyphen;
	is >> op.second;
}

// getOperations - given a string of hyphen separated integers each comma separated, 
// parse into a set of element swap operations
void getOperations (std::vector<OPERATION>& ops, std::string str){
	OPERATION op;
	std::istringstream is (str);
	std::string soperation;

	while(std::getline(is,soperation,',')){
		getOperation(op,soperation);		// parse each comma separated segment into an operation
		ops.push_back(op);
	}
}

// perform all of the swap operations on the set of elements
// <list> :: element set
// <ops> :: operation set
void doSwaps (std::vector<int>& list, std::vector<OPERATION>& ops){
	for(size_t i = 0; i < ops.size(); i++){
		
		// elements are not swapped with themselves
		if(list[ops[i].first] == list[ops[i].second]) continue;

		// perform the swap in place
		list[ops[i].first] ^= list[ops[i].second];
		list[ops[i].second] ^= list[ops[i].first];
		list[ops[i].first] ^= list[ops[i].second];
	}
}

// printList - print the list to standard output
void printList (std::vector<int>& list) {
	for(size_t i = 0; i < list.size(); i++){
		std::cout << list[i] << " ";
	}
	std::cout << "\n";
}

// processLine - parse a line from the input file into the element and operation sets
// then perform the element swaps
void processLine (std::string& str) {

	std::istringstream is(str);
	std::string segment;
	
	// parse the element set
	std::vector<int> list;
	list.reserve(10);
	std::getline(is, segment, ':');
	getList(list,segment);
	
	// parse the operation set
	std::vector<OPERATION> ops;
	ops.reserve(10);
	std::getline(is, segment, ':');
	getOperations(ops, segment);
	
	// swap the elements as instructed
	doSwaps (list,ops);
		
	// print out the elements in their new order
	printList (list);
}

// command line program is given the name of a text file
// each line is a test with a set of elements followed by a set of swap operations
int main(int argc, char **argv)
{
	std::ifstream file;
	std::string line;
	file.open (argv[1]);

	if(file.good()){
		while(std::getline(file,line)){
			processLine(line);
		}
	}else{
		std::cout << strerror(errno) << "\n";
		std::cout << "Could not open " << argv[1] << "\n";
	}

	return 0;
}
