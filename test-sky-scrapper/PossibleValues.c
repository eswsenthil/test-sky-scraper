//
//  PossibleValues.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "Position.h"
#include "Constants.h"

#include <errno.h>
#include <stdio.h>

struct PossibleValues {
    int numValues;
    int values[4];
};

struct PossibleValues gPossibleValues[4][4] = { 0 };

extern int gRowLeft[gNumRows];
extern int gRowRight[gNumRows];
extern int gColUp[gNumCols];
extern int gColDown[gNumCols];

const int gMinHeight = 1;
const int gMaxHeight = 4;

void initializePossibleValues(void)
{
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        int colIndex = 0;
        while (colIndex < gNumCols) {
            gPossibleValues[rowIndex][colIndex].numValues = 4;
            gPossibleValues[rowIndex][colIndex].values[0] = 1;
            gPossibleValues[rowIndex][colIndex].values[1] = 2;
            gPossibleValues[rowIndex][colIndex].values[2] = 3;
            gPossibleValues[rowIndex][colIndex].values[3] = 4;
            ++colIndex;
        }
        ++rowIndex;
    }
}

void printIntArray(const int *numArr, int count)
{
    int index = 0;
    while (index < count) {
        printf("%d,", numArr[index]);
        ++index;
    }
}
void printPossibleValues(void)
{
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        int colIndex = 0;
        while (colIndex < gNumCols) {
            printf("(");
            printIntArray(gPossibleValues[rowIndex][colIndex].values, gPossibleValues[rowIndex][colIndex].numValues);
            printf(")\t\t");
            ++colIndex;
        }
        
        printf("\n");
        ++rowIndex;
    }
}

int setValueForRowColumn(int rowIndex, int colIndex, int value)
{
    int index = 0;
    int found = 0;
    while (index < gPossibleValues[rowIndex][colIndex].numValues) {
        if (gPossibleValues[rowIndex][colIndex].values[index] == value) {
            found = 1;
            break;
        }
        ++index;
    }
    if (found == 0) {
        printf("%d is not a possible value at (%d, %d). Available values are:", value, rowIndex, colIndex);
        index = 0;
        while (index < gPossibleValues[rowIndex][colIndex].numValues) {
            printf("%d,", gPossibleValues[rowIndex][colIndex].values[index]);
            ++index;
        }
        printf("\n");
    }
    gPossibleValues[rowIndex][colIndex].numValues = 1;
    gPossibleValues[rowIndex][colIndex].values[0] = value;
    return 0;
}

int removeValueForRowColumn(int rowIndex, int colIndex, int value)
{
    int index = 0;
    int found = 0;
    while (index < gPossibleValues[rowIndex][colIndex].numValues) {
        if (gPossibleValues[rowIndex][colIndex].values[index] == value) {
            found = 1;
            break;
        }
        ++index;
    }
    if (found == 0) {
        printf("%d is not a possible value at (%d, %d). Available values are:", value, rowIndex, colIndex);
        index = 0;
        while (index < gPossibleValues[rowIndex][colIndex].numValues) {
            printf("%d,", gPossibleValues[rowIndex][colIndex].values[index]);
            ++index;
        }
        printf("\n");
        return ESRCH;
    }
    
    found = 0;
    while (index < gPossibleValues[rowIndex][colIndex].numValues) {
        if (found == 0) {
            if (gPossibleValues[rowIndex][colIndex].values[index] == value) {
                found = 1;
            }
        }
        if (found == 1) {
            int nextIndex = index + 1;
            if (nextIndex <  gPossibleValues[rowIndex][colIndex].numValues) {
                gPossibleValues[rowIndex][colIndex].values[index] = gPossibleValues[rowIndex][colIndex].values[nextIndex];
            }
        }
        ++index;
    }
    if (found == 1) {
        --gPossibleValues[rowIndex][colIndex].numValues;
    }
    
    return 0;
}

int removeValueForRowsAndColumns(int rowIndex, int colIndex, int value)
{
    int tmpRowIndex = rowIndex + 1;
    while (tmpRowIndex < gNumRows) {
        removeValueForRowColumn(tmpRowIndex, colIndex, value);
        ++tmpRowIndex;
    }
    
    tmpRowIndex = rowIndex - 1;
    while (tmpRowIndex >= 0) {
        removeValueForRowColumn(tmpRowIndex, colIndex, value);
        --tmpRowIndex;
    }
    
    int tmpColIndex = colIndex + 1;
    while (tmpColIndex < gNumCols) {
        removeValueForRowColumn(rowIndex, tmpColIndex, value);
        ++tmpColIndex;
    }
    tmpColIndex = colIndex -1;
    while (tmpColIndex >= 0) {
        removeValueForRowColumn(rowIndex, tmpColIndex, value);
        --tmpColIndex;
    }
    return 0;
}

