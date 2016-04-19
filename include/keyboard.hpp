/***********************************************************************
     * File       : keyboard.hpp
     * Created    : Apr 19, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __KEYBOARD
#define __KEYBOARD


namespace ach {
	struct Keyboard {
		bool state[sf::Keyboard::KeyCount];


		Keyboard();

		sf::Keyboard::Key update();
	};
}

#endif
