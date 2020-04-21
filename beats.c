// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    struct beat *curr;
    struct beat *head;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.



// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {
    if (octave < 0 || octave > 9) {
        return INVALID_OCTAVE;
    }
    if (key < 0 || key > 11) {
        return INVALID_KEY;
    }
    if (beat->notes == NULL) {
        struct note *n1 = malloc(sizeof(struct note));
        n1->octave = octave;
        n1->key = key;
        n1->next = NULL;
        beat->notes = n1;
        return VALID_NOTE;
    }
    struct note *curr = beat->notes;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    if (curr->octave > octave) {
        return NOT_HIGHEST_NOTE;
    }
    if (curr->octave == octave && curr->key >= key) {
        return NOT_HIGHEST_NOTE;
    }
    struct note *n2 = malloc(sizeof(struct note));
    n2->octave = octave;
    n2->key = key;
    n2->next = NULL;
    curr->next = n2;
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    struct note *temp = beat->notes;
    while (temp != NULL) {
        printf("%d %02d", temp->octave, temp->key);
        if (temp->next != NULL) {
            printf(" | ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    struct note *temp = beat->notes;
    int i = 0;
    while (temp != NULL) {
        if (octave == temp->octave) {
            i++;
        }
        temp = temp->next;
    }
    return i;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    // Note: there is no fprintf in this function, as the
    // Stage 1 autotests call create_track but expect it to return NULL
    // (so this function should do nothing in Stage 1).
    Track new_track = malloc(sizeof(struct track));
    new_track->curr = NULL;
    new_track->head = NULL;
    return new_track;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    if (track->head == NULL) {
        track->head = beat;
    }
    else {
        if (track->curr != NULL) {
            beat->next = track->curr->next;
            track->curr->next = beat;
        }
        else {
            beat->next = track->head;
            track->head = beat;
        }
    }
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {
    if (track->curr == NULL && track->head != NULL) {
        track->curr = track->head;
        return TRACK_PLAYING;
    }
    if (track->curr == NULL && track->head == NULL) {
        return TRACK_STOPPED;
    }
    if (track->curr->next == NULL) {
        track->curr = NULL;
        return TRACK_STOPPED;
    }
    track->curr = track->curr->next;
    return TRACK_PLAYING;
}

// Print the contents of a track.
void print_track(Track track) {
    if (track->head == NULL) {
        return;
    }
    Beat temp = track->head;
    int i = 1;
    while (temp != NULL) {
        if (temp == track->curr) {
            printf(">");
        }
        else {
            printf(" ");
        }
        printf("[%d] ", i);
        print_beat(temp);
        temp = temp->next;
        i++;
    }
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    int i = 0;
    Beat temp;
    if (track->head == NULL){
        return i;
    }
    if (track->curr == NULL) {
        temp = track->head;
        i++;
    }
    else {
        temp = track->curr;
    }
    while (temp->next != NULL) {
        i++;
        temp = temp->next;
    }
    return i;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    printf("remove_selected_beat not implemented yet.");
    return TRACK_STOPPED;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    printf("add_musical_note_to_beat not implemented yet.");
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    printf("cut_range_to_end not implemented yet.");
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    printf("reverse_range not implemented yet.");
    return 0;
}
