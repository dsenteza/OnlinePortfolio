#include "stdafx.h"
#include "DisplayableDay.h"
#include "../Lab5/Lab5/DisplayableEvent.h"
#include <iostream>
#include <algorithm>
#include "../Lab5/Lab5/compareTM.h"

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }

void DisplayableDay::display(int val)
{
	this->dateInfo.tm_mday;
	if (val == 1) {
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->display(val);
		}
	}
	else if (val == 2)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->display(val);
		}
		int stars = children.size();
		if (this->dateInfo.tm_mday > 9)
		{
			stars++;
		}
		for (int j = 0; j < 9 - stars; j++)
		{
			cout << " " << flush;
		}
	}
	else if (val == 3)
	{
		cout << daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->display(val);
		}
	}
}

shared_ptr<DisplayableComponent> DisplayableDay::addComponent(shared_ptr<DisplayableComponent> comp)
{
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableEvent* e = dynamic_cast<DisplayableEvent *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (e == nullptr)
	{ // the cast failed
		return nullptr;
	}

	//insertion sort algorithm using time compare

	children.push_back(comp);
	std::sort(children.begin(), children.end(), EventCompare());
	return comp;
	
}
