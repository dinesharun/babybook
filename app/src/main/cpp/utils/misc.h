//
// Created by Indumathi Dinesh on 31/12/18.
//

#ifndef BABYBOOK_MISC_H
#define BABYBOOK_MISC_H

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned int uint16;

typedef signed char sint8;
typedef signed int sint32;
typedef signed int sint16;

#define MAX_UINT32 (0xffffffffu)

uint32 currTimeMS(void);
uint32 currTimeDiff(uint32 t0);
uint32 timeDiff(uint32 t1, uint32 t0);

#endif //BABYBOOK_MISC_H
