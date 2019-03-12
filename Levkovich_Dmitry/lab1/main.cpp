#include <iostream>
#include <vector>
#include <cmath>
#include <exception>
#include <fstream>
using namespace std;

class Square{
public:
    Square(int N):arr(N, vector<int>(N, 0)), best(15, vector<int>(3, 0))
    {
        size = N;
        bestcolor = 16;
        color = 4;
        count = 1;
    }
    ~Square(){

    }
    void write(){
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++)
                cout<<best[i][j]<<" ";
            cout<<endl;
        }

    }
    void RemoveSqr(int N, int color){
        for(auto i = N; i<size;i++)
            for(auto j = N; j < size; j++){
                if(arr[i][j]==color)
                    arr[i][j] = 0;
            }

    }

    bool findEmptySquare(int & x, int & y){
            while(arr[y][x]!=0){
            if(x==size-1){
                x = 0;
                y++;
            }
            else
                x++;
            if(x>=size || y>=size)
                return false;
        }
        return true;
    }

    bool isOutOfBounds(int x, int y, int width)
    {
        if(width > size-x || width > size-y)
            return true;
        else
            return  false;
    }

    bool PutSquare(int x, int y, int w, int color, int N){
        if(isOutOfBounds(x, y, w))
            return false;
        for(auto i = 0; i<w;i++){
            for(auto j = 0;j<w;j++){
                if(arr[y+i][x+j] == 0){
                    arr[y+i][x+j] = color;
                }
                else{
                    RemoveSqr(N, color);
                    return false;
                }
            }
        }
        return true;
    }


    void BackTracking(int x, int y, int N){

        if(color>bestcolor){

            return;
        }
        for(int i = N ; i >= 1; i--)
        {
            if(PutSquare(x, y, i, color, N))
            {

                color++;
                int next_x = x;
                int next_y = y;

                if(findEmptySquare(next_x, next_y)){

                    BackTracking(next_x, next_y, N);

                }
                else

                {

                    color--;
                    if(color < bestcolor){

                        bestcolor = color;
                        print(bestcolor);
                    }
                    RemoveSqr(N, color);
                    return;
                }
                color--;
                RemoveSqr(N, color);
            }
        }
    }

    int findSquare(int & x, int & y,int K){
        while (arr[y][x] != K){
            if (x == size-1){
                x = 0;
                ++y;
            }
            else
                ++x;
            if (x>=size || y>=size)
                return 0;
        }
        int i = 0;
        while (!isOutOfBounds(x, y, i) && arr[y][x+i] == K){
                i++;
        }
        return i;
    }

    void print(int color){
        int x, y, size;
        for(int k = 1; k <= color; ++k)
        {
            x = 0;
            y = 0;
            size = findSquare(x, y, k);
            best[k-1][0] = x + 1;
            best[k-1][1] = y + 1;
            best[k-1][2] = size;
        }
    }

    void solve(){

        if(size%2 == 0){
            PutSquare(0, 0, size/2, 1, size/2);
            PutSquare(0, size/2,size/2, 2,size/2);
            PutSquare(size/2, 0,size/2, 3,size/2);
            BackTracking( size/2, size/2, size-size/2);
            cout << bestcolor << endl;
            for(int i = 0;i<bestcolor;i++){
                cout<<best[i][0]<<" "<<best[i][1]<<" "<<best[i][2]<<endl;
            }
        }
        else if(size%3 == 0){
            PutSquare(0, 0, 2*size/3, 1,size/3);
            PutSquare(0, 2*size/3, size/3, 2,size/3);
            PutSquare(2*size/3, 0, size/3, 3,size/3);
            BackTracking( 2*size/3, size/3, size/3);
            cout << bestcolor << endl;
            for(int i = 0;i<bestcolor;i++){
                cout<<best[i][0]<<" "<<best[i][1]<<" "<<best[i][2]<<endl;
            }
        }
        else if(size%5 == 0){

            PutSquare(0, 0, 3*size/5, 1,2*size/5);
                        PutSquare(0, 3*size/5, 2*size/5, 2,2*size/5);
                        PutSquare(3*size/5, 0, 2*size/5, 3,2*size/5);

            BackTracking(3*size/5, 2*size/5, 2*size/5);
            cout << bestcolor << endl;
            for(int i = 0;i<bestcolor;i++){
                cout<<best[i][0]<<" "<<best[i][1]<<" "<<best[i][2]<<endl;
            }
        }

        else{

            PutSquare(0,0,size/2+1,1,size-(size/2+1));
            PutSquare(size/2+1,0,size/2,2,size-(size/2+1));
            PutSquare(0,size/2+1,size/2,3,size-(size/2+1));
            BackTracking(size/2+1, size/2, size-(size/2+1));
            cout << bestcolor << endl;
            for(int i = 0;i<bestcolor;i++){
                cout<<best[i][0]<<" "<<best[i][1]<<" "<<best[i][2]<<endl;
            }

        }
    }

private:
    vector<vector<int>> best;
    vector<vector<int>> arr;
    int size;
    int bestcolor;
    int color;
    int count;
};

int main()
{
    int N = 0;
    cin>>N;
    Square a(N);
    a.solve();
    //a.write();
    return 0;
}
