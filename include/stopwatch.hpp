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
		sf::Clock          *clock;
		sf::RectangleShape *separator;
		ach::Timer         *timer;
		ach::TimeStamp      best;

		sf::Text         *caption;
		sf::Text         *goal;
		sf::Text         *bestCaption;
		sf::Text         *bestText;

		std::vector<ach::Checkpoint*> checkpoints;

		long lastClock;
		long offset;
		int  current;
		bool running;
		bool separated;


		 StopWatch();
		~StopWatch();

		void update();
		void render();
		void stop();

		void checkpoint();
		long calculate(int index);
		long getSegmentTime(int index);
		void updateBest();
		void updateCheckpoints();
		void reset();

		void load();
		void save();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
