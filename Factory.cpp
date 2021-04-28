#include "Factory.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <stdlib.h>
using namespace std;

void intro(int);

char get_char(string, const vector<char>& chars);


/** Return r,w, or p for what character the player will play as (Rogue, Warrior, Priest) **/
char choose_hero();

/** prints out story related messages before every fight. **/
void story(Enemy* &, int);

/** give range of items to player, will give permanent boosts tailored to Hero chosen
     Set all mythic items' bool isUsed to false
     uses hero->getInven() function */
void choose_item(class Hero* &hero, vector<Item>& early_item, vector<Item>& late_item, int fNum);

/* Method to have Character fight enemy */
/** returns true if character beats enemy, false if health == 0 or quit **/
bool fight(class Hero* &hero, class Enemy* &enemy, int fNum); // calls menu(), and fNum for intro(fNum)

/** Prints unsuccessful message since player *gave up* or *health == 0.0* **/
void defeat();

/** Prints successful message since player beat all ten bosses. **/
void win();

void Easy_Game::play_game(){

    //PROMPT USER TO CHOOSE HERO (Rogue, WARRIOR, OR PRIEST)
	char heroChar = choose_hero();
	Hero* hero = nullptr;
	if (heroChar == 'r') {
        // create Hero object - rogue
        hero = new Rogue(1.25);
	}
	else if (heroChar == 'w') {
	    // create Hero object - warrior
	    hero = new Warrior(1.25);
	}
	else if (heroChar == 'p') {
        // create Hero object - priest
	    hero = new Priest(1.25);
	}

    //SET ENEMY ARRAY
    const int BOSS_NUM = 10;
    Enemy* bosses[BOSS_NUM] = {new Goblin(0.75), new Elf(0.75), new Fairy(0.75), new Mermaid(0.75), new Cyclops(0.75),
                            new Yeti(0.75), new Ghast(0.75), new Ent(0.75), new Troll(0.75), new Dragon(0.75)};
    //IN LOOP, FIGHT ENEMY BOSSES FROM BOSSES ARRAY
    vector<Item> early_item = {Item("MINOR HP POTION"), Item("MINOR STRENGTH POTION"), Item("MINOR DEFENSE POTION"), Item("MINOR BULK POTION"), Item("MINOR GAMBLE POTION"),
                          Item("MINOR ALL-AROUND POTION"), Item("CLOAK OF AGILITY"), Item("CREST OF THE LEGIONNAIRE GENERAL"), Item("WORSHIP ROD")};
    vector<Item> late_item = {Item("MAJOR ALL-AROUND POTION"), Item("MAJOR SPLASH POTION OF WEAKNESS"), Item("MAJOR ADRENALINE POTION"), Item("MAJOR GAMBLE POTION"), Item("SHIV OF RAVENHOLT"),
                          Item("TITAN STONE"), Item("ANGEL HAND")};

    bool printWin = true;

    for(unsigned i = 0; i < BOSS_NUM; i++){
        choose_item(hero, early_item, late_item, i); // give player one out of three items
        hero->setHP(hero->getMaxHP()); // heal hero back to full hp before each fight

        story(bosses[i], i); //story will progress as the player plays

        double old_att = hero->getAttck(); //store attack
        double old_def = hero->getDfnse(); //and defense of hero
        //IF fight == false, PRINT DEFEAT MESSAGE AND EXIT
        //and of course each of the 10 fights take place...
        if(!fight(hero, bosses[i], i)){
            printWin = false;
		break;
        }
        //revert attack and defense of hero to value stored before fight, and set hp to max_hp
        hero->setAttck(old_att);
        hero->setDfnse(old_def);
        if(i != BOSS_NUM - 1) // don't print this out when player is going to win!
            printf("Your Attack and Defense have been reverted to the values they were before the fight! And your health has been replenished! (for the sake of game balance)\n\n");
    }
    if (printWin) {
        //ELSE, PRINT ENDING MESSAGE (CONGRATULATIONS, ETC...)
        win();
    }
    else {
        defeat();
    }
    delete hero;
    for (unsigned i = 0; i < BOSS_NUM; i++) {
        delete bosses[i];
    }
}

