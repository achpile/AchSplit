/***********************************************************************
     * File       : misc.hpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC
#define __MISC


void createWindow();
void createText(sf::Text **text, sf::Font *font, int size, sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), sf::Color color = sf::Color::White, const char *caption = "");
int  min(int a, int b);
int  bound(int x, int a, int b);

#endif
