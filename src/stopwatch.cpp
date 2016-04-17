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

	bestCaption = new sf::Text();
	bestCaption->setFont(*resources->fonts.caption);
	bestCaption->setCharacterSize(20);
	bestCaption->setColor(sf::Color::White);
	bestCaption->setPosition(10, HEIGHT - 65);
	bestCaption->setString("Best time");

	bestText = new sf::Text();
	bestText->setFont(*resources->fonts.timer);
	bestText->setCharacterSize(20);
	bestText->setColor(sf::Color::White);

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
	app->draw(*bestCaption);
	app->draw(*bestText);

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
			if (event.mouseButton.button == sf::Mouse::Left)
				checkpoint();
			else if (event.mouseButton.button == sf::Mouse::Right)
				reset();

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
	else if (current < (int)checkpoints.size()) {
		checkpoints[current]->setClock(timer->clock.clock);
		checkpoints[current]->setBest(getSegmentTime(current));
	}

	current++;

	if (current == (int)checkpoints.size()) {
		timer->active = false;

		if (timer->clock.clock < best.clock) {
			best.clock = timer->clock.clock;
			updateBest();
		}

		save();
	}
}



/***********************************************************************
     * StopWatch
     * reset

***********************************************************************/
void ach::StopWatch::reset() {
	timer->clock.clock = offset;
	timer->active      = false;
	current            = -1;

	for (unsigned int i = 0; i < checkpoints.size(); i++) {
		checkpoints[i]->setBest(checkpoints[i]->best);

		if (i == 0)
			checkpoints[i]->setClock(checkpoints[i]->best);
		else
			checkpoints[i]->setClock(checkpoints[i]->best + checkpoints[i - 1]->clock.clock);
	}

	updateBest();
}



/***********************************************************************
     * StopWatch
     * updateBest

***********************************************************************/
void ach::StopWatch::updateBest() {
	char cap[32];
	best.calc();
	best.sprint2(cap, sizeof(cap));

	bestText->setString(cap);
	bestText->setPosition(WIDTH - bestText->getGlobalBounds().width - 10, HEIGHT - 65);
}



/***********************************************************************
     * StopWatch
     * calculate

***********************************************************************/
long ach::StopWatch::calculate(int index) {
	long st = getSegmentTime(index);

	return (st - checkpoints[index]->best);
}



/***********************************************************************
     * StopWatch
     * getSegmentTime

***********************************************************************/
long ach::StopWatch::getSegmentTime(int index) {
	if (index == 0)
		return checkpoints[index]->clock.clock;
	else
		return checkpoints[index]->clock.clock - checkpoints[index - 1]->clock.clock;
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

	deleteList(checkpoints);

	config = json_load_file("docs/test.json", 0, &error);
	checks = json_object_get(config, "checkpoints");

	caption->setString(json_string_value (json_object_get(config, "game"  )));
	goal->setString   (json_string_value (json_object_get(config, "goal"  )));
	offset     =       json_integer_value(json_object_get(config, "offset"));
	best.clock =       json_integer_value(json_object_get(config, "best"  ));

	json_array_foreach(checks, index, item)
		checkpoints.push_back(new ach::Checkpoint(index, json_integer_value(json_object_get(item, "best")), json_string_value(json_object_get(item, "name"))));

	json_decref(config);

	caption->setPosition((WIDTH - caption->getGlobalBounds().width) / 2, 10);
	goal->setPosition((WIDTH - goal->getGlobalBounds().width) / 2, 30);

	reset();
}



/***********************************************************************
     * StopWatch
     * save

***********************************************************************/
void ach::StopWatch::save() {
	size_t index;
	json_error_t error;
	json_t *config;
	json_t *checks;
	json_t *item;

	config = json_load_file("docs/test.json", 0, &error);
	checks = json_object_get(config, "checkpoints");

	json_object_set_new_nocheck(config, "best", json_integer(best.clock));

	json_array_foreach(checks, index, item)
		json_object_set_new_nocheck(item, "best", json_integer(checkpoints[index]->best));

	json_dump_file(config, "docs/test.json", JSON_INDENT(6));
	json_decref(config);

}
