#include "stdafx.h"
#include "DisplayableYear.h"
#include <iostream>
#include "DisplayableMonth.h"
#include "CalendarComponent.h"
#include "DisplayableDay.h"

using namespace std;

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l)
{
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i)
	{
		children.push_back(nullptr);
	}
}

void DisplayableYear::display(int val)
{ //change display of each component based on how its being called/and who is calling it
	if (val == 1) 
	{
		cout << "Year " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
		for (size_t i = 0; i < children.size(); ++i) 
		{ // iterate through children
			if (children[i] != nullptr) 
			{
				cout << i << ": " << CalendarComponent::months[i] << endl;
				children[i]->display(1);
			}
		}
	}
	
}

shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp)
{
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr)
	{ // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) 
	{ // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}
