//
// Created by Anthony Anosov on 10/18/20.
//

#include "Hangman.h"

using namespace std;

// Constructor which fills the dictionary words set.
Hangman::Hangman() {
}

// Plays the game
void Hangman::play_game() {
    display_stage();
    while(!game_over()) {
        get_player_guess();
        if (check_guess()) {
            correct_message();
            display_stage();
        } else {
            incorrect_message();
            set_guesses_remaining();
            display_stage();
        }
        if (display_words) {
            display_number_words();
        }
    }
}

// Checks if the guess is correct
bool Hangman::check_guess() {
//    for (auto & character : target_word) {
//        if (player_guess == character) {
//            return true;
//        }
//    }
    guessed_letters.insert(player_guess);
    game_words = game_words.best_family_for_guess(player_guess);
    return game_words.is_letter_guessed();
}

// Checks to see if endgame conditions have been met
bool Hangman::game_over() {
    return check_win() || check_loss();
}

// Checks to see if a win has occurred
bool Hangman::check_win() {
    if (game_words.is_word_guessed()) {
        cout << "Nicely done! The word was indeed " << game_words.get_target_word() << "." << endl << endl;
        return true;
    } else {
        return false;
    }
}

// Checks to see if a loss has occurred
bool Hangman::check_loss() {
    if (num_guesses_available == 0) {
        cout << "Nice try, but the word was: " << game_words.get_target_word() << endl << endl;
        return true;
    } else {
        return false;
    }
}

// Displays the stage and the number of guesses remaining
void Hangman::display_stage() {
    cout << game_words.get_stage() << endl << endl;
    get_letters_guessed();
    get_guesses_remaining();
}

// Displays the letters that have already been guessed
void Hangman::get_letters_guessed() {
    it = guessed_letters.begin();
    cout << "You have already guessed these letters: ";
    while (it != guessed_letters.end()) {
        cout << *it;
        it++;
    }
    cout << endl << endl;
}

// Displays the number of guesses the player still has, removing guesses for every wrong guess.
void Hangman::get_guesses_remaining() {
    cout << "You have " << num_guesses_available << " guesses remaining." << endl << endl;
}

// Sets the number of guesses remaining for the player
void Hangman::set_guesses_remaining() {
    bool correct = check_guess();
    if (!correct) {
        num_guesses_available--;
    }
}

// Displays a message letting the player know if they made a correct guess
void Hangman::correct_message() {
    cout << "Good guess!" << endl << endl;
}

// Displays a message letting the player know if they made an incorrect guess.
void Hangman::incorrect_message() {
    cout << "Sorry, that letter is not in the word." << endl << endl;
}

// Gets the next character the player will guess
void Hangman::get_player_guess() {
    cout << "What is your next guess?" << endl;
    cin >> player_guess;
}

// Asks the player how many guesses they would like
void Hangman::get_desired_guesses() {
    cout << "How many guesses would you like?" << endl;
    while(!(cin >> num_guesses_available) || num_guesses_available < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Wrong data type/value. Please try again." << endl;
        cout << "How many guesses would you like?" << endl;
    }
}

// Asks the player how long of a word they would like to guess
void Hangman::get_desired_word_length() {
    cout << "How long of a word would you like?" << endl;
    while(!(cin >> word_size) || word_size < 1 || word_size == 26 || word_size == 27) {
        cin.clear();
        cin.ignore(1000, '\n');
        if (word_size == 26 || word_size == 27) {
            cout << "Error: There are no words of that length. Please try again." << endl;
        } else {
            cout << "Error: Wrong data type/value. Please try again." << endl;
        }
        cout << "How long of a word would you like?" << endl;
    }
}

void Hangman::get_desired_display() {
    char choice;
    cout << "Show a running total of words? (Y/N)" << endl;
    cin >> choice;
    cout << endl;
    if (choice == 'Y' || choice == 'y') {
        display_words = true;
    } else {
        display_words = false;
    }
}

// Displays the number of words possible given the state of the board
void Hangman::display_number_words() {
    cout << "Word in chosen family: " << game_words.number_of_words() << endl << endl;
}

// Loads the dictionary words of desired length into a vector
void Hangman::load_words() {
    string word;
    ifstream fin;
    fin.open("dictionary.txt");
    if (!fin.is_open()) {
        cout << "Error: Requested file failed to open." << endl;
    }
    while (!fin.eof()) {
        fin >> word;
        if (word.size() == word_size) {
            game_words.add(word);
        }
    }
    fin.close();
}

