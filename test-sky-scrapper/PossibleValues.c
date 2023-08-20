//
//  PossibleValues.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "Constants.h"

#include <errno.h>
#include <stdio.h>

const int gMinHeight = 1;
const int gMaxHeight = 4;

struct PossibleValues {
    int numValues;
    int values[gMaxHeight];
};

struct PossibleValues gPossibleValues[gMaxHeight][gMaxHeight] = { 0 };

extern int gRowLeft[gNumRows];
extern int gRowRight[gNumRows];
extern int gColUp[gNumCols];
extern int gColDown[gNumCols];

int removeValueExcludingRowColumn(int rowIndex, int colIndex, int value);


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

int findValueForRowColumn(int rowIndex, int colIndex, int value)
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
    return found;
}

int findExactInColumn(int colIndex, int value)
{
    int tmpRowIndex = 0;
    while (tmpRowIndex < gNumRows) {
        if ( (gPossibleValues[tmpRowIndex][colIndex].numValues == 1) &&
            (gPossibleValues[tmpRowIndex][colIndex].values[0] == gMaxHeight)) {
            return 1;
        }
    }
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
        
        if (gPossibleValues[rowIndex][colIndex].numValues == 1) {
            int valueToBeRemoved = gPossibleValues[rowIndex][colIndex].values[0];
            removeValueExcludingRowColumn(rowIndex, colIndex, valueToBeRemoved);
        }
    }
    
    return 0;
}

int removeValueExcludingRowColumn(int rowIndex, int colIndex, int value)
{
    printf("removeValueExcludingRowColumn\n");
    
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
    printPossibleValues();
    
    return 0;
}

int setValueForRowColumn(int rowIndex, int colIndex, int value)
{
    printf("setValueForRowColumn\n");
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
    printPossibleValues();
    
    removeValueExcludingRowColumn(rowIndex, colIndex, value);
    
    if (gRowLeft[rowIndex] == gMaxHeight && colIndex == (gMaxHeight-1)) {
        int tmpColIndex = 0;
        while (tmpColIndex < (gMaxHeight-1)) {
            setValueForRowColumn(rowIndex, tmpColIndex, 1 + tmpColIndex);
            ++tmpColIndex;
        }
    }
    
    if ((gRowRight[rowIndex] == gMaxHeight) && (rowIndex == 0)) {
        int tmpColIndex = 1;
        while (tmpColIndex < gMaxHeight) {
            setValueForRowColumn(rowIndex, tmpColIndex, gMaxHeight - tmpColIndex);
            ++tmpColIndex;
        }
    }
    
    if (gColUp[colIndex] == gMaxHeight && rowIndex == (gMaxHeight-1)) {
        int tmpRowIndex = 0;
        while (tmpRowIndex < (gMaxHeight-1)) {
            setValueForRowColumn(tmpRowIndex, colIndex, 1 + tmpRowIndex);
            ++tmpRowIndex;
        }
    }
    
    if ((gColDown[colIndex] == gMaxHeight) && (rowIndex == 0)) {
        int tmpRowIndex = 1;
        while (tmpRowIndex < (gMaxHeight-1)) {
            setValueForRowColumn(tmpRowIndex, colIndex, gMaxHeight - tmpRowIndex);
            ++tmpRowIndex;
        }
    }
    
    return 0;
}


int guessIndicesForTallestBuilding(int numOfBuildingsVisible, int direction, int* minIndex, int *maxIndex)
{
    *minIndex = numOfBuildingsVisible - 1;
        
    if ((numOfBuildingsVisible == 1) ||
        (numOfBuildingsVisible == gMaxHeight)) {
        *maxIndex = *minIndex;
    }
    else {
        *maxIndex = gMaxHeight - 1;
    }
    
    if (direction == -1) {
        *minIndex = gMaxHeight - *minIndex - 1;
        *maxIndex = gMaxHeight - *maxIndex - 1;
     }
    return 0;
}

