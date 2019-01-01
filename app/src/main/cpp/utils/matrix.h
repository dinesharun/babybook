/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#ifndef BABYBOOK_MATRIX_H
#define BABYBOOK_MATRIX_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "misc.h"

#define MAT(a, i, j)    (((float*) ((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATB(a, i, j)   (((uint8*) ((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATU8(a, i, j)  (((uint8*) ((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATS8(a, i, j)  (((sint8*) ((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATU16(a, i, j) (((uint16*)((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATS16(a, i, j) (((sint16*)((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATU32(a, i, j) (((uint32*)((a)->values))[j + (i * (a)->numberOfColumns)])
#define MATS32(a, i, j) (((sint32*)((a)->values))[j + (i * (a)->numberOfColumns)])

#define PMAT struct matrix*

#define MAT_FLOAT  0
#define MAT_BINARY 1
#define MAT_UINT8  2
#define MAT_SINT8  3
#define MAT_UINT16 4
#define MAT_SINT16 5
#define MAT_UINT32 6
#define MAT_SINT32 7

struct matrix{
    uint32 numberOfRows;
    uint32 numberOfColumns;
    uint32 valuesSize;
    uint8  dataType;
    void* values;
};

struct pixel_pos {
    int x;
    int y;
};

typedef struct pixel_pos POS;

PMAT createMatrix(uint32 numberOfRows, uint32 numberOfColumns);
PMAT createMatrixGnDataType(uint32 numberOfRows, uint32 numberOfColumns, uint8 dataType);
PMAT createMatrixFromGn(PMAT image);
void initMatrix(PMAT mat, void* values);
void destroyMatrix(PMAT mat);

void printMatrix(PMAT mat, char* desc);
void printMatrixOverride(PMAT mat,char* desc,int override) ;
void dumpMatrixToFile(PMAT mat, char* fileName, char* pattern, char* empty);

PMAT subtractMatrices(PMAT mat1, PMAT mat2);

void scalarMatrixAddition(PMAT mat, float value);
void scalarMatrixSubtraction(PMAT mat, float value);
void scalarMatrixDivision(PMAT mat, float divisor);
void scalarMatrixMultiplication(PMAT mat, float multiplier);

void normalizeMatrix(PMAT mat, float oldMinVal, float oldMaxVal, float newMinVal, float newMaxVal);

uint32 convertMatrixToBuffer(PMAT input, uint8* outputBuffer);

PMAT rotateLeft(PMAT input);

POS getMaxPos(PMAT img, float* opMaxVal);

#endif //BABYBOOK_MATRIX_H
