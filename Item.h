#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
class Item {
    public:
        Item(string name);
        ~Item() {}
        void print();
		bool getIsUsed() const {return isUsed;};
		void setIsUsed(bool used) {isUsed = used;};
		bool getIsPotion() const {return isPotion;};
		string getName() const {return name;};
		string getDescription() const { return description; };
    private:
        string name; // needed to identify item
        string description; //what is to be printed when items gets printed
		bool isUsed;	// Mythic items can be used once per fight, all get set to false at start of each fight
		bool isPotion; // Potions can be used once then are popped from inventory, true if potion, else false (for mythic)
};

#endif // ITEM_H
