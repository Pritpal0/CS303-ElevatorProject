#include "stdafx.h"
#include "Elevator.h"
#include "time.h"

using namespace std;
int main()
{
	clock_t end = clock() + 1000;
	clock_t current_time = clock();
	random_device luck;

	//Simulation 1:
	/*Elevator elevator(9);
	while (current_time < end)
	{
	current_time = clock();
	int waiting = luck() % 10;
	elevator.pick_up_at(waiting);
	if (current_time % 2 == 0)
	{
	waiting = luck() % 10;
	elevator.pick_up_at(waiting);
	}
	elevator.priority();
	}
	cout << "Simulation ended" << endl;
	system("pause");*/


	//Simulation 2:
	Elevator elevator_1(9);
	Elevator elevator_2(9);
	while (current_time < end)
	{
		current_time = clock();
		int waiting = luck() % 10;

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
			waiting = luck() % 10;
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
	cout << "Simulation ended" << endl;
	system("pause");

}