void Med_Game::play_game(){

    //PROMPT USER TO CHOOSE HERO (Rogue, WARRIOR, OR PRIEST)
	char heroChar = choose_hero();
	Hero* hero = nullptr;
	if (heroChar == 'r') {
        // create Hero object - rogue
        hero = new Rogue(1);
	}
	else if (heroChar == 'w') {
	    // create Hero object - warrior
	    hero = new Warrior(1);
	}
	else if (heroChar == 'p') {
        // create Hero object - priest
	    hero = new Priest(1);
	}

    //SET ENEMY ARRAY
    const int BOSS_NUM = 10;
    Enemy* bosses[BOSS_NUM] = {new Goblin(1), new Elf(1), new Fairy(1), new Mermaid(1), new Cyclops(1),
                            new Yeti(1), new Ghast(1), new Ent(1), new Troll(1), new Dragon(1)};
    //IN LOOP, FIGHT ENEMY BOSSES FROM BOSSES ARRAY
    vector<Item> early_item = {Item("MINOR HP POTION"), Item("MINOR STRENGTH POTION"), Item("MINOR DEFENSE POTION"), Item("MINOR BULK POTION"), Item("MINOR GAMBLE POTION"),
                          Item("MINOR ALL-AROUND POTION"), Item("CLOAK OF AGILITY"), Item("CREST OF THE LEGIONNAIRE GENERAL"), Item("WORSHIP ROD")};
    vector<Item> late_item = {Item("MAJOR ALL-AROUND POTION"), Item("MAJOR SPLASH POTION OF WEAKNESS"), Item("MAJOR ADRENALINE POTION"), Item("MAJOR GAMBLE POTION"), Item("SHIV OF RAVENHOLT"),
                          Item("TITAN STONE"), Item("ANGEL HAND")};

    bool printWin = true;

    for(unsigned i = 0; i < BOSS_NUM; i++){
        choose_item(hero, early_item, late_item, i); // give player one out of three items
        hero->setHP(hero->getMaxHP()); // heal hero back to full hp before each fight

        story(bosses[i], i); //story will progress as the player plays

        double old_att = hero->getAttck(); //store attack
        double old_def = hero->getDfnse(); //and defense of hero
        //IF fight == false, PRINT DEFEAT MESSAGE AND EXIT
        //and of course each of the 10 fights take place...
        if(!fight(hero, bosses[i], i)){
            printWin = false;
		break;
        }
        //revert attack and defense of hero to value stored before fight, and set hp to max_hp
        hero->setAttck(old_att);
        hero->setDfnse(old_def);
        if(i != BOSS_NUM - 1) // don't print this out when player is going to win!
            printf("Your Attack and Defense have been reverted to the values they were before the fight! And your health has been replenished! (for the sake of game balance)\n\n");
    }
    if (printWin) {
        //ELSE, PRINT ENDING MESSAGE (CONGRATULATIONS, ETC...)
        win();
    }
    else {
        defeat();
    }
    delete hero;
    for (unsigned i = 0; i < BOSS_NUM; i++) {
        delete bosses[i];
    }
}

