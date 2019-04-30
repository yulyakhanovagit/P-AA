#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include "queue"
#define N 26

using namespace std;

struct Vertex{
  vector <int> res;
  double prior;
  double evr;
  Vertex():prior(0),evr(0){}
  Vertex(double _p, double _e):prior(_p),evr(_e){}
};

class Graph{
private:
  vector<int> way;
  double ** matrix;
  int size;
public:
    Graph(int _N, int start): size(_N){
      way.push_back(start);
      matrix = new double *[size];
      for(int i = 0; i < size; i++)
        matrix[i] = new double[size];
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
          matrix[i][j] = 0;
        }
      }
    }
    ~Graph(){
      way.clear();
      for(int i = 0; i < size; i++)
        delete [] matrix[i];
    }
    void A_star(int start, int finish, priority_queue<Vertex>&p_queue, double dist);
    void Print();
    void Matrix(int from, int to, double way);
    double Evristic(int i, int j);

};

bool operator < (const Vertex &v1, const Vertex &v2){
    return v1.prior > v2.prior;
}

void Graph::Print(){
    for(int i = 0; i < way.size(); i++)
        cout << (char)(way[i] + 'a');
}

void Graph::Matrix(int from, int to, double way){
    matrix[from][to] = way;
}


double Graph::Evristic(int i, int j){
    return abs(i - j);
}

void Graph::A_star(int start, int finish, priority_queue<Vertex>&p_queue, double dist){
  vector<int> str;
  while(1){
    for(int i = 0; i < size; i++){
      if(matrix[start][i] != 0){
        Vertex tmp;
        tmp.evr = Evristic(finish, i);
        tmp.prior = matrix[start][i] + dist + tmp.evr;
        for(auto j: str)
            tmp.res.push_back(j);
        tmp.res.push_back(i);
        p_queue.push(tmp);
      }
    }
    if(p_queue.empty()) break;
    else {
        Vertex last;
        last = p_queue.top();
        p_queue.pop();
        start = last.res[last.res.size()-1];
        str = last.res;
        dist = last.prior - last.evr;
    }
    if(str[str.size()-1] == finish){
        for(auto i: str)
            way.push_back(i);
      break;
    }
  }
}

int main(){
      char start, finish, from, to;
      double way;
      cin >> start >> finish;
      Graph new_graph(N, start - 'a');
      priority_queue <Vertex> p_queue;
      while(cin >> from >> to >> way){
          new_graph.Matrix(from - 'a', to - 'a', way);
      }
      new_graph.A_star(start - 'a', finish - 'a', p_queue, 0);

      new_graph.Print();
      return 0;
}
