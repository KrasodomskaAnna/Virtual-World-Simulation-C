#ifndef C_MATH_VECTOR_H
#define C_MATH_VECTOR_H

struct math_vector {
    int x;
    int y;
    math_vector(int positionX, int positionY): x(positionX), y(positionY){}
    bool operator==(const math_vector& pos) const {
        return this->x == pos.x && this->y == pos.y;
    }
    math_vector operator+(const math_vector& pos) const {
        return math_vector{this->x+pos.x, this->y+pos.y};
    }
};


#endif //C_MATH_VECTOR_H
