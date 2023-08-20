//
//  WriteToConsole.c
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#include "WriteToConsole.h"

#include <unistd.h> // write

void writeToConsole(const char* message)
{
    while (*message != '\0') {
        write(1, message, 1);
    }
}