int reduceMinAndMaxFromLeft(void)
{
    int rowIndex = 0;
    int colIndex = 0;
    
    while (rowIndex < gNumRows) {
        if (gRowLeft[rowIndex] == 1) {
                setValueForRowColumn(rowIndex, colIndex, 4);
                removeValueForRowsAndColumns(rowIndex, colIndex, 4);
                printf("Handle gRowLeft[%d] == 1 for column 0\n", rowIndex);
                printPossibleValues();
        }
        else if (gRowLeft[rowIndex] == 4) {
            int tmpColIndex = colIndex;
            while (tmpColIndex < gNumCols) {
                setValueForRowColumn(rowIndex, tmpColIndex, 1 + tmpColIndex);
                removeValueForRowsAndColumns(rowIndex, tmpColIndex, 1 + tmpColIndex);
                ++tmpColIndex;
            }
            printf("Handle gRowLeft[%d] == 4 for column 0\n", rowIndex);
            printPossibleValues();
        }
        else if (gRowLeft[rowIndex] == 3) {
            // only 1 and 2 are allowed. 3 and 4 are not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
            removeValueForRowColumn(rowIndex, colIndex, 3);
        }
        else if (gRowLeft[rowIndex] == 2) {
            // only 1, 2 and 3 are allowed. 4 is not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
        }
        ++rowIndex;
    }
    
    return (0);
}

int reduceMinAndMaxFromRight(void)
{
    int rowIndex = 0;
    int colIndex = gNumCols - 1;
    
    while (rowIndex < gNumRows) {
        if (gRowRight[rowIndex] == 1) {
            setValueForRowColumn(rowIndex, colIndex, 4);
            removeValueForRowsAndColumns(rowIndex, colIndex, 4);
            printf("Handle gRowRight[%d] == 1 for column 3\n", rowIndex);
            printPossibleValues();
        }
        else if (gRowRight[rowIndex] == 4) {
            int tmpColIndex = 0;
            while (tmpColIndex < gNumCols) {
                setValueForRowColumn(rowIndex, tmpColIndex, 1 + tmpColIndex);
                removeValueForRowsAndColumns(rowIndex, tmpColIndex, 1 + tmpColIndex);
                ++tmpColIndex;
            }
            printf("Handle gRowRight[%d] == 4 for column 3\n", rowIndex);
            printPossibleValues();
        }
        else if (gRowRight[rowIndex] == 3) {
            // only 1 and 2 are allowed. 3 and 4 are not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
            removeValueForRowColumn(rowIndex, colIndex, 3);
        }
        else if (gRowRight[rowIndex] == 2) {
            // only 1, 2 and 3 are allowed. 4 is not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
        }
        
        ++rowIndex;
    }
    return 0;
}

int reduceMinAndMaxFromTop(void)
{
    int rowIndex = 0;
    int colIndex = 0;
    
    while (colIndex < gNumCols) {
        if (gColUp[colIndex] == 1) {
                setValueForRowColumn(rowIndex, colIndex, 4);
                removeValueForRowsAndColumns(rowIndex, colIndex, 4);
                printf("Handle gColUp[%d] == 1\n", colIndex);
                printPossibleValues();
        }
        else if (gColUp[colIndex] == 4) {
            int tmpRowIndex = rowIndex;
            while (tmpRowIndex < gNumRows) {
                setValueForRowColumn(tmpRowIndex, colIndex, 1 + tmpRowIndex);
                removeValueForRowsAndColumns(tmpRowIndex, colIndex, 1 + tmpRowIndex);
                ++tmpRowIndex;
            }
            printf("Handle gColUp[%d] == 4\n", colIndex);
            printPossibleValues();
        }
        else if (gColUp[rowIndex] == 3) {
            // only 1 and 2 are allowed. 3 and 4 are not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
            removeValueForRowColumn(rowIndex, colIndex, 3);
        }
        else if (gColUp[rowIndex] == 2) {
            // only 1, 2 and 3 are allowed. 4 is not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
        }
        
        ++colIndex;
    }
    
    return (0);
}

