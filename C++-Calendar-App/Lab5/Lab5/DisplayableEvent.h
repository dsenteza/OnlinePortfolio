#pragma once
#include "../../CODE/CalendarComponent.h"

class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;

class DisplayableEvent : public CalendarComponent
{
	friend class DisplayableMonth;
	friend FullCalendarBuilder;
	friend CalendarInterface;

	public:
		// 1st argument = start date/timeof the day, 2nd argument = its parent
		DisplayableEvent(std::tm, std::shared_ptr<DisplayableComponent>, std::string);
		virtual void display(int val) override;
		virtual DisplayableEvent::~DisplayableEvent();
		// currently a leaf class, so no need to override addComponent()
private:
	std::string name_;
};