int guessLeastColumnIndex(int rowIndex, int minColIndex, int maxColIndex, int *bestIndex)
{
    int foundColIndex = -1;
    int foundCount = 0;
    int colIndex = maxColIndex;
    while (colIndex >= minColIndex) {
        int found = findValueForRowColumn(rowIndex, colIndex, gMaxHeight);
        if (found) {
            ++foundCount;
            foundColIndex = colIndex;
//            TODO - check if any other entries in the same column
//            has the possible value set with gMaxHeight
        }
        --colIndex;
    }
    if (foundCount == 1) {
        *bestIndex = foundColIndex;
        return 1;
    }
    return -1;
}

int guessLeastRowIndex(int colIndex, int minRowIndex, int maxRowIndex, int *bestIndex)
{
    int foundRowIndex = -1;
    int foundCount = 0;
    int rowIndex = maxRowIndex;
    while (rowIndex >= minRowIndex) {
        int found = findValueForRowColumn(rowIndex, colIndex, gMaxHeight);
        if (found) {
            ++foundCount;
            foundRowIndex = rowIndex;
//            TODO - check if any other entries in the same row
//            has the possible value set with gMaxHeight
        }
        --rowIndex;
    }
    if (foundCount == 1) {
        *bestIndex = foundRowIndex;
        return 1;
    }
    return -1;
}

int reduceFromRowsClue(int *visibleBuildings, int direction, int allowedValue)
{
    printf("reduceOthersFromLeft\n");
    
    int minIndex;
    int maxIndex;
    
    int rowIndex = 0;
    while (rowIndex < gNumRows) {
        if (visibleBuildings[rowIndex] != allowedValue) {
            ++rowIndex;
            continue;
        }
        minIndex = -1;
        maxIndex = -1;
        guessIndicesForTallestBuilding(visibleBuildings[rowIndex], direction, &minIndex, &maxIndex);
        if (minIndex == maxIndex) {
            setValueForRowColumn(rowIndex, minIndex, gMaxHeight);
        }
        else {
            int bestIndex = -1;
            int found = guessLeastColumnIndex(rowIndex, minIndex, maxIndex, &bestIndex);
            if (found == 1) {
                setValueForRowColumn(rowIndex, bestIndex, gMaxHeight);
            }
        }
        ++rowIndex;
    }
    printPossibleValues();
    return 0;
}

int reduceFromColumnsClue(int *visibleBuildings, int direction, int allowedValue)
{
    printf("reduceFromColumnsClue\n");
    
    int minIndex;
    int maxIndex;
    
    int colIndex = 0;
    while (colIndex < gNumCols) {
        if (visibleBuildings[colIndex] != allowedValue) {
            ++colIndex;
            continue;
        }
        minIndex = -1;
        maxIndex = -1;
        guessIndicesForTallestBuilding(visibleBuildings[colIndex], direction, &minIndex, &maxIndex);
        if (minIndex == maxIndex) {
            setValueForRowColumn(minIndex, colIndex, gMaxHeight);
        }
        else {
            int bestIndex = -1;
            int found = guessLeastRowIndex(colIndex, minIndex, maxIndex, &bestIndex);
            if (found == 1) {
                setValueForRowColumn(bestIndex, colIndex, gMaxHeight);
            }
        }
        ++colIndex;
    }
    printPossibleValues();
    return 0;
}

int solve(void)
{    
    int clueOrder[4] = { 4, 1, 3, 2 };
    int clueIndex = 0;
    while (clueIndex < 4) {
        reduceFromRowsClue(gRowLeft, 1, clueOrder[clueIndex]);
        reduceFromRowsClue(gRowRight, -1, clueOrder[clueIndex]);
        reduceFromColumnsClue(gColUp, 1, clueOrder[clueIndex]);
        reduceFromColumnsClue(gColDown, -1, clueOrder[clueIndex]);
        ++clueIndex;
    }
    
    return 0;
}


