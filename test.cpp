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
#include <assert.h>


using namespace std;

unsigned int testNum = 0;

void cError(double num1, double num2, string suiteName) {
	++testNum;
	if (num1 != num2) { 
		printf("Test %d of %s failed. Aborting...\n\n", testNum, suiteName.c_str());
		exit(1);
	}
	printf("Test %d of %s passed. Continuing...\n\n", testNum, suiteName.c_str());
}

void TestAttack() {
	string name = "TestAttack";

	Hero* rogue = new Rogue(1);
	Enemy* goblin = new Goblin(1);

	double rogueAD = rogue->getAttck();
	double oldGoblinHP = goblin->getMaxHP();

	rogue->attack(goblin);
	cError(goblin->getHP(), oldGoblinHP - (rogueAD * (1 - goblin->getDfnse())), name);

	rogueAD = rogue->getAttck();
	oldGoblinHP = goblin->getHP();

	rogue->attack(goblin);
	cError(goblin->getHP(), oldGoblinHP - (rogueAD * (1 - goblin->getDfnse())), name);



	Hero* priest = new Priest(1);
	Enemy* mermaid = new Mermaid(1);

	double oldMermaidHP = mermaid->getMaxHP();

	priest->attack(mermaid);
	cError(mermaid->getHP(), oldMermaidHP - (1 + oldMermaidHP / mermaid->getMaxHP()) * priest->getAttck() * (1 - mermaid->getDfnse()), name);

	oldMermaidHP = mermaid->getHP();

	priest->attack(mermaid);
	cError(mermaid->getHP(), oldMermaidHP - (1 + oldMermaidHP / mermaid->getMaxHP()) * priest->getAttck() * (1 - mermaid->getDfnse()), name);



	Hero* warrior = new Warrior(1);
	Enemy* yeti = new Yeti(1);

	double oldWarriorHP = warrior->getMaxHP();

	yeti->attack(warrior);
	cError(warrior->getHP(), oldWarriorHP - (yeti->getAttck() * (1 - warrior->getDfnse())), name);

	double oldYetiHP = yeti->getHP();

	warrior->attack(yeti);
	// 2-getHP()/getMaxHP())*getAttck()*(1-enemy->getDfnse())
	cError(yeti->getHP(), oldYetiHP - (2 - warrior->getHP() / warrior->getMaxHP())* warrior->getAttck()* (1 - yeti->getDfnse()), name);
	
	testNum = 0;
}


void TestSpecial() {
	string name = "TestSpecial";

	Hero* rogue = new Rogue(1);
	Enemy* goblin = new Goblin(1);

	double rogueAD = rogue->getAttck();
	double oldGoblinHP = goblin->getMaxHP();

	rogue->special(goblin);
	cError(goblin->getHP(), oldGoblinHP - (2 * rogueAD * (1 - goblin->getDfnse())), name);
	cError(rogue->getAttck(), rogueAD + 40, name);

	double oldRogueHP = rogue->getMaxHP();

	goblin->special(rogue);
	cError(rogue->getHP(), oldRogueHP - (2 * goblin->getAttck() * (1 - rogue->getDfnse())), name);


	Hero* priest = new Priest(1);
	Enemy* cyclops = new Cyclops(1);

	double oldPriestHP = priest->getMaxHP();
	priest->special(cyclops);
	cError(priest->getHP(), oldPriestHP, name);

	priest->setHP(oldPriestHP - (priest->getMaxHP() - 1));
	oldPriestHP = priest->getHP();
	priest->special(cyclops);
	cError(priest->getHP(), oldPriestHP + priest->getMaxHP() * (1 - oldPriestHP / priest->getMaxHP()), name);

	double oldPriestDef = priest->getDfnse();
	cyclops->special(priest);
	cError(priest->getDfnse(), oldPriestDef * 0.9, name);



	Hero* warrior = new Warrior(1);
	Enemy* dragon = new Dragon(1);

	double oldWarriorHP = warrior->getMaxHP();

	dragon->special(warrior);
	cError(warrior->getHP(), oldWarriorHP - 2 * dragon->getAttck() * (1 - warrior->getDfnse()), name);

	double oldWarriorDef = warrior->getDfnse();
	warrior->special(dragon);
	cError(warrior->getDfnse(), oldWarriorDef * 1.2, name);

	testNum = 0;
}

