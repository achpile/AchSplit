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
#define VERSION  " v1.0-rc2"
#define SETTINGS "docs/settings.json"

#define HOTKEY_ID_CHECK 1
#define HOTKEY_ID_RESET 2

#endif