void Hard_Game::play_game(){

    //PROMPT USER TO CHOOSE HERO (Rogue, WARRIOR, OR PRIEST)
	char heroChar = choose_hero();
	Hero* hero = nullptr;
	if (heroChar == 'r') {
        // create Hero object - rogue
        hero = new Rogue(0.75);
	}
	else if (heroChar == 'w') {
	    // create Hero object - warrior
	    hero = new Warrior(0.75);
	}
	else if (heroChar == 'p') {
        // create Hero object - priest
	    hero = new Priest(0.75);
	}

    //SET ENEMY ARRAY
    const int BOSS_NUM = 10;
    Enemy* bosses[BOSS_NUM] = {new Goblin(1.25), new Elf(1.25), new Fairy(1.25), new Mermaid(1.25), new Cyclops(1.25),
                            new Yeti(1.25), new Ghast(1.25), new Ent(1.25), new Troll(1.25), new Dragon(1.25)};
    //IN LOOP, FIGHT ENEMY BOSSES FROM BOSSES ARRAY
    vector<Item> early_item = {Item("MINOR HP POTION"), Item("MINOR STRENGTH POTION"), Item("MINOR DEFENSE POTION"), Item("MINOR BULK POTION"), Item("MINOR GAMBLE POTION"),
                          Item("MINOR ALL-AROUND POTION"), Item("CLOAK OF AGILITY"), Item("CREST OF THE LEGIONNAIRE GENERAL"), Item("WORSHIP ROD")};
    vector<Item> late_item = {Item("MAJOR ALL-AROUND POTION"), Item("MAJOR SPLASH POTION OF WEAKNESS"), Item("MAJOR ADRENALINE POTION"), Item("MAJOR GAMBLE POTION"), Item("SHIV OF RAVENHOLT"),
                          Item("TITAN STONE"), Item("ANGEL HAND")};

    bool printWin = true;

    for(unsigned i = 0; i < BOSS_NUM; i++){
        choose_item(hero, early_item, late_item, i); // give player one out of three items
        hero->setHP(hero->getMaxHP()); // heal hero back to full hp before each fight

        story(bosses[i], i); //story will progress as the player plays

        double old_att = hero->getAttck(); //store attack
        double old_def = hero->getDfnse(); //and defense of hero
        //IF fight == false, PRINT DEFEAT MESSAGE AND EXIT
        //and of course each of the 10 fights take place...
        if(!fight(hero, bosses[i], i)){
            printWin = false;
		break;
        }
        //revert attack and defense of hero to value stored before fight, and set hp to max_hp
        hero->setAttck(old_att);
        hero->setDfnse(old_def);
        if(i != BOSS_NUM - 1) // don't print this out when player is going to win!
            printf("Your Attack and Defense have been reverted to the values they were before the fight! And your health has been replenished! (for the sake of game balance)\n\n");
    }
    if (printWin) {
        //ELSE, PRINT ENDING MESSAGE (CONGRATULATIONS, ETC...)
        win();
    }
    else {
        defeat();
    }
    delete hero;
    for (unsigned i = 0; i < BOSS_NUM; i++) {
        delete bosses[i];
    }
}

char choose_hero() {
	char choice = ' ';
	cout << "The Rogue class is powerful in the art of magic and wields poisoned daggers which grow stronger each turn." << endl;
	cout << "The Warrior class is strong, healthy, and gets stronger with less health." << endl;
	cout << "The Priest class is skilled in sustaining through a heavy barrage of attacks." << endl;
	cout << "Choose your hero!\n\n";

    vector<char> choices = {'r', 'w', 'p'};
    choice = get_char("Press (r) to choose Rogue, (w) to choose Warrior, (p) to choose Priest.", choices);

	switch(choice){
        case('r'):
            cout << "You have chosen the crafty Rogue! Be resourceful, and use the growing strength of your deadly poison to your advantage!" << endl;
            cout << "ROGUE IS VERY AGGRESSIVE, MEDIUM HP, LOW DEFENSE, HIGH DAMAGE, ATTACK AND SPECIAL DEALS MORE AND MORE DAMAGE THE LONGER THE FIGHT GOES ON!\n\n";
            break;
        case('w'):
            cout << "You have chosen the resilient Warrior! Don't be afraid to take a beating, as your power only grows the less health you have!" << endl;
            cout << "WARRIOR IS VERY STURDY, MEDIUM HP, HIGH DEFENSE, LOW DAMAGE, ATTACK DEALS MORE THE LESS % HEALTH YOU HAVE, " <<
            "SPECIAL INCREASES DEFENSE FOR THE REST OF THE FIGHT. BE CAREFUL OF ENEMIES THAT CUT YOUR DEFENSE!\n\n";
            break;
        case('p'):
            cout << "You have chosen the holy Priest! You are a brave servant to God, and live to smite the monsters of this castle. " <<
            "The angels have blessed you with the strength to take down large health foes!" << endl;
            cout << "THE HEALING ABILITIES OF THE PRIEST ARE NOT MATCHED, HIGH HP, MEDIUM DEFENSE, MEDIUM DAMAGE, ATTACK DOES MORE DAMAGE THE HIGHER % HP THE ENEMY IS, " <<
            "SPECIAL HEALS MORE HEALTH BASED ON HOW LOW HP YOU ARE!\n\n";
            break;
	}
	return choice;
}



