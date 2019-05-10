/*
Author: Jon Shidal
Purpose: Define full calendar builder class, responsible for building and managing the structure of the calendar
*/
#include "stdafx.h"
#include "FullCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include "../Lab5/Lab5/EventDecorator.h"
#include "../Lab5/Lab5/DisplayableEvent.h"

using namespace std;

shared_ptr<Calendar> FullCalendarBuilder::buildCalendar(string name, size_t years) //pass this name when saving an calendar
{
	currentCalendar = make_shared<Calendar>(name, years);
	// construct each year in a recursive way, add each year as a child of the calendar
	for (unsigned int i = 0; i < years; ++i) 
	{
		tm y = currentCalendar->dateInfo;
		y.tm_year += i;
		y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * i) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
		currentCalendar->addComponent(buildYear(y, currentCalendar));
	}
	return currentCalendar;
}

// you may decide to define this.
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor) {
	int year = when.tm_year;
	int mon = when.tm_mon;
	int weekDay = when.tm_wday;
	int mDay = when.tm_mday;
	tm copy_d = when;

	//shared_ptr<DisplayableComponent> theDay = cal->getChild(year - 2019)->getChild(mon)->getChild((weekDay + CalendarComponent::DAYSINAWEEK - (when.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK)->getChild(weekDay);

	shared_ptr<DisplayableComponent> theDay = cal->children[year-2019]->children[when.tm_mon]->children[when.tm_mday - 1];
	shared_ptr<DisplayableComponent> event = make_shared<DisplayableEvent>(when, theDay, name);

	theDay->addComponent(event);

	/*if (copy_d.tm_mon == now_tm.tm_mon) {
		event = make_shared<EventDecorator>(event); //modify for merging calendars
	}*/
	return event;
}

 std::shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEventDecorator(std::shared_ptr<DisplayableComponent> cal, std::string calName, std::string eventName, std::tm when, int recurrEvery, int recurrFor){
int year = when.tm_year;
	int mon = when.tm_mon;
	int weekDay = when.tm_wday;
	int mDay = when.tm_mday;
	tm copy_d = when;

	//shared_ptr<DisplayableComponent> theDay = cal->getChild(year - 2019)->getChild(mon)->getChild((weekDay + CalendarComponent::DAYSINAWEEK - (when.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK)->getChild(weekDay);

	shared_ptr<DisplayableComponent> theDay = cal->children[year - 2019]->children[when.tm_mon]->children[when.tm_mday - 1];
	shared_ptr<DisplayableComponent> event = make_shared<DisplayableEvent>(when, theDay, eventName);
	//shared_ptr<DisplayableComponent> eventDecorator = make_shared<EventDecorator>(when,theDay,event,eventName,calName);
	std::shared_ptr<EventDecorator> eventDecorator(new EventDecorator(when, theDay, event, eventName, calName));

	theDay->addComponent(event);

	/*if (copy_d.tm_mon == now_tm.tm_mon) {
	event = make_shared<EventDecorator>(event); //modify for merging calendars
	}*/
	return event;
}

std::shared_ptr<DisplayableComponent> FullCalendarBuilder::getMonth(std::shared_ptr<DisplayableComponent> year, tm d)
{
	return year->getChild(d.tm_mon);
}

std::shared_ptr<DisplayableComponent> FullCalendarBuilder::getDay(std::shared_ptr<DisplayableComponent> month, tm d)
{
	return month->getChild(d.tm_mday-1);
}

// you may decide to define this.
shared_ptr<DisplayableComponent> FullCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity)
{
	if (granularity == "y")
	{
		if (d.tm_year == 2019 - 1900) 
		{
			return cal->children[0];
		}
		else if (d.tm_year == 2020 - 1900) 
		{
			return cal->children[1];
		}
		else if (d.tm_year == 2021 - 1900)
		{
			return cal->children[2];
		}
		else 
		{
			return nullptr;
		}
	}
	else if(granularity == "m")
	{
		if (d.tm_year == 2019 - 1900)
		{
			return getMonth(cal->children[0], d);
		}
		else if (d.tm_year == 2020 - 1900) 
		{
			return getMonth(cal->children[1], d);
		}
		else if (d.tm_year == 2021 - 1900)
		{
			return getMonth(cal->children[2], d);
		}
		else
		{
			return nullptr;
		}
	}
	else if (granularity == "d")
	{
		if (d.tm_year == 2019 - 1900)
		{
			return getDay(cal->children[0]->getChild(d.tm_mon), d);
		}
		else if (d.tm_year == 2020 - 1900)
		{
			return getDay(cal->children[1]->getChild(d.tm_mon), d);
		}
		else if (d.tm_year == 2021 - 1900)
		{
			return getDay(cal->children[2]->getChild(d.tm_mon), d);
		}
		else
		{
			return nullptr;
		}
	}
	return nullptr;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p)
{
	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);
	return day;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p)
{
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	for (int i = 0; i < CalendarComponent::days[index]; ++i) 
	{ // for each day in the month
		m->addComponent(buildDay(d, m)); // construct day and add as a child of the month
		++(d.tm_mday); // increment day of the month
		d.tm_wday = (d.tm_wday + 1) % CalendarComponent::DAYSINAWEEK; // increment weekday, reset to 0 if needed
	}
	return m;
}
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p)
{
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d,p,false);
	// construct each month and add it as a child of the year
	for (unsigned int i = 0; i < CalendarComponent::MONTHS; ++i)
	{
		d.tm_mon = i;
		y->addComponent(buildMonth(d, y));
		// set week day of first day of the next month
		d.tm_wday = (d.tm_wday + CalendarComponent::days[i]) % CalendarComponent::DAYSINAWEEK; 
	}
	return y;
}