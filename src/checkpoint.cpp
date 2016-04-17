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
	best    = _best;
	visible = false;

	highlight = new sf::RectangleShape(sf::Vector2f(WIDTH - 10, 25));
	highlight->setFillColor(sf::Color(50, 50, 50));

	caption = new sf::Text();
	caption->setFont(*resources->fonts.caption);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color(128, 128, 255));
	caption->setPosition(10, 60 + index * 25);
	caption->setString(label);

	differ = new sf::Text();
	differ->setFont(*resources->fonts.timer);
	differ->setCharacterSize(16);
	differ->setPosition(10, 60 + index * 25);

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
	timer->setPosition(WIDTH - 7 * strlen(cap) - 10, 60 + index * 25);
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
	if (visible) render();
}



/***********************************************************************
     * Checkpoint
     * render

***********************************************************************/
void ach::Checkpoint::render() {
	if (highlighted)
		app->draw(*highlight);

	app->draw(*caption);

	if (clock.clock)
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
     * setIndex

***********************************************************************/
void ach::Checkpoint::setIndex(int index, bool _highlighted) {
	int yPos = 60 + index * 25;

	visible     = true;
	highlighted = _highlighted;

	timer->setPosition(timer->getPosition().x, yPos);
	differ->setPosition(differ->getPosition().x, yPos);
	caption->setPosition(caption->getPosition().x, yPos);
	highlight->setPosition(5, yPos - 2);
}



/***********************************************************************
     * Checkpoint
     * setBest

***********************************************************************/
void ach::Checkpoint::setBest(long _best) {
	char cap[32];

	if (best && _best)
		diff.clock = _best - best;

	diff.calc();
	diff.sprint2(cap, sizeof(cap), "+");


	if (best > _best || !best) {
		best = _best;
		differ->setColor(sf::Color::Green);
	} else {
		differ->setColor(sf::Color::Red);
	}


	differ->setString(cap);
	differ->setPosition(WIDTH - 7 * strlen(cap) - 60, timer->getPosition().y);
}
