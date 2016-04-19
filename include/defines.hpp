/***********************************************************************
     * File       : defines.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __DEFINES
#define __DEFINES



/***********************************************************************
     * Function macros

***********************************************************************/
#define deleteList(list)       for (; !(list).empty(); delete (list).back(), (list).pop_back())



/***********************************************************************
     * Misc

***********************************************************************/
#define CAPTION  "ASplit"
#define VERSION  " v1.0"
#define SETTINGS "data/settings.json"

#endif
