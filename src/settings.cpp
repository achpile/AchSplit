/***********************************************************************
     * File       : settings.cpp
     * Created    : Apr 18, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Settings
     * constructor

***********************************************************************/
ach::Settings::Settings() {
	load(SETTINGS);
}



/***********************************************************************
     * Settings
     * destructor

***********************************************************************/
ach::Settings::~Settings() {
	save(SETTINGS);
	json_decref(config);
}



/***********************************************************************
     * Settings
     * load

***********************************************************************/
void ach::Settings::load(const char *filename) {
	json_error_t error;
	config = json_load_file(filename, 0, &error);
}



/***********************************************************************
     * Settings
     * save

***********************************************************************/
void ach::Settings::save(const char *filename) {
	json_dump_file(config, filename, JSON_INDENT(6));
}



/***********************************************************************
     * Settings
     * getWidth

***********************************************************************/
int ach::Settings::getWidth() {
	return json_integer_value(json_object_get(config, "width"));
}



/***********************************************************************
     * Settings
     * getHeight

***********************************************************************/
int ach::Settings::getHeight() {
	return json_integer_value(json_object_get(config, "height"));
}



/***********************************************************************
     * Settings
     * getSeparatorY

***********************************************************************/
int ach::Settings::getSeparatorY() {
	return 56 + 25 * (getVisibleCount() - 1);
}



/***********************************************************************
     * Settings
     * getVisibleCount

***********************************************************************/
int ach::Settings::getVisibleCount() {
	return (getHeight() - 125) / 25;
}



/***********************************************************************
     * Settings
     * getPosition

***********************************************************************/
sf::Vector2i ach::Settings::getPosition() {
	return sf::Vector2i(json_integer_value(json_object_get(config, "x")),
	                    json_integer_value(json_object_get(config, "y")));
}



/***********************************************************************
     * Settings
     * getKeyCheckpoint

***********************************************************************/
sf::Keyboard::Key ach::Settings::getKeyCheckpoint() {
	if (!json_object_get(config, "hk_checkpoint"))
		return sf::Keyboard::Unknown;

	return (sf::Keyboard::Key)json_integer_value(json_object_get(config, "hk_checkpoint"));
}



/***********************************************************************
     * Settings
     * getKeyReset

***********************************************************************/
sf::Keyboard::Key ach::Settings::getKeyReset() {
	if (!json_object_get(config, "hk_reset"))
		return sf::Keyboard::Unknown;

	return (sf::Keyboard::Key)json_integer_value(json_object_get(config, "hk_reset"));
}



/***********************************************************************
     * Settings
     * setWidth

***********************************************************************/
void ach::Settings::setWidth(int value) {
	json_object_set_new_nocheck(config, "width", json_integer(value));
}



/***********************************************************************
     * Settings
     * setHeight

***********************************************************************/
void ach::Settings::setHeight(int value) {
	json_object_set_new_nocheck(config, "height", json_integer(value));
}



/***********************************************************************
     * Settings
     * setPosition

***********************************************************************/
void ach::Settings::setPosition(sf::Vector2i value) {
	json_object_set_new_nocheck(config, "x", json_integer(value.x));
	json_object_set_new_nocheck(config, "y", json_integer(value.y));
}



/***********************************************************************
     * Settings
     * setKeyCheckpoint

***********************************************************************/
void ach::Settings::setKeyCheckpoint(sf::Keyboard::Key key) {
	json_object_set_new_nocheck(config, "hk_checkpoint", json_integer(key));
}



/***********************************************************************
     * Settings
     * setKeyReset

***********************************************************************/
void ach::Settings::setKeyReset(sf::Keyboard::Key key) {
	json_object_set_new_nocheck(config, "hk_reset", json_integer(key));
}
