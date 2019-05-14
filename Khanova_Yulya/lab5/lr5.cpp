#include <iostream>
#include <vector>
#include <string.h>

#define A 6

using namespace std;

struct bohr_vrtx{
    int next_vrtx[A];
    int path_num;
    bool flag;
    int suff_link;
    int auto_move[A];
    int par;
    char symbol;
    int suff_flink;
};

vector<bohr_vrtx> bohr;
vector <string> pattern;

bohr_vrtx make_bohr_vrtx(int par, char symbol){    //Функции создания новой вершины и инициализации бора:
    bohr_vrtx vertex;
    memset((vertex.next_vrtx), 255, sizeof(vertex.next_vrtx));
    vertex.flag = false;
    vertex.suff_link = -1;
    memset((vertex.auto_move), 255, sizeof(vertex.auto_move));
    vertex.par = par;
    vertex.symbol = symbol;
    vertex.suff_flink = -1;
return vertex;
}

void init_bohr() {
    bohr.push_back(make_bohr_vrtx(-1, -1));
}

int find(char symbol) {
    int ch;
    switch (symbol)
    {
    case 'A':
        ch = 0;
        break;
    case 'C':
        ch = 1;
        break;
    case'G':
        ch = 2;
        break;
    case 'T':
        ch = 3;
        break;
    case 'N':
        ch = 4;
        break;
    default:
        break;
    }
    return ch;
}

void add_string_to_bohr(const string& s){
   int num=0;                                                           //начинаем с корня
   for (int i=0; i<s.length(); i++){
      char ch = find(s[i]);                                                 //получаем номер в алфавите
      if (bohr[num].next_vrtx[ch]==-1){                                   //-1 - признак отсутствия ребра
         bohr.push_back(make_bohr_vrtx(num, ch));
         bohr[num].next_vrtx[ch]=bohr.size()-1;
         }
      num=bohr[num].next_vrtx[ch];
   }
   bohr[num].flag=true;
   pattern.push_back(s);
   bohr[num].path_num=pattern.size()-1;
}

bool is_string_in_bohr(const string& s){
   int num=0;
   for (int i=0; i<s.length(); i++){
      char ch = find(s[i]);
      if (bohr[num].next_vrtx[ch]==-1){
         return false;
         }
      num=bohr[num].next_vrtx[ch];
   }
   return true;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
    if (bohr[v].suff_link == -1) {
        if (v == 0 || bohr[v].par == 0) {
            bohr[v].suff_link = 0;
        }
        else {
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symbol);  //пройдем по суф.ссылке предка и запустим переход по символу.
        }
    }
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch){                        //вычисляемая функция переходов
   if (bohr[v].auto_move[ch]==-1)
      if (bohr[v].next_vrtx[ch]!=-1)    //если из текущей вершины есть ребро с символом ch
         bohr[v].auto_move[ch]=bohr[v].next_vrtx[ch];                   //то идем по нему
      else
         if (v==0)
            bohr[v].auto_move[ch]=0;
         else                                                               //иначе перейдем по суффиксальной ссылке
            bohr[v].auto_move[ch]=get_auto_move(get_suff_link(v), ch);
   return bohr[v].auto_move[ch];
}

void check(int v,int i);

void find_all_pos(const string& s){
    int u=0;
    for(int i=0;i<s.length();i++){
        u=get_auto_move(u,find(s[i]));
        check(u,i+1);
    }
}

int get_suff_flink(int v) {
    if (bohr[v].suff_flink == -1) {
        int u = get_suff_link(v);
        if (u == 0) {
            bohr[v].suff_flink = 0;
        }
        else {
            bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);  //если для вершины по суф.ссылке flag=true, то это искомая вершина, иначе рекурсия.
        }
    }
    return bohr[v].suff_flink;
}

void check(int v, int i) {  //хождение по хорошим суффиксальнм ссылкам из текущей позиции, учитывая, что эта позиция оканчивается на симво i
    for (int u = v; u != 0; u = get_suff_flink(u)) {
        if (bohr[u].flag) {
            cout << i - pattern[bohr[u].path_num].length() + 1 << " " << bohr[u].path_num +1<< endl;
        }
    }
}

int main(){
  string str;
  int n;
  init_bohr();
  cin >> str;
  cin >> n;
  for (int i = 0; i < n; i++) {
      string tmp;
      cin >> tmp;
      add_string_to_bohr(tmp);
  }
  find_all_pos(str);
return 0;
}
