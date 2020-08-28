#ifndef PIPE_H
#define PIPE_H
class Pipe {
    private:
        float posX;
        int shift;

    public:
        Pipe(float posX, int shift);
        float getPosX();
        int getShift();
        void setPosX(float x);
        void setShift(int shift);
};
#endif