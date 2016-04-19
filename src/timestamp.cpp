/***********************************************************************
     * File       : timestamp.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * TimeStamp
     * constructor

***********************************************************************/
ach::TimeStamp::TimeStamp() {
	clock = 0;

	calc();
}



/***********************************************************************
     * TimeStamp
     * update

***********************************************************************/
void ach::TimeStamp::update() {
	clock += frameClock;
	calc();
}



/***********************************************************************
     * TimeStamp
     * setClock

***********************************************************************/
void ach::TimeStamp::setClock(long _clock) {
	clock = _clock;
	calc();
}



/***********************************************************************
     * TimeStamp
     * calc

***********************************************************************/
void ach::TimeStamp::calc() {
	long absClock = abs(clock);

	usec = absClock % 1000;
	sec  = (absClock % 60000) / 1000;
	min  = (absClock % 3600000) / 60000;
	hour = absClock / 3600000;
}



/***********************************************************************
     * TimeStamp
     * sprint

***********************************************************************/
sf::String ach::TimeStamp::sprint() {
	char   buf[32];
	size_t size = sizeof(buf);

	snprintf(buf, size, "%s%ld:%02ld:%02ld.%03ld",
	                    (clock < 0) ? "-" : "",
	                    hour,
	                    min,
	                    sec,
	                    usec);

	return sf::String(buf);
}



/***********************************************************************
     * TimeStamp
     * sprint2

***********************************************************************/
sf::String ach::TimeStamp::sprint2(const char *positive) {
	char   buf[32];
	size_t size = sizeof(buf);

	if (hour)
		snprintf(buf, size, "%s%ld:%02ld:%02ld.%ld",
		                    (clock < 0) ? "-" : positive,
		                    hour,
		                    min,
		                    sec,
		                    usec / 100);
	else if (min)
		snprintf(buf, size, "%s%ld:%02ld.%ld",
		                    (clock < 0) ? "-" : positive,
		                    min,
		                    sec,
		                    usec / 100);
	else
		snprintf(buf, size, "%s%ld.%ld",
		                    (clock < 0) ? "-" : positive,
		                    sec,
		                    usec / 100);

	return sf::String(buf);
}
