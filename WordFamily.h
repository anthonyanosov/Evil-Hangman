//
// Created by Anthony Anosov on 10/24/20.
//

#ifndef PROJECT_3__HANGMAN_WORDFAMILY_H
#define PROJECT_3__HANGMAN_WORDFAMILY_H

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

using namespace std;

class WordFamily {
private:

    string stage;
    bool letter_guessed;
    vector<string> words;
    string merge_with_stage(string);
    string build_pattern(string, char);
    void update_stage(string pattern);
    explicit WordFamily(string stage);

public:

    WordFamily();
    int number_of_words();
    void add(string word);
    void initialize_stage();
    bool is_letter_guessed();
    bool is_word_guessed();
    string get_stage();
    string get_target_word();
    WordFamily best_family_for_guess(char guess);

};


#endif //PROJECT_3__HANGMAN_WORDFAMILY_H
