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

void addEdge(VVI &g, int u, int v){
   g[u].push_back(v);
   g[v].push_back(u);
}

class Solver
{
   VI dis;
   VI disFull; //CC numbers for original graph. CC numbers start from 1. 0 = undiscovered yet.
   VI ccpop; //population of CCs in original graph
   /**
    * nv: incremented for each new verted discovered
    */
   void dfs(const VVI &g, int u, int cc, int &nv)
   {
      if(dis[u]){
         cout << "Already dis: " << u << endl;
         assert(0);
         return;
      }
      nv++;
      dis[u] = cc;
      FOR0(vi, g[u].size()){
         int v = g[u][vi];
         if(!dis[v]){
            dfs(g,v,cc, nv);
         }
      }
   }
   bool connectedWithout(const VVI &g, int i){
      int nc = g.size();
      dis.clear();
      dis.resize(nc, 0);
      dis[i] = INT_MAX;
      //Find another vertex originally in same CC as i. Run DFS from there and compare CC population to population of same CC in original graph.
      FOR0(j,nc){
         if( i == j) continue;
         if(disFull[i] == disFull[j]){
            //j originally in same CC as i
            int nv = 0;
            dfs(g, j, disFull[j], nv);
            return nv == ccpop[disFull[j]]-1;
         }
      }
      return true; //no one else in same CC
   }
   public:
   void solve(const VVI &g, VI &pts)
   {
      int nc = g.size();
      dis.clear();
      dis.resize(nc, 0);
      int cc = 0;
      ccpop.push_back(0); //some junk at index 0
      FOR0(i, nc){
         if(!dis[i]){
            int nv = 0;
            dfs(g, i, ++cc, nv);
            ccpop.push_back(nv);
         }
      }
      disFull = dis;
      FOR0(i, nc){
         if(!connectedWithout(g, i)){
            pts.push_back(i);
         }
      }
   }
};

class namesorter
{
   VS names;
   public:
   namesorter(const VS &names) : names(names) {}
   bool operator()(int a, int b){
      return names[a] < names[b];
   }
};

int main(int argc, char **argv)
{
   int t = 0;
   while(true){
      Solver slv;
      int nc;
      cin >> nc;
      if(!nc) return 0;
      if(t) cout << endl;
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
      cout << "City map #" << 1+t << ": " << pts.size() << " camera(s) found\n";
      sort(pts.begin(), pts.end(), namesorter(carr));
      VS cams;
      FOR0(i, pts.size()){
         cout << carr[pts[i]] << endl;
      }
      t++;
   }
   return 0;
}
