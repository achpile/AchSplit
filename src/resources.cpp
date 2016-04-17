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
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
ach::Resources::~Resources() {
	delete fonts.timer;
	delete fonts.caption;
}



/***********************************************************************
     * Resources
     * loadFont

***********************************************************************/
void ach::Resources::loadFont(sf::Font **font, const char *filename) {
	(*font) = new sf::Font();
	(*font)->loadFromFile(filename);
}
