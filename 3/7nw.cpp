#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <stdint.h>
#include <sstream>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

namespace __gnu_cxx
{
template<> struct hash<std::string>                                          
{                                                                            

   size_t operator()(const std::string& __x) const 
   { 
      return __stl_hash_string(__x.c_str()); 
   }                                                                          

};                                                                           
}

typedef hash_map<string, string> dict_t;

#define FOR0(i, n) for(int i = 0; i < n; i++)
#if 1
#define INS \
{ \
   static int calls; \
   calls++; \
   cout << __FUNCTION__ << ":" << calls << endl; \
}
#else
#define INS 
#endif
template<class T>
void pv(const vector<T> &v){
   if(!v.size()){
      cout <<"{}\n";
      return;
   }
   cout << "{";
   FOR0(i,v.size()-1){
      cout << v[i] <<", ";
   }
   cout << v[v.size()-1] << "}\n";
}

class Solver
{
   void backtrace(const string &w1, const string &w2, const string &prev, const dict_t &dict)
   {
      stack<string> st;
      st.push(w2);
      st.push(prev);
      string w = prev;
      while(w != w1){
         dict_t::const_iterator it = dict.find(w);
         assert(it != dict.end());
         w = it->second;
         st.push(w);
      }
      while(!st.empty()){
         cout << st.top() << endl;
         st.pop();
      }
   }
   public:
   void solve(dict_t &dict, const string &w1, const string &w2)
   {
      queue<string> q;
      if(dict.find(w1) == dict.end()){
         cout << "No solution.\n";
         return;
      }
      if(w1 == w2){
         cout << w1 << endl;
         return;
      }
      q.push(w1);
      dict[w1] = "----------";
      while(!q.empty()){
         string &w = q.front();
         FOR0(c,w.size()){
            for(char a = 'a'; a <= 'z' ; a++){
               if(w[c] == a) continue;
               string wc = w;
               wc[c] = a;
               if(dict.find(wc) != dict.end()){
                  if(wc == w2){
                     backtrace(w1,w2, w, dict);
                     return;
                  }
                  if(dict[wc].empty()){
                     dict[wc] = w;
                     q.push(wc);
                  }
               }
            }
         }
         q.pop();
      }
      cout << "No solution.\n";
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   string line;
   dict_t dict;
   while(getline(cin, line),line.size()){
      dict[line]="";
   }
   string w1,w2;
   int t = 0;
   while(cin>>w1>>w2, cin.good()){
      if(t) cout << endl;
      slv.solve(dict, w1,w2);
      t++;
   }
   return 0;
}
