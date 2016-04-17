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
ach::Checkpoint::Checkpoint(int index) {
	caption = new sf::Text();
	caption->setFont(*resources->fonts.caption);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color::White);
	caption->setPosition(10, 10 + index * 25);

	timer = new sf::Text();
	timer->setFont(*resources->fonts.timer);
	timer->setCharacterSize(16);
	timer->setColor(sf::Color::Green);


	char cap[32];
	sprintf(cap, "Level %d", index);
	caption->setString(cap);

	clock.clock = 10000 * index;
	clock.calc();
	clock.sprint2(cap, sizeof(cap));
	timer->setString(cap);
	timer->setPosition(WIDTH - 7 * strlen(cap) - 10, 10 + index * 25);
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
