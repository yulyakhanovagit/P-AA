#include <iostream>
#include "field.h"

using namespace std;

int main()
{
    int n;
    std::cin >> n;
    field f(n);
    f.run();
    f.print_result();
    return 0;
}
