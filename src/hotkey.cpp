/***********************************************************************
     * File       : hotkey.cpp
     * Created    : Apr 19, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * HotKey
     * constructor

***********************************************************************/
ach::HotKey::HotKey() {
	key   = sf::Keyboard::Unknown;
	state = false;
}



/***********************************************************************
     * HotKey
     * update

***********************************************************************/
bool ach::HotKey::update() {
	bool newState = sf::Keyboard::isKeyPressed(key);

	if (newState != state) {
		state = newState;
		return !state;
	}

	return false;
}
