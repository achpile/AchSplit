/***********************************************************************
     * File       : arch.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * UNIX

***********************************************************************/
#ifdef __unix__
static void signal_catcher(int signum) {
	switch (signum) {
		case SIGUSR1: sw->checkpoint(); break;
		case SIGUSR2: sw->reset()     ; break;
	}
}

static void signals_unix() {
	struct sigaction act;
	memset(&act, 0, sizeof(act));

	act.sa_handler = signal_catcher;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}
#endif



/***********************************************************************
     * signals

***********************************************************************/
void signals() {
#ifdef __unix__
	signals_unix();
#endif
}
