#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Enemy.h"
#include "Item.h"
#include <string>
#include <vector>
using namespace std;

//Hero class to implement all heroes functionality
class Hero : public Character
{
    public:
        Hero() {}
        virtual ~Hero() {}
		vector<Item>& getInven() { return inventory; } // inventory needs to be changed in main
		friend class Enemy;
		friend char get_char(string, const vector<char>&);
        virtual void attack(class Enemy* &enemy) = 0;
        virtual void special(class Enemy* &enemy) = 0;
        bool use_item(class Enemy* &enemy); // returns false if item was used, true otherwise
        bool activate_item(Item, Hero* hero, class Enemy* enemy, unsigned int);
    private:
        vector<Item> inventory;
};

//Rogue IS VERY AGGRESSIVE, LOW HP, LOW DEFENCE, HIGH DAMAGE,
//ATTACK AND SPECIAL DEALS MORE AND MORE DAMAGE THE LONGER THE FIGHT GOES ON
class Rogue : public Hero
{
    public:
        Rogue(double diff_mod);
        virtual ~Rogue() {}
    protected:
        virtual void attack(class Enemy* &enemy);
        virtual void special(class Enemy* &enemy);
    private:
        double bonusAD = 10.0;
};

//WARRIOR IS VERY STURDY, HIGH HP, HIGH DEFENSE, LOW DAMAGE,
//SPECIAL INCREASES DEFENSE FOR THE REST OF THE FIGHT
//BE CAREFUL OF ENEMIES THAT CUT YOUR DEFENSE
class Warrior : public Hero
{
    public:
        Warrior(double diff_mod);
        virtual ~Warrior(){}
    protected:
        virtual void attack(class Enemy* &enemy);
        virtual void special(class Enemy* &enemy);
    private:

};

//PRIEST'S HEALING ABILITIES ARE NOT MATCHED, MEDIUM HP, MEDIUM DEFENSE, ABOVE AVERAGE DAMAGE,
//SPECIAL HEALS HEALTH BASED ON HOW LOW HP YOU ARE
class Priest : public Hero
{
    public:
        Priest(double diff_mod);
        virtual ~Priest() {}
    protected:
        virtual void attack(class Enemy* &enemy);
        virtual void special(class Enemy* &enemy);
    private:

};

#endif // HERO_H
