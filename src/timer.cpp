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

	active      = false;
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
	if (active) {
		checkBeep();
		clock.clock += frameClock;
	}

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
	text->setPosition(settings->getWidth() - text->getGlobalBounds().width - 10, settings->getHeight() - 45);
}



/***********************************************************************
     * Timer
     * render

***********************************************************************/
void ach::Timer::render() {
	app->draw(*text);
}



/***********************************************************************
     * Timer
     * checkBeep

***********************************************************************/
void ach::Timer::checkBeep() {
	if (clock.clock > 0 || !beep)
		return;

	int newClock = ceil((float)(clock.clock + frameClock) / 1000.f) - 1;
	int oldClock = ceil((float)(clock.clock             ) / 1000.f) - 1;

	if (newClock != oldClock && newClock > -4) {
		if (newClock) resources->sfx.beep1->play();
		else          resources->sfx.beep2->play();
	}
}