void TestLastResort() {
	string name = "TestLastResort";

	Hero* rogue = new Rogue(1);
	Enemy* goblin = new Goblin(1);

	double oldRogueDef = rogue->getDfnse();

	goblin->last_resort(rogue);
	cError(rogue->getDfnse(), oldRogueDef * 0.85, name);


	Hero* priest = new Priest(1);
	Enemy* cyclops = new Cyclops(1);

	double oldCyclopsAD = cyclops->getAttck();

	cyclops->last_resort(priest);
	cError(cyclops->getAttck(), oldCyclopsAD * 1.2, name);


	Hero* warrior = new Warrior(1);
	Enemy* dragon = new Dragon(1);

	double oldDragonDef = dragon->getDfnse();

	dragon->last_resort(warrior);
	cError(dragon->getDfnse(), oldDragonDef * 1.25, name);

	testNum = 0;
}

void TestItem() {
	string name = "TestItem";

	Hero* warrior = new Warrior(1);
	Enemy* goblin = new Goblin(1);

	warrior->getInven().push_back(Item("MINOR HP POTION"));
	warrior->setHP(1);
	double oldWarriorHP = warrior->getHP();
	warrior->activate_item(warrior->getInven().at(0), warrior, goblin, 0);
	cError(warrior->getHP(), oldWarriorHP + 200, name);
	cError(warrior->getInven().size(), 0, name);


	warrior->getInven().push_back(Item("MAJOR ALL-AROUND POTION"));
	oldWarriorHP = warrior->getHP();
	double oldWarriorAD = warrior->getAttck();
	double oldWarriorDef = warrior->getDfnse();
	warrior->activate_item(warrior->getInven().at(0), warrior, goblin, 0);
	cError(warrior->getHP(), oldWarriorHP + 100, name);
	cError(warrior->getAttck(), oldWarriorAD + 25, name);
	cError(warrior->getDfnse(), oldWarriorDef * 1.1, name);
	cError(warrior->getInven().size(), 0, name);

	oldWarriorHP = warrior->getHP();
	oldWarriorAD = warrior->getAttck();
	oldWarriorDef = warrior->getDfnse();

	warrior->getInven().push_back(Item("CLOAK OF AGILITY"));
	warrior->activate_item(warrior->getInven().at(0), warrior, goblin, 0);
	cError(warrior->getDfnse(), oldWarriorDef * 1.15, name);

	double oldWarriorMaxHP = warrior->getMaxHP();
	warrior->getInven().push_back(Item("TITAN STONE"));
	warrior->activate_item(warrior->getInven().at(1), warrior, goblin, 1);
	cError(warrior->getMaxHP(), oldWarriorMaxHP + 200, name);

	warrior->setHP(1);
	oldWarriorHP = warrior->getHP();
	warrior->getInven().push_back(Item("ANGEL HAND"));
	warrior->activate_item(warrior->getInven().at(2), warrior, goblin, 2);
	cError(warrior->getHP(), oldWarriorHP + 1000, name);

	testNum = 0;
}

void TestMiscellaneous() {
	string name = "TestMiscellaneous";
	
	Hero* warrior = new Warrior(1);
	warrior->setDfnse(1000000);
	cError(warrior->getDfnse(), 0.85, name);

	warrior->setHP(1000000);
	cError(warrior->getHP(), warrior->getMaxHP(), name);

	testNum = 0;
}

int main() {

	printf("Testing about to start. Program terminates if any test fails.\n\n");
	printf("Testing beginning...\n\n");

	// call all functions
	TestAttack();
	TestSpecial();
	TestLastResort();
	TestItem();
	TestMiscellaneous();

	printf("All testing passed !\n\n");

	return 0;
}
