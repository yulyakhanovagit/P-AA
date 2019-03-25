include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct Node{
    char name;
    Node* parent;
    bool is_visited;
    std::vector <double> weights;
    std::vector <Node*> nodes;
    int h;
    int key;
};

bool cmp(const Node* a, const Node* b) {return a->key > b->key;}


void create_list(std::vector <Node*>& list, char n1, char n2, double weight){
        int it1 = -1, it2 = -1, i = 0;

        for (auto nd : list)
            {
                if (nd->name == n1)
                    it1 = i;
                if (nd->name == n2)
                    it2 = i;
                i++;
            }

        if (it1 == -1){
            Node* first = new Node;
            first->name = n1;
            first->is_visited = false;
            first->key = 0;
            first->parent = nullptr;
            list.push_back(first);
            it1 = list.size() - 1;

        }

        if (it2 == -1){
            Node* second = new Node;
            second->name = n2;
            second->is_visited = false;
            second->key = 0;
            second->parent = nullptr;
            list.push_back(second);
            it2 = list.size() - 1;
        }

        list[it1]->nodes.push_back(list[it2]);
        list[it1]->weights.push_back(weight);

}



void set_keys(Node* tmp, std::vector <Node*>& str){
    std::vector <Node*>:: iterator it;
    double path = tmp->key - tmp->h;
    size_t i = 0;
    for (; i < tmp->nodes.size(); i++){
        if(tmp->nodes[i]->is_visited == false){
            if(tmp->nodes[i]->key == 0 || (tmp->nodes[i]->h + path + tmp->weights[i] < tmp->nodes[i]->key)){
                tmp->nodes[i]->key = tmp->nodes[i]->h + path + tmp->weights[i];
                tmp->nodes[i]->parent = tmp;
                it = std::find (str.begin(), str.end(), tmp->nodes[i]);
                if( it == str.end()){
                    str.push_back(tmp->nodes[i]);
                }

            }
        }
    }
}


std::string Astar(Node* start, Node* finish){
    std::vector <Node*> str;
    std::string ans;
    Node* tmp = start;
    tmp->key = tmp->h;
    while (true){
        if(tmp->name == finish->name)
            break;
        else{
            tmp->is_visited = true;
            set_keys(tmp, str);
            sort(str.begin(), str.end(), cmp);
            tmp = str[str.size() - 1];
            str.pop_back();
        }
    }
    while(tmp){
        ans.push_back(tmp->name);
        tmp = tmp->parent;
    }
    delete tmp;
    return ans;
}



int main()
{
    Node node;
    std::vector <Node*> list;
    std::string ans;
    char start, finish, n1, n2;
    double weight;
    int i = 0, it1 = 0, it2 = 0, heruistic = 0;
    std::cin >> start >> finish;
    while (std::cin >> n1 ){
        if(n1 == '!')
            break;
        std::cin >> n2 >> weight;
        create_list(list, n1, n2, weight);
    }
    for (auto nd : list){
        std::cout << "Enter the heruistic for "<<nd->name<<std::endl;
        std::cin.clear();
        std::cin >> heruistic;
        while (heruistic < 0){
            std::cout<<"Enter the right heruistic for " << nd->name <<std::endl;
            std::cin>>heruistic;
        }
        nd->h = heruistic;
        if (nd->name == start)
            it1 = i;
        if (nd->name == finish)
            it2 = i;
        i++;
    }

    ans = Astar(list[it1], list[it2]);
    std::reverse(ans.begin(), ans.end());
    std::cout<<ans<<std::endl;
    return 0;

}
