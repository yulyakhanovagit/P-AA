#ifndef FIELD_H
#define FIELD_H

#include <iostream>

class field
{
public:
	field(int size);
	void run();
	void print_result();
	~field();
	
private:
	int O = 0;
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
	void put_sqare(int x, int y, int s, int n);
	void del_sqare(int x, int y, int s);
	void put_1st_square();
	void put_2_3st_square();
	bool find_emty_pice(int &x, int &y);
	int back_tracking(int deep);
};

#endif // FIELD_H
