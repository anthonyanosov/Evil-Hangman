//
// Created by Anthony Anosov on 10/24/20.
//

#include "WordFamily.h"

#include <utility>

// Helps me push the words back into the vector of words
void WordFamily::add(string word) {
    words.push_back(word);
}

// Returns the number of words in the vector of words
int WordFamily::number_of_words() {
    return words.size();
}

// Divides the words into families
WordFamily WordFamily::best_family_for_guess(char guess) {
    map<string, WordFamily> family_map;
    for (auto &word : words) {
        string pattern = build_pattern(word, guess);
        int containment = family_map.count(pattern);
        WordFamily* f = new WordFamily(stage);
        if (containment == 0) {
            f->update_stage(pattern);
            f->add(word);
            family_map.insert(pair<string, WordFamily>(pattern, *f));
        } else {
            f = &(family_map.find(pattern)->second);
            f->add(word);
        }
    }
    WordFamily current_biggest;
    for (auto & pair : family_map) {
        if (pair.second.number_of_words() > current_biggest.number_of_words()) {
            current_biggest = pair.second;
        }
    }
    return current_biggest;
}

// Creates patterns for the families
string WordFamily::build_pattern(string word, char guess) {
    string pattern;
    for (char i : word) {
        if (i == guess) {
            pattern += guess;
        } else {
            pattern += '-';
        }
    }
    return pattern;
}

// Updates the stage by merging the pattern with the pre-existing stage
void WordFamily::update_stage(string pattern) {
    stage = stage.empty()
        ? pattern
        : merge_with_stage(pattern);
}

// Does the merging
string WordFamily::merge_with_stage(string pattern) {
    string merged_stage = stage;
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] != '-') {
            merged_stage[i] = pattern[i];
            letter_guessed = true;
        }
    }
    return merged_stage;
}

// Gets the stage and initializes it if it is empty
string WordFamily::get_stage() {
    if (stage.empty()) {
        initialize_stage();
    }
    return stage;
}

// Checks if the letter that is guessed is the correct one (algorithm cornered)
bool WordFamily::is_letter_guessed() {
    return letter_guessed;
}

// Checks if the word has been entirely guessed
bool WordFamily::is_word_guessed() {
    for (auto ch : stage) {
        if (ch == '-') {
            return false;
        }
    }
    return !stage.empty();
}

// Returns the final word that got cornered
string WordFamily::get_target_word() {
    return words[0];
}

// Initializes the stage
void WordFamily::initialize_stage() {
    for (int i = 0; i < words[0].size(); i++) {
        stage += '-';
    }
}

// Constructors
WordFamily::WordFamily(string s) {
    stage = move(s);
}

WordFamily::WordFamily() {
    stage = "";
}
