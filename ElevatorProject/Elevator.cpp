#include "stdafx.h"
#include "Elevator.h"

using namespace std;
void Elevator::pick_up_at(int waiting_at) {
	//If Queue is empty
	if (head == NULL)
	{
		while (current_level != waiting_at)
		{
			cout << "Current level is:" << current_level << endl;
			if (current_level < waiting_at)
				current_level++;
			else if (current_level > waiting_at)
				current_level--;
		}
		random_device number; // This object will be used to generate a random number
		int floor = number() % 10; // This will generate a random number that will act as the floor the person wishes to go to
		while (floor == waiting_at) // This is to make sure that the choosen floor is not the same as the one they are on
		{
			floor = number() % 10; // generate a new random number
		}
		add_level(floor); // add the floor to the queue
	}

	//If Queue is not empty
	else if (head != NULL) {
		/*When a new person wants to get on then we want to move through the levels
		until the current level is equal to the level someone is waiting at*/
		while (current_level != waiting_at) {
			/*We want to be able to check whether we go up or down*/
			if (current_level < waiting_at) {
				cout << "Current level is:" << current_level << endl;
				remove_level(); // When we go to a new level we want to check if someone wants to get off at this level
				current_level++; // increase the level
			}
			else if (waiting_at < current_level)
			{
				cout << "Current level is:" << current_level << endl;
				remove_level();
				current_level--; // decrease the level
			}
		}
		/*When we reach the level someone is waiting at we want to
		- check if anyone is getting off
		- add whoever is getting on*/
		remove_level();
		random_device number; // This object will be used to generate a random number
		int floor = number() % 10; // This will generate a random number that will act as the floor the person wishes to go to
		while (floor == waiting_at) // This is to make sure that the choosen floor is not the same as the one they are on
		{
			floor = number() % 10; // generate a new random number
		}
		add_level(floor); // add the floor to the queue
	}
	level* temp = head;
	for (int i = 0; i < count; i++)
	{
		cout << temp->requested_level << " " << endl;
		temp = temp->next;
	}
}

void Elevator::add_level(int level_request)
{
	/*For this we want to:
	- check if we are adding the first element in the queue
	- check if we are adding something to a none empty queue
	- Also check if the requested level is already in the queue*/

	if (head == NULL) {
		level* add_to_queue = new level(level_request, NULL, NULL); // create a new level object that will be added
		head = add_to_queue; // set head to the new level
		tail = head; // set tail to head
		cout << "Entered on level: " << current_level << endl;
		count++; // increase the count of the number of people in the elevator
				 //num_people_entered++;
	}
	else if (head != NULL)
	{
		level* temp = head;
		for (int i = 0; i < count; i++) // This is to check if the request is already in the queue
		{
			if (temp->requested_level == level_request) { // if it is in queue then:
														  //num_people_entered++; // increase the number of people that stepped into elevator
				return;
			}
			temp = temp->next;
		}
		level* add_to_queue = new level(level_request, NULL, NULL);
		tail->next = add_to_queue;
		add_to_queue->previous = tail;
		tail = add_to_queue;
		count++;
		cout << "Entered on level: " << current_level << endl;
	}
}

void Elevator::remove_level()
{
	level* temp = head;
	for (int i = 0; i < count; i++)
	{
		if (temp->requested_level == current_level)
		{
			if (temp == head)
			{
				if (head->next == NULL)
				{
					cout << "Exited on level: " << current_level << endl;
					cout << "Went through: " << head->num_floors_before_exiting << " levels before exiting" << endl;
					head = NULL;
					tail = head;
					count = 0;
				}
				else {
					level* remove_this = head;
					head = head->next;
					head->previous = NULL;
					remove_this->next = NULL;
					cout << "Exited on level: " << current_level << endl;
					cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
					delete remove_this;
					count--;
				}
			}
			else {
				level* remove_this = temp;
				if (remove_this == tail)
				{
					tail = remove_this->previous;
					tail->next = NULL;
					remove_this->previous = NULL;
					cout << "Exited on level: " << current_level << endl;
					cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
					delete remove_this;
					count--;
				}
				else {
					remove_this->previous->next = remove_this->next;
					if (remove_this->next != NULL) {
						remove_this->next->previous = remove_this->previous;
						remove_this->previous = NULL;
						remove_this->next = NULL;
						cout << "Exited on level: " << current_level << endl;
						cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
						delete remove_this;
						count--;
					}
				}
			}
		}
		temp->num_floors_before_exiting++;
		temp = temp->next;
	}
}

void Elevator::priority()
{
	while (head != NULL)
	{
		if (head->requested_level < current_level)
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
			current_level--;
		}
		else if (head->requested_level > current_level)
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
			current_level++;
		}
		else
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
		}
	}
}



