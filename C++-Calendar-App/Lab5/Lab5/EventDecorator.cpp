#include "stdafx.h"
#include "EventDecorator.h"
#include <iostream>
using namespace std;

EventDecorator::EventDecorator(tm d, std::shared_ptr<DisplayableComponent> p, std::shared_ptr<DisplayableComponent> comp, std::string eventName, std::string calendarName) : DisplayableComponent(p){ //DisplayableEvent(d,p,eventName){
	calendarName_ = calendarName;
}

void EventDecorator::display(int val) {
	//if (val != 2) {
		cout << calendarName_ << "::" << flush;
		comp_->display(val);
	//}
	////->display(val);
}
