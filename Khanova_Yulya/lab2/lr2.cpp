#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include "queue"

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
 size_t size;
public:
   Graph(size_t _N, int start): size(_N){
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
   void A_star(vector<int>&vertex,int start, int finish, priority_queue<Vertex>&p_queue, double dist);
   void Print();
   double Evristic(vector<int> vert,int i, int j);
   void New_matrix(int vert,vector<int> &vertex,vector<int> &v,vector <int> &u,vector<double> &w);
   int Find_i(vector<int>&vert, int f);

};

bool operator < (const Vertex &v1, const Vertex &v2){
   return v1.prior > v2.prior;
}

void Graph::Print(){
   for(int i = 0; i < way.size(); i++)
       cout << way[i] << ' ';
}

void Graph::Matrix(int from, int to, double way){
   matrix[from][to] = way;
}

void Graph::New_matrix(int vert,vector<int> &vertex,vector<int> &v,vector <int> &u,vector<double> &w){
   for(int i = 0; i < size; i++){
       if(v[i] == vert) Matrix(Find_i(vertex, v[i]), Find_i(vertex, u[i]), w[i]);
   }
}
int Graph::Find_i(vector<int>&vert, int f){
   for(int i = 0; i<vert.size(); i++){
       if (vert[i]==f) return i;
   }
}

double Graph::Evristic(vector<int> vert,int i, int j){
   return abs(vert[i] - vert[j]);
}

void Graph::A_star(vector<int>&vertex,int start, int finish, priority_queue<Vertex>&p_queue, double dist){
 vector<int> str;
 while(1){
   for(int i = 0; i < size; i++){
     if(matrix[Find_i(vertex,start)][Find_i(vertex,i)] != 0){
       Vertex tmp;
       tmp.evr = Evristic(vertex, finish, i);
       tmp.prior = matrix[Find_i(vertex,start)][Find_i(vertex,i)]  + dist + tmp.evr;
       for(auto j: str)
           tmp.res.push_back(Find_i(vertex,j));
       tmp.res.push_back(vertex[i]);
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

void Graph::Print_m(){
 for(int i = 0; i<size; i++){
   for(int j = 0; j<size; j++){
     cout << matrix[i][j] << ' ';
   }
   cout << endl;
 }
}

int main(){
     int start, finish, from, to;
     double way;
     cin >> start >> finish;
     priority_queue <Vertex> p_queue;
     vector <int> vertex;
     vector<int> v_from;
     vector <int> v_to;
     vector<double> v_way;
     bool ch1,ch2;
     while(cin >> from >> to >> way){
         ch1 = false;
         ch2 = false;
         v_from.push_back(from);
         v_to.push_back(to);
         v_way.push_back(way);
         for(int i = 0; i < vertex.size(); i++){
           if(v_from.back() == vertex[i]) ch1 = true;
           if(v_to.back() == vertex[i]) ch2 = true;
         }
         if(ch1 == false) vertex.push_back(v_from.back());
         if(ch2 == false) vertex.push_back(v_to.back());
     }
     Graph new_graph(vertex.size(), start);
     for(int i = 0; i < vertex.size(); i++){
       new_graph.New_matrix(vertex[i],vertex, v_from,v_to,v_way);
     }
     new_graph.A_star(vertex,start, finish, p_queue, 0);
     new_graph.Print();
     return 0;
}
