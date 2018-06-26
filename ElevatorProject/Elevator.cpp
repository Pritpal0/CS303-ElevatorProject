#include "stdafx.h"
#include "Elevator.h"

void Elevator::pick_up_at(int waiting_at)
{
	//If Queue is empty
	if (head == NULL)
	{
		current_level = waiting_at;
	}
	//If Queue is not empty
	else if (head != NULL) {
		while (current_level != waiting_at) {
			if (current_level < waiting_at) {
				remove_level(true);
				current_level++;
			}
			else if (waiting_at < current_level)
			{
				remove_level(true);
				current_level--;
			}
		}
	}
	cout << "Entered on level: " << current_level << endl;
}

void Elevator::add_level(int level_request) {
	//If queue is empty
	if (head == NULL)
	{
		head = new level(level_request);
		tail = head;
		current_level = level_request;
		count++;
	}

	//If queue is not empty
	else if (head != NULL)
	{
		level* temp = head;
		for (int i = 0; i < count; i++) {
			if (temp->next == NULL) {
				cout << "Elevator Empty" << endl;
			}
			else if (temp->requested_level == level_request) {
				cout << "New request: " << level_request << endl;
				return;
			}
			temp = temp->next;
		}
		tail->next = new level(level_request);
		tail = tail->next;
		count++;
	}
	cout << "Current level is: " << current_level << endl;
}

void Elevator::remove_level(bool from_pick_up) {
	level* temp = head;
	if (from_pick_up == true) {
		for (int i = 0; i < count; i++) {
			if (temp->requested_level == current_level) {
				level* to_remove = temp;
				temp->next = to_remove->next;
				delete to_remove;
				count--;
				return;
			}
			else {
				temp = temp->next;
			}
		}
		return;
	}
	else {
		if (current_level < head->requested_level) {
			while (head->requested_level != current_level) {
				if (temp->requested_level == current_level) {
					level* to_remove = temp;
					temp->next = to_remove->next;
					delete to_remove;
					count--;
					cout << "Exited on level: " << current_level << endl;
					current_level++;
				}
				else {
					temp = temp->next;
				}
			}
		}
		else if (current_level > head->requested_level) {
			while (head->requested_level != current_level) {
				if (temp->requested_level == current_level) {
					level* to_remove = temp;
					temp->next = to_remove->next;
					delete to_remove;
					count--;
					cout << "Exited on level: " << current_level << endl;
					current_level--;
				}
				else {
					temp = temp->next;
				}
			}
		}
		current_level = head->requested_level;
		temp = head;
		head = head->next;
		delete temp;
		count--;
		cout << "Exited on level: " << current_level << endl;

	}
}