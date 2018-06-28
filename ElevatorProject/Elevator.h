#pragma once
#pragma once
#include <iostream>
#include <random>
using namespace std;

/*This is the name of the Nodes that will be used*/
struct level
{
	int requested_level; // This is the level that someone wants to go to
	int num_floors_before_exiting = 0;
	level* next;
	level* previous;
	level(int new_level, level* prev, level* nex) {
		requested_level = new_level;
		next = nex;
		previous = prev;
	};
};

class Elevator
{
private:
	//Variables to be used
	int top_level;
	int count = 0;
	int current_level = 0;
	int num_people_entered = 0;
	int num_people_left = 0;

	level* head = NULL;
	level* tail = NULL;

public:
	Elevator(int top) { top_level = top; };
	int get_current_level() { return current_level; };
	int get_count() { return count; };
	void pick_up_at(int waiting_at);
	void add_level(int level_request);
	//bool check_queue(int requested);
	void remove_level();
	void priority();
};