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

		void setWidth(int value);
		void setHeight(int value);
		void setPosition(sf::Vector2i value);
	};
}

#endif
