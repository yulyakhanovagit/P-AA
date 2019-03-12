#include "matrix.h"

int main()
{
    unsigned int N;
    cin >> N;
    Matrix table(N);
    table.push_3_squares();
    table.print();
    return 0;
}
