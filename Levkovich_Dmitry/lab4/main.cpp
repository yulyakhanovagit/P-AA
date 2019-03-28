#include <iostream>
#include <vector>
using namespace std;
class A{
public:
vector<size_t> prefix(string s) {
    size_t n = s.length();
    vector<size_t> p(n);

    for (int i = 1; i < n; i++) {
        int j = p[i - 1];

        while ((j > 0) && (s[i] != s[j]))
            j = p[j - 1];

        if (s[i] == s[j])
            ++j;

        p[i] = j;
    }

    return p;
}

vector<size_t> K_M_P(string needle, string haystack){
    vector<size_t> p = prefix(needle+"$"+haystack);
    vector<size_t> result;
    for (size_t i = 2*needle.size(); i < p.size(); i++)
        if (p[i] == needle.size())
            result.push_back(i - 2 * needle.size());
    return result;

}

int isCicleShift(string A, string B) {
    std::vector<size_t> p = prefix(A + "$" + B);
    size_t index = p[p.size() - 1];
    for (int i = index; i < A.size(); i++)
        if (A[i] != B[i - index])
            return -1;

    return index;
}
};

int main() {
    A a;
    string A, B;

    cin >> A >> B;

    vector<size_t> t = a.prefix(A+"+"+B);
    for(int i = 0;i<t.size();i++){
        cout<<t[i]<<" ";
    }

    return 0;
}
