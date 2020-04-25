// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by Osmond Gong (z5293467)
// on 26/04/2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting inputs greater than octave and key range.
    if (add_note_to_beat(test_beat, 20, 20) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 20, 1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, 20) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Rejects same value inputted twice.
    add_note_to_beat(test_beat, 0, 0);
    if (add_note_to_beat(test_beat, 0, 0) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    //Test 4: Accepts valid inputs.
    if (add_note_to_beat(test_beat, 0, 11) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 9, 11) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
    // Test 1: Counting invalid octaves.
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Counting octaves with notes
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    add_note_to_beat(test_beat, 1, 2);
    add_note_to_beat(test_beat, 1, 10);
    if (count_notes_in_octave(test_beat, 1) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Counting valid octaves without notes.
    if (count_notes_in_octave(test_beat, 8) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 5) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: Adding beat to track
    Track test_track = create_track();
    Beat test_beat_1 = create_beat();
    add_note_to_beat(test_beat_1, 0, 11);
    add_beat_to_track(test_track, test_beat_1);
    
    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Checks current beat is unaffected after function
    select_next_beat(test_track);

    Beat test_beat_2 = create_beat();
    add_note_to_beat(test_beat_2, 1, 11);
    add_beat_to_track(test_track, test_beat_2);

    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Adding beat after first and last beat of track
    Beat test_beat_3 = create_beat();
    add_note_to_beat(test_beat_3, 2, 11);
    add_beat_to_track(test_track, test_beat_3);

    Beat test_beat_after_first = create_beat();
    add_note_to_beat(test_beat_after_first, 4, 11);
    add_beat_to_track(test_track, test_beat_after_first);

    if (count_beats_left_in_track(test_track) != 3) {
        return DOES_NOT_MEET_SPEC;
    }

    select_next_beat(test_track);
    select_next_beat(test_track);
    select_next_beat(test_track);

    if (count_beats_left_in_track(test_track) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Test 1: Does not remove beat if none is playing
    Track test_track = create_track();
    
    Beat test_beat_1 = create_beat();
    add_note_to_beat(test_beat_1, 0, 11);
    add_beat_to_track(test_track, test_beat_1);

    remove_selected_beat(test_track);

    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Removes first and last beats
    Beat test_beat_3 = create_beat();
    add_note_to_beat(test_beat_3, 2, 11);
    add_beat_to_track(test_track, test_beat_3);

    Beat test_beat_after_first = create_beat();
    add_note_to_beat(test_beat_after_first, 4, 11);
    add_beat_to_track(test_track, test_beat_after_first);

    select_next_beat(test_track);

    remove_selected_beat(test_track);

    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    select_next_beat(test_track);

    remove_selected_beat(test_track);

    if (count_beats_left_in_track(test_track) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: Valid notes
    Beat test_beat = create_beat();
    char test1[10] = "1A";
    char test2[50] = "1A#############################";
    char test3[10] = "9G#";
    if (add_musical_note_to_beat(test_beat, test1) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(test_beat, test2) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(test_beat, test3) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Invalid notes
    char test4[10] = "9G######";
    char test5[10] = "-1a";
    char test6[10] = "abc";
    if (add_musical_note_to_beat(test_beat, test4) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(test_beat, test5) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(test_beat, test6) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}
