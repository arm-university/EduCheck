/*H**********************************************************************
* FILENAME : song.h          DESIGN REF:
*
* DESCRIPTION :
*       Defining Class Song
*
* PUBLIC FUNCTIONS : None.
*
* NOTES :
*
*       Copyright (c) 2020 Arm Limited and affiliates.
*       SPDX-License-Identifier: Apache-2.0
*
* AUTHOR :    Arm Education      START DATE :    January 2021
*
* CHANGES :
*
 * REF NO    DATE                WHO                                       DETAIL
 *           January 2021        Arm Education ()      Original Code
*
*H*/

#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

// Define float pointer to array
typedef float *ptrtoarray;

class Song
{

    // Public access specifier
public:
    // Class attributes
    string name1;
    string name2;
    ptrtoarray note;
    ptrtoarray beat;
    float tempo;
    int length;

    // Class constructor with parameters
    Song(string in_name1, string in_name2, ptrtoarray in_note, ptrtoarray in_beat, float in_tempo, int in_length)
    {
        // Set the attributes equal to the constructor parameters
        name1 = in_name1; // song name
        name2 = in_name2; // author name
        note = in_note;
        beat = in_beat;
        tempo = in_tempo;
        length = in_length;
    }
};

#endif
