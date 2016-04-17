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
void ach::TimeStamp::sprint(char *buf, size_t size) {
	snprintf(buf, size, "%s%ld:%02ld:%02ld.%03ld",
	                    (clock < 0) ? "-" : "",
	                    hour,
	                    min,
	                    sec,
	                    usec);
}



/***********************************************************************
     * TimeStamp
     * sprint2

***********************************************************************/
void ach::TimeStamp::sprint2(char *buf, size_t size, const char *positive) {
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
}