void story(Enemy* &enemy, int fNum){
  string enemyName = enemy->getName();
    printf("FIGHT %d\n---------\n", fNum+1);
    printf("You encounter %s!\nGood Luck!\n\n", enemyName.c_str());


    switch(fNum){
        case(0):
            printf("He is the doormat of the castle. He should not be of any trouble to you.\n\n");
            break;
        case(1):
            printf("You beat Gunther, the Goblin. But your journey has barely begun!\n");
            printf("As you climb to the 2nd floor of the eerily quiet castle, an arrow whizzes by your shoulder, grazing your cheek.\n");
            printf("%s suddenly appears!\n\n", enemyName.c_str());
            break;
        case(2):
            printf("You slay Edgar, the Elf. But your journey isn't close to over!\n");
            printf("You continue onto the carpetted spiral staircase and make your way to the 3rd floor of the eerily quiet castle\n");
            printf("You hear the tinkling of light feathers behind you. Quickly turning around, you see %s descending from a broken cage!\n\n", enemyName.c_str());
            break;
        case(3):
            printf("You beat Finka, the Fairy. But your journey isn't close to over!\n");
            printf("As you reach the 4th floor, you see an enormous circular pool in the center of the room.\n");
            printf("You look around for the water source, but jump when you hear the voice of a woman coming from the water.\n");
            printf("With a splash, %s jumps from the water, holding a coral trident and ready to fight!\n\n", enemyName.c_str());
            break;
        case(4):
            printf("You beat Monika, the Mermaid. But your first hurdle is about to wake up!\n");
            printf("You empty your shoes from the water from your previous fight, but freeze as you hear the dozing of a massive creature laying on its back before you.\n");
            printf("Quickly, you don your boots and sprint for the door at the end of the room.\n");
            printf("Upon reaching it, you find the door is locked with an empty golden keyhole which would lead you further on your quest.\n");
            printf("Suddenly, you feel heavy, hot breathing on the back of your neck.\n");
            printf("Spinning around you see a one - eyed monster, wielding a wooden cluband wearing a necklace holding many objects, among which were bones... and a golden key.\n");
            printf("\"I am %s,\" the beast roars at you, spraying you with a mixture of spittle and bad breath.\n\n", enemyName.c_str());
            break;
        case(5):
            printf("You knock out CRANSURP, THE CYCLOPS, putting him back to sleep His necklace falls apart as he lands, and the golden key rolls to your feet. But your journey is only half complete!\n");
            printf("You unlock the heavy oak door and open it, only to feel a heavy blast of cold win pushing you back.\n");
            printf("Clawing your way into the room, you finally close the door and the snowstorm calms, but snow continues to fall.\n");
            printf("You notice a large block of ice with something frozen within it and continue to look around, searching for the source of the cold.\n");
            printf("You see a window and rush to shut it. Bolting it, the cold dies down, leaving your clothes a little wet, and the room warmer than it had been moments ago.\n");
            printf("You hear the groaning of a monster behind you. You turn and see the ice boulder has melted, leaving a puddle of water and a white-furred beast in its wake.\n");
            printf("%s has woken from his eternal, frozen slumber and charges! Defend yourself hero!\n\n", enemyName.c_str());
            break;
        case(6):
            printf("Upon felling Yunther, the Yeti, a door of ice appears on the other side of the room. The ice melts, revealing a pathway to the next floor.\n");
            printf("As you climb to the 7th floor of the eerily quiet castle, you hear screams and shrieks echoing from wall to wall.\n");
            printf("Suddenly, the torches lining the walls dim, revealing a pale figure by the name of %s!\n\n", enemyName.c_str());
            break;
        case(7):
            printf("You rush past a dazed Ghosty, the Ghast and the torches start burning again as they had been minutes ago.\n");
            printf("Your quest is nearing its finish but it is not over yet, hero!\n");
            printf("As you reach the 8th castle floor, you hear birds chirping and flower blooming in a verdant area.\n");
            printf("You smell the fresh dew on the grass of the meadow and see small trees lining the sides of the room.\n");
            printf("The one large tree, at the center of the room, slowly turns around. It is %s!!\n\n", enemyName.c_str());
            break;
        case(8):
            printf("You cut down Endtree, the Ent. Stay vigilant, hero!\n");
            printf("You climb to the 9th floor of the castle, and come to locked door. Seeing no keyhole and frustrated from the previous fights, you bang on the door.\n");
            printf("The door slowly opens revealing a well-lit throneroom, lined golden chairs and crystal chandeliers hanging from the ceiling.\n");
            printf("At the end of the room, there is a heavy looking man. You approach him and see that he is not like any man you have seen before.\n");
            printf("His teeth are yellow and his nose is smashed. He has four fingers on each hand and has an evil smirk on his face.\n");
            printf("He opens his mouth and speaks in a harsh voice. \"So, you have reached the top of my master's castle, eh?\n");
            printf("You have come to kill him but I stand in your way. I will not fail him like my henchman have.\"\n");
            printf("With a heavy grunt, he gets up from his golden throne, and takes a sword and shield from a nearby suit of armour.\n");
            printf("His smile becomes an evil grin which twists into an angry scowl.\n");
            printf("\"I am %s\", he bellows. \"Die by my hand!\"\n\n", enemyName.c_str());
            break;
        case(9):
            printf("You beat Troggbogg, the Troll. But your journey has one more !\n");
            printf("As you climb to the 2nd floor of the eerily quiet castle, %s suddenly appears!\n\n", enemyName.c_str());
            printf("As the Troll falls, his throne crumbles, revealing a silver ladder leading up to a trapdoor.\n");
            printf("You climb the ladder and see the moonlight seeping through the cracks of the wooden door.\n");
            printf("Relieved to see the night sky, you open the door and climb up, and you find yourself standing at the roof of the castle.\n\n");
            printf("Suddenly, you hear the beating of heavy, leathery wings and the crunching, crumbling, and falling of stone pillars.\n\n");
            printf("You turn around and see a monstrous dragon with massive, jet-black wings, dark scales shimmering in the moonlight,\n");
            printf("white fangs licked by a forked tongue,\n and claws the size of a suit of armour wrapped around a cracked pillar, likely due to the overbearing weight of the drake.\n");
            printf("It opens its maw, bearing its white fangs and writhing forked tongue. You feel the heat emenating from its jaws.\n");
            printf("\"I.. I am %s,\" the dragon thunders.\n\n", enemyName.c_str());
            break;

        default:
            cout << "Never print this statement  :)\n" << endl;
            break;
    }
    return;
}

