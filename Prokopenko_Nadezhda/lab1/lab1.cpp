#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

class Mass{
private:
    int **Mas;
    int d;
    int sum;
public:
    Mass(int i): d(i), sum(3){
        Mas = new int *[d];
        for(int i = 0; i < d; i++)
            Mas[i] = new int[d];
        for(int i = 0; i < d; i++){
            for(int j = 0; j < d; j++)
                  Mas[i][j] = 0;
        }
    }
    Mass(const Mass &N){
        d = N.d;
        sum = N.sum;
        Mas = new int*[d];
        for (int i = 0; i < d; i++)
            Mas[i] = new int[d];
        for (int i = 0; i < d; i++){
            for (int j = 0; j < d; j++){
                Mas[i][j] = N.Mas[i][j];
            }
        }
    }
    Mass &operator = (Mass const &origin){
        if(this != &origin){
            Mass temp(origin);
            d = temp.d;
            sum = temp.sum;
            for(int i = 0; i < d; i++){
                for(int j = 0; j < d; j++)
                    Mas[i][j] = origin.Mas[i][j];
            }
        }
        return *this;
    }
    ~Mass(){
            for (int i = 0; i < d; i++)
                delete[] Mas[i];
            delete[] Mas;
        }
    void squares(int l){
        for(int i = 0; i < l; i++){
            for(int j = 0; j < l; j++)
                Mas[i][j] = 1;
        }
        for(int i = 0; i < d - l; i++){
            for(int j = l; j < d; j++)
                Mas[i][j] = 2;
        }
        for(int i = l; i < d; i++){
            for(int j = 0; j < d - l; j++)
                Mas[i][j] = 3;
        }
        if(d % 2 == 0){
            for(int i = l; i < d; i++){
                for(int j = l; j < d; j++)
                    Mas[i][j] = 4;
              }
            sum++;
        }
    }
    bool find_s(int &x, int &y){
        for(int i = d - 1; i >= d / 2; i--){
            for(int j = d - 1; j >= d / 2; j--){
                if(Mas[i][j] == 0){
                    x = j;
                    y = i;
                    return true;
                }
            }
        }
        return false;
    }
    void delet(int x, int y, int size){
        for(int i = y; i > (y - size) && (Mas[i][x] == sum); i--)
            for(int j = x; j > (x - size) && (Mas[i][j] == sum); j--){
                Mas[i][j] = 0;
            }
        sum--;
    }
    bool insert(int x, int y, int size){
        bool empty_space = true;
        if((x - size) < 0 || (y - size) < 0)
            return false;
        for(int i = y; i > y - size; i--){
            for(int j = x; j > x - size; j--){
                if(Mas[i][j] != 0)
                    return  empty_space = false;
            }
        }

        sum++;
        for(int i = y; i > y - size; i--)
            for(int j = x; j > x - size   ; j--)
                Mas[i][j] = sum;
        return empty_space;
    }
    int size_of_squar(int x, int y){
        int count = 0;
        int check = Mas[y][x];
        for(int j = x; j < d; j ++){
            if(Mas[y][j] != check)
                return count;
            else
                count++;
        }
        return count;

    }
    void backtracking(Mass &best, int size, int x, int y, int &best_numbers ){
        if(sum >= best_numbers)
            return;
        for(int i = size; i > 0; i--){
            if(insert(x, y, i)){
                int x1 = x;
                int y1 = y;
                if(find_s(x1, y1)){
                    backtracking(best, size, x1, y1, best_numbers);
                }
                else{
                    if(sum < best_numbers){
                        best_numbers = sum;
                        best = *this;
                    }
                    delet(x, y, size);
                    return;
                }
                delet(x, y, size);
            }
        }

    }
    void print(){
        vector<int> check;
        int count = 0;
        for(int i = 0; i < d; i++){
            for(int j = 0; j < d; j++){
                if(find(check.begin(), check.end(), Mas[i][j]) == check.end()){
                    check.push_back(Mas[i][j]);
                    cout <<setw(2)<<right<< i + 1 <<setw(5)<<right<< j + 1 <<setw(5)<<right<< size_of_squar(j, i) << endl;
                    count = 0;
                }
            }
        }
    }
};
int main(){
    int size, k;
    cout <<" Введите длину квадрата:  ";
    cin >> size;
    int best_numbers = pow(size, 2);
    Mass mas(size);
    Mass best(size);
    if(size % 2 == 0){
        k = size / 2;
        mas.squares(k);
        best = mas;
        best_numbers = 4;
    }
    else{
        if(size % 3 == 0)
            k = size * 2 / 3;
        else if(size % 5 == 0)
            k = size * 3 / 5;
        else
            k = (size + 1) / 2;
        mas.squares(k);
        mas.backtracking(best, size - k, size - 1, size - 1, best_numbers);
    }
    cout <<" Минимальное число квадратов:  ";
    cout << best_numbers << endl;
    best.print();
    cout << endl;
    return 0;
}
