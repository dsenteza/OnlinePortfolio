#include "stdafx.h"
#include "../../CODE/CalendarComponent.h"
#include <iostream>
#include "DisplayableEvent.h"
#include "../../CODE/DisplayableDay.h"

using namespace std;

DisplayableEvent::DisplayableEvent(std::tm t, std::shared_ptr<DisplayableComponent> p, std::string name) : CalendarComponent(t, p)
{
	this->name_ = name;
}

// zero out all shared_ptr so resources are cleaned up
DisplayableEvent::~DisplayableEvent() 
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		// parent is a weak_ptr, so no need to clear children's parent
		children[i] = nullptr;
	}
	children.clear();
}

void DisplayableEvent::display(int val)
{
	if (val == 1) 
	{
		cout << "     " <<daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR - 1900 << flush ;

		cout << " Event" << ": ";
		cout << name_ << " " << flush;
		cout << dateInfo.tm_hour << ":" << dateInfo.tm_min << flush;
		if (dateInfo.tm_min < 10)
		{
			cout << "0" << flush;
		}
		cout << endl;
	}
	else if (val == 2)
	{
		cout << "*" << flush;
	}
	else if (val == 3)
	{
		if (dateInfo.tm_hour < 10)
		{
			cout << "0" << flush;
		}
		cout << dateInfo.tm_hour << ":" << flush;
		if (dateInfo.tm_min < 10)
		{
			cout << "0" << flush;
		}
		cout << dateInfo.tm_min << flush;

		cout << " Event" << ": " << name_ << endl;
		
	}
	else 
	{
		cout << daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR - 1900 << endl;

		cout << "Event" << ": ";
		cout << name_ << endl;
		if (dateInfo.tm_hour < 10)
		{
			cout << "0" << flush;
		}
		cout << dateInfo.tm_hour << ":" << flush;
		if (dateInfo.tm_min < 10)
		{
			cout << "0" << flush;
		}
		cout << dateInfo.tm_min << endl;
	}
}
