#include "stdafx.h"
#include "DisplayableTask.h"
#include <iostream>

using namespace std;

DisplayableTask::DisplayableTask(std::tm d, std::shared_ptr<DisplayableComponent> p, std::string name, bool complete) : CalendarComponent(d,p), name_(name), complete_(false) {}

void DisplayableTask::display(int val) {
	if (val == 0) {
		cout << name_ << " " << dateInfo.tm_mon << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << " " << flush;
		cout << dateInfo.tm_hour << ":" << flush;
		
		if (dateInfo.tm_min < 10) {
			cout << "0" << flush;
		}
		cout << dateInfo.tm_min << " " << flush;

		if (complete_) {
			cout << "COMPLETE" << endl;
		}
		else {
			cout << "TODO" << endl;
		}
	}
}

