#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
   string norm(const string &s)
   {
      char nxt='a';
      string r;
      r.resize(s.size());
      FOR0(i,s.size()){
         if(s[i] == ' ') {r[i] = ' '; continue;}
         FOR0(j, i){
            if(s[j] == s[i]){
               r[i] = r[j];
               break;
            }
         }
         if(!r[i]){
            r[i] = nxt++;
         }
      }
      return r;
   }
   public:
   void solve(const VS &l)
   {
      const char *qk="the quick brown fox jumps over the lazy dog";
      string qk_norm = norm(qk);
      char dt[26];
      memset(dt, 0, sizeof(dt));
      FOR0(i, l.size()){
         if(l[i].size() == strlen(qk) && norm(l[i]) == qk_norm){
            FOR0(c, l[i].size()){
               if(qk[c] == ' ') continue;
               //decryption: l[i][c] -> qk[c]
               dt[l[i][c]-'a'] = qk[c];
            }
            break;
         }
      }
      if(dt[0]){
         FOR0(i, l.size()){
            FOR0(c, l[i].size()){
               if(l[i][c] == ' ') {cout << ' '; continue;}
               cout << dt[l[i][c]-'a'];
            }
            cout << endl;
         }
      }else{
         cout << "No solution.\n";
      }
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   string line;
   getline(cin, line);
   getline(cin, line);
   FOR0(t,tt){
      if(t) cout << endl;
      VS l;
      while(getline(cin, line), line.size() && cin.good()){
         l.push_back(line);
      }
      slv.solve(l);
   }
   return 0;
}
