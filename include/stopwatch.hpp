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
		ach::Timer       *timer;

		sf::Text         *caption;
		sf::Text         *goal;

		std::vector<ach::Checkpoint*> checkpoints;

		long lastClock;
		int  current;
		bool running;


		 StopWatch();
		~StopWatch();

		void update();
		void render();
		void stop();

		void checkpoint();
		void reset();
		void load();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
