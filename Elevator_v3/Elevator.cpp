#include "Elevator.h"

void Elevator::pick_up_at(int waiting_at) {
	//If Queue is empty
	if (head == NULL)
	{
		while (current_level != waiting_at)
		{
			/*This is to simulate an elevator moving up and down floors*/
			cout << "Current level is:" << current_level << endl;
			if (current_level < waiting_at) {
				current_level++;
				number_of_travels++;
			}
			else if (current_level > waiting_at) {
				current_level--;
				number_of_travels++;
			}
		}
		random_device number; // This object will be used to generate a random number
		int floor = number() % top_level; // This will generate a random number that will act as the floor the person wishes to go to
		while (floor == waiting_at) // This is to make sure that the choosen floor is not the same as the one they are on
		{
			floor = number() % top_level; // generate a new random number
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
				number_of_travels++;
			}
			else if (waiting_at < current_level)
			{
				cout << "Current level is:" << current_level << endl;
				remove_level();
				current_level--; // decrease the level
				number_of_travels++;
			}
		}
		/*When we reach the level someone is waiting at we want to
			- check if anyone is getting off
			- add whoever is getting on*/
		remove_level();
		random_device number; // This object will be used to generate a random number
		int floor = number() % top_level; // This will generate a random number that will act as the floor the person wishes to go to
		while (floor == waiting_at) // This is to make sure that the choosen floor is not the same as the one they are on
		{
			floor = number() % top_level; // generate a new random number
		}
		add_level(floor); // add the floor to the queue
	}

	/*This is too help visualize the current queue of floor request*/
	/*level* temp = head;
	for (int i = 0; i < count; i++)
	{
		cout << temp->requested_level << " " << endl;
		temp = temp->next;
	}*/
}

void Elevator::add_level(int level_request)
{
	/*For this we want to:
		- check if we are adding the first element in the queue
		- check if we are adding something to a none empty queue
			- Also check if the requested level is already in the queue*/

	if (head == NULL){ 
		level* add_to_queue = new level(level_request, NULL, NULL); // create a new level object that will be added
		head = add_to_queue; // set head to the new level
		tail = head; // set tail to head
		cout << "Entered on level: " << current_level << endl;
		count++; // increase the count of the number of people in the elevator
	}
	else if (head != NULL)
	{
		level* temp = head;
		for (int i = 0; i < count; i++) // This is to check if the request is already in the queue
		{
			if (temp->requested_level == level_request) { // if it is in queue then we don't add it
				return;
			}
			temp = temp->next;
		}
		/*If the request was not found in the queue then we add it*/
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
	level* temp = head; //This will help us go through the queue
	for (int i = 0; i < count; i++) // This is to iterate through the queue
	{
		if (temp->requested_level == current_level) // If we found a request for the floor the Elevator is on then we want to check a few things
		{
			if (temp == head) // Check if the one getting off is the head
			{
				if (head->next == NULL) // check is the next spot is empty (i.e. the queue will be empty)
				{
					if (head->num_floors_before_exiting * 5 > longest_ride)
					{
						longest_ride = head->num_floors_before_exiting * 5; // This is to report what was the longest wait time for someone
					}
					else if (head->num_floors_before_exiting * 5 < shortest_ride || shortest_ride == 0)
					{
						shortest_ride = head->num_floors_before_exiting * 5; // This is to report the shortest ride
					}
					cout << "Exited on level: " << current_level << endl; 
					cout << "Went through: " << head->num_floors_before_exiting << " levels before exiting" << endl;
					head = NULL; // Since the queue will be empty we can just set head to NULL
					tail = head; // We can set tail to head
					count = 0; // Reset our count to 0
				}
				else { // If the queue will not be empty after removing the head we have to be more careful
					level* remove_this = head; // This is what will be removed
					head = head->next; // Make the next in the queue the head
					head->previous = NULL; // Sever the connection to the previous head
					remove_this->next = NULL; // Sever the connection to the queue
					if (remove_this->num_floors_before_exiting * 5 > longest_ride)
					{
						longest_ride = remove_this->num_floors_before_exiting * 5; // This is to keep track of the longest ride
					}
					else if (remove_this->num_floors_before_exiting * 5 < shortest_ride || shortest_ride == 0)
					{
						shortest_ride = remove_this->num_floors_before_exiting * 5; // This is to report the shortest ride
					}
					cout << "Exited on level: " << current_level << endl;
					cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
					delete remove_this; // This simulates all that wanted to get off on that floor exiting
					count--; // Decrease our queue count
				}
			}
			else { // If the one to remove is not the head
				level* remove_this = temp; // This will be used to remove the request
				if (remove_this == tail) // If what we are removing is the tail we have to be careful
				{
					tail = remove_this->previous; // first set the tail to the one before the request that is being removed
					tail->next = NULL; // Sever the connection to the previous tail
					remove_this->previous = NULL; // Sever the connction to the queue
					if (remove_this->num_floors_before_exiting * 5 > longest_ride)
					{
						longest_ride = remove_this->num_floors_before_exiting * 5; // This is to keep track of the longest ride
					}
					else if (remove_this->num_floors_before_exiting * 5 < shortest_ride || shortest_ride == 0)
					{
						shortest_ride = remove_this->num_floors_before_exiting * 5; // This is to report the shortest ride
					}
					cout << "Exited on level: " << current_level << endl;
					cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
					delete remove_this; // This simulates all that wanted to get off on that floor exiting
					count--;// Decrease our count
				}
				else { // If it is not the tail
					remove_this->previous->next = remove_this->next; // We want to make the previous's next be the one after the one that is being removed
					if (remove_this->next != NULL) { // We want to check if the Node after the one we are removing is  not NULL (This way we dont have to worry checking if it is NULL)
						remove_this->next->previous = remove_this->previous; // We want the next's previous to be the one before the Node we are removing
						remove_this->previous = NULL; // We want to sever the connection to the previous
						remove_this->next = NULL; // We want to the next
						if (remove_this->num_floors_before_exiting * 5 > longest_ride)
						{
							longest_ride = remove_this->num_floors_before_exiting * 5; // This is to keep track of the longest ride
						}
						else if (remove_this->num_floors_before_exiting * 5 < shortest_ride || shortest_ride == 0)
						{
							shortest_ride = remove_this->num_floors_before_exiting * 5; // This is to report the shortest ride
						}
						cout << "Exited on level: " << current_level << endl;
						cout << "Went through: " << remove_this->num_floors_before_exiting << " levels before exiting" << endl;
						delete remove_this; // This simulates all that wanted to get off on that floor exiting
						count--; // Decrease our count
					}
				}
			}
		}
		/*This is important and used to keep track of how many levels have been visted
			by the people in the elevator going to a specific floor.
			Every floor will count as 5 seconds that they were in the elevator*/
		temp->num_floors_before_exiting++;
		temp = temp->next; // Move to the next Node and do it all again
	}
}

void Elevator::priority()
{
	// This is to make sure that the head gets without waiting too long
	while (head != NULL)
	{
		// We want to see if the elevator needs to go up or down to let the head out
		if (head->requested_level < current_level) 
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
			current_level--;
			number_of_travels++;
		}
		else if (head->requested_level > current_level)
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
			current_level++;
			number_of_travels++;
		}
		else
		{
			cout << "Current level is:" << current_level << endl;
			remove_level();
		}
	}
}



