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

	caption = new sf::Text();
	caption->setFont(*resources->fonts.caption);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color::Yellow);

	goal = new sf::Text();
	goal->setFont(*resources->fonts.caption);
	goal->setCharacterSize(12);
	goal->setColor(sf::Color::White);


	createWindow();
	load();

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
	delete timer;
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
	app->draw(*caption);
	app->draw(*goal);

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



/***********************************************************************
     * StopWatch
     * load

***********************************************************************/
void ach::StopWatch::load() {
	size_t index;
	json_error_t error;
	json_t *config;
	json_t *checks;
	json_t *item;

	config = json_load_file("docs/test.json", 0, &error);
	checks = json_object_get(config, "checkpoints");

	caption->setString(json_string_value(json_object_get(config, "game")));
	goal->setString(json_string_value(json_object_get(config, "goal")));
	timer->clock.clock = json_integer_value(json_object_get(config, "offset"));

	json_array_foreach(checks, index, item)
		checkpoints.push_back(new ach::Checkpoint(index, json_string_value(json_object_get(item, "name"))));

	json_decref(config);

	caption->setPosition((WIDTH - caption->getGlobalBounds().width) / 2, 10);
	goal->setPosition((WIDTH - goal->getGlobalBounds().width) / 2, 30);
}
