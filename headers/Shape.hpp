#ifndef SHAPE
#define SHAPE

#include "./Cell.hpp"
#include <math.h>

// The idea was to extnd the edges and form an edge list and apply 2D ray casting within the caves
// I guess I'll just make a seperate project for that one

class Edge{
    public: Vector2f a,b;
    Edge() noexcept : a(0.0,0.0), b(0.0,0.0) {}
    Edge(float&& x1,float&& y1,float&& x2,float&& y2) noexcept : a(x1,y1), b(x2,y2) {}
    float dist() const {
        float x = a.x-b.x;
        float y = a.y-b.y;
        return sqrt(x*x+y*y);
    }
};

class Shape{
    public: vector<Edge> edgeList;
};

#endif //SHAPE