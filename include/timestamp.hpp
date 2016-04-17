/***********************************************************************
     * File       : timestamp.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __TIMESTAMP
#define __TIMESTAMP


namespace ach {
	struct TimeStamp {
		long clock;

		long usec;
		long sec;
		long min;
		long hour;


		 TimeStamp();

		void calc();
		void sprint(char *buf, size_t size);
		void sprint2(char *buf, size_t size, const char *positive = "");
	};
}

#endif
