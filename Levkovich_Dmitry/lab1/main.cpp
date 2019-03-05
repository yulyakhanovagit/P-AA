#include <iostream>
#include <vector>
#include <cmath>
#include <exception>
#include <fstream>
using namespace std;

class Square{
public:
    Square(int N):arr(N, vector<int>(N, 0)), best(15, vector<int>(3, 0)), q(N, vector<int>(N, 0))
    {

        size = N;
        bestcolor = 16;
        color = 4;
        count = 3;
    }
    ~Square(){

    }

    void solve(){

        if(size%2 == 0){
            PutSquare(0, 0, size/2, 1, size/2);
            PutSquare(0, size/2,size/2, 2,size/2);
            PutSquare(size/2, 0,size/2, 3,size/2);
            BackTracking( size/2, size/2, size-size/2);
            ans();
        }
        else if(size%3 == 0){
            PutSquare(0, 0, 2*size/3, 1,size/3);
            PutSquare(0, 2*size/3, size/3, 2,size/3);
            PutSquare(2*size/3, 0, size/3, 3,size/3);
            BackTracking( 2*size/3, size/3, size/3);
            ans();
        }
        else if(size%5 == 0){
            PutSquare(0, 0, 3*size/5, 1,2*size/5);
            PutSquare(0, 3*size/5, 2*size/5, 2,2*size/5);
            PutSquare(3*size/5, 0, 2*size/5, 3,2*size/5);
            BackTracking(3*size/5, 2*size/5, 2*size/5);
            ans();
        }

        else{
            color++;
            PutSquare(0,0,size/2+1,1,size-(size/2+1));
            PutSquare(size/2+1,0,size/2,2,size-(size/2+1));
            PutSquare(0,size/2+1,size/2,3,size-(size/2+1));
            PutSquare(size/2+1, size/2,1, 4, size-(size/2+1));
            BackTracking(size/2+2, size/2, size-(size/2+1));
            ans();
        }
    }

private:
    vector<vector<int>> best;
    vector<vector<int>> arr;
    int size;
    int bestcolor;
    int color;
    int count;
    vector<vector<int>> q;
    void RemoveSqr(int N, int color){
        for(auto i = N; i<size;i++)
            for(auto j = N; j < size; j++){
                if(arr[i][j]==color)
                    arr[i][j] = 0;
            }

    }

    bool findEmptySquare(int & x, int & y, int N){
        for (y = N;y<size;y++) {
            for (x = N;x<size;x++) {
                if(arr[y][x]==0)
                    return true;
            }
        }
        return false;
    }

    bool isOutOfBounds(int x, int y, int width)
    {
        if(width +x > size || width +y > size)
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

    void BackTracking(int x, int y, unsigned N){
        if(color-1>bestcolor){
            return;
        }
        if(findEmptySquare(x, y, N)){
            for(int i = N; i > 0;i--){
                if(PutSquare(x, y, i, color, N)){
                    color++;
                    BackTracking(x, y, N);
                    color--;
                }
             RemoveSqr(N, color);
            }
        }
        else if((color-1) < bestcolor){
            bestcolor = color-1;
            print(bestcolor);
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
        while (arr[y][x+i] == K){
            if ((x+i) < size)
            {
                ++i;
            }
            else return --i;
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
    void ans(){
        cout << bestcolor << endl;
        for(int i = 0;i<bestcolor;i++){
           cout<<best[i][0]<<" "<<best[i][1]<<" "<<best[i][2]<<endl;
        }
    }
};

int main()
{
    int N = 0;
    cin>>N;
    Square a(N);
    a.solve();
    return 0;
}
