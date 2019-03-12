#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class OneFin     //структура ребра графа
{
public:
    char top;
    char last;
    double dist;
};

class ways    //возможные пути
{
public:
    string path;
    double lgth;
};

class graph
{
private:
    vector <OneFin> spisok;
    vector <ways> result;
    vector <char> watch;
    char source;
    char finish1;
    char finish2;
public:
    graph()
    {
         cin >> source >> finish1 >> finish2;
         char temp;
         while(cin >> temp)
         {
             OneFin element;
             element.top = temp;
             cin >> element.last;
             cin >> element.dist;
             spisok.push_back(element);
         }
         string buf = "";
         buf += source;
         for(size_t i=0; i < spisok.size(); i++)
         {
             if(spisok.at(i).top == source)
             {
                 buf += spisok.at(i).last;
                 result.push_back({buf, spisok.at(i).dist});
                 buf.resize(1);
             }
         }
         watch.push_back(source);
    }

    size_t MinSearch() //возвращает минимальный индекс еще не просмотренных вершин
    {
        double min = 9999;
        size_t temp;
        char val;
        for(size_t i=0; i < result.size(); i++)
        {
            if (abs(finish1- result.at(i).path.back()) >= abs(finish1- result.at(i).path.back()))
                val = finish2;
            else
                val = finish1;

            if(result.at(i).lgth + abs(val - result.at(i).path.back()) < min)
            {
                if(Check(result.at(i).path.back()))
                {
                    result.erase(result.begin() + i);
                }
                else
                {
                    min = result.at(i).lgth + abs(val - result.at(i).path.back());
                    temp = i;
                }
            }
        }
        return temp;
    }

    bool Check(char value)
    {
        for(size_t i = 0; i < watch.size(); i++)
            if(watch.at(i) == value)
                return true;
        return false;
    }

    void SearchPath()
    {
        while(true)
        {
            size_t min = MinSearch();
            if(result.at(min).path.back() == finish1 || result.at(min).path.back() == finish2)
            {
                cout << result.at(min).path;
                return;
            }
            for(size_t i=0; i < spisok.size(); i++)
            {
                if(spisok.at(i).top == result.at(min).path.back())
                {
                    string buf = result.at(min).path;
                    buf += spisok.at(i).last;
                    result.push_back({buf, spisok.at(i).dist + result.at(min).lgth});
                }
            }
            watch.push_back(result.at(min).path.back());
            result.erase(result.begin() + min);
        }
    }
};

int main()
{
    graph element;
    element.SearchPath();
    return 0;
}
