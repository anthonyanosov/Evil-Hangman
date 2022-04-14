//
// Created by Anthony Anosov on 10/18/20.
//

#ifndef PROJECT_3__HANGMAN_HANGMAN_H
#define PROJECT_3__HANGMAN_HANGMAN_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include "WordFamily.h"

using namespace std;

class Hangman {
public:

    Hangman();

    void play_game();
    void get_desired_guesses();
    void get_desired_word_length();
    void get_desired_display();
    void load_words();

private:

    bool game_over();
    bool check_win();
    bool check_loss();
    bool check_guess();
    void get_player_guess();
    void get_letters_guessed();
    void get_guesses_remaining();
    void set_guesses_remaining();
    void display_number_words();
    void display_stage();
    void correct_message();
    void incorrect_message();

    int num_guesses_available;
    char player_guess;
    int word_size;
    bool display_words;
    WordFamily game_words;
    set<char> guessed_letters;
    set<char>::iterator it = guessed_letters.begin();

};


#endif //PROJECT_3__HANGMAN_HANGMAN_H
