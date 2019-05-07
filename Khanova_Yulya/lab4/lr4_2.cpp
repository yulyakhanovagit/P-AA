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

void Shift(string A, string B, vector<int> &pi, int &index){
    int k = 0, l = 0;
    while(true){
        if(k == B.length())
            k = 0;
        if(B[k] == A[l]){
            k++, l++;
            if(l == A.length()){
                index = (l - k);
                break;
            }
        } else if(l == 0){
                    k++;
                    if(k == B.length())
                        break;
        } else l = pi[l -1];
    }
}

int main() {
    string A, B;
    getline(cin, A);
    getline(cin, B);
    vector <int> pi(B.size());
    int index = -1;
    Pi(B, pi);
    if(A.length()==B.length()) Shift(A, B, pi, index);
    else index = -1;
    cout << index;
    pi.clear();
    A.clear();
    B.clear();
    // put your code here
    return 0;
}
