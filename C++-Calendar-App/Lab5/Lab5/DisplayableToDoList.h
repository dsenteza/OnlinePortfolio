#pragma once

#include "../../CODE/CalendarComponent.h"
#include "../../CODE/DisplayableComponent.h"
#include "compareTM.h"
#include <map>

// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;

class DisplayableToDoList : public CalendarComponent {
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	virtual void display(int val) override;
	// currently a leaf class, so no need to override addComponent()
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
	static DisplayableToDoList* getInstance();
	void markComplete();
	void addTask();
	void zoom();
private:
	DisplayableToDoList(tm, std::shared_ptr<DisplayableComponent>);
	static DisplayableToDoList* instance;
};