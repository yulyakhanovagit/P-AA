#include <iostream>
#include "field.h"

using namespace std;

int main()
{
	int n;
	std::cin >> n;

	field table(n);
	
	table.run();
	table.print_result();

	return 0;
}
