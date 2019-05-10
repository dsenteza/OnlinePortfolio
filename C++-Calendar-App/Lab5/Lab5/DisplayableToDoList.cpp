#include "stdafx.h"
#include <iostream>
#include "DisplayableToDoList.h"
#include <sstream>
#include "../../CODE\Calendar.h"
#include "DisplayableTask.h"
using namespace std;

DisplayableToDoList::DisplayableToDoList(tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d,p) {}

void DisplayableToDoList::display(int val)
{
	cout << "ToDo List: " << endl;
	for (size_t i = 0; i < children.size(); ++i)
	{ // iterate through children
		if (children[i] != nullptr)
		{
			cout << i << ": " << flush;
			children[i]->display(0);
		}
	}

	cout << "add task: a, mark complete: m, zoom: z, go to calendar: g" << endl;
	string in;
	cin >> in;

	if (in == "a") {
		addTask();
	}
	else if (in == "m") {
		markComplete();
	}
	else if (in == "z") {
		zoom();
	}
	else if (in == "g") {
		//how?!??!?
	}

}

shared_ptr<DisplayableComponent> DisplayableToDoList::addComponent(shared_ptr<DisplayableComponent> comp)
{
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableTask* t = dynamic_cast<DisplayableTask *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (t == nullptr)
	{ // the cast failed
		return nullptr;
	}
	return comp;

}

DisplayableToDoList* DisplayableToDoList::instance = 0;

tm blah;

DisplayableToDoList * DisplayableToDoList::getInstance() {
	if (instance == 0) {
		instance = new DisplayableToDoList(blah, nullptr);
	}
	return instance;
}

void DisplayableToDoList::addTask() {
	cout << "Enter the name of your task (50 characters or less)";
	cout << " and date of your event in the format 'mm/dd/yyyy'." << endl;
	string eventName;
	string eventDate;
	if (cin >> eventName >> eventDate)
	{
		if (eventName.size() > 50)
		{
			cout << "Task name too long, cannot be more than 50 characters" << endl;
		}
		size_t findSlash = eventDate.find('/');
		if (findSlash != string::npos)
		{
			eventDate[findSlash] = ' ';
			size_t findSlash2 = eventDate.find('/');
			if (findSlash2 != string::npos)
			{
				eventDate[findSlash2] = ' ';
				std::stringstream ssDate(eventDate);
				unsigned int eventMonth;
				int eventDay;
				unsigned int eventYear;
				if (ssDate >> eventMonth && ssDate >> eventDay && ssDate >> eventYear)
				{
					if (eventYear < 2018 || eventYear >= 2021)
					{
						cout << "Error: event cannot be made in the past or more than three years in the future" << endl;
					}
					if (eventMonth > 12 || eventMonth < 1)
					{
					}
					eventMonth -= 1;
					if (eventDay > Calendar::days[eventMonth])
					{
						cout << "Error: enter invalid day for month inputted" << endl;
					}
					cout << "Enter the time of your event in the format 'hh:mm' using military time" << endl;
					std::string eventTime;
					cin >> eventTime;
					size_t findColon = eventTime.find(':');
					if (findColon != string::npos)
					{
						eventTime[findColon] = ' ';
						std::stringstream ssTime(eventTime);
						unsigned int eventHour;
						unsigned int eventMinute;
						if (ssTime >> eventHour >> eventMinute)
						{
							if (eventHour <= 24 && eventMinute <= 60)
							{
								tm newEvent;
								newEvent.tm_year = eventYear;
								newEvent.tm_mon = eventMonth;
								newEvent.tm_mday = eventDay;
								newEvent.tm_yday = 0;
								for (int i = 0; i < newEvent.tm_mon; i++)
								{
									newEvent.tm_yday += Calendar::days[i];
								}
								newEvent.tm_yday += newEvent.tm_mday;
								newEvent.tm_wday = (newEvent.tm_mday + CalendarComponent::DAYSINAWEEK - (newEvent.tm_mday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
								newEvent.tm_hour = eventHour;
								newEvent.tm_min = eventMinute;
								newEvent.tm_sec = 0;
							}
						}
					}
				}
			}
		}
	}
	//else
	cout << "Error: inputting event" << endl;
}

void DisplayableToDoList::zoom() {
	/*shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr)
	{
		currentDisplay = temp;
	}*/
}

void DisplayableToDoList::markComplete() {
	cout << "Input the number of the task you want to mark complete" << endl;
	int index;
	cin >> index;

	std::shared_ptr<DisplayableComponent> task = children[index];
	DisplayableTask* t = dynamic_cast<DisplayableTask *>(task.get());
	if (t->complete_) {
		//do nothing
	}
	else {
		t->complete_ = true;
	}

}

