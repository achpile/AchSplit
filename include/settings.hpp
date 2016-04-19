/***********************************************************************
     * File       : settings.hpp
     * Created    : Apr 18, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SETTINGS
#define __SETTINGS


namespace ach {
	struct Settings {
		json_t *config;


		 Settings();
		~Settings();

		void load(const char *filename);
		void save(const char *filename);

		int getWidth();
		int getHeight();
		int getVisibleCount();
		int getSeparatorY();
		sf::Vector2i getPosition();
		sf::Keyboard::Key getKeyCheckpoint();
		sf::Keyboard::Key getKeyReset();

		void setWidth(int value);
		void setHeight(int value);
		void setPosition(sf::Vector2i value);
		void setSize(sf::Vector2u value);
		void setKeyCheckpoint(sf::Keyboard::Key key);
		void setKeyReset(sf::Keyboard::Key key);
	};
}

#endif
