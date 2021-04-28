#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Hero.h"
using namespace std;
///ALL ENEMIES WILL BE ABLE TO
/// 1) ATTACK
/// 2) SPECIAL
/// 3) USE ITEM (ONCE PER FIGHT), TWICE FOR MINI BOSS AND FINAL BOSS
/// MAKE 10 ENEMIES

class Enemy : public Character
{
    public:
        Enemy() {}
        virtual ~Enemy() {}
        friend class Hero;
        virtual void attack(class Hero* &) = 0; // all enemies attack function implemented here
        virtual void special(class Hero* &) = 0; // all enemies special function implemented here
        virtual void last_resort(class Hero* &) = 0; // all enemies use_item function implemented here
        bool isBoss();
    private:
};

class Goblin : public Enemy
{
    public:
        Goblin(double diff_mod);
        virtual ~Goblin() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Elf : public Enemy
{
    public:
        Elf(double diff_mod);
        virtual ~Elf() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Fairy : public Enemy
{
    public:
        Fairy(double diff_mod);
        virtual ~Fairy() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Mermaid : public Enemy
{
    public:
        Mermaid(double diff_mod);
        virtual ~Mermaid() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Cyclops : public Enemy
{
    public:
        Cyclops(double diff_mod);
        virtual ~Cyclops() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Yeti : public Enemy
{
    public:
        Yeti(double diff_mod);
        virtual ~Yeti() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Ghast : public Enemy
{
    public:
        Ghast(double diff_mod);
        virtual ~Ghast() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Ent : public Enemy
{
    public:
        Ent(double diff_mod);
        virtual ~Ent() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Troll : public Enemy
{
    public:
        Troll(double diff_mod);
        virtual ~Troll() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

class Dragon : public Enemy
{
    public:
        Dragon(double diff_mod);
        virtual ~Dragon() {}
    protected:
        void attack(class Hero* &);
        void special(class Hero* &);
        void last_resort(class Hero* &);
    private:
};

#endif // ENEMY_H
