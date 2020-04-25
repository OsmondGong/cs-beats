// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by Osmond Gong (z5293467)
// on 26/04/2020
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
    // Rejecting invalid octave inputs.
    if (octave < 0 || octave > 9) {
        return INVALID_OCTAVE;
    }
    // Rejecting invalid key inputs.
    if (key < 0 || key > 11) {
        return INVALID_KEY;
    }
    // Creating first note in beat.
    if (beat->notes == NULL) {
        // Creating a node of struct note.
        struct note *note_1 = malloc(sizeof(struct note));
        // Assigning octave and key into node and next as NULL.
        note_1->octave = octave;
        note_1->key = key;
        note_1->next = NULL;
        // Linking node to beat.
        beat->notes = note_1;
        return VALID_NOTE;
    }
    // Attaining last note in beat.
    struct note *last = beat->notes;
    while (last->next != NULL) {
        last = last->next;
    }
    // Rejecting notes that are not the highest
    if (last->octave > octave) {
        return NOT_HIGHEST_NOTE;
    }
    if (last->octave == octave && last->key >= key) {
        return NOT_HIGHEST_NOTE;
    }
    // Creating a node of struct note.
    struct note *note_1 = malloc(sizeof(struct note));
    // Assigning octave and key into node and next as NULL.
    note_1->octave = octave;
    note_1->key = key;
    note_1->next = NULL;
    // Linking node to end of beat.
    last->next = note_1;
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    struct note *temp = beat->notes;
    while (temp != NULL) {
        printf("%d %02d", temp->octave, temp->key);
        // Separates notes in beat.
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
    Track new_track = malloc(sizeof(struct track));
    new_track->curr = NULL;
    new_track->head = NULL;
    return new_track;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    // Assigns head as beat if there is no beat that is playing.
    if (track->head == NULL) {
        track->head = beat;
    }
    // Otherwise, a beat is added after the current beat in a track.
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
    // Sets current beat as first beat if there is no beat playing.
    if (track->curr == NULL && track->head != NULL) {
        track->curr = track->head;
        return TRACK_PLAYING;
    }
    // Track remains stopped if there is no beat in track.
    if (track->head == NULL) {
        return TRACK_STOPPED;
    }
    // Track is stopped if current beat is last beat.
    if (track->curr->next == NULL) {
        track->curr = NULL;
        return TRACK_STOPPED;
    }
    // Otherwise, current beat is set to the next beat.
    track->curr = track->curr->next;
    return TRACK_PLAYING;
}

