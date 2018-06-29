#include "Elevator.h"
#include "time.h"
//Try to compare the differences in levels and request orders
// make a report at the end
// mode the simulation to be able to have more traffic
// to mode the number of elevators
//make uml diagram and complexities
int main()
{
	//The clock objects are to help run the simulation for 1 second
	clock_t end = clock() + 1000; // This is 1 second from current time
	clock_t current_time = clock(); // This is current time
	random_device chance;
	random_device top_floor;
	random_device luck; // This is to get random numbers to simulate random request

	//Simulation 1:
	int top = top_floor() % 100;
	cout << "This building has: " << top << " floors." << endl;
	Elevator elevator(top);
	while (current_time < end)
	{
		current_time = clock();
		int waiting = luck() % top;
		elevator.pick_up_at(waiting);
		if (current_time % 2 == 0)
		{
			waiting = luck() % top;
			elevator.pick_up_at(waiting);
			current_time = clock();
		}
		elevator.priority();
	}
	cout << endl << "Single Elevator Simulation ended" << endl << endl;
	cout << "This building had: " << top << " floors." << endl;
	cout << "Longest ride was " << elevator.get_longest_ride() * 5 << " seconds" << endl;
	cout << "Shortest ride was " << elevator.get_shortest_ride() * 5 << " seconds" << endl;
	cout << "Total number of travels done were " << elevator.get_number_of_travels() << endl;
	cout << " Press any key to run simulation 2..." << endl;
	system("pause");


	//Simulation 2:
	top = top_floor() % 100;
	end = clock() + 1000;
	current_time = clock();
	Elevator elevator_1(top);
	Elevator elevator_2(top);
	while (current_time < end)
	{
		current_time = clock();
		int waiting = luck() % top;

		if ((abs(elevator_1.get_current_level() - waiting)) < (abs(elevator_2.get_current_level() - waiting))) {
			cout << "Sending Elevator 1" << endl;
			elevator_1.pick_up_at(waiting);
		}
		else if ((abs(elevator_1.get_current_level() - waiting)) > abs((elevator_2.get_current_level() - waiting))) {
			cout << "Sending Elevator 2" << endl;
			elevator_2.pick_up_at(waiting);
		}
		else
		{
			cout << "Sending Elevator 1" << endl;
			elevator_1.pick_up_at(waiting);
		}

		if (current_time % 2 == 0)
		{
			waiting = luck() % top;
			if ((abs(elevator_1.get_current_level() - waiting)) < (abs(elevator_2.get_current_level() - waiting))) {
				cout << "Sending Elevator 1" << endl;
				elevator_1.pick_up_at(waiting);
			}
			else if ((abs(elevator_1.get_current_level() - waiting)) > abs((elevator_2.get_current_level() - waiting))) {
				cout << "Sending Elevator 2" << endl;
				elevator_2.pick_up_at(waiting);
			}
			else
			{
				cout << "Sending Elevator 1" << endl;
				elevator_1.pick_up_at(waiting);
			}
		}
		elevator_1.priority();
		elevator_2.priority();
	}
	cout << endl << "Multi Elevator Simulation ended" << endl << endl;
	cout << "This building has: " << top << " floors." << endl;
	cout << "Longest ride on Elevator 1 was " << elevator_1.get_longest_ride() * 5 << " seconds" << endl;
	cout << "Shortest ride on Elevator 1 was " << elevator_1.get_shortest_ride() * 5 << " seconds" << endl;
	cout << "Total number of travels done by Elevator 1 were " << elevator_1.get_number_of_travels() << endl << endl;

	cout << "Longest ride on Elevator 2 was " << elevator_2.get_longest_ride() * 5 << " seconds" << endl;
	cout << "Shortest ride on Elevator 2 was " << elevator_2.get_shortest_ride() * 5 << " seconds" << endl;
	cout << "Total number of travels done by Elevator 2 were " << elevator_2.get_number_of_travels() << endl;
	system("pause");
}