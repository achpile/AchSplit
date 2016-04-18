/***********************************************************************
     * File       : misc.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * createWindow

***********************************************************************/
void createWindow() {
	app = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32),
	                           CAPTION VERSION,
	                           sf::Style::Close);
}