// Print the contents of a track.
void print_track(Track track) {
    // Does not print anything if track is empty.
    if (track->head == NULL) {
        return;
    }
    // Otherwise, the track is printed.
    Beat temp = track->head;
    int i = 1;
    while (temp != NULL) {
        // Prints ">" to indicate current beat.
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
    // Returns 0 if there is no beat in track.
    if (track->head == NULL) {
        return i;
    }
    // If there is no current beat, the count starts 
    // on the first beat of the track.
    Beat temp;
    if (track->curr == NULL) {
        temp = track->head;
        i++;
    }
    // Otherwise, the count starts after the current beat.
    else {
        temp = track->curr;
    }
    // Counts amount of beats remaining.
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
    // Does not free beat if beat has not been assigned memory.
    if (beat == NULL) {
        return;
    }
    // Otherwise, frees every note of the beat.
    struct note *temp;
    while (beat->notes != NULL) {
        temp = beat->notes->next;
        free(beat->notes);
        beat->notes = temp;
    }
    // Frees the beat.
    free(beat);
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Does not free track if track has not been assigned memory.
    if (track == NULL) {
        return;
    }
    // Frees every beat in track before freeing track.
    Beat temp;
    while (track->head != NULL) {
        temp = track->head->next;
        free_beat(track->head);
        track->head = temp;
    }
    free(track);
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    // If there is no selected beat, function does nothing.
    if (track->curr == NULL) {
        return TRACK_STOPPED;
    }
    // Reassigns the head beat of the track to the next beat in the 
    // track if the current beat is the head beat in the track. It 
    // then removes the previous current beat and assigns the next 
    // beat as the new current beat.
    if (track->head == track->curr) {
        Beat temp2 = track->curr;
        track->head = track->curr->next;
        track->curr = track->head;
        free_beat(temp2);
        if (track->curr == NULL) {
            return TRACK_STOPPED;
        }
        return TRACK_PLAYING;
    }
    // Removes the current beat and reassigns the next beat as the
    // new current beat.
    Beat temp = track->head;
    while (temp->next != track->curr) {
        temp = temp->next;
    }
    Beat temp2 = track->curr;
    temp->next = track->curr->next;
    track->curr = temp->next;
    free_beat(temp2);
    // If the current beat is the last beat, the track is stopped.
    if (track->curr == NULL) {
        return TRACK_STOPPED;
    }
    return TRACK_PLAYING;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    // Rejects invalid inputs (It must be numbers between 1-9).
    if (musical_notation[0] < '0' || musical_notation[0] > '9') {
        return INVALID_MUSICAL_NOTE;
    }
    // Converts char into int.
    int octave = musical_notation[0] - '0';
    int key;
    // Assigns different values to key depending on letter.
    if (musical_notation[1] == 'A') {
        key = 0;
    }
    else if (musical_notation[1] == 'B') {
        key = 2;
    }
    else if (musical_notation[1] == 'C') {
        key = 3;
    }
    else if (musical_notation[1] == 'D') {
        key = 5;
    }
    else if (musical_notation[1] == 'E') {
        key = 7;
    }
    else if (musical_notation[1] == 'F') {
        key = 8;
    }
    else if (musical_notation[1] == 'G') {
        key = 10;
    }
    // Rejects invalid inputs (must be a capital letter between 
    // A and G
    else {
        return INVALID_MUSICAL_NOTE;
    }
    // Counts the amount of "#".
    int j = 2;
    while (musical_notation[j] != '\0') {
        // Rejects any input other than "#".
        if (musical_notation[j] != '#') {
            return INVALID_MUSICAL_NOTE;
        }
        j++;
    }
    // Adds amount of "#" to key.
    key = key + j - 2;
    while (key > 11) {
        key -= 12;
        octave++;
    }
    // Rejects octave values greater than 9.
    if (octave > 9) {
        return INVALID_MUSICAL_NOTE;
    }
    // Adds note to beat if there is no note in beat.
    if (beat->notes == NULL) {
        add_note_to_beat(beat, octave, key);
        return VALID_NOTE;
    }
    // Creating a node of struct note.
    struct note *notes = malloc(sizeof(struct note));
    // Assigning octave and key to note.
    notes->octave = octave;
    notes->key = key;

    // Placing note in right position in beat.

    // Places note as first note if the note is smaller than the
    // first note.
    if (beat->notes->octave > octave) {
        notes->next = beat->notes;
        beat->notes = notes;
        return VALID_NOTE;
    }
    if (beat->notes->octave == octave && beat->notes->key > key) {
        notes->next = beat->notes;
        beat->notes = notes;
        return VALID_NOTE;
    }
    // If the first note has the same octave and key, reject the note.
    if (beat->notes->octave == octave && beat->notes->key == key) {
        free(notes);
        return INVALID_MUSICAL_NOTE;
    }
    // If the beat only contains one note, the note is placed after 
    // the first note (The note will be a higher note as it has 
    // already been tested on lines 408 to 417).
    if (beat->notes->next == NULL) {
        notes->next = beat->notes->next;
        beat->notes->next = notes;
        return VALID_NOTE;
    }
    // Finds where to place the note so that note is higher than notes 
    // before it and lower than notes after it.
    struct note *curr = beat->notes;
    while (curr->next->octave < octave) {
        curr = curr->next;
        if (curr->next == NULL) {
            break;
        }
    }
    if (curr->next != NULL) {
        while (curr->next->octave == octave && curr->next->key < key) {
            curr = curr->next;
        }
        // Rejects notes with same octave and key
        if (curr->next->octave == octave && curr->next->key == key) {
            free(notes);
            return INVALID_MUSICAL_NOTE;
        }
    }
    // Places note into the position.
    notes->next = curr->next;
    curr->next = notes;
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    // Function does not do anything if given range is below 1.
    if (range_length < 1) {
        return;
    }
    // Function does not do anything if there is no selected beat.
    if (track->curr == NULL) {
        return;
    }
    // Function does not do anything if given range is below the amount 
    // of beats left in track.
    if (count_beats_left_in_track(track) < range_length) {
        return;
    }
    // Gets the last beat in track.
    Beat last = track->head;
    while (last->next != NULL) {
        last = last->next;
    }
    // Set the last beat in track to point to the current beat.
    last->next = track->curr;
    // Gets beat before current beat in track.
    Beat temp = track->head;
    while (temp->next != track->curr) {
        temp = temp->next;
    }
    // Gets last beat in the range that is being cut.
    Beat temp_curr = track->curr;
    int i = 1;
    while (i < range_length) {
        temp_curr = temp_curr->next;
        i++;
    }
    // Sets the beat before the cur range to point to the beat after
    // the cut range.
    if (track->head == track->curr) {
        track->head = temp_curr->next;
    }
    else {
        temp->next = temp_curr->next;
    }
    // Sets the new last beat to point at NULL.
    temp_curr->next = NULL;
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    // Changes the range length if it is larger than the amount of beats 
    // left in track so that it reverses the max amount it can.
    if (count_beats_left_in_track(track) < range_length) {
        range_length = count_beats_left_in_track(track) + 1;
    }
    // Function does not do anything if range is less than 2.
    if (range_length < 2) {
        return 0;
    }
    // Function does not do anything if there is no selected beat.
    if (track->curr == NULL) {
        return 0;
    }
    // "ret_range" is used as range_length is changed in function for the
    // reversing of beats.
    int ret_range = range_length;
    // Gets beat before the current beat.
    Beat temp = track->head;
    while (temp != track->curr && temp->next != track->curr) {
        temp = temp->next;
    }
    // Gets beat at the end of the range of beats that is being reversed.
    Beat after = track->curr;
    int i = 1;
    while (i < range_length) {
        after = after->next;
        i++;
    }
    // Makes the beat before the range of beats that is being reversed 
    // point to the last beat of the range.
    if (track->head == track->curr) {
        track->head = after;
    }
    else {
        temp->next = after;
    }
    // Change "after" to be the beat after the range that is being reversed.
    after = after->next;
    // Reversing the beats.
    while (range_length > 0) {
        Beat from = track->curr;
        Beat to = track->curr;
        i = 1;
        while (i < range_length) {
            from = from->next;
            i++;
        }
        i = 1;
        while (i < range_length - 1) {
            to = to->next;
            i++;
        }
        from->next = to;
        range_length--;
    }
    // Makes the current beat point to beat after the range that was 
    // reversed.
    track->curr->next = after;
    return ret_range - 1;
}
