#ifndef PIPE_H
#define PIPE_H
class Pipe {
    private:
        float posX;
        int thickness;
        int shift;
        int points;

    public:
        Pipe(float posX, int shift, int thickness, int points);
        float getPosX();
        int getShift();
        int getThickness();
        int getPoints();
        void setPosX(float x);
        void setShift(int shift);
        void setThickness(int thickness);
        void setPoints(int points);
};
#endif