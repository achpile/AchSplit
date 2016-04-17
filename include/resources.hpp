/***********************************************************************
     * File       : resources.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __RESOURCES
#define __RESOURCES


namespace ach {
	struct Resources {
		struct {
			sf::Font *timer;
			sf::Font *caption;
		} fonts;

		struct {
			sf::SoundBuffer *beepBuf1;
			sf::SoundBuffer *beepBuf2;

			sf::Sound       *beep1;
			sf::Sound       *beep2;
		} sfx;


		 Resources();
		~Resources();

		void loadFont(sf::Font **font, const char *filename);
		void loadSound(sf::SoundBuffer **buf, sf::Sound **snd, const char *filename);
	};
}

#endif