int reduceMinAndMaxFromBottom(void)
{
    int rowIndex = gNumRows - 1;
    int colIndex = 0;
    
    while (colIndex < gNumCols) {
        if (gColDown[colIndex] == 1) {
                setValueForRowColumn(rowIndex, colIndex, 4);
                removeValueForRowsAndColumns(rowIndex, colIndex, 4);
                printf("Handle gColDown[%d] == 1\n", colIndex);
                printPossibleValues();
        }
        else if (gColDown[colIndex] == 4) {
            int tmpRowIndex = rowIndex;
            while (tmpRowIndex >= 0) {
                setValueForRowColumn(tmpRowIndex, colIndex, 1 + tmpRowIndex);
                removeValueForRowsAndColumns(tmpRowIndex, colIndex, 1 + tmpRowIndex);
                --tmpRowIndex;
            }
            printf("Handle gColUp[%d] == 4\n", colIndex);
            printPossibleValues();
        }
        else if (gColDown[rowIndex] == 3) {
            // only 1 and 2 are allowed. 3 and 4 are not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
            removeValueForRowColumn(rowIndex, colIndex, 3);
        }
        else if (gColDown[rowIndex] == 2) {
            // only 1, 2 and 3 are allowed. 4 is not allowed.
            removeValueForRowColumn(rowIndex, colIndex, 4);
        }
        ++colIndex;
    }
    
    return (0);
}


int reduceMinAndMax(void)
{
    reduceMinAndMaxFromLeft();
    reduceMinAndMaxFromRight();
    reduceMinAndMaxFromTop();
    reduceMinAndMaxFromBottom();
    
    return 0;
}

int guessMinIndexForTallestBuildingInForwardDirection(int numOfBuildingsVisible, int* minIndex, int *maxIndex)
{
    int minIndexForTallestBuilding = numOfBuildingsVisible - 1;
    
    if ((numOfBuildingsVisible == 1) ||
        (numOfBuildingsVisible == gMaxHeight)) {
        *minIndex = minIndexForTallestBuilding;
        *maxIndex = *minIndex;
    }
    
    
    return 0;
}

int reduceOtherFromLeft(void)
{
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        
    }
    return 0;
}

int iteration1(void)
{
    printf("Iteration 1:\n");
    
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        int colIndex = 0;
        while (colIndex < gNumCols) {
            if (gPossibleValues[rowIndex][colIndex].numValues != 1) {
                
            }
            ++colIndex;
        }
        printf("\n");
        ++rowIndex;
    }
    return 0;
}

int solve(void)
{
    reduceMinAndMax();
    
    iteration1();
    return 0;
}

int setExpectedValuesForRow(int rowIndex)
{
    switch (gRowLeft[rowIndex]) {
        case 1:
        {
            if (rowIndex == 0 && gColUp[0] != 1) {
                printf("gRowLeft[0] is 1 but gColUp[0] is not 1\n");
                return EINVAL;
            }
            
            if (rowIndex == 3 && gColDown[0] != 1) {
                printf("gRowLeft[3] is 1 but gColDown[0] is not 1\n");
                return EINVAL;
            }
            gPossibleValues[rowIndex][0].numValues = 1;
            gPossibleValues[rowIndex][0].values[0] = 4;
            int colIndex = 1;
            
            break;
        }
            
        case 2:
        {
            break;
        }
        
        case 3:
        {
            break;
        }
        
        case 4:
        {
            if (gRowRight[rowIndex] != 1) {
                printf("gRowLeft[rowIndex] is 4 but gRowRight[rowIndex] is not 1 for rowIndex:%d\n", rowIndex);
                return EINVAL;
            }
            
            int colIndex = 0;
            while (colIndex < 4) {
                gPossibleValues[rowIndex][colIndex].numValues = 1;
                gPossibleValues[rowIndex][colIndex].values[0] = 1 + colIndex;
                ++colIndex;
            }
            
            break;
        }
    }
    return 0;
}

int initializeMatrix(void)
{
    struct Position *position = gHeadPosition;
    while (position) {
        int rowIndex = position->row;
        int colIndex = position->column;
        
    }
    
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        switch (gRowLeft[rowIndex]) {
            case 1:
                {
                    int colIndex = 0;
                    while (colIndex < 4) {
                        gPossibleValues[rowIndex][colIndex].numValues = 1;
                        gPossibleValues[rowIndex][colIndex].values[0] = 4 - colIndex;
                        ++colIndex;
                    }
                    if (rowIndex == 0) {
                        
                    }
                }
                break;
                
            default:
                break;
        }
    }
    return 0;
}

