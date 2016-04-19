/***********************************************************************
     * File       : arch_win.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

************************************************************************
     * WIN

***********************************************************************/
#include "headers.hpp"
#ifdef SFML_SYSTEM_WINDOWS
#include <windows.h>



/***********************************************************************
     * archInit

***********************************************************************/
void archInit() {
	RegisterHotKey(app->getSystemHandle(), HOTKEY_ID_CHECK, MOD_ALT , VK_NUMPAD0   );
	RegisterHotKey(app->getSystemHandle(), HOTKEY_ID_RESET, MOD_ALT , VK_OEM_PERIOD);
}



/***********************************************************************
     * archCleanUp

***********************************************************************/
void archCleanUp() {
	UnregisterHotKey(app->getSystemHandle(), HOTKEY_ID_CHECK);
	UnregisterHotKey(app->getSystemHandle(), HOTKEY_ID_RESET);
}



/***********************************************************************
     * archEvent

***********************************************************************/
void archEvent(sf::Event event) {
	if (event.os.message == WM_DROPFILES) {
		char buf[256];
		HDROP hDropInfo = (HDROP) event.os.wParam;
		DragQueryFile (hDropInfo, 0, buf, sizeof(buf));
		load(buf);
	}

	if (event.os.message == WM_HOTKEY) {
		if (event.os.wParam == HOTKEY_ID_CHECK) stopwatch->checkpoint();
		if (event.os.wParam == HOTKEY_ID_RESET) stopwatch->reset();
	}
}

#endif
