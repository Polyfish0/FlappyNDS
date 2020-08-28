#ifndef PIPE_H
#define PIPE_H
class Pipe {
    private:
        float posX;
        int shift;

    public:
        Pipe(float posX, float posY);
        float getPosX();
        int getShift();
        void setShift();
};
#endif