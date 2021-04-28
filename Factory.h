#ifndef FACTORY_H
#define FACTORY_H


class Factory {
    public:
        virtual ~Factory(){}
        virtual void play_game() = 0;
    protected:
    private:
};

class Easy_Game : public Factory {
    public:
        virtual void play_game();
    protected:
    private:
};

class Med_Game : public Factory {
    public:
        virtual void play_game();
    protected:
    private:
};

class Hard_Game : public Factory {
    public:
        virtual void play_game();
    protected:
    private:
};

#endif // FACTORY_H
