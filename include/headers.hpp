/***********************************************************************
     * File       : headers.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __HEADERS
#define __HEADERS


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <math.h>
#include <jansson.h>


#ifdef __unix__
#include <signal.h>
#endif


#include "defines.hpp"
#include "misc.hpp"
#include "resources.hpp"
#include "timestamp.hpp"
#include "timer.hpp"
#include "checkpoint.hpp"
#include "stopwatch.hpp"
#include "arch.hpp"
#include "externs.hpp"

#endif
