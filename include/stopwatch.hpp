/***********************************************************************
     * File       : stopwatch.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __STOPWATCH
#define __STOPWATCH


namespace ach {
	struct StopWatch {
		sf::Clock        *clock;

		long lastClock;
		bool running;


		 StopWatch();
		~StopWatch();

		void update();
		void stop();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
