#include <iostream>
#include <vector>

std::vector<int> pref_func(std::string const & str){
	int n = str.length();
	std::vector<int> pi(n);
	int j;
	for(int i=1; i<n; ++i){
		j = pi[i-1];
		while(str[j] != str[i] && j > 0){
			j = pi[j-1];
		}
		if(str[j] == str[i]){
			j += 1;
		}
		pi[i] = j;
	}
	return pi;
}
	
std::string cmp(std::string const & p, std::string const & t){
	int n = p.length();
	std::string ans;
	std::vector<int> pi = pref_func(p);
	int j = 0;
	int t_len = t.length();
	for(int i=0; i<t_len; ++i){
		while(p[j] != t[i] && j > 0){
			j = pi[j-1];
		}
		if(p[j] == t[i]){
			j += 1;
		}
		if(j == n){
			ans += std::to_string(i-n+1);
			ans.push_back(',');
		}
	}
	if(ans == "")
		return "-1";
	ans.pop_back();
	return ans;
}

int find_cycle(std::string a, std::string b){
	int b_len = b.length();
	if(b_len != a.length())
		return -1;
	std::vector<int> pi = pref_func(b);
	int j = 0;
	for(int i=0; i<b_len; ++i){
		while(j == b_len || (b[j] != a[i] && j > 0)){
			j = pi[j-1];
		}
		if(b[j] == a[i]){
			j += 1;
		}
	}
	pi = pref_func(a);
	int k = 0;
	for(int i=0; i<b_len; ++i){
		while(k == b_len || (a[k] != b[i] && k > 0)){
			k = pi[k-1];
		}
		if(a[k] == b[i]){
			k += 1;
		}
	}
	if(j + k < b_len)
		return -1;
	return b_len - j;
}
				
int main(){
	std::string p, t;
	std::getline(std::cin, p);
	std::getline(std::cin, t);
	auto ans = cmp(p, t);
	std::cout << ans << std::endl;
	return 0;
}
