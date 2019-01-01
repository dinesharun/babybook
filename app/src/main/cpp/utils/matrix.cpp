/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "matrix.h"

PMAT createMatrix(uint32 numberOfRows, uint32 numberOfColumns)
{
    return createMatrixGnDataType(numberOfRows, numberOfColumns, MAT_FLOAT);
}

PMAT createMatrixGnDataType(uint32 numberOfRows, uint32 numberOfColumns, uint8 dataType)
{
    PMAT mat;
    int size = 0;

    mat = (PMAT)malloc(sizeof(struct matrix));

    mat->numberOfRows = numberOfRows;
    mat->numberOfColumns = numberOfColumns;
    mat->dataType = dataType;

    if(dataType == MAT_FLOAT) {
        size = sizeof(float);
    } else if(dataType == MAT_BINARY) {
        size = sizeof(uint8);
    } else if(dataType == MAT_UINT32) {
        size = sizeof(uint32);
    } else {
        assert(0);
    }

    mat->valuesSize = numberOfRows * numberOfColumns * size;
    mat->values = malloc(mat->valuesSize);
    memset(mat->values, 0, mat->valuesSize);

    return mat;
}

PMAT createMatrixFromGn(PMAT image)
{
    PMAT mat;

    mat = (PMAT)malloc(sizeof(struct matrix));

    mat->numberOfRows = image->numberOfRows;
    mat->numberOfColumns = image->numberOfColumns;
    mat->dataType = image->dataType;
    mat->valuesSize = image->valuesSize;

    mat->values = malloc(mat->valuesSize);
    memcpy(mat->values, image->values, mat->valuesSize);

    return mat;
}

void destroyMatrix(PMAT mat) {
    mat->numberOfRows = 0;
    mat->numberOfColumns = 0;

    free(mat->values);
    free(mat);
}

void printMatrix(PMAT mat,char* desc)
{

#ifdef LOG_ENABLED

    uint32 i;
    uint32 j;

    printf("\n --------------------------------------- \n");
    printf("\t%s",desc);
    printf("\n --------------------------------------- \n");
    for (i = 0; i < mat->numberOfRows; ++i) {
        for (j = 0; j < mat->numberOfColumns; ++j) {
            if(mat->dataType == MAT_FLOAT) {
                printf("%10.3f ", MAT(mat, i, j));
            } else if(mat->dataType == MAT_BINARY) {
                printf("%03d ", MATB(mat, i, j));
            } else {
                assert(0);
            }
        }
        printf("\n");
    }

#endif

}

void dumpMatrixToFile(PMAT mat, char* fileName, char* pattern, char* empty)
{
    FILE* fp = fopen(fileName, "w");

    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            if(mat->dataType == MAT_FLOAT) {
                if(MAT(mat, i, j) == 0) {
                    fprintf(fp, "%s", empty);
                } else {
                    fprintf(fp, pattern, MAT(mat, i, j));
                }
            } else if(mat->dataType == MAT_BINARY) {
                if(MATB(mat, i, j) == 0) {
                    fprintf(fp, "%s", empty);
                } else {
                    fprintf(fp, pattern, MATB(mat, i, j));
                }
            } else {
                assert(0);
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

PMAT subtractMatrices(PMAT mat1, PMAT mat2) {
    assert(mat1->numberOfRows == mat2->numberOfRows);
    assert(mat1->numberOfColumns == mat2->numberOfColumns);

    PMAT output = createMatrix(mat1->numberOfRows,
                               mat1->numberOfColumns);

    for (int i = 0; i < mat1->numberOfRows; ++i) {
        for (int j = 0; j < mat1->numberOfColumns; ++j) {
            MAT(output,i,j) = MAT(mat1,i,j) - MAT(mat2, i, j);
        }

    }

    return output;
}

void scalarMatrixAddition(PMAT mat, float value) {
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            MAT(mat,i,j) = MAT(mat,i,j) + value;
        }
    }
}

void scalarMatrixSubtraction(PMAT mat, float value) {
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            MAT(mat,i,j) = MAT(mat,i,j) - value;
        }
    }
}

void scalarMatrixMultiplication(PMAT mat, float multiplier) {
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            MAT(mat,i,j) = MAT(mat,i,j) * multiplier;
        }
    }
}

