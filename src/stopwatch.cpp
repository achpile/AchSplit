/***********************************************************************
     * File       : stopwatch.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * StopWatch
     * constructor

***********************************************************************/
ach::StopWatch::StopWatch() {
	clock     = new sf::Clock;
	resources = new ach::Resources();
	timer     = new ach::Timer();

	createWindow();

	for (int i = 0; i < 10; i++)
		checkpoints.push_back(new ach::Checkpoint(i));

	current   = -1;
	running   = true;
	lastClock = clock->getElapsedTime().asMilliseconds();
}



/***********************************************************************
     * StopWatch
     * destructor

***********************************************************************/
ach::StopWatch::~StopWatch() {
	deleteList(checkpoints);

	delete clock;
	delete resources;
	delete app;
}



/***********************************************************************
     * StopWatch
     * update

***********************************************************************/
void ach::StopWatch::update() {
	long currentClock = clock->getElapsedTime().asMilliseconds();

	frameClock = (currentClock - lastClock);
	lastClock = currentClock;

	processEvents();

	app->clear();
	render();
	app->display();
}



/***********************************************************************
     * StopWatch
     * render

***********************************************************************/
void ach::StopWatch::render() {
	for (unsigned int i = 0; i < checkpoints.size(); i++)
		checkpoints[i]->update();

	timer->update();
}



/***********************************************************************
     * StopWatch
     * processEvents

***********************************************************************/
void ach::StopWatch::processEvents() {
	sf::Event event;
	while (app->pollEvent(event)) processEvent(event);

	if (!app->isOpen()) running = false;
}



/***********************************************************************
     * StopWatch
     * stop

***********************************************************************/
void ach::StopWatch::stop() {
	running = false;
}



/***********************************************************************
     * StopWatch
     * processEvent

***********************************************************************/
void ach::StopWatch::processEvent(sf::Event event) {
	switch(event.type) {
		case sf::Event::Closed:
			stop();
			break;

		case sf::Event::MouseButtonReleased:
			checkpoint();
			break;

		default:
			break;
	}
}



/***********************************************************************
     * StopWatch
     * checkpoint

***********************************************************************/
void ach::StopWatch::checkpoint() {
	if (current == -1)
		timer->active = true;
	else if (current < (int)checkpoints.size())
		checkpoints[current]->setClock(timer->clock.clock);

	current++;

	if (current == (int)checkpoints.size())
		timer->active = false;
}



/***********************************************************************
     * StopWatch
     * reset

***********************************************************************/
void ach::StopWatch::reset() {
}