void choose_item(class Hero* &hero, vector<Item>& early_item, vector<Item>& late_item, int fNum) {
    //After each early game fight, pick three items from early game vector @ random, pop out only the one the player chooses (Fights 1-5)
    //Same process late game (Fights 6-10)
    if(fNum == 0)
        printf("Before your journey begins, your lord allows you to choose between an assortment of Rewards!\n\n");
    else
        printf("Because of your successful vanquishing of this monster, an assortment of Rewards suddenly appear before you!\n\n");
    //choose ITEM_OPTIONS random indices from within the range of early_item or late_item depending on fNum
    const int ITEM_OPTIONS = 3;
    vector<Item> temp_item;
    srand(time(0));
    for(int i = 0; i < ITEM_OPTIONS; i++){
        if(fNum <= 4){
            int randIdx = rand() % early_item.size();
            temp_item.push_back(early_item.at(randIdx));
            early_item.erase(early_item.begin()+randIdx);
        }
        else{
            int randIdx = rand() % late_item.size();
            temp_item.push_back(late_item.at(randIdx));
            late_item.erase(late_item.begin()+randIdx);
        }
    }
    //get player input
    vector<char> numbers;
    for(unsigned i = 0; i < ITEM_OPTIONS; i++){
        numbers.push_back(i+48);
    }
    string itemStr = string("Choose an item from below by typing (0) to (") + to_string(numbers.size()-1) + ") for the item you want to receive:\n\n";
    for(int i = 0; i < ITEM_OPTIONS; i++){
            itemStr += to_string(i) + " -- " + temp_item.at(i).getName() + " -- " + temp_item.at(i).getDescription() + "\n";
    }
    char itemChosen = get_char(itemStr, numbers);
    int iIdex = itemChosen - 48;

    // implement PASSIVE effects for mythic items
    if(temp_item.at(iIdex).getName() == "CLOAK OF AGILITY")
        hero->setAttck(hero->getAttck()+50);
    else if(temp_item.at(iIdex).getName() == "CREST OF THE LEGIONNAIRE GENERAL")
        hero->setDfnse(hero->getDfnse()*1.15);
    else if(temp_item.at(iIdex).getName() == "WORSHIP ROD")
        hero->setMaxHP(hero->getMaxHP()+200);
    else if(temp_item.at(iIdex).getName() == "SHIV OF RAVENHOLT")
        hero->setAttck(hero->getAttck()+75);
    else if(temp_item.at(iIdex).getName() == "TITAN STONE")
        hero->setDfnse(hero->getDfnse()*1.25);
    else if(temp_item.at(iIdex).getName() == "ANGEL HAND")
        hero->setMaxHP(hero->getMaxHP()+500);

    hero->getInven().push_back(temp_item.at(iIdex)); // add itemChosen to hero inventory
    //push_back other un chosen items back to proper vector for future choosing
    for(int i = 0; i < ITEM_OPTIONS; i++){
        if(i == iIdex) // don't re-add chosen item to future options
            continue;
        if(fNum <= 4){
            early_item.push_back(temp_item.at(i));
        }
        else{
            late_item.push_back(temp_item.at(i));
        }
    }
    // set all item's isUsed to false
    for(unsigned int i = 0; i < hero->getInven().size(); i++){
        hero->getInven().at(i).setIsUsed(false);
    }
}

