#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

typedef struct node{
    double key;
    double dif;
    vector <char> str;
}node;

bool operator < (const node& a,const node& b){
    return a.key > b.key;
}

class list{
private:
    vector <tuple <char, char, double> > edge;
public:
    void add_edge(char v1, char v2, double weight){
        edge.push_back(make_tuple(v1, v2, weight));
    }
    double evristic(int i,double way){
        return get<2>(edge[i])+way;
    }
    void path(char first, char last1, char last2, priority_queue <node> &queue1, double way, vector <char>& str_way){
        vector<char> str1;
        while(true){
            for(int i = 0; i < edge.size(); i++)
                if(get<0>(edge[i]) == first){
                    node elem;
                    elem.dif=min( fabs(last1-get<1>(edge[i])), fabs(last2-get<1>(edge[i])));
                    elem.key=evristic(i,way)+elem.dif;
                    for(auto j:str1)
                        elem.str.push_back(j);
                    elem.str.push_back(get<1>(edge[i]));
                    queue1.push(elem);
                }
            if(queue1.empty())
                break;
            if(!queue1.empty()){
                node popped;
                popped=queue1.top();
                queue1.pop();
                first=popped.str[popped.str.size()-1];
                str1=popped.str;
                way=popped.key-popped.dif;
            }
            if(str1[str1.size()-1] == last1 || str1[str1.size()-1] == last2){
                for(auto j:str1)
                    str_way.push_back(j);
                break;
            }
        }
    }
};

int main(){
    char first,last1,last2,v1;
    cin>>first;
    cin>>last1;
    cin>>last2;
    list list1;
    while(cin>>v1){
        char v2;
        cin>>v2;
        double weight;
        cin>>weight;
        if(isalpha(v1) && isalpha(v2))
            list1.add_edge(v1, v2, weight);
    }
    vector <char> str;
    str.push_back(first);
    priority_queue <node> queue1;
    double way=0;
    list1.path(first, last1, last2, queue1, way, str);
    if(str[str.size()-1] == last1 || str[str.size()-1] ==last2)
        for(auto j:str)
            cout<<j;
    return 0;
}
