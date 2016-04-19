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
ach::Checkpoint::Checkpoint(long _best, const char *label) {
	best       = _best;
	visible    = false;
	diff.clock = 0;

	highlight = new sf::RectangleShape(sf::Vector2f(settings->getWidth() - 10, 25));
	highlight->setFillColor(sf::Color(50, 50, 50));

	createText(&caption, resources->fonts.caption, 14, sf::Vector2f(10, 0), sf::Color(128, 128, 255), label);
	createText(&differ , resources->fonts.timer  , 16, sf::Vector2f(10, 0));
	createText(&timer  , resources->fonts.timer  , 16, sf::Vector2f(10, 0));
}



/***********************************************************************
     * Checkpoint
     * destructor

***********************************************************************/
ach::Checkpoint::~Checkpoint() {
	delete caption;
	delete timer;
	delete differ;
	delete highlight;
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
	clock.setClock(_clock);
	timer->setString(clock.sprint2());

	resize();
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
	if (best && _best)
		diff.setClock(_best - best);

	if (best > _best || !best) {
		best = _best;
		differ->setFillColor(sf::Color::Green);
	} else {
		differ->setFillColor(sf::Color::Red);
	}


	differ->setString(diff.sprint2("+"));
	resize();
}



/***********************************************************************
     * Checkpoint
     * resize

***********************************************************************/
void ach::Checkpoint::resize() {
	differ->setPosition(settings->getWidth() - 7 * differ->getString().getSize() - 90, differ->getPosition().y);
	timer->setPosition (settings->getWidth() - 7 * timer->getString().getSize()  - 10, timer->getPosition().y );

	highlight->setSize(sf::Vector2f(settings->getWidth() - 10, highlight->getSize().y));
}
