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
   int solve(const VI &l)
   {
      int mn = INT_MAX;
      for(int i = 1; i < 30000;i++){
         int s = 0;
         FOR0(j,l.size()){
            s += abs(i-l[j]);
         }
         mn = min(mn,s);
      }
      return mn;
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   FOR0(t,tt){
      int n;
      cin >> n;
      VI l;
      FOR0(i,n){
         int x;
         cin >> x;
         l.push_back(x);
      }
      cout << slv.solve(l) << endl;
   }
   return 0;
}
