#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "Calendar.h"
#include "DisplayableYear.h"
#include "DisplayableMonth.h"
#include "DisplayableDay.h"
//#include "DisplayableToDo.h"
#include "../Lab5/Lab5/DisplayableEvent.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

tm lol;
//std::shared_ptr<DisplayableComponent> theToDoList = make_shared<DisplayableComponent>(DisplayableToDoList::getInstance());

CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) 
{
	if (builderType == "full") 
	{
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		currentDisplay = cal;
	}
}

void CalendarInterface::run()
{
	// run until the user quits
	while (1) 
	{
		Calendar * possibleCal = dynamic_cast<Calendar *>(currentDisplay.get());
		DisplayableYear * possibleYear = dynamic_cast<DisplayableYear *>(currentDisplay.get());
		DisplayableMonth * possibleMonth = dynamic_cast<DisplayableMonth *>(currentDisplay.get());
		DisplayableDay * possibleDay = dynamic_cast<DisplayableDay*>(currentDisplay.get());
		DisplayableEvent * possibleEvent = dynamic_cast<DisplayableEvent *>(currentDisplay.get());
	//	DisplayableToDo * possibleToDo = dynamic_cast<DisplayableToDo *>(currentDisplay.get());

		int displayVal;
		if (possibleCal != nullptr)
		{
			displayVal = 0;
		}
		else if (possibleYear != nullptr)
		{
			displayVal = 1;
		}
		else if (possibleMonth != nullptr)
		{
			displayVal = 2;
		}
		else if (possibleDay != nullptr)
		{
			displayVal = 3;
		}
		else if (possibleEvent != nullptr)
		{
			displayVal = 4;
		}
		/*else if (possibleToDo != nullptr) {
			displayVal = 5;
		}*/
	
		currentDisplay->display(displayVal);

		// display options to the user and respond to user input accordingly
		cout << "zoom out: out, zoom in: in, create event: c, search: s, jump: j, save calendar to file: sa, restore calendar from file: r, view ToDo list : t, merge calendar: m, quit: q" << flush;
				
		//the cast only works if the current display is an event. If its not event, it will return nullptr
		//if the current display is an event, show additional options
		if (possibleEvent != nullptr)
		{
			cout << ", delete event: d, edit event: e" << endl;
		}
		else 
		{
			cout << endl; // for the end of the options menu
		}
		
		string in;
		cin >> in;
		if (in == "in")
		{
			if (currentDisplay->children.size() > 0) 
			{
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
				int index = 0;
				cin >> index;
				zoomIn(index);
			}
			else 
			{
				cout << "Nothing to zoom in on" << endl;
			}
		}
		else if (in == "out")
		{
			zoomOut();
		}
		else if (in == "q")
		{
			break;
		}
		else if (in == "c")
		{
			createEvent();
		}
		else if (in == "s")
		{
			search();
		}
		else if (in == "j")
		{
			jumpTo();
		}
		else if (in == "sa")
		{
			save();
		}
		else if (in == "r")
		{
			restore();
		}
		else if (in == "d")
		{
			if (possibleEvent != nullptr)
			{ // double check for an event
				deleteEvent();
			}
		}
		else if(in == "e")
		{
			if (possibleEvent != nullptr)
			{
				editEvent();
			}
		}
		else if (in == "t")
		{
			viewToDoList();
		}
		else if (in == "m"){
			merge();
		}
	}
}

void CalendarInterface::zoomIn(unsigned int index)
{
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr)
	{
		currentDisplay = temp;
	}
}

void CalendarInterface::zoomOut() 
{
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) 
	{
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
}

