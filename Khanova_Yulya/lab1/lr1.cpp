#include <iostream>

using namespace std;


struct Point{
    int x;
    int y;
    int len; //сторона квадрата
};


class Square{
public:

  Square(int k)
  {
  	arr = new int[(k + 1)*(k + 1)]();
  	this->num = 0;
  	this->k = k;
  }

  ~Square()
  {
                delete[] arr;
  }

  void Insert(int x, int y, int k)
    {
      for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
          arr[(i + y)*this->k + (j + x)] = k;
      num++;
    }


  void Insert(int x, int y, int k, Point &len)
    {
      for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
          arr[(i + y)*this->k + (j + x)] = k;

      len.x = x;
      len.y = y;
      len.len = k;
      num++;
    }

  bool Check_this_position(int x, int y, int k)
    {
      if ((k > this->k - x)  || (k > this->k - y)) return false;

      for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
          if (arr[(i + y)*this->k + (j + x)]) return 0;

      return true;
    }


  void Remove_elements(int x, int y, int k)
    {
      for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
          arr[(i + y)*this->k + (j + x)] = 0;

      num--;
    }


  void Backtracking_of_square(int x, int y, int k)
    {

      for (int i = 2; i < k*k; i++)
      {
        point = new Point[i + 3];
        if (Backtracking(x, y, k, i, 0, 0, 0)) break;
        delete point;
      }

    }


  bool Backtracking(const int &x0, const int &y0, const int &k, const int &num, int r, int x, int y)
    {
      if (num == r)
      {
        for (int i = 0; i < k; i++)
        {
          if (!(arr[(y0 + i)*this->k + (x0 + k - 1)]
            &&            arr[(y0 + k - 1)*this->k + (x0 + i)])) return false;
        }

        return true;
      }

      while ((arr[(y0 + y)*this->k + (x0 + x)]) || (x == k))
      {
        if (x >= k)
        {
          if (y == k) return true;
          y++;
          x = 0;
        }
        else x++;
      }


      for (int i = 1; i<k; i++)
      {
        if (Check_this_position(x0 + x, y0 + y, i))
        {
          Insert(x0 + x, y0 + y, i, point[r]); r++;

          if (Backtracking(x0, y0, k, num, r, x + i, y)) return true;

          Remove_elements(x0 + x, y0 + y, i); r--;
        }
      }

      return false;
    }

  void Print()
  {
    cout << num;
  	for (int i = 0; i < num; i++)
  		cout << endl << point[i].x + 1 << " " << point[i].y + 1 << " " << point[i].len;
  }

  void Split()
  {
  	if (!(k % 2))
  	{
  		point = new Point[4];
  		Insert(0, 0, k / 2, point[0]);
  		Insert(0, k / 2, k / 2, point[1]);
  		Insert(k / 2, 0, k / 2, point[2]);
  		Insert(k / 2, k / 2, k / 2, point[3]);

  		return;
  	}
  	if (!(k % 3))
  	{
  		point = new Point[6];
  		Insert(0, 0, k * 2 / 3, point[0]);
  		Insert(0, k * 2 / 3, k / 3, point[1]);
  		Insert(k * 2 / 3, 0, k / 3, point[2]);
  		Insert(k / 3, k * 2 / 3, k / 3, point[3]);
  		Insert(k * 2 / 3, k / 3, k / 3, point[4]);
  		Insert(k * 2 / 3, k * 2 / 3, k / 3, point[5]);

  		return;
  	}
  	if (!(k % 5))
  	{
  		point = new Point[8];
  		Insert(0, 0, k * 3 / 5, point[0]);
  		Insert(k * 3 / 5, k / 5, k * 2 / 5, point[1]);
  		Insert(k / 5, k * 3 / 5, k * 2 / 5, point[2]);
  		Insert(k * 3 / 5, k * 3 / 5, k * 2 / 5, point[3]);

  		Backtracking(0, 0, k, 8, 4, k * 3 / 5, 0);
  		return;
  	}


  	int m = k / 2 + 1;
  	Insert(0, 0, m);
  	Insert(0, m, m - 1);
  	Insert(m, 0, m - 1);

  	Backtracking_of_square(m - 1, m - 1, m);

  	point[num - 3].x = 0; point[num - 3].y = 0; point[num - 3].len = m;
  	point[num - 2].x = 0; point[num - 2].y = m; point[num - 2].len = m - 1;
  	point[num - 1].x = m; point[num - 1].y = 0; point[num - 1].len = m - 1;
  }

private:
  int* arr; //заполнение квадрата
  int k; //размер квадрата
  Point* point; //верхний левый угол и сторона квадрата
  int num; //колличество обрезков


};



int main()
{
	int n;
	cin >> n;
	Square Big_square(n);
  Big_square.Split();
  Big_square.Print();
	return 0;
}
