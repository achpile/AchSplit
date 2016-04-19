/***********************************************************************
     * File       : hotkey.hpp
     * Created    : Apr 19, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __HOTKEY
#define __HOTKEY


namespace ach {
	struct HotKey {
		sf::Keyboard::Key key;
		bool              state;


		 HotKey();

		bool update();
	};
}

#endif
