//
//  Position.h
//  test-sky-scrapper
//
//  Created by Tester on 20.8.2023.
//

#ifndef Position_h
#define Position_h

struct Position {
    int row;
    int column;
    struct Position *next;
};

extern struct Position *gHeadPosition;

#endif /* Position_h */
