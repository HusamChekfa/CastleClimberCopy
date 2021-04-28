#include "Hero.h"
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
char get_char(string, const vector<char>&);

Rogue::Rogue(double diff_mod) {
    setAttck(200.0*diff_mod);
    setDfnse(0.2);
    setMaxHP(1250);
    setHP(getMaxHP());
    setName("Rogue");
}

Warrior::Warrior(double diff_mod) {
    setAttck(100.0*diff_mod);
    setDfnse(0.5);
    setMaxHP(1250);
    setHP(getMaxHP());
    setName("Warrior");
}

Priest::Priest(double diff_mod) {
    setAttck(150.0*diff_mod);
    setDfnse(0.35);
    setMaxHP(1500);
    setHP(getMaxHP());
    setName("Priest");
}

void Rogue::attack(Enemy* &enemy){
    printf("You choose to attack %s.\n", enemy->getName().c_str());
    printf("You deal %.1f damage to %s. Your deadly poison allows you to gain %.1f attack points.\n\n", getAttck()*(1-enemy->getDfnse()), enemy->getName().c_str(), bonusAD);
    enemy->setHP(enemy->getHP() - getAttck()*(1-enemy->getDfnse()));
    setAttck(getAttck() + bonusAD); // rouge innate ability
}
void Rogue::special(Enemy* &enemy){
    printf("You choose to use your special ability against %s.\n\n", enemy->getName().c_str());
    printf("You deal %.1f damage to %s. Your deadly poison allows you to gain %.1f attack points.\n\n", 2 * getAttck() * (1 - enemy->getDfnse()), enemy->getName().c_str(), bonusAD * 4);
    enemy->setHP(enemy->getHP() - 2 * getAttck() * (1 - enemy->getDfnse()));
    setAttck(getAttck() + bonusAD * 4); // rouge innate ability
}

void Warrior::attack(Enemy* &enemy){
    printf("You choose to attack %s.\n", enemy->getName().c_str());
    printf("You deal %.1f damage to %s. You have dealt %.1f more damage based on how low %% health you were.\n\n", (2-getHP()/getMaxHP())*getAttck()*(1-enemy->getDfnse()),
           enemy->getName().c_str(),(1-getHP()/getMaxHP())*getAttck()*(1-enemy->getDfnse())); // x*y - y = y(x-1)
    enemy->setHP(enemy->getHP() - (2-getHP()/getMaxHP()) * getAttck() * (1-enemy->getDfnse()));
}
void Warrior::special(Enemy* &enemy){
    printf("You choose to use your special ability against %s.\n\n", enemy->getName().c_str());
    printf("You bolster your armor, causing your defense to rise by 20%%.\n\n");
    setDfnse(1.2*getDfnse());
}

void Priest::attack(Enemy* &enemy){
    printf("You choose to attack %s.\n", enemy->getName().c_str());
    printf("You deal %.1f damage to %s. Your holy abilities allowed you to deal %.1f more damage based on the higher %% health the enemy was.\n\n",
        (1+enemy->getHP()/enemy->getMaxHP())*getAttck()*(1-enemy->getDfnse()), enemy->getName().c_str(), (enemy->getHP()/enemy->getMaxHP())*getAttck()*(1-enemy->getDfnse())); // x*y - y = y(x-1)
    enemy->setHP(enemy->getHP() - (1+enemy->getHP()/enemy->getMaxHP())*getAttck()*(1-enemy->getDfnse()));
}
void Priest::special(Enemy* &enemy){
    printf("You choose to use your special ability against %s.\n\n", enemy->getName().c_str());
    printf("The blessing of the Gods allow you to heal for %.1f health. You heal for more health the less %% health you have.\n\n", getMaxHP() * (1-getHP()/getMaxHP()));
    setHP(getHP() + getMaxHP()*(1-getHP()/getMaxHP()));
}

//if items.size() > 0, print out items with description, and prompt which item to use (return false after use) or re prompt menu (return true). No items, print that out (return false).
bool Hero::use_item(Enemy* &enemy){
    srand(time(0));

    if(getInven().size() == 0){
        printf("You have no items in your inventory! You can collect ONE (1) item after each fight!\n\n");
        return true;
    }
		// print out menu of all items
		while(true) {
			printf("Hero, your current items are:\n\n");
			for (unsigned int i = 0; i < getInven().size(); ++i) {
				// print format: USED (if isUsed == true) -- i -- item name
				if (getInven().at(i).getIsUsed() == true) {
					printf("USED -- ");
				}
				printf("%d -- ", i);
				getInven().at(i).print();
			}
            printf("\n"); // extra line between printed items for general readability

			vector<char> numbers; // for get_char()
			for (unsigned int i = 0; i < getInven().size(); ++i) {
				numbers.push_back(i + 48); // +48 makes the value into the ASCII rep. of the character (#48 in ascii = '0'), only works for max 10 items
			}
			numbers.push_back('q'); // q to quit the current selection if you decide not to use an item
			string rStr = "Choose a number from 0 to " + to_string(getInven().size()-1) + ", or press (q) to make a different decision:";
			char choiceNum = get_char(rStr, numbers);

			if (choiceNum == 'q') {
				return true; // take back to main fight menu and choose another action
			}

            unsigned int itemIdx = choiceNum - 48;

			// first check if used mythic
			if (getInven().at(itemIdx).getIsUsed() == true) {
				printf("Hero, you may use each item only once per fight! Choose again:\n\n");
				continue;
			}

      return activate_item(inventory.at(itemIdx), this, enemy, itemIdx);
		}
}

