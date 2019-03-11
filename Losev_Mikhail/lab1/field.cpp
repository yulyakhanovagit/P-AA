#include "field.h"

void field::extend_array()
{
	array_size *= 2;
	int *tmp_x = new int[array_size];
	int *tmp_y = new int[array_size];
	int *tmp_w = new int[array_size];

	for (int i = 0; i < ans_size; i++){
		tmp_x[i] = ans_x[i];
		tmp_y[i] = ans_y[i];
		tmp_w[i] = ans_w[i];
	}

	delete[] ans_x;
	delete[] ans_y;
	delete[] ans_w;

	ans_x = tmp_x;
	ans_y = tmp_y;
	ans_w = tmp_w;
}

int field::find_max_size(int x, int y)
{
	for (int s = 1; s <= size - x && s <= size - y; s++) 
		for (int i = 0; i < s; i++)
			for (int j = 0; j < s; j++)
				if (pieces[x + i][y + j] != 0)
					return --s;
}

bool field::find_emty_pice(int &x, int &y)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (pieces[i][j] == 0) {
				x = i;
				y = j;
				return true; // нашли
			}
	return false;
}

void field::put_sqare(int x, int y, int s, int n)
{
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
			pieces[x + i][y + j] = n;
	O++;
}

void field::del_sqare(int x, int y, int s)
{
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
			pieces[x + i][y + j] = 0;
}

void field::put_1st_square()
{
	ans_x[ans_size] = 0;
	ans_y[ans_size] = 0;
	if (size % 2 == 0){
		ans_w[ans_size] = size / 2;
	} // в опт. разб. кв. 2*2 всего 4 квадрата, один 1*1
	else if (size % 3 == 0){
		ans_w[ans_size] = size * 2 / 3;
	} // в опт. разб. кв. 3*3 всего 6 квадратов, один 2*2
	else if (size % 5 == 0){
		ans_w[ans_size] = size * 3 / 5;
	} // в опт. разб. кв. 5*5 всего 8 квадратов, один 3*3
	else if (size % 7 == 0){
		ans_w[ans_size] = size * 4 / 7;
	} // в опт. разб. кв. 7*7 всего 9 квадратов, один 4*4
	// 4 < 6 < 8 < 9
	else{
		ans_w[ans_size] = size / 2 + 1;
	}

	put_sqare(0, 0, ans_w[ans_size], ans_size + 1);
	ans_size ++;
}

void field::put_2_3st_square()
{
	ans_x[ans_size] = ans_w[0];
	ans_y[ans_size] = 0;
	ans_w[ans_size] = find_max_size(ans_x[ans_size], ans_y[ans_size]);
	put_sqare(ans_x[ans_size], ans_y[ans_size], ans_w[ans_size], ans_size + 1);
	ans_size++;

	ans_x[ans_size] = 0;
	ans_y[ans_size] = ans_w[0];
	ans_w[ans_size] = find_max_size(ans_x[ans_size], ans_y[ans_size]);
	put_sqare(ans_x[ans_size], ans_y[ans_size] , ans_w[ans_size], ans_size + 1);
	ans_size++;
}

int field::back_tracking(int deep)
{
	if (final && (deep > ans_size))
		return deep;

	int cur_x;
	int cur_y;

	if (!find_emty_pice(cur_x, cur_y)){ // если не нашли свободное место
		if (!final || (final && deep - 1 < ans_size))
			ans_size = deep - 1;
		final = true;
		return ans_size;
	}

	if (deep >= array_size)
		extend_array();

	int min_ans = size * size;
	for (int cur_w = find_max_size(cur_x, cur_y); cur_w > 0; cur_w--) {
		put_sqare(cur_x, cur_y, cur_w, deep);
	   
		int cur_ans = back_tracking(deep + 1);
		min_ans = min_ans < cur_ans ? min_ans : cur_ans;
		if (final && cur_ans <= ans_size){
			ans_x[deep - 1] = cur_x;
			ans_y[deep - 1] = cur_y;
			ans_w[deep - 1] = cur_w;
		}

		del_sqare(cur_x, cur_y, cur_w);
	}

	return min_ans;
}

field::field(int size) : size(size)
{
	pieces = new int*[size];
	for (int i = 0; i < size; i++){
		pieces[i] = new int[size];
		for (int j = 0; j < size; j++)
			pieces[i][j] = 0;
	}
	ans_x = new int[array_size];
	ans_y = new int[array_size];
	ans_w = new int[array_size];
}

void field::run()
{
	put_1st_square();
	put_2_3st_square();
	back_tracking(4);
}

void field::print_result()
{
	//std::cout << "O = " << O << std::endl;
	std::cout << ans_size << std::endl;
	for (int i = 0; i < ans_size; i++)
		std::cout << ans_x[i] + 1 << ' ' << ans_y[i] + 1 << ' ' << ans_w[i] << std::endl;
}

field::~field()
{
	delete[] ans_x;
	delete[] ans_y;
	delete[] ans_w;
	for (int i = 0; i < size; i++)
		delete[] pieces[i];
	delete[] pieces;
}