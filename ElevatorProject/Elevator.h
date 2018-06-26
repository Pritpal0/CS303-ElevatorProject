#pragma once
#include <iostream>
using namespace std;

struct level
{
	int requested_level;
	level* next;
	level(int new_level) {
		requested_level = new_level;
		next = NULL;
	};
};

class Elevator
{
private:
	int top_level;
	int ground_level = 0;
	int count;
	int current_level;
	level* head;
	level* tail;

public:
	Elevator(int top) { current_level = ground_level; head = NULL; top_level = top; };
	int get_current_level() { return current_level; };
	void pick_up_at(int waiting_at);
	void add_level(int level_request);
	void remove_level(bool from_pick_up);
};
