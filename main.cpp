#include "Factory.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <stdlib.h>
using namespace std;


/** Prints intro to Castle Climber **/
void intro(int);

/** Return character when character inputted matches one character from vector passed in **/
char get_char(string, const vector<char>& chars);

int main(){
    // PRINT OUT INTRO TO GAME
    intro(0); // to print that there are 10 fights remaining
    //get difficulty from user
    vector<char> options = {'e', 'm', 'h'};
    char diff = get_char("Pick your difficulty between (e) for Easy, (m) for Medium, and (h) for hard.\nThe harder the difficulty, the less attack you will have and the more health the enemies will have!", options);
    //call proper game -> play_game
    Factory* fac = nullptr;
    if(diff == 'e'){
        printf("You have chosen the Easy difficulty! Your attack will be increased by 25%% and the enemy health will be decreased by 25%%!\n\n");
        fac = new Easy_Game();
    }
    else if(diff == 'm'){
        printf("You have chosen the Medium difficulty! Your attack and enemy health will be kept as the game devs have intended. :)\n\n");
        fac = new Med_Game();
    }
    else if(diff == 'h'){
        printf("You have chosen the Hard difficulty! Your attack will be decreased by 25%% and all enemy health will be increased by 25%%!\n\n");
        fac = new Hard_Game();
    }
    fac->play_game();
    delete fac;

    cin.get(); // to prevent the game from auto-closing after victory is achieved...

    return 0;
}

//print intro message
void intro(int fNum) {
cout <<
"_________                  __  .__           _________ .__  .__       ___.                 " << endl <<
"\\_   ___ \\_____    _______/  |_|  |   ____   \\_   ___ \\|  | |__| _____\\_ |__   ___________ " << endl <<
"/    \\  \\/\\__  \\  /  ___/\\   __\\  | _/ __ \\  /    \\  \\/|  | |  |/     \\| __ \\_/ __ \\_  __ \\" << endl <<
"\\     \\____/ __ \\_\\___ \\  |  | |  |_\\  ___/  \\     \\___|  |_|  |  Y Y  \\ \\_\\ \\  ___/|  | \\/" << endl <<
" \\______  (____  /____  > |__| |____/\\___  >  \\______  /____/__|__|_|  /___  /\\___  >__|   " << endl <<
"        \\/     \\/     \\/                 \\/          \\/              \\/    \\/     \\/       " << endl <<
"-------------------------------------------------------------------------------------------------" << endl;

    printf("This is a turn-based strategy game in which the player will progress through fights and boss battles in order to ultimately defeat FRYNALDIR, THE FEARED.\n");
	printf("Maximum Defense is 0.85 for both Enemies and Heroes. And this game should be played in full-screen for the best experience!\n");
	printf("There are %d fights remaining.\n\n", 10-fNum);
}

char get_char(string rMsg, const vector<char>& chars){
    char choice = ' ';
    while (count(chars.begin(), chars.end(), choice) == 0) {
            printf("%s\n", rMsg.c_str());
            cin.get(choice);
            cin.clear();
            if(choice != '\n')
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
    }
    return choice;
}

