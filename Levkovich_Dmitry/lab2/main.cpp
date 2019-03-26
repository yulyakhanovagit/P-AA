#include <iostream>
#include <vector>
#include <queue>
#include <ctype.h>
#include <cstring>
#include <algorithm>
using namespace std;
struct A{
    vector<char> resulte;
    double weight = 0;
    int prior = 0;
};
struct B{
    char a;
    char b;
    double weight;
};
template <typename T, typename type>
class Graph{
    vector<vector<T>> m;
    size_t size;
    type start;
    type finish;
    double weight;
    vector<type> result;

public:
    Graph(){
        size = 26;
    }
    void Init(){
        type vertex1, vertex2;
        cin>>start>>finish;
        bool t = true;

        while(t){
            if(cin>>vertex1 && isalpha(vertex1)){
                cin>>vertex2>>weight;
                m[vertex1-'a'][vertex2-'a'] = weight;
            }
            else {
                t = false;
            }
        }
    }

    bool find(vector<type> t, type c){
        if(t.size()==0){
            return false;
        }
        for(int i = 0;i<t.size();i++){
            if(t[i]==c){
                return true;
            }
        }
        return false;
    }

    int find_index(vector<type> t, type c){
        int index = 0;
        for(int i = 0;i<t.size();i++){
            if(c==t[i])
                return index;
            index++;
        }
    }

    void new_Init(){
        vector<B> edge;
        vector<type> a;
        type vertex1, vertex2;
        cin>>start>>finish;
        bool t = true;
        while(t){
            if(cin>>vertex1 && isalpha(vertex1)){
                cin>>vertex2>>weight;
                edge.push_back({vertex1, vertex2, weight});
                if(!find(a, vertex1))
                    a.push_back(vertex1);
                if(!find(a, vertex2))
                    a.push_back(vertex2);

            }
            else {
                t = false;
            }
        }
        sort(a.begin(), a.end());
        size = a.size();
        m.resize(size);
        for(int i = 0;i<size;i++){
            m[i].resize(size);
        }
        for(int i = 0;i<edge.size();i++){
            m[find_index(a, edge[i].a)][find_index(a, edge[i].b)] = edge[i].weight;
        }
        GreedIsGood(a);
    }

    void GreedIsGood(vector<type> a){
        result.resize(size);
        int min = 1000;
        int res = 0;
        result[0] = start;
        while (result[res] != this->finish)
        {
            min = 1000;
            res++;
            for (int i = 0; i < size; i++)
                if ((min > m[find_index(a, result[res-1])][i]) && (m[find_index(a, result[res-1])][i] != 0)){
                    min = m[find_index(a, result[res-1])][i];
                    result[res] = a[i];
                }
            if(min == 1000){
                m[find_index(a, result[res-1])][find_index(a, result[res-1])] = 0;
                res-=2;
            }
            else {
                 m[find_index(a, result[res-1])][find_index(a, result[res])] = 0;
            }
        }
        for (int i = 0;i<result.size();i++) {
            if(isalpha(result[i]))
                    cout<<result[i];
        }
    }

    int veclen(vector<type> a){
        int count = 0;
        for (int i = 0;i<a.size();i++) {
             count++;
            if(a[i]==0)
                return i;
        }
    }

    void A_Star(vector<type> a){
        vector<A> solution;
        A *curr_sol;
        vector<type> str(size, 0);
        type *finish = nullptr;
        bool vertex_duplication;
        T weight_cur, fin_w;
        int sol = 0, current = 0;
        current = find_index(a, this->start);
        weight_cur = 0;
        while(1)
        {
            for (int i = 0; i < size; i++)
                if (m[find_index(a, (type)(current+97))][i] != 0)
                {
                    vertex_duplication = false;
                    for (int j = 0; j < veclen(str); j++)
                        if(a[i] == str[j]) {
                            vertex_duplication = true;
                            break;
                        }
                    if ((vertex_duplication == false) && (a[i] != this->start))
                    {
                        curr_sol = new A;
                        solution.push_back(*curr_sol);
                        solution.at(sol).resulte.resize(size);
                            solution.at(sol).resulte = str;
                        solution.at(sol).resulte[veclen(str)]=a[i];
                        solution.at(sol).weight=m[find_index(a, (type)(current+97))][i] + weight_cur;
                        solution.at(sol).prior=this->finish - (int)a[i];
                        delete curr_sol;
                        sol++;
                    }
                }
            sol--;
            std::sort(solution.begin(), solution.end(), [](const A& a, const A& b) {//сортировка по убыванию
                      return (a.weight+a.prior) > (b.weight+b.prior);});

            if(finish != nullptr)
            {
                while (sol >=0)
                    {
                        if(solution.at(sol).weight < fin_w)
                            break;
                        else {
                            solution.erase(solution.begin() + sol);
                            sol--;
                        }
                    }
                if (sol == -1)
                    break;

            }
            if(solution.at(sol).resulte[veclen(solution.at(sol).resulte) - 1] == this->finish)
            {
                if(finish == nullptr)
                {
                    finish = new type(solution.at(sol).resulte.size());
                    for(int i = 0;i<solution.at(sol).resulte.size();i++){
                        finish[i] = solution.at(sol).resulte[i];
                    }
                    fin_w=solution.at(sol).weight;
                    solution.erase(solution.begin() + sol);
                }
                else {
                    if(solution.at(sol).weight < fin_w)
                        {
                        delete[] finish;
                        finish = new type(solution.at(sol).resulte.size());
                        for(int i = 0;i<solution.at(sol).resulte.size();i++){
                            finish[i] = solution.at(sol).resulte[i];
                        }
                            fin_w=solution.at(sol).weight;
                        }
                        solution.erase(solution.begin() + sol);
                    }
                sol--;
                while (sol >=0)
                {
                    if(solution.at(sol).weight < fin_w) break;
                    else {
                        solution.erase(solution.begin() + sol);
                        sol--;
                    }
                }

                if (sol == -1)
                    break;
            }
            current = (int)(solution.at(sol).resulte[veclen(solution.at(sol).resulte)-1]) - 97;
            str = solution.at(sol).resulte;
            weight_cur = solution.at(sol).weight;
        }
        cout<<this->start<<finish<<endl;
    }
};

int main()
{
    Graph<double, char> s;
    s.new_Init();
    return 0;s
}
