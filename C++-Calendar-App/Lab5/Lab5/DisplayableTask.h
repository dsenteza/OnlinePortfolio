#pragma once
#include "../../CODE/CalendarComponent.h"

class FullCalendarBuilder;
class CalendarInterface;

class DisplayableTask : public CalendarComponent
{
	friend FullCalendarBuilder;
	friend CalendarInterface;
	
public:
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	DisplayableTask(std::tm, std::shared_ptr<DisplayableComponent>, std::string, bool);
	virtual void display(int val) override;
	// currently a leaf class, so no need to override addComponent()
	bool complete_;
private:
	std::string name_;
protected:
	//virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
};
