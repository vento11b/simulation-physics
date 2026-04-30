#pragma on

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    Vec2* vertices;
    int count;
} Polygon;

Polygon triangle;