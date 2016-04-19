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

		ach::Keyboard       kbd;
		ach::HotKey         hotkeyCheck;
		ach::HotKey         hotkeyReset;

		sf::Text         *caption;
		sf::Text         *goal;
		sf::Text         *bestCaption;
		sf::Text         *bestText;

		sf::Texture      *bgTex;
		sf::Sprite       *bgSpr;

		std::vector<ach::Checkpoint*> checkpoints;
		char                          JSONfile[256];

		long lastClock;
		long offset;
		int  current;
		bool running;
		bool separated;
		bool hkConfigured;
		int  hkCurrent;


		 StopWatch(int argc, char **argv);
		~StopWatch();

		void update();
		void render();
		void stop();
		void resize();

		void updateStopwatch();
		void updateConfig();

		void loadBG(const char *filename, const char *JSON);

		void checkpoint();
		long getSegmentTime(int index);
		void updateBest();
		void updateCheckpoints();
		void reset();

		void load(const char *filename);
		void save(const char *filename);

		void configHotkey(sf::Keyboard::Key key);
		void updateConfigScreen();
		void processHotkeys();
		void checkHotkeys();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
