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
	clock        = new sf::Clock;
	resources    = new ach::Resources();
	settings     = new ach::Settings();
	timer        = new ach::Timer();

	bgTex        = NULL;
	bgSpr        = NULL;

	current      = -1;
	running      = true;
	lastClock    = clock->getElapsedTime().asMilliseconds();
	hkCurrent    = 0;

	separator    = new sf::RectangleShape();
	separator->setFillColor(sf::Color::White);

	createText(&caption    , resources->fonts.caption, 14, sf::Vector2f(0.0f, 0.0f), sf::Color::Yellow);
	createText(&goal       , resources->fonts.caption, 12, sf::Vector2f(0.0f, 0.0f), sf::Color::White);
	createText(&bestCaption, resources->fonts.caption, 20, sf::Vector2f(0.0f, 0.0f), sf::Color::White, "Best time");
	createText(&bestText   , resources->fonts.timer  , 20, sf::Vector2f(0.0f, 0.0f), sf::Color::White);

	createWindow();

	if (argc > 1) load(argv[1]);
	else          load("data/games/test/test.json");

	checkHotkeys();
	resize();
}



/***********************************************************************
     * StopWatch
     * destructor

***********************************************************************/
ach::StopWatch::~StopWatch() {
	settings->setPosition(app->getPosition());
	deleteList(checkpoints);

	if (bgTex) delete bgTex;
	if (bgSpr) delete bgSpr;


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

	if (hkConfigured) updateStopwatch();
	else              updateConfig();

	app->clear();
	render();
	app->display();
}



/***********************************************************************
     * StopWatch
     * updateStopwatch

***********************************************************************/
void ach::StopWatch::updateStopwatch() {
	processHotkeys();
}



/***********************************************************************
     * StopWatch
     * configStopwatch

***********************************************************************/
void ach::StopWatch::updateConfig() {
	sf::Keyboard::Key i = kbd.update();

	if (i != sf::Keyboard::Unknown)
		configHotkey(i);
}



/***********************************************************************
     * StopWatch
     * render

***********************************************************************/
void ach::StopWatch::render() {
	if (bgSpr) app->draw(*bgSpr);

	app->draw(*caption);
	app->draw(*goal);

	if (!hkConfigured)
		return;

	app->draw(*bestCaption);

	if (separated)  app->draw(*separator);
	if (best.clock) app->draw(*bestText);

	for (unsigned int i = 0; i < checkpoints.size(); i++)
		checkpoints[i]->update();

	timer->update();
}



/***********************************************************************
     * StopWatch
     * processHotkeys

***********************************************************************/
void ach::StopWatch::processHotkeys() {
	if (hotkeyCheck.update()) checkpoint();
	if (hotkeyReset.update()) reset();
}



/***********************************************************************
     * StopWatch
     * checkHotkeys

***********************************************************************/
void ach::StopWatch::checkHotkeys() {
	hkConfigured = (settings->getKeyCheckpoint() != sf::Keyboard::Unknown) &&
	               (settings->getKeyReset()      != sf::Keyboard::Unknown);

	if (hkConfigured) {
		hotkeyCheck.key = settings->getKeyCheckpoint();
		hotkeyReset.key = settings->getKeyReset();
	} else {
		caption->setString("Config");
		updateConfigScreen();
	}
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
			if (!hkConfigured)
				break;

			if      (event.mouseButton.button == sf::Mouse::Left ) checkpoint();
			else if (event.mouseButton.button == sf::Mouse::Right) reset();
			break;


		default:
			break;
	}
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
	settings->setSize(app->getSize());

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
     * updateConfigScreen

***********************************************************************/
void ach::StopWatch::updateConfigScreen() {
	switch (hkCurrent) {
		case 0: goal->setString("Press key for 'checkpoint' action"); break;
		case 1: goal->setString("Press key for 'reset' action"     ); break;

		default:
			hkConfigured = true;
			load(JSONfile);
	}

	resize();
}



/***********************************************************************
     * StopWatch
     * configHotkey

***********************************************************************/
void ach::StopWatch::configHotkey(sf::Keyboard::Key key) {
	if (hkCurrent == 0) {
		hotkeyCheck.key = key;
		settings->setKeyCheckpoint(key);
	} else if (hkCurrent == 1) {
		hotkeyReset.key = key;
		settings->setKeyReset(key);
	}

	hkCurrent++;
	updateConfigScreen();
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


	from      = bound(current - settings->getVisibleCount() / 2 + 1, 0, checkpoints.size() - settings->getVisibleCount());
	to        = min(checkpoints.size(), from + settings->getVisibleCount());
	separated = (to != (int)checkpoints.size());


	for (int i = from; i < to - 1; i++)
		checkpoints[i]->setIndex(index++, i == current);

	checkpoints.back()->setIndex(index, current == (int)checkpoints.size() - 1);
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
	best.calc();

	bestText->setString(best.sprint2());
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
		checkpoints.push_back(new ach::Checkpoint(json_integer_value(json_object_get(item, "best")), json_string_value(json_object_get(item, "name"))));

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
