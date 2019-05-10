#pragma once
#include "../../CODE/CalendarComponent.h"
#include "DisplayableEvent.h"
class EventDecorator : public DisplayableComponent {
protected:
	std::shared_ptr<DisplayableComponent> comp_;
public:
	EventDecorator(tm, std::shared_ptr<DisplayableComponent>, std::shared_ptr<DisplayableComponent>, std::string, std::string);
	virtual void display(int val) override;
private:
	std::string calendarName_;
};