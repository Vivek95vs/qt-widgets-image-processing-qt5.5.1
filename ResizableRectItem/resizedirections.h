#ifndef RESIZEDIRECTIONS
#define RESIZEDIRECTIONS

struct ResizeDirections
{
    enum { HorzNone, Left, Right } horizontal;
    enum { VertNone, Top, Bottom } vertical;
    bool any() { return horizontal || vertical; }
};

#endif // RESIZEDIRECTIONS

