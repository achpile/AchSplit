/***********************************************************************
     * File       : timer.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Timer
     * constructor

***********************************************************************/
ach::Timer::Timer() {
	text = new sf::Text();
	text->setFont(*resources->fonts.timer);
	text->setCharacterSize(32);
	text->setColor(sf::Color::Green);

	clock.clock = -5000;
}



/***********************************************************************
     * Timer
     * destructor

***********************************************************************/
ach::Timer::~Timer() {
	delete text;
}



/***********************************************************************
     * Timer
     * update

***********************************************************************/
void ach::Timer::update() {
	clock.clock += frameClock;
	clock.calc();

	updateText();
	render();
}



/***********************************************************************
     * Timer
     * updateText

***********************************************************************/
void ach::Timer::updateText() {
	char caption[32];
	clock.sprint(caption, sizeof(caption));

	text->setString(caption);
	text->setPosition(WIDTH - text->getGlobalBounds().width - 10, HEIGHT - 45);
}



/***********************************************************************
     * Timer
     * render

***********************************************************************/
void ach::Timer::render() {
	app->draw(*text);
}
