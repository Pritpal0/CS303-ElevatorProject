#pragma once
#pragma once
#include <iostream>
#include <random>
using namespace std;

/*This is the name of the Nodes that will be used*/
struct level
{
	int requested_level; // This is the level that someone wants to go to
	int num_floors_before_exiting = 0; // This to keep of the number of floors someone has traveled
	level* next; // This is the next node
	level* previous; // This is the previous node

	level(int new_level, level* prev, level* nex) { // This the defualt constructor
		requested_level = new_level;
		next = nex;
		previous = prev;
	};
};

class Elevator
{
private:
	//Variables to be used
	int top_level; // This is to simulate the highest floor
	int count = 0; // This is to keep track the queue size
	int current_level = 0; // This is to keep track of the current elevator level
	int longest_ride = 0; // This is to keep track of the longest ride
	int shortest_ride = 0;
	int number_of_travels = 0;

	level* head = NULL;
	level* tail = NULL;

public:
	Elevator(int top) {top_level = top; }; // Defualt constructor
	int get_current_level() { return current_level; };// Returns current level 
	int get_count() { return count; }; // returns count
	int get_longest_ride() { return longest_ride; }; // returns longest ride
	int get_shortest_ride() { return shortest_ride; };// returns shortest ride
	int get_number_of_travels() { return number_of_travels; }; // returns number of travels
	void pick_up_at(int waiting_at); // This is to simulate someone requesting to get on
	void add_level(int level_request);// This add the request to the queue
	void remove_level(); // This is to simulate someone exiting the elevator
	void priority(); // This is to ensure everyone leaves the elevator
};