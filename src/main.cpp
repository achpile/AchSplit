/***********************************************************************
     * File       : main.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * Global variables

***********************************************************************/
long                       frameClock;
ach::StopWatch            *sw;
ach::Resources            *resources;
ach::Settings             *settings;
sf::RenderWindow          *app;



/***********************************************************************
     * Main function

***********************************************************************/
int main(int argc, char **argv) {
	sw = new ach::StopWatch(argc, argv);

	signals();

	while(sw->running) sw->update();
	delete sw;

	return EXIT_SUCCESS;
}
