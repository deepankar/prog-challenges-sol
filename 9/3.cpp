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

class Edge
{
   public:
   int u, v, w;
   Edge(int u, int v, int w) : u(u), v(v), w(w) {}
   Edge() {}
   bool operator>(const Edge &e) const
   {
      return w > e.w;
   }
};

ostream& operator<<(ostream &os, const Edge &e)
{
   os << e.u << "->" << e.v << "(" << e.w << ")";
   return os;
}

class Graph{
   class EdgeT
   {
      public:
         int v;
         int w;
         EdgeT(int v, int w) : v(v), w(w) {}
         EdgeT() {}
   };
   vector<vector<EdgeT> > g;
   public:
   Graph(int n){
      g.resize(n+1);
   }
   void addEdge(const Edge &e){
      addEdge(e.u, e.v, e.w);
   }
//undirected
   void addEdge(int u, int v, int w){
      EdgeT et(v,w);
      g[u].push_back(et);
      et.v = u;
      g[v].push_back(et);
   }
   bool reachable(int v, int u)
   {
      vector<bool> dis(g.size(), false);
      return reachable(dis, v, u);
   }
   bool reachable(vector<bool> &dis, int v, int u)
   {
      vector<EdgeT> &ed = g[u];
      FOR0(e, ed.size()){
         if(v == ed[e].v) return true;
         if(!dis[ed[e].v]){
            dis[ed[e].v] = true;
            if(reachable(dis, v, ed[e].v)){
               return true;
            }
         }
      }
      return false;
   }
   friend ostream& operator<<(ostream &os, const Graph &g);
};

ostream& operator<<(ostream &os, const Graph &g)
{
   for(int i = 1; i < g.g.size(); i++){
      cout << i << ":";
      const vector<Graph::EdgeT> &ed = g.g[i];
      FOR0(e, ed.size()){
         const Graph::EdgeT &et = ed[e];
         cout << " " << et.v << "(" << et.w << ")";
      }
      cout << endl;
   }
   return os;
}

class Solver
{
   public:
   int solve(vector<Edge> &e, int numc, int c1, int c2, int nt)
   {
      if(c1 == c2) return 0;
      Graph x(numc);
      sort(e.begin(), e.end(), std::greater<Edge>());
      int i = 0;
      int lastw = -1;
      while(!x.reachable(c2, c1)){
         /*if(i >= e.size()){
            cout << c1 << " ----> " << c2 << endl;
            cout << x;
            assert(0);
         }*/
         lastw = e[i].w;
//         cout << "Adding Edge " << e[i] << endl;
         x.addEdge(e[i++]);
      }
      int trips = nt/(lastw-1);
      if(nt % (lastw-1)){
         trips++;
      }
      return trips;
   }
};

int main(int argc, char **argv)
{
   int t=0;
   while(true){
      Solver slv;
      int n,r;
      cin >> n >> r;
      if(n==0) return 0;
      vector<Edge> e(r);
      FOR0(i, r){
         cin >> e[i].u >> e[i].v >> e[i].w;
 //        cout << "+edge " << e[i] << endl;
      }
      int st, end, nt;
      cin >> st >> end >> nt;
      int trips = slv.solve(e, n, st, end, nt);
      cout << "Scenario #" << (1+t) << endl;
      cout << "Minimum Number of Trips = " << trips << endl;
      cout << endl;
      t++;
   }
   return 0;
}
