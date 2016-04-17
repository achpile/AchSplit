/***********************************************************************
     * File       : checkpoint.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHECKPOINT
#define __CHECKPOINT


namespace ach {
	struct Checkpoint {
		sf::Text       *caption;
		sf::Text       *timer;
		sf::Text       *differ;
		ach::TimeStamp  clock;
		ach::TimeStamp  diff;

		long            best;
		bool            visible;


		 Checkpoint(int index, long _best, const char *label);
		~Checkpoint();

		void update();
		void render();

		void setClock(long _clock);
		void setBest(long _best);
		void setIndex(int index);
	};
}

#endif
