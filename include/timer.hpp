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
		sf::Text       *text;
		ach::TimeStamp  clock;

		bool active;


		 Timer();
		~Timer();

		void update();
		void render();
		void updateText();
		void init();
	};
}

#endif
