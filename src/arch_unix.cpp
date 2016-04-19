/***********************************************************************
     * File       : arch_linux.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

************************************************************************
     * LINUX

***********************************************************************/
#include "headers.hpp"
#ifdef SFML_SYSTEM_LINUX
#include <signal.h>



/***********************************************************************
     * signal_catcher

***********************************************************************/
static void signal_catcher(int signum) {
	switch (signum) {
		case SIGUSR1: sw->checkpoint(); break;
		case SIGUSR2: sw->reset()     ; break;
	}
}



/***********************************************************************
     * archInit

***********************************************************************/
void archInit() {
	struct sigaction act;
	memset(&act, 0, sizeof(act));

	act.sa_handler = signal_catcher;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}



/***********************************************************************
     * archCleanUp

***********************************************************************/
void archCleanUp() {
}



/***********************************************************************
     * archEvent

***********************************************************************/
void archEvent(sf::Event) {
}

#endif
