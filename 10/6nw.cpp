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
typedef vector<vector<int> > VVI;

#define FOR0(i, n) for(int i = 0; i < n; i++)

#if 1
#define C cout
#else
#include <fstream>
ofstream C("/dev/null");
#endif

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

void addEdge(VVI &g, int u, int v){
   g[u].push_back(v);
   g[v].push_back(u);
}

class Solver
{
   VB dis;
   void dfs(
   bool connectedWithout(const VVI &g, int i){
      int nc = g.size();
      dis.clear();
      dis.resize(nc, false);
      dis[i] = true;
      dfs(g, 0);
      return find(dis.begin(), dis.end(), false) == dis.end();
   }
   public:
   void solve(const VVI &g, VI &pts)
   {
      int nc = g.size();
      FOR0(i, nc){
         if(!connectedWithout(g, i)){
            pts.push_back(i);
         }
      }
   }
};

int main(int argc, char **argv)
{
   int t = 0;
   while(true){
      t++;
      Solver slv;
      if(t) cout << endl;
      int nc;
      cin >> nc;
      map<string,int> c;
      VS carr(nc);
      FOR0(i,nc){
         string x;
         cin >> x;
         c[x] = i;
         carr[i] = x;
      }
      VVI g(nc);
      int nr;
      cin >> nr;
      FOR0(i, nr){
         string c1, c2;
         cin >> c1 >> c2;
         int ci1 = c[c1];
         int ci2 = c[c2];
         addEdge(g, ci1, ci2);
      }
      VI pts;
      slv.solve(g, pts);
   }
   return 0;
}