void scalarMatrixDivision(PMAT mat, float divisor) {
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            MAT(mat,i,j) = MAT(mat,i,j) / divisor;
        }
    }
}

void normalizeMatrix(PMAT mat, float oldMinVal, float oldMaxVal, float newMinVal, float newMaxVal)
{
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            MAT(mat, i, j) = (((newMaxVal - newMinVal) * (MAT(mat, i, j) - oldMinVal)) / (oldMaxVal - oldMinVal)) + newMinVal;
        }
    }
}

void initMatrix(PMAT mat, void* values) {
    for (int i = 0; i < mat->numberOfRows; ++i) {
        for (int j = 0; j < mat->numberOfColumns; ++j) {
            if(mat->dataType == MAT_FLOAT) {
                MAT(mat,i,j) = ((float*) values)[j + (i * mat->numberOfColumns)];
            } else if(mat->dataType == MAT_BINARY) {
                MATB(mat,i,j) = ((uint8*) values)[j + (i * mat->numberOfColumns)];
            } else {
                assert(0);
            }
        }
    }
}

uint32 convertMatrixToBuffer(PMAT input, uint8* outputBuffer) {
    uint32 bufferSize = 0;

    for (int i = 0; i < input->numberOfRows; ++i) {
        int numColBytes = 0;
        for (int j = 0; j < input->numberOfColumns; ++j) {
            if(input->dataType == MAT_FLOAT) {
                outputBuffer[bufferSize] = (uint8) MAT(input, i, j);
                outputBuffer[bufferSize+1] = (uint8) MAT(input, i, j);
                outputBuffer[bufferSize+2] = (uint8) MAT(input, i, j);
            } else if(input->dataType == MAT_BINARY) {
                outputBuffer[bufferSize] = (uint8) MATB(input, i, j)*(uint8)255;
                outputBuffer[bufferSize+1] = (uint8) MATB(input, i, j)*(uint8)255;
                outputBuffer[bufferSize+2] = (uint8) MATB(input, i, j)*(uint8)255;
            } else if(input->dataType == MAT_UINT32) {
                uint32 rgbVal = MATU32(input, i, j);
                outputBuffer[bufferSize+2] = (uint8) (rgbVal & 0x000000ff);   rgbVal = rgbVal >> 8;
                outputBuffer[bufferSize+1] = (uint8) (rgbVal & 0x000000ff); rgbVal = rgbVal >> 8;
                outputBuffer[bufferSize] = (uint8) (rgbVal & 0x000000ff);
            } else {
                assert(0);
            }

            bufferSize+=3;
            numColBytes+=3;
        }

        while((numColBytes%4) != 0) {
            outputBuffer[bufferSize] = 0;
            bufferSize++; numColBytes++;
        }
    }

    return bufferSize;
}

PMAT rotateLeft(PMAT input)
{
    PMAT rotatedMat = createMatrixGnDataType(input->numberOfColumns, input->numberOfRows, input->dataType);

    for (int i = 0; i < input->numberOfRows; ++i) {
        for (int j = 0; j < input->numberOfColumns; ++j) {
            if(input->dataType == MAT_FLOAT) {
                MAT(rotatedMat, ((rotatedMat->numberOfRows - 1) - j), i) = MAT(input, i, j);
            } else if(input->dataType == MAT_BINARY) {
                MATB(rotatedMat, ((rotatedMat->numberOfRows - 1) - j), i) = MATB(input, i, j);
            } else {
                assert(0);
            }
        }
    }

    return rotatedMat;
}

POS getMaxPos(PMAT img, float* opMaxVal)
{
    POS maxPos;
    float maxVal = 0;

    maxPos.x = 0;
    maxPos.y = 0;

    for (int i = 0; i < img->numberOfRows; ++i) {
        for (int j = 0; j < img->numberOfColumns; ++j) {
            if(MAT(img, i, j) > maxVal) {
                maxVal = MAT(img, i, j);
                maxPos.x = i;
                maxPos.y = j;
            }
        }
    }

#ifdef LOG_ENABLED
    printf("getMaxPos max (%f) at pos: %d,%d \n", maxVal, maxPos.y, maxPos.x);
#endif
    *opMaxVal = maxVal;

    return maxPos;
}