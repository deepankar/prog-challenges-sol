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
typedef pair<u8,u8> PU8;
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

class Bead
{
   public:
   u8 c[2];
   u8 rightcol(int dir) const
   {
      return c[1-dir];
   }
   u8 leftcol(int dir) const
   {
      return c[dir];
   }
   bool compatible(const Bead &b2, int dir1, int dir2) const
   {
      return rightcol(dir1) == b2.leftcol(dir2);
   }
   void print(int dir) const
   {
      cout << (int)leftcol(dir) << " " << (int)rightcol(dir) << endl;
   }
};

class Solver
{
   void addEdge(VVI &g, int u, int v){
      g[u].push_back(v);
   }
   void printSt(const vector<Bead> &b, VI &p, int l)
   {
      stack<int> st;
      int i = l;
      int nr = 0;
      while(i){
         st.push(i);
         i = p[i];
         nr++;
         assert(nr < 1010);
      }
      st.push(0);
      while(!st.empty()){
         int v = st.top(); st.pop();
         b[v/2].print(v&1);
      }
   }
   public:
   void solve(const vector<Bead> &b)
   {
      int nb = b.size();
      VVI g(nb*2);
      FOR0(u, nb){
         for(int v = 0; v < nb; v++){
            if(u == v) continue;
            FOR0(d1, 2){
               FOR0(d2, 2){
                  if(b[u].compatible(b[v], d1, d2)){
//                     cout << u << ':' << d1 << " " << v << ':' << d2 << endl;
                     addEdge(g, 2*u+d1, 2*v+d2);
                  }
               }
            }
         }
      }
#if 0
      FOR0(i, 2*nb){
         cout << "===" << i << endl;
         pv(g[i]);
      }
#endif
      VI st;
      VI level(nb,-1);
      VB exp(nb, false);
      VI p(2*nb, 0);
      st.push_back(0); level[0/2] = 0;
      while(!st.empty()){
         int u = st.back(); st.pop_back();
         if(exp[u/2]) continue;
         cout << (int)b[u/2].c[0] << ' ';
         exp[u/2] = true;
         FOR0(vi, g[u].size()){
            int v = g[u][vi];
            //if(level[v/2] == -1){
            if(!exp[v/2]){
               st.push_back(v);
               level[v/2] = level[u/2] + 1;
#if 0
               cout << "v=" << v << ":" << level[v/2];
               cout << "  u=" << u << ":" << level[u/2] << endl;
#endif
               p[v] = u;
            }else if(v == 0){
//               cout << "BEdge to 0 from " << u << " level " << level[u/2] << endl;
               if(level[u/2] == nb-1){
#if 0
                  cout << " Sol " ;
                  pv(st);
                  cout << " P " ;
                  pv(p);
#endif
                  printSt(b, p, u);
                  return;
               }
            }
         }
      }
      cout << "some beads may be lost\n";
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   FOR0(t,tt){
      Solver slv;
      if(t) cout << endl;
      int n;
      cin >> n;
      vector<Bead> beads(n);
      FOR0(i,n){
         int c1, c2;
         cin >> c1 >> c2;
         beads[i].c[0] = c1;
         beads[i].c[1] = c2;
      }
      cout << "Case #"<<t+1 << endl;
      slv.solve(beads);
   }
   return 0;
}
