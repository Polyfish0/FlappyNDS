#ifndef PLAYER_H
#define PLAYER_H
class Player {
    private:
        float y = 50;
        bool alive = false;

    public:
        float getY();
        bool isAlive();
        void setY(float y);
        void setAlive(bool alive);
};
#endif