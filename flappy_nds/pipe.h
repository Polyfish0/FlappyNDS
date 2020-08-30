#ifndef PIPE_H
#define PIPE_H
class Pipe {
    private:
        float posX;
        int thickness;
        int shift;

    public:
        Pipe(float posX, int shift, int thickness);
        float getPosX();
        int getShift();
        int getThickness();
        void setPosX(float x);
        void setShift(int shift);
        void setThickness(int thickness);
};
#endif