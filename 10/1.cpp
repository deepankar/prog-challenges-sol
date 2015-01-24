#include <limits.h>
#include <limits>
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
typedef vector<double> VD;
typedef pair<int,int> PI;
typedef pair<double,double> PD;
typedef vector<PD> VPD;
typedef vector<vector<double> > VVD;
typedef long long int lint;
typedef unsigned long long int luint;
typedef vector<vector<int> > VVI;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
   public:
   //Prim's minimum spanning tree (MST) algo.
   //Code is with adj-matrix representation where all vertices are connected to each other directly.
   double solve(const VPD &c)
   {
      int nv = c.size();
      VVD d(c.size(), VD(c.size()));
      FOR0(i, nv){
         d[i][i] = 0;
         for(int j = i+1; j < nv; j++){
            double x = c[i].first - c[j].first;
            double y = c[i].second - c[j].second;
            d[j][i] = d[i][j] = sqrt(x*x+y*y);
         }
      }
      vector<double> est(nv);
      est[0] = 0;
      for(int i = 1; i < nv; i++){
         est[i] = numeric_limits<double>::max();
      }
      VB added(nv, false);
      int nadded = 0;
      double total = 0;
      while(nadded < nv){
         int vi = min_element(est.begin(), est.end()) - est.begin();
         nadded++;
         added[vi] = true;
         total += est[vi];
         est[vi] = numeric_limits<double>::max();
         FOR0(n, nv){ //neighbors
            if(!added[n]){
               est[n] = min(est[n], d[vi][n]);
            }
         }
      }
      return total;
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   std::cout.precision(2);
   std::cout << fixed;
   FOR0(t,tt){
      if(t) cout << endl;
      int nv;
      cin >> nv;
      VPD v(nv);
      FOR0(i,nv){
         cin >> v[i].first;  
         cin >> v[i].second;  
      }
      Solver slv;
      double l = slv.solve(v);
      cout << l << endl;
   }
   return 0;
}
