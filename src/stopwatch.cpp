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
ach::StopWatch::StopWatch(int argc, char **argv) {
	clock     = new sf::Clock;
	resources = new ach::Resources();
	settings  = new ach::Settings();
	timer     = new ach::Timer();

	bgTex     = NULL;
	bgSpr     = NULL;

	separator = new sf::RectangleShape();
	separator->setFillColor(sf::Color::White);

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
	bestCaption->setString("Best time");

	bestText = new sf::Text();
	bestText->setFont(*resources->fonts.timer);
	bestText->setCharacterSize(20);
	bestText->setColor(sf::Color::White);

	createWindow();

	if (argc > 1) load(argv[1]);
	else          load("docs/test.json");

	resize();

	current   = -1;
	running   = true;
	lastClock = clock->getElapsedTime().asMilliseconds();
}



/***********************************************************************
     * StopWatch
     * destructor

***********************************************************************/
ach::StopWatch::~StopWatch() {
	settings->setPosition(app->getPosition());

	deleteList(checkpoints);

	delete clock;
	delete separator;
	delete timer;
	delete resources;
	delete settings;
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
	if (bgSpr)
		app->draw(*bgSpr);

	app->draw(*caption);
	app->draw(*goal);
	app->draw(*bestCaption);

	if (separated)
		app->draw(*separator);

	if (best.clock)
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
     * resize

***********************************************************************/
void ach::StopWatch::resize() {
	settings->setWidth (app->getSize().x);
	settings->setHeight(app->getSize().y);

	app->setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(app->getSize()))));

	caption->setPosition((settings->getWidth() - caption->getGlobalBounds().width) / 2, 10);
	goal->setPosition((settings->getWidth() - goal->getGlobalBounds().width) / 2, 30);
	bestCaption->setPosition(10, settings->getHeight() - 65);
	bestText->setPosition(settings->getWidth() - bestText->getGlobalBounds().width - 10, settings->getHeight() - 65);

	separator->setSize(sf::Vector2f(settings->getWidth() - 20, 1));
	separator->setPosition(10, settings->getSeparatorY());

	if (bgSpr)
		bgSpr->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(app->getSize())));

	for (unsigned int i = 0; i < checkpoints.size(); i++)
		checkpoints[i]->resize();

	updateCheckpoints();
}



/***********************************************************************
     * StopWatch
     * updateCheckpoints

***********************************************************************/
void ach::StopWatch::updateCheckpoints() {
	int index = 0;
	int from;
	int to;


	for (unsigned int i = 0; i < checkpoints.size(); i++)
		checkpoints[i]->visible = false;

	if ((int)checkpoints.size() <= settings->getVisibleCount()) {
		from      = 0;
		to        = checkpoints.size() - 1;
		separated = false;
	} else {
		from      = current - settings->getVisibleCount() / 2;
		separated = true;

		if (from < 0) {
			from = 0;
		} else if (from + settings->getVisibleCount() >= (int)checkpoints.size()) {
			from      = checkpoints.size() - settings->getVisibleCount();
			separated = false;
		}

		to = from + settings->getVisibleCount() - 1;
	}


	for (int i = from; i < to; i++)
		checkpoints[i]->setIndex(index++, i == current);

	checkpoints.back()->setIndex(index, current == (int)checkpoints.size() - 1);
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


		case sf::Event::Resized:
			resize();
			break;


		case sf::Event::MouseButtonReleased:
			if      (event.mouseButton.button == sf::Mouse::Left ) checkpoint();
			else if (event.mouseButton.button == sf::Mouse::Right) reset();
			break;


		case sf::Event::KeyReleased:
			if      (event.key.code == sf::Keyboard::Space) checkpoint();
			else if (event.key.code == sf::Keyboard::R)     reset();
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
	if (timer->clock.clock <= 0 && current >= 0)
		return;

	if (current == -1)
		timer->active = true;
	else if (current < (int)checkpoints.size()) {
		checkpoints[current]->setClock(timer->clock.clock);
		checkpoints[current]->setBest(getSegmentTime(current));
	} else
		return;

	current++;

	if (current == (int)checkpoints.size()) {
		timer->active = false;

		if (timer->clock.clock < best.clock || !best.clock) {
			best.clock = timer->clock.clock;
			updateBest();
		}

		save(JSONfile);
	}

	updateCheckpoints();
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
		if (best.clock) {
			checkpoints[i]->setBest(checkpoints[i]->best);

			if (i == 0) checkpoints[i]->setClock(checkpoints[i]->best);
			else        checkpoints[i]->setClock(checkpoints[i]->best + checkpoints[i - 1]->clock.clock);
		} else {
			checkpoints[i]->setBest(0);
			checkpoints[i]->setClock(0);
		}
	}

	updateBest();
	updateCheckpoints();
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
	bestText->setPosition(settings->getWidth() - bestText->getGlobalBounds().width - 10, settings->getHeight() - 65);
}



