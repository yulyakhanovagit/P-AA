#include <iostream>

using namespace std;

struct Point
{
    unsigned i;
    unsigned j;
};

#pragma pack (4)
class Square
{
private:
    unsigned size;
    unsigned** arr;
    unsigned** framing_arr;

private:
    void framing_odd()
    {
        this->set_main_sq();
        unsigned min = size*size - size - (size+1)/2;
        cout << this->b_track(3, min) << endl;
        cout << min << endl;
        print_coordinates();
    }

    void framing_even()
    {
        for(unsigned i=0; i<size/2; ++i)
        {
            for(unsigned j=0; j<size/2; ++j)
                framing_arr[i][j] = size/2;
        }

        for(unsigned i=size/2; i<size; ++i)
        {
            for(unsigned j=0; j<size/2; ++j)
                framing_arr[i][j] = size/2;
        }

        for(unsigned i=0; i<size/2; ++i)
        {
            for(unsigned j=size/2; j<size; ++j)
                framing_arr[i][j] = size/2;
        }

        for(unsigned i=size/2; i<size; ++i)
        {
            for(unsigned j=size/2; j<size; ++j)
                framing_arr[i][j] = size/2;
        }

        cout << 4 << endl;
        print_coordinates();
    }

    void framing_3_5(unsigned k, unsigned fl)
    {
        Square tmp(fl);

        tmp.set_main_sq();
        unsigned min = tmp.size*tmp.size - tmp.size - (tmp.size+1)/2 + 3;
        cout << tmp.b_track(3, min) << endl;
        cout << min << endl;
        tmp.print_coordinates(k);
    }

    unsigned b_track(unsigned count, unsigned& min, unsigned c=0)
    {
        if(min <= count)
            return c;

        Point tmp = this->find_NoClrLeft();
        if(tmp.i == size && tmp.j == size)
        {
            if(min > count)
            {
                min = count;
                for(unsigned j=0; j<size; ++j)
                {
                    for(unsigned k=0; k<size; ++k)
                        framing_arr[j][k] = arr[j][k];
                }
            }

            return c;
        }

        for(unsigned i=size/2; i>0; --i)
        {
            if(is_fit(tmp, i))
            {
                count++;
                for(unsigned j=tmp.i; j<tmp.i+i; ++j)
                {
                    for(unsigned k=tmp.j; k<tmp.j+i; ++k)
                        arr[j][k] = i;
                }
                c++;

                c = b_track(count, min, c);

                count--;
                for(unsigned j=tmp.i; j<tmp.i+i; ++j)
                {
                    for(unsigned k=tmp.j; k<tmp.j+i; ++k)
                        arr[j][k] = 0;
                }
            }
        }
        return c;
    }

    bool is_fit(Point p, unsigned sz)
    {
        for(unsigned i=p.i; i<p.i+sz; ++i)
        {
            for(unsigned j=p.j; j<p.j+sz; ++j)
            {
                if(i==size || j==size || arr[i][j])
                    return false;
            }
        }

        return true;
    }

    void set_main_sq()
    {
        for(unsigned i=0; i<(size+1)/2; ++i)
        {
            for(unsigned j=0; j<(size+1)/2; ++j)
                arr[i][j] = (size+1)/2;
        }

        for(unsigned i=size-1; i>size/2; --i)
        {
            for(unsigned j=0; j<size/2; ++j)
                arr[i][j] = size/2;
        }

        for(unsigned i=0; i<size/2; ++i)
        {
            for(unsigned j=size-1; j>size/2; --j)
                arr[i][j] = size/2;
        }
    }

    void print_coordinates(unsigned k=1)
    {
        for(unsigned i=0; i<size; ++i)
        {
            for(unsigned j=0; j<size; ++j)
            {
                if(framing_arr[i][j])
                {
                    cout << i*k << ' ' << j*k << ' ' << k*framing_arr[i][j] << endl;
                    delete_fr_sq({i, j}, framing_arr[i][j]);
                }
            }
        }
    }

    void delete_fr_sq(Point st, unsigned sz)
    {
        for(unsigned j=st.i; j<st.i+sz; ++j)
        {
            for(unsigned k=st.j; k<st.j+sz; ++k)
                framing_arr[j][k] = 0;
        }
    }

public:
    Square(unsigned sz)
    {
        size = sz;
        arr = new unsigned*[size];
        for(unsigned i=0; i<size; ++i)
        {
            arr[i] = new unsigned[size];
            for(unsigned j=0; j<size; ++j)
                arr[i][j] = 0;
        }
        framing_arr = new unsigned*[size];
        for(unsigned i=0; i<size; ++i)
        {
            framing_arr[i] = new unsigned[size];
            for(unsigned j=0; j<size; ++j)
                framing_arr[i][j] = 0;
        }
    }

    void framing()
    {
        if(!(size%2))
            framing_even();
        else if(!(size%3))
            framing_3_5(size/3, 3);
        else if(!(size%5))
            framing_3_5(size/5, 5);
        else
            framing_odd();
    }

    Point find_NoClrLeft()
    {
        for(unsigned i=size/2; i<size; ++i)
        {
            for(unsigned j=size/2; j<size; ++j)
            {
                if(!arr[i][j])
                    return {i, j};
            }
        }

        return {size, size};
    }

    ~Square()
    {
        for(unsigned i=0; i<size; ++i)
        {
            delete[] arr[i];
            delete[] framing_arr[i];
        }
        delete[] arr;
        delete[] framing_arr;
        size = 0;
    }
};

int main()
{
    unsigned N;
    cin >> N;
    Square a(N);
    a.framing();

    return 0;
}
