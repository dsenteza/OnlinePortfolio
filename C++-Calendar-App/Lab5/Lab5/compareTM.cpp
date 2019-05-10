#include "stdafx.h"
#include "compareTM.h"
#include "DisplayableEvent.h"
#include "../../CODE/CalendarComponent.h"

bool EventCompare::operator() (const std::shared_ptr<DisplayableComponent>&p1, const std::shared_ptr<DisplayableComponent>&p2) {
	DisplayableEvent * e1 = dynamic_cast<DisplayableEvent *>(p1.get());
	DisplayableEvent * e2 = dynamic_cast<DisplayableEvent *>(p2.get());
	tm tm1 = e1->dateInfo;
	tm tm2 = e2->dateInfo;

	if (tm1.tm_year < tm2.tm_year) {
		//time one is less than time two
		return true;
	}
	else if (tm1.tm_year > tm2.tm_year) {
		//time one is greater than time two
		return false;
	}
	else {
		if (tm1.tm_yday < tm2.tm_yday) {
			//time one is less than time two
			return true;
		}
		else if (tm1.tm_yday > tm2.tm_yday) {
			//time one is greater than time two
			return false;
		}
		else {
			if (tm1.tm_hour < tm2.tm_hour) {
				//time one is less than time two
				return true;
			}
			else if (tm1.tm_hour > tm2.tm_hour) {
				//time one is greater than time two
				return false;
			}
			else {
				if (tm1.tm_min < tm2.tm_min) {
					//time one is less than time two
					return true;
				}
				if (tm1.tm_min > tm2.tm_min) {
					//time one is greater than time two
					return false;
				}
				else {
					//completely equal
					return false;
				}
			}
		}
	}
	return true;
}
