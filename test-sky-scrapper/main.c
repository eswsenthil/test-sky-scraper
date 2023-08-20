//
//  main.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "WriteToConsole.h"
#include "Constants.h"
#include "Arguments.h"
#include "PossibleValues.h"

#include <stdlib.h> // malloc
#include <errno.h>
#include <stdio.h>


int initializeMatrix(void);

int main(int argc, const char * argv[]) {
    
    int errCode = parseArguments(argc, argv);
    if (errCode != 0) {
        return errCode;
    }
    
    errCode = validateArgs();
    if (errCode != 0) {
        return errCode;
    }
    
    initializePossibleValues();
    printPossibleValues();
    solve();
    return 0;
}
