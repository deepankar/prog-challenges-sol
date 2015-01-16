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
typedef vector<vector<int> > VVI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Cube
{
   public:
   u8 c[6];
};

class Solver
{
   class CP
   {
      public:
      int cube;
      int topface;
      const vector<Cube> *cubes;
      CP(const vector<Cube> &cubes, int i): cube(i/6), topface(i % 6), cubes(&cubes) {}

      int topColor() const
      {
         return(*cubes)[cube].c[topface];
      }
      int bottomColor() const
      {
         int bface;
         int odd = topface & 1;
         bface = odd? topface -1 : topface+1;
         return(*cubes)[cube].c[bface];
      }
   };
   /**
   * can u be placed over v?
   */
   bool compatible(const vector<Cube> &cubes, int u, int v){
      CP uu(cubes,u);
      CP vv(cubes,v);
      return uu.bottomColor() == vv.topColor();
   }
   public:
   void solve(const vector<Cube> &cubes)
   {
      const char*facename[] = {"front","back","left","right","top","bottom"};

      int nc = cubes.size();
      VVI g(nc*6);
      FOR0(u, nc*6){
         for(int v = 6*(1+u/6); v < nc*6; v++){
            if(compatible(cubes,u,v)){
               g[u].push_back(v);
            }
         }
      }
      VI mxlen(nc*6,1);
      VI predv(nc*6,-1);
      for(int u = 0; u < 6*nc-6; u++){
         VI &e = g[u];
         FOR0(ei, e.size()){
            int v = e[ei];
            if(mxlen[v] < mxlen[u]+1){
               mxlen[v] = mxlen[u]+1;
               predv[v] = u;
            }
         }
      }
      int mx = 0;
      int mxi = -1;
      FOR0(i, 6*nc){
         if(mx < mxlen[i]){
            mx = mxlen[i];
            mxi = i;
         }
      }
      int v = mxi;
      stack<int> tower;
      while(v != -1){
         tower.push(v);
         v = predv[v];
      }
      assert(tower.size() == mx);
      cout << mx << endl;
      while(!tower.empty()){
         int v = tower.top(); tower.pop();
         CP cp(cubes,v);
         cout << (cp.cube+1) << " " << facename[cp.topface]<< endl;
      }
   }
};

int main(int argc, char **argv)
{
   int t = 0;
   while(true){
      Solver slv;
      int nc;
      cin >> nc;
      if(nc == 0) return 0;
      vector<Cube> cubes(nc);
      for(int i = 0; i < nc; i++){
         FOR0(f, 6){
            int x;
            cin >> x;
            cubes[i].c[f] = x;
         }
      }
      if(t) cout <<endl;
      t++;
      cout <<"Case #" << t << endl;
      slv.solve(cubes);
   }
   return 0;
}
