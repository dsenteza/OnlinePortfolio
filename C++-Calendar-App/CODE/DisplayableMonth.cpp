#include "stdafx.h"
#include "DisplayableMonth.h"
#include "DisplayableDay.h"
#include <iostream>

using namespace std;

DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) : CalendarComponent(d, p), name(monthname), numberOfDays(numdays) 
{
	// initialize children vector, one spot for each day
	for (size_t i = 0; i < numberOfDays; ++i)
	{
		children.push_back(nullptr);
	}
}

void DisplayableMonth::display(int val)
{
	if (val == 1) 
	{
		for (int i = 0; i < children.size(); i++) 
		{
			children[i]->display(val);
		}
	}
	else if(val==2) 
	{
		cout << CalendarComponent::months[this->dateInfo.tm_mday - 1] << endl;
		cout << "Sunday    Monday    Tuesday   Wednesday Thursday  Friday    Saturday  " << endl;
		int weekday = this->dateInfo.tm_wday;
		for (int i = 0; i < weekday; i++)
		{
			cout << "          " << flush;
		}
		//Keeps track of days of the month
		int dayOfMonth = 1;
		for (int i = weekday; i < (weekday + days[dateInfo.tm_mon]); i++)
		{
			//Printing out number the day
			cout << dayOfMonth << flush;
			//Adding stars to the date
			children[dayOfMonth - 1]->display(val);
			//If we've reached the end of the week
			if ((i + 1) % 7 == 0)
			{
				cout << endl;
			}
			dayOfMonth++;
		}
		/*cout << "\t\t" << name << ":" << endl;
		for (size_t i = 0; i < children.size(); ++i) {
			if (children[i] != nullptr) { // forward request to all children
				children[i]->display(val);
			}
		}*/
	}
	cout << endl;
}

shared_ptr<DisplayableComponent> DisplayableMonth::addComponent(shared_ptr<DisplayableComponent> comp)
{
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableDay* d = dynamic_cast<DisplayableDay *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr)
	{ // the cast failed
		return nullptr;
	}
	// otherwise, add the day to the correct location
	int dayOfMonth = d->dateInfo.tm_mday - 1;
	if (children[dayOfMonth] == nullptr)
	{ // day does not already exist
		children[dayOfMonth] = comp;
		return comp;
	}
	else 
	{  // day already exist, return existing day
		return children[dayOfMonth];
	}
}