/***********************************************************************
     * StopWatch
     * getSegmentTime

***********************************************************************/
long ach::StopWatch::getSegmentTime(int index) {
	if (index == 0) return checkpoints[index]->clock.clock;
	else            return checkpoints[index]->clock.clock - checkpoints[index - 1]->clock.clock;
}



/***********************************************************************
     * StopWatch
     * loadBG

***********************************************************************/
void ach::StopWatch::loadBG(const char *filename, const char *JSON) {
	char bgFile[256];
	char cwd[256];

	if (bgTex) {
		delete bgTex;
		bgTex = NULL;
	}

	if (bgSpr) {
		delete bgSpr;
		bgSpr = NULL;
	}

	if (!filename)
		return;

	if (access(filename, F_OK) != -1) {
		strncpy(bgFile, filename, sizeof(bgFile));
		goto load;
	};

	strncpy(cwd, JSON, sizeof(cwd));
	snprintf(bgFile, sizeof(bgFile), "%s/%s", dirname(cwd), filename);
	if (access(bgFile, F_OK) != -1)
		goto load;

	return;

load:
	bgTex = new sf::Texture();
	bgTex->loadFromFile(bgFile);
	bgTex->setRepeated(true);
	bgTex->setSmooth(true);

	bgSpr = new sf::Sprite();
	bgSpr->setTexture(*bgTex);
}



/***********************************************************************
     * StopWatch
     * load

***********************************************************************/
void ach::StopWatch::load(const char *filename) {
	size_t index;
	json_error_t error;
	json_t *config;
	json_t *checks;
	json_t *item;

	deleteList(checkpoints);

	config = json_load_file(filename, 0, &error);
	checks = json_object_get(config, "checkpoints");

	strncpy(JSONfile, filename, 256);

	caption->setString(json_string_value (json_object_get(config, "game"  )));
	goal->setString   (json_string_value (json_object_get(config, "goal"  )));
	offset      =      json_integer_value(json_object_get(config, "offset"));
	best.clock  =      json_integer_value(json_object_get(config, "best"  ));
	timer->beep =      json_is_true      (json_object_get(config, "beep"  ));

	json_array_foreach(checks, index, item)
		checkpoints.push_back(new ach::Checkpoint(index, json_integer_value(json_object_get(item, "best")), json_string_value(json_object_get(item, "name"))));

	loadBG(json_string_value(json_object_get(config, "background")), filename);

	json_decref(config);

	reset();
}



/***********************************************************************
     * StopWatch
     * save

***********************************************************************/
void ach::StopWatch::save(const char *filename) {
	size_t index;
	json_error_t error;
	json_t *config;
	json_t *checks;
	json_t *item;

	config = json_load_file(filename, 0, &error);
	checks = json_object_get(config, "checkpoints");

	json_object_set_new_nocheck(config, "best", json_integer(best.clock));

	json_array_foreach(checks, index, item)
		json_object_set_new_nocheck(item, "best", json_integer(checkpoints[index]->best));

	json_dump_file(config, filename, JSON_INDENT(6));
	json_decref(config);

}
