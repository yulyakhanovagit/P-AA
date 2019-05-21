#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <map>
#include <cmath>
#define A 'z'

using namespace std;
using List = map<char, map <char, int>>;

class Graph{
private:
  char distance[A];
  List orig_graph;
  List real_graph;
  array <bool, A> check;
public:
  Graph() = default;
  ~Graph() = default;
  void Print();
  void Insert(char from, char to, int way);
  int Residual_Capacity(char from, char to);
  bool Find_way(char source, char sink);
  int Ford_Fulkerson(char source, char sink);

};


bool Graph::Find_way(char source, char sink){
  check.fill (false);
  check[source] = true;
  distance[source] = -1;
  queue <char> queue;
  queue.push(source);
  while (!queue.empty()) {
      char from = queue.front();
      for (char to = 0; to < A; to++) {
          if (!check[to] && Residual_Capacity(from, to) > 0) {
              queue.push(to);
              check[to] = true;
              distance[to] = from;
              if (to == sink) {
                  queue.pop();
                  return (true);
              }
          }
      }
      queue.pop();
  }
  return (false);
}

int Graph::Residual_Capacity(char from, char to){
  return (orig_graph[from][to] - real_graph[from][to]);
}

void Graph::Insert(char from, char to, int way){
  orig_graph[from][to] = way;
  real_graph[to][from]= 0;
}

void Graph::Print(){
  for (char i = 0; i < A; i++)
      for (char j = 0; j < A; j++)
          if (orig_graph[i][j])
              cout << char(i) << " " << char(j) << " " << max(real_graph[i][j], 0) <<endl;
}

int Graph::Ford_Fulkerson(char source, char sink) {
    int maxFlow = 0;
    while (Find_way(source, sink)) {
        int minFlow = INT_MAX;
        char to = sink;
        for(int i = sink; 0 <= distance[i]; i = distance[i])
            minFlow = min(minFlow, Residual_Capacity(distance[i], i));
        for(int i = sink; 0 <= distance[i]; i = distance[i]) {
            real_graph[distance[i]][i] += minFlow;
            real_graph[i][distance[i]] -= minFlow;
        }
        maxFlow += minFlow;
        memset(distance, -1, A * sizeof(char));
        check.fill (false);
    }
    return (maxFlow);
}


int main(){
  int N, w;
  char source, sink, v, u;
  cin >> N >> source >> sink;
  Graph new_graph;
  for(int i = 0; i < N; i++){
    cin >> v >> u >> w;
    new_graph.Insert(v, u, w);
  }
  cout << new_graph.Ford_Fulkerson(source, sink) <<endl;
  new_graph.Print();

  return 0;
}
