#include "Enemy.h"

using namespace std;

Goblin::Goblin(double diff_mod) {
    setAttck(50.0);
    setDfnse(0.1);
    setMaxHP(500*diff_mod);
    setHP(getMaxHP());
    setName("Gunther, the Goblin");
}

Elf::Elf(double diff_mod) {
    setAttck(50.0);
    setDfnse(0.1);
    setMaxHP(650*diff_mod);
    setHP(getMaxHP());
    setName("Edgar, the Elf");
}

Fairy::Fairy(double diff_mod) {
    setAttck(75.0);
    setDfnse(0.2);
    setMaxHP(800*diff_mod);
    setHP(getMaxHP());
    setName("Finka, the Fairy");
}

Mermaid::Mermaid(double diff_mod) {
    setAttck(75.0);
    setDfnse(0.2);
    setMaxHP(950*diff_mod);
    setHP(getMaxHP());
    setName("Monika, the Mermaid");
}

Cyclops::Cyclops(double diff_mod) {
    setAttck(100.0);
    setDfnse(0.3);
    setMaxHP(1750*diff_mod);
    setHP(getMaxHP());
    setName("CRANSURP, THE CYCLOPS");
}

Yeti::Yeti(double diff_mod) {
    setAttck(100.0);
    setDfnse(0.3);
    setMaxHP(1100*diff_mod);
    setHP(getMaxHP());
    setName("Yunther, the Yeti");
}

Ghast::Ghast(double diff_mod) {
    setAttck(125.0);
    setDfnse(0.4);
    setMaxHP(1250*diff_mod);
    setHP(getMaxHP());
    setName("Ghosty, the Ghast");
}

Ent::Ent(double diff_mod) {
    setAttck(125.0);
    setDfnse(0.4);
    setMaxHP(1400*diff_mod);
    setHP(getMaxHP());
    setName("Endtree, the Ent");
}

Troll::Troll(double diff_mod) {
    setAttck(150.0);
    setDfnse(0.5);
    setMaxHP(1550*diff_mod);
    setHP(getMaxHP());
    setName("Troggbogg, the Troll");
}

Dragon::Dragon(double diff_mod) {
    setAttck(150.0);
    setDfnse(0.5);
    setMaxHP(3500*diff_mod);
    setHP(getMaxHP());
    setName("FRYNALDIR, THE FEARED");
}

bool Enemy::isBoss(){ // return true if enemy is a boss
    return (getName().compare("FRYNALDIR, THE FEARED") == 0 || getName().compare("CRANSURP, THE CYCLOPS") == 0);
}

void Goblin::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Goblin::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("deal %.1f damage.\n\n",  2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Goblin::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("throw acid at you to decrease your defense by 15%%!\n\n");
    hero->setDfnse(hero->getDfnse()*0.85);
}

void Elf::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Elf::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("shoot an arrow that causes you to take %.1f damage.\n\n", 2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Elf::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("increase their attack by 25%%!\n\n");
    setAttck(getAttck()*1.25);
}

void Fairy::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Fairy::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("deal %.1f damage.\n\n",  2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Fairy::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("heal to full health!\n\n");
    setHP(getMaxHP());
}

void Mermaid::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Mermaid::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("sing a melody, and lower your attack by %.1f points.\n\n", hero->getAttck()*0.1);
    hero->setAttck(hero->getAttck()*0.9);
}
void Mermaid::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("sing an even more melodic song to decrease your attack by 20%%!\n\n");
    hero->setAttck(hero->getAttck()*0.8);
}

void Cyclops::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n", getName().c_str(), (1+hero->getHP()/hero->getMaxHP())*getAttck()*(1-hero->getDfnse()));
    printf("His deadly stare causes you to take %.1f more damage based on how high %% HP you are.\n\n", (hero->getHP()/hero->getMaxHP())*getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - (1+hero->getHP()/hero->getMaxHP())*getAttck()*(1-hero->getDfnse()));
}
void Cyclops::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("focus its gaze to decrease your defense by 10%%.\n\n");
    hero->setDfnse(hero->getDfnse()*0.9);
}
void Cyclops::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("increase his attack by 20%%!\n\n");
    setAttck(getAttck()*1.2);
}

void Yeti::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Yeti::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("create an avalanche to deal %.1f damage.\n\n", 2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Yeti::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("bulk up in order to increase his attack and defense by 10%%!\n\n");
    setAttck(getAttck()*1.1);
    setDfnse(getDfnse()*1.1);
}

void Ghast::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Ghast::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("make the air deadly cold to deal %.1f damage.\n\n", 2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Ghast::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("greatly increase attack by 20%%.\n\n");
    setAttck(getAttck()*1.2);
}

void Ent::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Ent::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("call upon the power of the Earth to deal %.1f damage.\n\n", 2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Ent::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("dig its roots into the Earth in order to heal to full health!.\n\n");
    setHP(getMaxHP());
}

void Troll::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n\n", getName().c_str(), getAttck() * (1-hero->getDfnse()));
    hero->setHP(hero->getHP() - getAttck()*(1-hero->getDfnse()));
}
void Troll::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("make a boulder avalanche to deal %.1f damage.\n\n", 2*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Troll::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("allow an ear-shattering scream that reduces your attack by 20%%.\n\n");
    hero->setAttck(getAttck()*0.8);
}

void Dragon::attack(Hero* &hero){
    printf("%s attacks you for %.1f damage.\n", getName().c_str(), (2-(hero->getHP()/hero->getMaxHP()))*getAttck()*(1-hero->getDfnse()));
    printf("His fiery breath causes you to take %.1f more damage based on how low %% HP you are.\n\n", (1-(hero->getHP()/hero->getMaxHP()))*getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - (2-(hero->getHP()/hero->getMaxHP()))*getAttck()*(1-hero->getDfnse()));
}
void Dragon::special(Hero* &hero){
    printf("%s uses their special ability to ", getName().c_str()); // common among all enemies
    printf("spew a scorchingly hot blast to deal %.1f damage.\n\n", 2* getAttck()*(1-hero->getDfnse()));
    hero->setHP(hero->getHP() - 2*getAttck()*(1-hero->getDfnse()));
}
void Dragon::last_resort(Hero* &hero) {
    printf("%s uses their secret power to ", getName().c_str());
    printf("sharpen his scales to increase his defense by 25%%!\n\n");
    setDfnse(getDfnse()*1.25);
}

