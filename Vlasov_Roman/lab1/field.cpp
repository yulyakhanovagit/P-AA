#include "field.h"

void field::extend_array()
{
    array_size += 20;
    int *tmp_x = new int[array_size];
    int *tmp_y = new int[array_size];
    int *tmp_w = new int[array_size];

    for (int i = 0; i < ans_size; i++)
    {
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
    int s = 1;
    bool flag = true;
    while(flag && s <= size - x && s <= size - y)
    {
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                if (pieces[x + i][y + j] != 0)
                {
                    flag = false;
                    s--;
                }
        s++;
    }
    s--;
    if (s == size)
        s--;
    return s;
}

void field::clear_field(int x, int y, int s)
{
    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            pieces[x + i][y + j] = 0;
}

void field::step1()
{
    ans_x[ans_size] = 0;
    ans_y[ans_size] = 0;
    if (size % 2 == 0)
    {
        ans_w[ans_size] = size / 2;
    }
    else if (size % 3 == 0)
    {
        ans_w[ans_size] = size * 2 / 3;
    }
    else if (size % 5 == 0)
    {
        ans_w[ans_size] = size * 3 / 5;
    }
    else
    {
        ans_w[ans_size] = size / 2 + 1;
    }
    for (int i = 0; i < ans_w[ans_size]; i++)
        for (int j = 0; j < ans_w[ans_size]; j++)
            pieces[i][j] = ans_size + 1;
    ans_size ++;
}

void field::step2()
{
    ans_y[ans_size] = 0;
    for (int i = 0; i < size; i++)
    {
        if (pieces[i][0] == 0)
        {
            ans_x[ans_size] = i;
            break;
        }
    }
    ans_w[ans_size] = find_max_size(ans_x[ans_size], ans_y[ans_size]);
    for (int i = 0; i < ans_w[ans_size]; i++)
        for (int j = 0; j < ans_w[ans_size]; j++)
            pieces[ans_x[ans_size] + i][ans_y[ans_size] + j] = ans_size + 1;
    ans_size++;

    ans_x[ans_size] = 0;
    for (int i = 0; i < size; i++)
    {
        if (pieces[0][i] == 0)
        {
            ans_y[ans_size] = i;
            break;
        }
    }
    ans_w[ans_size] = find_max_size(ans_x[ans_size], ans_y[ans_size]);
    for (int i = 0; i < ans_w[ans_size]; i++)
        for (int j = 0; j < ans_w[ans_size]; j++)
            pieces[ans_x[ans_size] + i][ans_y[ans_size] + j] = ans_size + 1;
    ans_size++;
}

int field::step3(int deep)
{
    if (final && deep > ans_size)
        return deep;

    int cur_x = -1;
    int cur_y = -1;
    int cur_w = -1;
    int max_square_size;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (cur_x == -1 && pieces[i][j] == 0)
            {
                cur_x = i;
                cur_y = j;
            }
    if (cur_x == -1)
    {
        if (!final || (final && deep - 1 < ans_size))
            ans_size = deep - 1;
        final = true;
        return ans_size;
    }
    if (deep >= array_size)
        extend_array();
    max_square_size = find_max_size(cur_x, cur_y);
    int min_ans = size * size;
    for (cur_w = max_square_size; cur_w > 0; cur_w--)
    {
        for (int x = 0; x < cur_w; x++)
            for (int y = 0; y < cur_w; y++)
                pieces[cur_x + x][cur_y + y] = deep;
        int cur_ans = step3(deep + 1);
        min_ans = min_ans < cur_ans ? min_ans : cur_ans;
        if (final && cur_ans <= ans_size)
        {
            ans_x[deep - 1] = cur_x;
            ans_y[deep - 1] = cur_y;
            ans_w[deep - 1] = cur_w;
        }
        clear_field(cur_x, cur_y, cur_w);
    }
    return min_ans;
}

field::field(int size) : size(size)
{
    pieces = new int*[size];
    for (int i = 0; i < size; i++)
    {
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
    step1();
    step2();
    step3(4);
}

void field::print_result()
{
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
