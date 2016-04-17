/***********************************************************************
     * File       : checkpoint.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Checkpoint
     * constructor

***********************************************************************/
ach::Checkpoint::Checkpoint(int index, const char *label) {
	caption = new sf::Text();
	caption->setFont(*resources->fonts.caption);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color::Blue);
	caption->setPosition(10, 50 + index * 25);
	caption->setString(label);

	timer = new sf::Text();
	timer->setFont(*resources->fonts.timer);
	timer->setCharacterSize(16);
	timer->setColor(sf::Color::White);


	char cap[32];

	clock.clock = 10000 * index + 5000;
	clock.calc();
	clock.sprint2(cap, sizeof(cap));
	timer->setString(cap);
	timer->setPosition(WIDTH - 7 * strlen(cap) - 10, 50 + index * 25);
}



/***********************************************************************
     * Checkpoint
     * destructor

***********************************************************************/
ach::Checkpoint::~Checkpoint() {
	delete caption;
	delete timer;
}



/***********************************************************************
     * Checkpoint
     * update

***********************************************************************/
void ach::Checkpoint::update() {
	render();
}



/***********************************************************************
     * Checkpoint
     * render

***********************************************************************/
void ach::Checkpoint::render() {
	app->draw(*caption);
	app->draw(*timer);
}



/***********************************************************************
     * Checkpoint
     * setClock

***********************************************************************/
void ach::Checkpoint::setClock(long _clock) {
	char cap[32];

	clock.clock = _clock;
	clock.calc();
	clock.sprint2(cap, sizeof(cap));
	timer->setString(cap);
	timer->setPosition(WIDTH - 7 * strlen(cap) - 10, timer->getPosition().y);
}
