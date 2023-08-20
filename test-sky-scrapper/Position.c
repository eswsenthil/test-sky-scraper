//
//  Position.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "Position.h"

#include <stdlib.h>

// Singly linked list

struct Position *gHeadPosition = NULL;

void insertPositionWith(int rowIndex, int colIndex) {
    struct Position* position = malloc(sizeof(struct Position));
    position->row = rowIndex;
    position->column = colIndex;
    position->next = gHeadPosition;
    gHeadPosition = position;
}

void initializePositions(int rowSize, int colSize) {
    int rowIndex = 0;
    
    while (rowIndex < rowSize) {
        int colIndex = 0;
        while (colIndex < colSize) {
            insertPositionWith(rowIndex, colIndex);
            ++colIndex;
        }
        ++rowIndex;
    }
}

