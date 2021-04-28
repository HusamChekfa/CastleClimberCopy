#include "Item.h"
using namespace std;
Item::Item(string nme){
    name = nme;
    isUsed = false;
    //set description AND isPotion based on name
    //if type == HEALTH POTION
    //      description = "HEALTH POTION - HEAL 200 HP";
    //else if ...

    //Potions(10): 6 Minor and 4 Major
	isPotion = true;

	if(name == "MINOR HP POTION") {
	    description = "Heal 200 HP for the rest of the fight";
	}
	else if(name == "MINOR STRENGTH POTION") {
	    description = "Increase Attack by 50 for the rest of the fight";
	}
	else if(name == "MINOR DEFENSE POTION") {
	    description = "Increase Defense by 20% for the rest of the fight";
	}
	else if (name == "MINOR BULK POTION") {
	    description = "Boost Max HP by 200 and heal for 100 HP for the rest of the fight";
	}
	else if (name == "MINOR GAMBLE POTION") {
	    description = "Have a 50/50 chance HP goes up or down by 100, Defense goes up or down 5%, and Attack goes up or down by 5% for the rest of the fight";
	}
	else if (name == "MINOR ALL-AROUND POTION") {
	    description = "Heal 50 HP, Increase Attack by 10, Increase Defense by 5% for the rest of the fight";
	}
	else if(name == "MAJOR ALL-AROUND POTION") {
	    description = "Heal 100 HP, Increase Attack by 25, Increase Defense by 10% for the rest of the fight";
	}
	else if (name == "MAJOR SPLASH POTION OF WEAKNESS") {
	    description = "Decrease Enemy Attack by 30% for the rest of the fight";
	}
	else if (name == "MAJOR ADRENALINE POTION") {
	    description = "Lose half of HP but increase Attack by 100 for the rest of the fight";
	}
	else if (name == "MAJOR GAMBLE POTION") {
	    description = "Have a 50/50 chance HP goes up or down by 200, Defense goes up or down 10%, and Attack goes up or down by 10% for the rest of the fight";
	}

	//Mythics(6): 3 Minor 3 Major
	// ALL ACTIVES MUST BE IN THE FORMAT "ACTIVE - ", then description of active... otherwise mythic usage will not print out properly.
	else if (name == "CLOAK OF AGILITY") { //Rogue
	    description = "PASSIVE - Increase Attack by 50 permanently -- ACTIVE - Increase Defense by 15% for the rest of the fight";
		isPotion = false;
	}
	else if (name == "CREST OF THE LEGIONNAIRE GENERAL") { //Warrior
	    description = "PASSIVE - Increase Defense by 15% permanently -- ACTIVE - Increase Attack by 10% for the rest of the fight";
		isPotion = false;
	}
	else if (name == "WORSHIP ROD") { //Priest
	    description = "PASSIVE - Increase Max HP by 200 permanently -- ACTIVE - Heal by 500 HP";
		isPotion = false;
	}
	else if (name == "SHIV OF RAVENHOLT") { //Rogue
	    description = "PASSIVE - Increase Attack by 75 permanently -- ACTIVE - Increase Attack by 30% for the rest of the fight";
		isPotion = false;
	}
	else if (name == "TITAN STONE") { //Warrior
	    description = "PASSIVE - Increase Defense by 25% permanently -- ACTIVE - Increase Max HP by 200 permanently";
		isPotion = false;
	}
	else if (name == "ANGEL HAND") { //Priest
	    description = "PASSIVE - Increase Max HP by 500 permanently -- ACTIVE - Heal by 1000 HP";
		isPotion = false;
	}
}

void Item::print() {
	// print name of item then description
    printf("%s -- %s\n", getName().c_str(), getDescription().c_str());
}
