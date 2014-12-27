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
typedef vector<PI> VPI;
typedef vector<string> VS;
typedef long long int lint;
typedef unsigned long long int luint;

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
   public:
   void solve(const VPI &j)
   {
      int n = j.size();
      VB done(n, false);
      VI res;
      int F = 0;
      FOR0(i, n) F+=j[i].second;
      //Essentially sorting by Fine/Time
      FOR0(it, n){
         double mn = -1;
         int mni = -1;
         FOR0(i, n){
            if(done[i]) continue;
            double f = ((double)j[i].second)/j[i].first;
            if(f > mn){
               mn = f;
               mni = i;
            }
         }
         res.push_back(mni);
         done[mni] = true;
         F -= j[mni].second;
      }
      FOR0(i, n){
         if(i) cout << ' ';
         cout << 1+res[i];
      }
      cout << endl;
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   FOR0(t,tt){
      if(t) cout << endl;
      int n;
      cin >> n;
      VPI j;
      FOR0(i, n){
         int t,f;
         cin >> t >> f;
         j.push_back(PI(t,f));
      }
      slv.solve(j);
   }
   return 0;
}
