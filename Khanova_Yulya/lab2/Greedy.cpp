#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#define N 26

using namespace std;

struct Vertex{
  bool check;
  char name;
  char prev;
  Vertex():check(false),name('a'),prev('a'){}
  Vertex(bool _ch, char _name, char _prev):check(_ch),name(_name),prev(_prev){}
};

class Graph{
private:
  vector<char> way;
  double ** matrix;
  int size;
  int start;
  vector<Vertex> vertex;
public:
    Graph(int _N, int _start): size(_N), start(_start){
      way.push_back(start+'a');
      vertex.push_back(Vertex(true, 'a' + start, 0));
      matrix = new double *[size];
      for(int i = 0; i < size; i++)
        matrix[i] = new double[size];
      for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
          matrix[i][j] = 0;
        }
      }
      for(int i = 1; i < size; i++){
        vertex.push_back(Vertex(false, 'a' + i, 0));
      }
    }
    ~Graph(){
      vertex.clear();
      way.clear();
      for(int i = 0; i < size; i++)
        delete [] matrix[i];
    }
    int Local_min(int i);
    void Min_way(int start, char finish);
    void Print();
    void Matrix(int from, int to, double way);

};

void Graph::Print(){
    for(int i = 0; i < way.size(); i++)
        cout << way[i];
}

void Graph::Matrix(int from, int to, double way){
    matrix[from][to] = way;
}

int Graph::Local_min(int i){
    double min = 9999;
    int index = 0;
    for(int j = 0; j < size; j++){
      if(matrix[i][j]!=0 && matrix[i][j]<min && vertex[j].check == false){
        min = matrix[i][j];
        index = j;
      }
    }
    return index;
}

void Graph::Min_way(int start, char finish){
    if(vertex[start].name == finish) return;
    int tmp = Local_min(start);
    if(vertex[tmp].check == false && tmp!=0){
      vertex[tmp].prev = 'a' + start;
      vertex[tmp].check = true;
      vertex[tmp].name = 'a' + tmp;
      way.push_back('a'+ tmp);
    }
    else {
        way.pop_back();
        vertex[start].check = true;
        vertex[vertex[start].prev - 'a'].check = true;
        tmp = vertex[start].prev - 'a';
    }
      Min_way(tmp, finish);
}

int main(){
      char start, finish, from, to;
      double way;
      cin >> start >> finish;
      Graph new_graph(N, start - 'a');
      while(cin >> from >> to >> way){
          new_graph.Matrix(from - 'a', to - 'a', way);
      }
      new_graph.Min_way(start - 'a', finish );

      new_graph.Print();
      return 0;
}
