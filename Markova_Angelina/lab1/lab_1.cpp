#include <iostream>
#include <ctime>
#define N 40

class Square{
private:
	int  **coloring; //раскраска
	int  *abscissa;  //массив координат x
	int  *ordinate;  //массив координат y
	int  *length;    //массив длин сторон квадратов
	int  count;      //возможное кол-во квадратов
	int  size;       //размер текущего квадрата
	int  num;        //порядковый номер квадрата
	bool f;          //послдений возможный квадарт
	
	void insert_square(int x, int y, int n, int side);
	void remove_square(int x, int y, int side);
	bool place_to_insert(int &x, int &y);
	void multiple_of_three(int side);
	int  find_max_size(int x, int y);
	void multiple_of_five(int side);
	void insert_the_second_square();
	void insert_the_third_square();
	void even_square(int side);
	void print_square();
	
public:
	void output_of_the_result(int amount);
	int  insert_the_first_square();
	int  backtracking(int deep);
        Square(int size);	
	~Square();
};

void Square::insert_square(int x, int y, int n, int side){ //дружественная функция
	for(int i = x; i < side + x; i++)
		for(int j = y; j < side + y; j++)
			coloring[i][j] = n;
}

void Square::remove_square(int x, int y, int side){
	for(int i = x; i < side + x; i++)
		for(int j = y; j < side + y; j++)
			coloring[i][j] = 0;
}

bool Square::place_to_insert(int &x, int &y){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(!coloring[i][j]){
				x = i;
				y = j;
				return true;
			}
	return false;
}

void Square::multiple_of_three(int side){
	abscissa[1] = abscissa[2] = abscissa[3] = ordinate[3] = ordinate[5] = ordinate[4] = side;
	abscissa[5] = ordinate[2] = side*1/2;
	abscissa[4] = ordinate[1] = 0;
	for(int i = 1; i < 6; i++)
		length[i] = size*1/3;
}

int Square::find_max_size(int x, int y){
	int  max_size;
	bool allowed = true;
	for(max_size = 1; allowed && max_size <= size - x && max_size <= size - y; max_size++) //проверка на пересечение границ квадрата
		for(int i = 0; i < max_size; i++)
			for(int j = 0; j < max_size; j++)
				if(coloring[x + i][y + j]){ //проверка на пересечение с уже существующим квадратом
					allowed = false;
					max_size--;
				}
	max_size--;
	return max_size;
}

void Square::multiple_of_five(int side){
	abscissa[1] = abscissa[2] = abscissa[7] = ordinate[4] = ordinate[5] = ordinate[7] = side;
	abscissa[5] = abscissa[6] = ordinate[2] = ordinate[3] = size*2/5;
	length[2] = length[3] = length[5] = length[6] = side*1/3;
	length[1] = length[4] = length[7] = side*2/3;
	abscissa[3] = ordinate[6] = size*4/5;
	abscissa[4] = ordinate[1] = 0;
}
	
void Square::insert_the_second_square(){
	abscissa[num] = length[0];
	ordinate[num] = 0;
	length[num] = find_max_size(abscissa[num], ordinate[num]);
	insert_square(abscissa[num], ordinate[num], num + 1, length[num]);
	num++;
}

void Square::insert_the_third_square(){
	abscissa[num] = 0;
	ordinate[num] = length[0];
	length[num] = find_max_size(abscissa[num], ordinate[num]);
	insert_square(abscissa[num], ordinate[num], num + 1, length[num]);
	num++;
}

void Square::even_square(int side){
	abscissa[1] = abscissa [3] = ordinate[2] = ordinate[3] = size*1/2;
	abscissa[2] = ordinate[1] = 0;
	for(int i = 0; i < 4; i++)
		length[i] = size*1/2;
}

void Square::print_square(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			std::cout << coloring[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Square::output_of_the_result(int amount){
	std::cout << amount << std::endl;
	for(int i = 0; i < amount; i++)
		std::cout << abscissa[i]+1 << " " << ordinate[i]+1 << " " << length[i] << std::endl;
}

int Square::insert_the_first_square(){
	abscissa[num] = ordinate[num] = 0;
	if(size % 2 == 0){                 //если сторона квадрата кратна 2-м
		even_square(size*1/2);
		return 4;
	}
	if(size % 3 == 0){                 //если сторона квадрата кратна 3-м
		length[num] = size*2/3;
		multiple_of_three(length[num]);
		return 6;
	}
	if(size % 5 == 0){                 //если сторона квадрата кратна 5-ти
		length[num] = size*3/5;
		multiple_of_five(length[num]);
		return 8;
	}
	else{                              //все остальные случаи
		length[num] = size*1/2 + 1;
		insert_square(abscissa[num], ordinate[num], num + 1, length[num]);
		num++;
		insert_the_second_square();
		insert_the_third_square();
		return backtracking(4);
	}
}

int Square::backtracking(int deep){   
	if(f && deep > num)               //если текущее разбиение больше предыдущего
		return deep;
	int min_result = size * size;
	int temporary_length;
	int temporary_result;
    	int temporary_x;
	int temporary_y;
	if(!place_to_insert(temporary_x, temporary_y)){ //если нет места для вставки
		if(!f || (f && deep - 1 < num))
			num = deep - 1;
		f = true;
		return num;
	}
	for(temporary_length = find_max_size(temporary_x, temporary_y); temporary_length > 0; temporary_length--){
		insert_square(temporary_x, temporary_y, deep, temporary_length);
		temporary_result = backtracking(deep + 1);
		min_result = min_result < temporary_result ? min_result : temporary_result;
		if(temporary_result <= num){
			length[deep - 1] = temporary_length;
			abscissa[deep - 1] = temporary_x;
			ordinate[deep - 1] = temporary_y;
		}
		remove_square(temporary_x, temporary_y, temporary_length);
	}
	return min_result;
}

Square::Square(int size) : size(size){
	coloring = new int*[size];
	for(int i = 0; i < size; i++){
		coloring[i] = new int[size];
		for(int j = 0; j < size; j++)
			coloring[i][j] = 0;
	}
	abscissa = new int[N];
	ordinate = new int[N];
	length = new int[N];
	count = N;
	f = false;
	num = 0;
}

Square::~Square(){
	delete[] abscissa;
	delete[] ordinate;
	delete[] length;
	for(int i = 0; i < size; i++)
		delete[] coloring[i];
	delete[] coloring;
}

int main(){
	//clock_t time;
	//time = clock();
	int size, count;
	std::cout << "Size is:" << std::endl;
	std::cin >> size;
	Square table(size);
	count = table.insert_the_first_square();
	table.output_of_the_result(count);
	//time = clock() - time;
	//std::cout<<time/CLOCKS_PER_SEC<<std::endl;
	return 0;
}
