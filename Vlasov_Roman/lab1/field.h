#ifndef FIELD_H
#define FIELD_H

#include <iostream>

class field
{
    int size;
    int **pieces;
    int ans_size = 0;
    int *ans_x;
    int *ans_y;
    int *ans_w;
    int array_size = 20;
    bool final = false;

    void extend_array();
    int find_max_size(int x, int y);
    void clear_field(int x, int y, int s);
    void step1();
    void step2();
    int step3(int deep = 4);



public:
    field(int size);
    void run();
    void print_result();
    ~field();
};

#endif // FIELD_H
