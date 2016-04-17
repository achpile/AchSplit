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
ach::Checkpoint::Checkpoint(int index, long _best, const char *label) {
	best = _best;

	caption = new sf::Text();
	caption->setFont(*resources->fonts.caption);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color::Blue);
	caption->setPosition(10, 50 + index * 25);
	caption->setString(label);

	differ = new sf::Text();
	differ->setFont(*resources->fonts.timer);
	differ->setCharacterSize(14);
	differ->setPosition(10, 50 + index * 25);

	timer = new sf::Text();
	timer->setFont(*resources->fonts.timer);
	timer->setCharacterSize(16);
	timer->setColor(sf::Color::White);


	char cap[32];

	diff.clock = 0;
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

	if (diff.clock)
		app->draw(*differ);
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



/***********************************************************************
     * Checkpoint
     * setBest

***********************************************************************/
void ach::Checkpoint::setBest(long _best) {
	char cap[32];

	diff.clock = _best - best;
	diff.calc();
	diff.sprint2(cap, sizeof(cap));


	if (best > _best) {
		best = _best;
		differ->setColor(sf::Color::Green);
	} else {
		differ->setColor(sf::Color::Red);
	}


	differ->setString(cap);
	differ->setPosition(WIDTH - 7 * strlen(cap) - 60, timer->getPosition().y);
}