int CalendarInterface::createEvent() 
{
		cout << "Enter the name of your event (50 characters or less)";
		cout << " and date of your event in the format 'mm/dd/yyyy'." << endl;
		string eventName;
		string eventDate;
		if (cin >> eventName >> eventDate)
		{
			if (eventName.size() > 50)
			{
				cout << "Event name too long, cannot be more than 50 characters" << endl;
				return LONG_EVENT_NAME;
			}
			size_t findSlash = eventDate.find('/');
			if (findSlash != string::npos)
			{
				eventDate[findSlash] = ' ';
				size_t findSlash2 = eventDate.find('/');
				if (findSlash2 != string::npos)
				{
					eventDate[findSlash2] = ' ';
					std::stringstream ssDate(eventDate);
					unsigned int eventMonth;
					int eventDay;
					unsigned int eventYear;
					if (ssDate >> eventMonth && ssDate >> eventDay && ssDate >> eventYear)
					{
						if (eventYear < 2018 || eventYear >= 2021)
						{
							cout << "Error: event cannot be made in the past or more than three years in the future" << endl;
							return INVALID_DATE_INPUT;
						}
						if (eventMonth > 12 || eventMonth < 1)
						{
							cout << "Error: month must be between 1 and 12" << endl;
							return INVALID_DATE_INPUT;
						}
						eventMonth -= 1;
						if (eventDay > Calendar::days[eventMonth])
						{
							cout << "Error: enter invalid day for month inputted" << endl;
							return INVALID_DATE_INPUT;
						}
						cout << "Enter the time of your event in the format 'hh:mm' using military time" << endl;
						std::string eventTime;
						cin >> eventTime;
						size_t findColon = eventTime.find(':');
						if (findColon != string::npos)
						{
							eventTime[findColon] = ' ';
							std::stringstream ssTime(eventTime);
							unsigned int eventHour;
							unsigned int eventMinute;
							if (ssTime >> eventHour >> eventMinute)
							{
								if (eventHour <= 24 && eventMinute <= 60)
								{
									tm newEvent;
									newEvent.tm_year = eventYear;
									newEvent.tm_mon = eventMonth;
									newEvent.tm_mday = eventDay;
									newEvent.tm_yday = 0;
									for (int i = 0; i < newEvent.tm_mon; i++)
									{
										newEvent.tm_yday += Calendar::days[i];
									}
									newEvent.tm_yday += newEvent.tm_mday;
									newEvent.tm_wday = (newEvent.tm_mday + CalendarComponent::DAYSINAWEEK - (newEvent.tm_mday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
									newEvent.tm_hour = eventHour;
									newEvent.tm_min = eventMinute;
									newEvent.tm_sec = 0;

									cout << "Is this a recurring event? Enter yes or no" << endl;
									std::string recurringEvent;
									cin >> recurringEvent;

									unsigned int recurrEvery = 0;
									unsigned int recurrFor = 0;

									if (recurringEvent == "yes" || recurringEvent == "Yes" || recurringEvent == "YES")
									{
										cout << "Enter how often this event will occur in days (for example, if you want this event to occurr every week, enter 7" << endl;
										if (cin >> recurrEvery)
										{
											cout << "Enter how many times this event will repeat" << endl;
											if (cin >> recurrFor)
											{
												addEvent(eventName, newEvent, recurrEvery, recurrFor);
												for (int i = 0; i < recurrFor; i++) 
												{
														newEvent.tm_yday = newEvent.tm_yday + recurrEvery;
														newEvent.tm_mday = newEvent.tm_mday + recurrEvery;
														newEvent.tm_wday = newEvent.tm_wday + recurrEvery;
														//If recurrs into a new week
														if (newEvent.tm_wday > 6) 
														{
															newEvent.tm_wday = newEvent.tm_wday % 7;
														}
														//If recurrs in to a new month
														if (newEvent.tm_mday > CalendarComponent::days[newEvent.tm_mon])
														{
															newEvent.tm_mday = newEvent.tm_mday - CalendarComponent::days[newEvent.tm_mon];
															newEvent.tm_mon++;
															//If the month is december to january
															if (newEvent.tm_mon > 11)
															{
																newEvent.tm_mon = 0;
															}
														}
														//If recurrs into a new year
														if (newEvent.tm_yday > 365)
														{
															newEvent.tm_mday = newEvent.tm_yday - 365;
															newEvent.tm_year++;

														}
														addEvent(eventName, newEvent, recurrEvery, recurrFor);	
												}
												return SUCCESS;
											}
										}
									}
									else
									{
										addEvent(eventName, newEvent, recurrEvery, recurrFor);
										return SUCCESS;
									}
								}
							}
						}
					}
				}
			}
		}
		//else
		cout << "Error: inputting event" << endl;
		return INVALID_DATE_INPUT;
	}

	void CalendarInterface::addEvent(std::string name, std::tm t, int recurrEvery, int recurrFor)
	{
		shared_ptr<DisplayableComponent> event =builder->buildEvent(cal, name,t, recurrEvery, recurrFor );
		cal->eventMap.insert(std::pair<std::string, std::shared_ptr<DisplayableComponent>>(name, event));
	}

	void CalendarInterface::search()
	{
		cout << "Enter name of the event" << endl;
		string eventName;

		cin >> eventName;

		std::vector<std::pair<std::string, std::shared_ptr<DisplayableComponent>>> results;

		for (multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator it = cal->eventMap.find(eventName); it != cal->eventMap.end(); it++) {
			results.push_back(*it);
		}

		if (results.size() == 0)
		{
			cout << "Event name not found" << endl;
		}
		else if (results.size() == 1) 
		{
			currentDisplay = results[0].second;
		}
		else 
		{
			for (int i = 0; i < results.size(); i++) 
			{
				cout << i + 1 << ": " << results[i].first << endl;
			}
			
			cout << "Input the number of the event you want to view" << endl;
			int index;
			cin >> index;
			if (index > results.size()) 
			{
				cout << "invalid index" << endl;
			}
			else 
			{
				currentDisplay = results[index - 1].second;
			}
		}
		
		
	}
 
	void CalendarInterface::jumpTo()
	{
		unsigned int mo;
		unsigned int da;
		unsigned int ye;
		string gran;
		cout << "Enter '[Month] [Day] [Year]' (ex: '10 18 2019')" << endl;
		cin >> mo >> da >> ye;
		if (mo > 12)
		{
			cout << "Invalid month index" << endl;
		}
		else if (da > CalendarComponent::days[mo - 1]) 
		{
			cout << "Invalid day index" << endl;
		}
		else if (ye < 2019 || ye > 2021) 
		{
			cout << "Invalid year input" << endl;
		}
		else if (mo == 2 && da >28) 
		{
			if (da == 29 && (ye % 4 != 0))
			{
				cout << "Invalid date: not a leap year." << endl;
			}
			else if (da == 29 && (ye % 4 == 0))
			{
				cout << "Leap year." << endl;
			}
			else 
			{
				cout << "Invalid date." << endl;
			}
		}
		else
			cout << "Granularity: Enter 'y' for year, 'm' for month, or 'd' for day." << endl;
		cin >> gran;
		struct std::tm timeStamp;
		timeStamp.tm_mon = mo - 1;
		timeStamp.tm_year = ye - 1900;
		timeStamp.tm_mday = da;
		if (gran == "d" || gran == "m" || gran == "y")
		{

			shared_ptr<DisplayableComponent> temp = builder->getComponentByDate(cal, timeStamp, gran);
			if (temp != nullptr)
			{
				currentDisplay = temp;
			}

			//currentDisplay->display();
		}
		else
		{
			cout << "Invalid granularity specified." << endl;
		}
	}

	void CalendarInterface::save()
	{
		cout << "Enter file name (no spaces)" << endl;
		string fileName;
		cin >> fileName;

		ofstream outputFile;
		outputFile.open(fileName + ".txt");
		auto it = cal->eventMap.begin();
		if (outputFile.is_open())
		{
			while (it != cal-> eventMap.end())
			{
				DisplayableEvent* e = dynamic_cast<DisplayableEvent *>(it->second.get());
				outputFile << it->first << " ";
				outputFile << e->dateInfo.tm_mon + 1 << "/" << e->dateInfo.tm_mday << "/" << e->dateInfo.tm_year << " ";
				if (e->dateInfo.tm_hour < 10 && e->dateInfo.tm_min < 10)
				{
					outputFile << "0" << e->dateInfo.tm_hour << ":0" << e->dateInfo.tm_min << endl;

				}
				else if (e->dateInfo.tm_min < 10)
				{
					outputFile << e->dateInfo.tm_hour << ":0" << e->dateInfo.tm_min << endl;

				}
				else if (e->dateInfo.tm_hour < 10)
				{
					outputFile << "0" << e->dateInfo.tm_hour << ":" << e->dateInfo.tm_min << endl;

				}
				else
				{
					outputFile << e->dateInfo.tm_hour << ":" << e->dateInfo.tm_min << endl;
				}
				++it;
			}
			outputFile.close();
		}
		else
		{
			cout << "Error saving calendar to file" << endl;
		}
	}

	void CalendarInterface::restore()
	{
		cout << "Enter the name of the file you want to restore" << endl;
		string fileToRestore;
		cin >> fileToRestore;

		ifstream inFile(fileToRestore + ".txt");

		if (inFile)
		{
			cal->eventMap.clear(); //erases items in eventMap so that new items can be added
							  //remove all event children from all days with events
			string line;
			while (getline(inFile, line))
			{
				cout << "getLine" << endl;
				stringstream lineInfo(line);
				string name;
				string day;
				string time;
				if (lineInfo >> name >> day >> time)
				{
					size_t slash = day.find('/');

					if (slash != string::npos)
					{
						day[slash] = ' ';
						size_t slash2 = day.find('/');
						if (slash2 != string::npos)
						{
							day[slash2] = ' ';
							std::stringstream ssDate(day);
							unsigned int month;
							int mDay;
							unsigned int year;

							if (ssDate >> month && ssDate >> mDay && ssDate >> year)
							{
								month -= 1;

								size_t findColon = time.find(':');
								if (findColon != string::npos)
								{
									time[findColon] = ' ';
									std::stringstream ssTime(time);
									unsigned int eventHour;
									unsigned int eventMinute;
									if (ssTime >> eventHour >> eventMinute)
									{
										tm newDate;
										newDate.tm_year = year;
										newDate.tm_mon = month;
										newDate.tm_mday = mDay;
										newDate.tm_wday = (newDate.tm_mday + CalendarComponent::DAYSINAWEEK - (newDate.tm_mday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
										newDate.tm_yday = 0;
										for (int i = 0; i < newDate.tm_mon; i++)
										{
											newDate.tm_yday += Calendar::days[i];
										}
										newDate.tm_yday += newDate.tm_mday;
										//newDate.tm_yday = dayOfMonth(month) + mDay;
										newDate.tm_sec = 0;
										newDate.tm_min = eventMinute;
										newDate.tm_hour = eventHour;

										cout << "Added Event: Name: " << name << " Date: " << newDate.tm_mday << " " << newDate.tm_mon << " " << newDate.tm_year << " Time: " << newDate.tm_hour << ":" << newDate.tm_min << endl;
										addEvent(name, newDate, 0, 0);
									}
								}
							}
						}
					}
				}
			}
			inFile.close();
		}

		else
		{
			cout << "File name does not exist" << endl;
		}
	}

	void CalendarInterface::deleteEvent() 
	{
		//currently the current display is pointing to an event (we already checked in the run method)
		//so now we need to change the current display to the day holding it.
		//then we delete the event
		std::shared_ptr<DisplayableComponent> eventToRemove = currentDisplay; // the event
		currentDisplay = eventToRemove->parent.lock(); //current display is now the day that holds the event. (parent is a weak_ptr, so you have to call lock to get the shared_ptr)
		
		//find the index of the event we need to remove
		int index;

		for (int i = 0; i < currentDisplay->children.size(); i++)
		{
			if (currentDisplay->children[i] == eventToRemove)
			{
				index = i;
			}
		}

		std::shared_ptr<DisplayableComponent> removed = currentDisplay->removeComponent(index);
		
		//cast it so we can get the name of the event
		DisplayableEvent * removedEvent = dynamic_cast<DisplayableEvent *>(removed.get());
		
		string eventName = removedEvent->name_;

		//use the name to search for the event in the map. Then remove the correct pair
		
		typedef multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator iter;
		std::pair<iter, iter> iterpair = cal->eventMap.equal_range(eventName);

		iter it = iterpair.first;
		for (; it != iterpair.second; ++it) 
		{
			if (it->second == removed)
			{
				cal->eventMap.erase(it);
				break;
			}
		}
	}

	void CalendarInterface::editEvent() 
	{
		deleteEvent();
		cout << "Re-enter the information even if you want it to remain the same" << endl;
		createEvent();
			
	}

	void CalendarInterface::viewToDoList() {

	}

	void CalendarInterface::merge() {
		cout << "Enter the name of the file you want to merge" << endl;
		string fileToRestore;
		cin >> fileToRestore;

		ifstream inFile(fileToRestore + ".txt");

		if (inFile)
		{
			string line;
			while (getline(inFile, line))
			{
				cout << "getLine" << endl;
				stringstream lineInfo(line);
				string name;
				string day;
				string time;
				if (lineInfo >> name >> day >> time)
				{
					cout << "here1" << endl;
					size_t slash = day.find('/');

					if (slash != string::npos)
					{
						cout << "here2" << endl;
						day[slash] = ' ';
						size_t slash2 = day.find('/');
						if (slash2 != string::npos)
						{
							cout << "here3" << endl;
							day[slash2] = ' ';
							std::stringstream ssDate(day);
							unsigned int month;
							int mDay;
							unsigned int year;

							if (ssDate >> month && ssDate >> mDay && ssDate >> year)
							{
								cout << "here4" << endl;
								month -= 1;

								size_t findColon = time.find(':');
								if (findColon != string::npos)
								{
									cout << "here5" << endl;
									time[findColon] = ' ';
									std::stringstream ssTime(time);
									unsigned int eventHour;
									unsigned int eventMinute;
									if (ssTime >> eventHour >> eventMinute)
									{
										cout << "here6" << endl;
										tm newDate;
										newDate.tm_year = year;
										newDate.tm_mon = month;
										newDate.tm_mday = mDay;
										newDate.tm_wday = (newDate.tm_mday + CalendarComponent::DAYSINAWEEK - (newDate.tm_mday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
										newDate.tm_yday = 0;
										for (int i = 0; i < newDate.tm_mon; i++)
										{
											cout << "here7" << endl;
											newDate.tm_yday += Calendar::days[i];
										}
										newDate.tm_yday += newDate.tm_mday;
										//newDate.tm_yday = dayOfMonth(month) + mDay;
										newDate.tm_sec = 0;
										newDate.tm_min = eventMinute;
										newDate.tm_hour = eventHour;

										cout << "Name: " << name << " Date: " << newDate.tm_mday << " " << newDate.tm_mon << " " << newDate.tm_year << " Time: " << newDate.tm_hour << ":" << newDate.tm_min << endl;
										
										addEventDecorator(fileToRestore, name, newDate, 0, 0);
									}
								}
							}
						}
					}
				}
			}
			inFile.close();
		}

		else
		{
			cout << "File name does not exist" << endl;
		}
}

void CalendarInterface::addEventDecorator(std::string calName, std::string eventName, std::tm t, int recurrEvery, int recurrFor) {
	shared_ptr<DisplayableComponent> eventDecorator = builder->buildEventDecorator(cal, calName,eventName,t,recurrEvery,recurrFor);

	cal->eventMap.insert(std::pair<std::string, std::shared_ptr<DisplayableComponent>>(eventName, eventDecorator));
}