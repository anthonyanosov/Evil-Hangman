#include "Hangman.h"

int main() {

    cout << "Welcome to Hangman!" << endl << "===================" << endl;
    char playAgain = 'y';
    while (playAgain == 'y') {
        Hangman game;
        game.get_desired_guesses();
        game.get_desired_word_length();
        game.get_desired_display();
        game.load_words();
        game.play_game();
        cout << "Would you like to play again? (Y/N)" << endl;
        cin >> playAgain;
    }

    cout << "Thank you for playing Hangman!";
    return 0;
}
