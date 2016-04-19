/***********************************************************************
     * File       : keyboard.cpp
     * Created    : Apr 19, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Keyboard
     * constructor

***********************************************************************/
ach::Keyboard::Keyboard() {
	for (int i = 0; i < (int)sf::Keyboard::KeyCount; i++)
		state[i] = false;
}



/***********************************************************************
     * Keyboard
     * update

***********************************************************************/
sf::Keyboard::Key ach::Keyboard::update() {
	sf::Keyboard::Key result = sf::Keyboard::Unknown;

	for (int i = 0; i < (int)sf::Keyboard::KeyCount; i++) {
		bool newState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);

		if (newState != state[i]) {
			state[i] = newState;

			if (!newState)
				result = (sf::Keyboard::Key)i;
		}
	}

	return result;
}