bool Hero::activate_item(Item item, Hero* hero, Enemy* enemy, unsigned int itemIdx) {

    // check if potion - if potion remove from vector
    if (item.getIsPotion() == true) {
        // print use effect "you drink the potion and heal for ..." "you throw the potion at the **enemy_name**. It is surprisingly effective"
        // potion -> empty vial -> cracked potion leaks some of it every turn logarithmic
        // radioactive leakage of potion depending on bottle type
        // potions scale with fight number and turn number and temperature and heart rate of player and general handsomeness

        string itemName = item.getName();
        string itemDescription = item.getDescription();
        printf("You drink the %s and you %s.\n\n", itemName.c_str(), itemDescription.c_str());

        if (itemName == "MINOR HP POTION") {
            setHP(getHP() + 200);
            // add troll face if they try to go over max :DDD
        }
        else if (itemName == "MINOR STRENGTH POTION") {
            setAttck(getAttck() + 50);
        }
        else if (itemName == "MINOR DEFENSE POTION") {
            setDfnse(getDfnse() * 1.2);
        }
        else if (itemName == "MINOR BULK POTION") {
            setMaxHP(getMaxHP() + 200);
            setHP(getHP() + 100);
        }
        else if (itemName == "MINOR GAMBLE POTION") {
            int x = rand() % 2;
            if (x == 0) { // buff option
                setHP(getHP() + 100);
                setDfnse(getDfnse() * 1.05);
                setAttck(getAttck() * 1.05);
                printf("You got lucky! You heal for 100, and your defense and attack increase by 5%%!\n\n");
            }
            else { // x == 1 // nerf option
                setHP(getHP() - 100);
                setDfnse(getDfnse() * 0.95);
                setAttck(getAttck() * 0.95);
                printf("Oh no! You got unlucky! You take 100 damage, and your defense and attack decrease by 5%%...\n\n");
            }
        }
        else if (itemName == "MINOR ALL-AROUND POTION") {
            setHP(getHP() + 50);
            setDfnse(getDfnse() * 1.05);
            setAttck(getAttck() + 10);
        }
        else if (itemName == "MAJOR ALL-AROUND POTION") {
            setHP(getHP() + 100);
            setDfnse(getDfnse() * 1.1);
            setAttck(getAttck() + 25);
        }
        else if (itemName == "MAJOR ADRENALINE POTION") {
            setHP(getHP() / 2);
            setAttck(getAttck() + 100);
        }
        else if (itemName == "MAJOR GAMBLE POTION") {
            int x = rand() % 2;
            if (x == 0) { // buff option
                setHP(getHP() + 200);
                setDfnse(getDfnse() * 1.1);
                setAttck(getAttck() * 1.1);
                printf("You got lucky! You heal for 200, and your defense and attack increase by 10%%!\n\n");
            }
            else { // x == 1 // nerf option
                setHP(getHP() - 200);
                setDfnse(getDfnse() * 0.9);
                setAttck(getAttck() * 0.9);
                printf("Oh no! You got unlucky! You take 200 damage, and your defense and attack decrease by 10%%...\n\n");
            }
        }
        else if (itemName == "MAJOR SPLASH POTION OF WEAKNESS") {
            enemy->setAttck(enemy->getAttck() * 0.7);
        }

        getInven().erase(getInven().begin() + itemIdx);
        return false;
    }
    else {
        // here if not potion
        // trigger item active effect
        // mythic items
        // print active
        string mythicName = getInven().at(itemIdx).getName();
        size_t activeLoc = getInven().at(itemIdx).getDescription().find("ACTIVE");
        string mythicDescription = getInven().at(itemIdx).getDescription().substr(activeLoc + 9);
        printf("You use your %s and %s.\n\n", mythicName.c_str(), mythicDescription.c_str());
        if (mythicName == "CLOAK OF AGILITY") {
            setDfnse(getDfnse() * 1.15);
        }
        else if (mythicName == "CREST OF THE LEGIONNAIRE GENERAL") {
            setAttck(getAttck() * 1.1);
        }
        else if (mythicName == "WORSHIP ROD") {
            setHP(getHP() + 500);
        }
        else if (mythicName == "SHIV OF RAVENHOLT") {
            setAttck(getAttck() * 1.3);
        }
        else if (mythicName == "TITAN STONE") {
            setMaxHP(getMaxHP() + 200);
        }
        else if (mythicName == "ANGEL HAND") {
            setHP(getHP() + 1000);
        }

        // set mythic item to used for the rest of this fight, reset to false in choose_item() in main
        getInven().at(itemIdx).setIsUsed(true);

        return false;
    }

}
