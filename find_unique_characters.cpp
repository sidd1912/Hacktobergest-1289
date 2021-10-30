#include <bits/stdc++.h>
using namespace std;

string uniqueChar(string str) {
    unordered_map<char,int> mp;
    int idx=0;
    for(int i=0;i<str.size();i++)
    {
        if(mp[str[i]]==0)
        {
            str[idx++]=str[i];
            mp[str[i]]++;
        }        
    }
	return str.substr(0,idx);
}
int main() {
    string str;
    cin >> str;
    cout << uniqueChar(str);
}
