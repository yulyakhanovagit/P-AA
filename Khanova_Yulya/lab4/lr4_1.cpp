#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Pi(string P, vector<int>&pi){
    pi[0]=0;
    int i = 1, j = 0;
    while(i<P.length()){
        if(P[i]==P[j]) {
            pi[i] = j+1;
            i++;
            j++;
        }
        else
            if(j==0){
                pi[i] = 0;
                i++;
                }
            else j = pi[j- 1];
    }
}

void KMP(string P, string T, vector<int> &pi, vector<int>&result){
    int k = 0, l = 0;
    while(k < T.length()){
        if(T[k] == P[l]){
            k++;
            l++;
            if(l == P.length())
                result.push_back(k - l);
        } else if(l == 0){
            k++;
        } else l = pi[l - 1];
    }
}

int main() {
    string P, T;
    getline(cin, P);
    getline(cin, T);
    vector <int> pi(P.size()), result;
    Pi(P, pi);
    KMP(P, T, pi,result);
    if(result.size() == 0) cout << -1 << endl;
    else {
        for(int i = 0; i <(result.size()- 1); i++){
            cout << result[i] << ",";
        }
        cout << result[result.size()- 1] << endl;
    }
    pi.clear();
    result.clear();
    P.clear();
    T.clear();
    // put your code here
    return 0;
}
