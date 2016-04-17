/***********************************************************************
     * File       : container_resources.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Resources
     * constructor

***********************************************************************/
ach::Resources::Resources() {
	loadFont(&fonts.timer  , "fonts/digits.ttf");
	loadFont(&fonts.caption, "fonts/ethnocentric.ttf");

	loadSound(&sfx.beepBuf1, &sfx.beep1, "sfx/beep1.wav");
	loadSound(&sfx.beepBuf2, &sfx.beep2, "sfx/beep2.wav");
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
ach::Resources::~Resources() {
	delete fonts.timer;
	delete fonts.caption;

	delete sfx.beepBuf1;
	delete sfx.beepBuf2;
	delete sfx.beep1;
	delete sfx.beep2;
}



/***********************************************************************
     * Resources
     * loadFont

***********************************************************************/
void ach::Resources::loadFont(sf::Font **font, const char *filename) {
	(*font) = new sf::Font();
	(*font)->loadFromFile(filename);
}



/***********************************************************************
     * Resources
     * loadSound

***********************************************************************/
void ach::Resources::loadSound(sf::SoundBuffer **buf, sf::Sound **snd, const char *filename) {
	(*buf) = new sf::SoundBuffer();
	(*buf)->loadFromFile(filename);

	(*snd) = new sf::Sound();
	(*snd)->setBuffer(**buf);
}
