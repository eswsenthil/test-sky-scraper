//
//  Arguments.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "Arguments.h"
#include "Constants.h"
#include "WriteToConsole.h"

#include <errno.h>
#include <stdio.h>

int gRowLeft[gNumRows];
int gRowRight[gNumRows];
int gColUp[gNumCols];
int gColDown[gNumCols];

int getNumberFromString(const char* str, int *number)
{
    if (str[0] >= '1' && str[0] <= '4' && str[1] == '\0') {
        *number = str[0] - '0' ;
        return 0;
    }
    writeToConsole("Error. Unxpected:");
    writeToConsole(str);
    writeToConsole("\n");
    return EINVAL;
}

int getValueForSides(const char *argv[], int beginIndexOfArgv, int *side, int numOfEntriesForTheSide)
{
    int sideIndex = 0;
    while (sideIndex < numOfEntriesForTheSide) {
        int errCode = getNumberFromString(argv[beginIndexOfArgv+sideIndex], side+sideIndex);
        if (errCode != 0) {
            return errCode;
        }
        ++sideIndex;
    }
    return 0;
}

int parseArguments(int argc, const char *argv[])
{
    if (argc != 17) {
        writeToConsole("Error. Invalid number of arguments");
        return EINVAL;
    }
    
    int errCode;
    
    errCode = getValueForSides(argv, 1, gColUp, 4);
    if (errCode != 0) {
        return errCode;
    }
    
    errCode = getValueForSides(argv, 5, gColDown, 4);
    if (errCode != 0) {
        return errCode;
    }
    
    errCode = getValueForSides(argv, 9, gRowLeft, 4);
    if (errCode != 0) {
        return errCode;
    }
    
    errCode = getValueForSides(argv, 13, gRowRight, 4);
    if (errCode != 0) {
        return errCode;
    }
    
    return 0;
}

int validateArgs(void)
{
    int index = 0;
    while (index < gNumRows) {
        if (gRowLeft[index] == 4 && gRowRight[index] != 1) {
            writeToConsole("Error\n");
            printf("gRowLeft[%d] == 4 && gRowRight[%d] != 1\n", index, index);
            return EINVAL;
        }
        if (gColUp[index] == 4 && gColDown[index] != 1) {
            writeToConsole("Error\n");
            printf("gColUp[%d] == 4 && gColDown[%d] != 1\n", index, index);
            return EINVAL;
        }
        if (gRowRight[index] == 4 && gRowLeft[index] != 1) {
            writeToConsole("Error\n");
            printf("gRowRight[%d] == 4 && gRowLeft[%d] != 1\n", index, index);
            return EINVAL;
        }
        if (gColDown[index] == 4 && gColUp[index] != 1) {
            writeToConsole("Error\n");
            printf("gColDown[%d] == 4 && gColUp[%d] != 1\n", index, index);
            return EINVAL;
        }
        ++index;
    }
    if (gRowLeft[0] == 4 && gColUp[0] != 4) {
        writeToConsole("Error\n");
        printf("gRowLeft[0] == 4 && gColUp[0] != 4\n");
        return EINVAL;
    }
    if (gRowLeft[3] == 4 && gColDown[0] != 4) {
        writeToConsole("Error\n");
        printf("gRowLeft[3] == 4 && gColDown[0] != 4\n");
        return EINVAL;
    }
    if (gColDown[3] == 4 && gRowRight[3] != 4) {
        writeToConsole("Error\n");
        printf("gColDown[3] == 4 && gRowRight[3] != 4\n");
        return EINVAL;
    }
    if (gRowRight[0] == 4 && gColUp[3] != 4) {
        writeToConsole("Error\n");
        printf("gRowRight[0] == 4 && gColUp[3] != 4\n");
        return EINVAL;
    }
    
    return 0;
}