bool fight(Hero* & hero, Enemy* &enemy, int fNum) {
    int trnLeft = 3; //turns left used for special ability usage availability
    int enemy_trnLeft = 3;
    //for-loop until player gives up or their health == 0 (return false), or enemy health == 0 (return true).
    bool repAct = true;
    bool usedResort = false;
    do{
        repAct = true;
        //get user input
        do{
            hero->printStats();  //print out player and enemy stats
            enemy->printStats();
            vector<char> choices = {'a','s','i','g','q'};
            char act = get_char("Enter (a) to Attack, (s) to Special, (i) to use an Item, (g) to see the Game Details, and (q) to quit the game.\n", choices);
            switch(act){
                //if choose (a) attack, we call hero->attack(enemy);
                case('a'):
                    hero->attack(enemy);
                    repAct = false;
                    break;
                //if choose (s) special, check if trnLeft == 0, if true, we call hero->special(enemy);
                case('s'):
                    if(trnLeft == 0) {
                        hero->special(enemy);
                        trnLeft = 4; // reset trnLeft
                        repAct = false;
                    }
                    //otherwise print how many turns left until player can use special
                    else
                        printf("Your Special ability is not ready yet! There are %d turns left before you can use your Special ability.\n\n", trnLeft);
                    break;
                //if choose (i) use item,
                case('i'):
                    repAct = hero->use_item(enemy); // will equal false if item was used, true otherwise
                    break;
                //if choose (g), print out game details, and re prompt menu
                case('g'):
                    intro(fNum);
                    break;
                //if choose (q) quit game (return false)
                case('q'):
                    vector<char> choices = {'y','n'};
                    char choice = get_char("Are you sure you want to quit? There is no saving in this game!\nEnter (y) to quit, or (n) to keep playing!", choices);
                    if(choice == 'y'){
                        printf("You have quit the game. Your quest awaits your return!\n\n");
                        return false; // player quit
                    }
                    break;
            }
        }while(repAct);

        //check enemy health if <= 0, if yes return true
        if(enemy->getHP() <= 0){
            return true; // player won
        }

        //determine enemy action
        //PRIO: 1) check if can use item, 2) check if can use special, 3) else use attack
        if(!usedResort && ((enemy->isBoss() && (enemy->getHP() < enemy->getMaxHP()*0.75 || hero->getHP() < enemy->getMaxHP()*0.25)) || (!enemy->isBoss() && (enemy->getHP() <= enemy->getMaxHP()*0.5)))){
                enemy->last_resort(hero);
                usedResort = true;
        }
        else if(enemy_trnLeft == 0){
            enemy->special(hero);
            enemy_trnLeft = 4;
        }
        else{
            enemy->attack(hero);
        }

        if(trnLeft > 0)
            trnLeft--; // decrement trnLeft for special usability
        if(enemy_trnLeft > 0)
            enemy_trnLeft--;
    }while(hero->getHP() > 0); //check if player health > 0, if yes, return false
    printf("Your health has reached 0.0! You're too weak for this challenge...\n\n");
    return false; // player died
}

void defeat() {
    //print loss message
    cout << "You have failed this attempt in the quest to slay FRYNALDIR, THE FEARED! Do not fret.\n";
    cout << "There's always another Hero that will take your stead.\n\n\n\n";
}

void win() {
    //print win message
    cout << "VICTORY! YOU HAVE SLAIN FRYNALDIR, THE FEARED!\n ON TO THE NEXT CONQUEST FOR YOU!\n";
    cout << "THANKS FOR PLAYING!\n\n\n\n";
}
