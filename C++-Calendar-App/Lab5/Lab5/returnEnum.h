#pragma once

enum returnValues
{
	SUCCESS = 0,
	INVALID_DATE_INPUT = 1,
	LONG_EVENT_NAME = 2,
	INVALID_RECURR_EVERY,
	INVALID_RECURR_FOR,
	TOO_FAR_IN_FUTURE
};

enum displayValues {
	cal,
	year, 
	month, 
	day,
	event,
	todo
};