#pragma once
#include "../../CODE/CalendarComponent.h"


#ifndef TMCOMPARE_H
#define TMCOMPARE_H

struct EventCompare {
	bool operator() (const std::shared_ptr<DisplayableComponent>&p1, const std::shared_ptr<DisplayableComponent>&p2);
};

#endif TMCOMPARE_H

