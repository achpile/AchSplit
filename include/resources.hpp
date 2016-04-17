/***********************************************************************
     * File       : resources.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __RESOURCES
#define __RESOURCES


namespace ach {
	struct Resources {
		struct {
			sf::Font *timer;
			sf::Font *caption;
		} fonts;


		 Resources();
		~Resources();

		void loadFont(sf::Font **font, const char *filename);
	};
}

#endif
