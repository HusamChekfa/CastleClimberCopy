#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;
class Character
{
    public:
        Character() {}
        virtual ~Character() {}
        void printStats(){
            printf("%s:\n", getName().c_str());
            printf("HEALTH: %.1f / %.1f\n", getHP(), getMaxHP());
            printf("ATTACK: %.1f, DEFENSE: %.1f\n\n", getAttck(), getDfnse());
        }
        double getHP() const { return hp; }
        double getMaxHP() const { return max_hp; }
        double getAttck() const { return attck; }
        double getDfnse() const { return dfnse; }
        string getName() const { return name; }

        void setHP(double _hp) {
            if(_hp > max_hp)
                hp = max_hp;
            else
                hp = _hp;
        }
        void setMaxHP(double _max_hp) { max_hp = _max_hp; }
        void setAttck(double _attck) { attck = _attck; }
        void setDfnse(double _dfnse) {
            if(_dfnse >= 0.85)
                dfnse = 0.85;
            else
                dfnse = _dfnse;
        }
        void setName(string _name) { name = _name; }
    protected:
    private:
        double hp; //current health points. hp <= max_hp
        double max_hp; // maximum health character can be
        double attck; // amount of damage dealt to enemy when attack function is called (times enemy defense modifier)
        double dfnse; // attack modifier between 0.0 <= dfnse <= 0.85, where 0.0 is taking full damage, and 0.85 is taking 85% damage
        string name; // helps with identifying different objects within functions, for differing results (Strategy)
};

#endif // CHARACTER_H
