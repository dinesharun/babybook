/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#ifndef BABYBOOK_SCRIBBLEAPP_H
#define BABYBOOK_SCRIBBLEAPP_H

#include "../gameCommon.h"

void scribbleOnDraw(void);
void scribbleOnTouch (float fPosX, float fPosY,bool release);
void scribbleOnInit();

#endif //BABYBOOK_SCRIBBLEAPP_H
