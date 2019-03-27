#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct point {
    int x, y;
    point(int _x, int _y) {
        x = _x; y = _y;
    }
};

struct square {
    int x, y, side;
    square(int _x, int _y, int _side) {
        x = _x; y = _y; side = _side;
    }
};

int n;
int best_result;
bool a[50][50];
vector<square> buffer, answer;
int quantity=0;

point free_cell() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (!a[i][j])
                return point(i, j);
    return point(0, 0);
}

bool check_edge(point p, int side) {
    if (p.x + side - 1 > n || p.y + side - 1 > n)
        return false;
    for (int i = 0; i <= side - 1; ++i)
        if (a[p.x + side - 1][p.y + i] || a[p.x + i][p.y + side - 1])
            return false;
    return true;
}

int max_free_square(point p) {
    int max_side = 1;
    while (check_edge(p, max_side + 1) and max_side < n - 1)
        max_side++;
    return max_side;
}

void fill_sqr(int x, int y, int side, int val) {
    for (int i = x; i < x + side; ++i)
        for (int j = y; j < y + side; ++j)
            a[i][j] = val;
    if(val == 1)
        quantity++;
}

void func(int used, int squares) {
    if (used == n * n) {
        if (squares < best_result) {
            best_result = squares;
            answer.clear();
            for (int i = 0; i < buffer.size(); ++i)
                answer.push_back(buffer[i]);
        }
        return;
    }
    if (squares + 1 >= best_result) return;
    point p = free_cell();
    int max_side = min(max_free_square(p), n - 1);
    for (int i = max_side; i >= 1; --i) {
        fill_sqr(p.x, p.y, i, 1);
        buffer.push_back(square(p.x, p.y, i));
        func(used + i*i, squares + 1);
        buffer.pop_back();
        fill_sqr(p.x, p.y, i, 0);
    }
}

void even(int n) {
    quantity+=4;
    cout << 4 << endl;
    int m = n / 2;
    cout << 1 << " " << 1 << " " << m << endl;
    cout << 1 << " " << m + 1 << " " << m << endl;
    cout << m + 1 << " " << 1 << " " << m << endl;
    cout << m + 1 << " " << m + 1 << " " << m << endl;
    cout << quantity << endl;
}

int is_prime(int n) {
    int min_div=1;
    for(int i=3;i<=sqrt(n);){
        if((n % i == 0)){
            min_div=i;
            break;
        }else
            ++i;
    }
    int sqr;
    if(min_div == 1)
        sqr=(n+1)/2;
    else
        sqr=(n/min_div)*(min_div+1)/2;
    return sqr;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    if (n % 2 == 0){
        even(n);
        return 0;
    }else{
        best_result = n * n;
        int m1 = is_prime(n);
        int m2 = n - m1;
        fill_sqr(1, 1, m1, 1); buffer.push_back(square(1, 1, m1));
        fill_sqr(1, m1 + 1, m2, 1); buffer.push_back(square(1, m1 + 1, m2));
        fill_sqr(m1 + 1, 1, m2, 1); buffer.push_back(square(m1 + 1, 1, m2));
        func(m1 * m1 + 2 * m2 * m2, 3);
    }
    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); ++i) {
        square s = answer[i];
        cout << s.x << " " << s.y << " " << s.side << endl;
    }
    cout << quantity << endl;
    return 0;
}
