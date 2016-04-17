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
unsigned long              frameClock;
ach::StopWatch            *sw;
ach::Resources            *resources;
sf::RenderWindow          *app;



/***********************************************************************
     * Main function

***********************************************************************/
int main() {
	sw = new ach::StopWatch;

	signals();

	while(sw->running) sw->update();
	delete sw;

	return EXIT_SUCCESS;
}
