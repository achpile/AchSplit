/***********************************************************************
     * File       : timer.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __TIMER
#define __TIMER


namespace ach {
	struct Timer {
		sf::Text *text;

		long clock;

		long usec;
		long sec;
		long min;
		long hour;


		 Timer();
		~Timer();

		void update();
		void render();
		void updateText();
		void calc();
		void init();
	};
}

#endif
