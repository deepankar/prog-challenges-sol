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
   public:
/*   void solve(int n)
   {
      VI v(n+1);
      int w = 0;
      v[w++] = 1;
      v[w++] = 1;
      v[w++] = 2;
      v[w++] = 2;
      int i = 3;
      bool done = false;
      while(w < n+1 && !done){
         cout <<i<<" : " << w <<"-" << (w+v[i]-1) << "(" << v[i] <<")\n";
         FOR0(j, v[i]){
            if(w == n+1){
               done = true;
               break;
            }
            v[w++] = i;
         }
         i++;
      }
      cout << v.back() << endl;
   }
*/
   int solve2(int n)
   {
      if(n == 1) return 1;
      VI ic(1);
      ic.push_back(1);
      ic.push_back(2);
      ic.push_back(4);
      while(ic.back() < n){
         int k = ic.size()-1;
         VI::const_iterator it = upper_bound(ic.begin(), ic.end(), k);
         assert(it != ic.end());
         assert(it != ic.begin());
         it--;
         int fk = it-ic.begin();
//         cout <<(k+1)<<" += " << fk << " " <<  (ic.back() + fk) <<"\n";
         ic.push_back(ic.back() + fk);
      }
      return n == ic.back()? ic.size()-1 : ic.size()-2 ;
   }
};

int main(int argc, char **argv)
{
   int n;
   while(cin >> n, cin.good() && n){
      Solver slv;
//      slv.solve(n);
      cout << slv.solve2(n) << endl;
   }
   return 0;
}
