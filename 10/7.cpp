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
typedef vector<vector<bool> > VVB;

#define FOR0(i, n) for(int i = 0; i < n; i++)

//Bipartite matching using network flow.

class Solver
{
   VB sdis, tdis; //discovered
   virtual bool findSTPath(const VI &sflows,const VI &tflows,const VI &scaps,const VI &tcaps, const VVB &gp, VI &path)
   {
      sdis.assign(sflows.size(), false);
      tdis.assign(tflows.size(), false);
      return _findSTPath(sflows, tflows, scaps, tcaps, gp, path);
   }
   virtual bool _findSTPath(const VI &sflows,const VI &tflows,const VI &scaps,const VI &tcaps, const VVB &gp, VI &path)
   {
      if(path.size() == 0){
         FOR0(i, sflows.size()){
            if(sflows[i] < scaps[i]){
               path.push_back(i);
               if(_findSTPath(sflows, tflows, scaps, tcaps, gp, path)) {
                  return true;
               }
               path.pop_back();
            }
         }
      }else if(path.size() % 2 == 1){
         //team -> table
         int team = path.back();
         sdis[team] = true;
         FOR0(i, gp[team].size()){
            if(gp[team][i] && !tdis[i]){
               path.push_back(i);
               if(_findSTPath(sflows, tflows, scaps, tcaps, gp, path)){
                  return true;
               }
               path.pop_back();
            }
         }
      }else{
         int table = path.back();
         tdis[table] = true;
         if(tflows[table] < tcaps[table]){
            //table->sink
            return true;
         }
         //table -> team
         FOR0(i, sflows.size()){
            if(!gp[i][table] &&!sdis[i]){ //back edge exists
               path.push_back(i);
               if(_findSTPath(sflows, tflows, scaps, tcaps, gp, path)){
                  return true;
               }
               path.pop_back();
            }
         }
      }
      return false;
   }
   void done(const VVB &g)
   {
      cout << "1\n";
      FOR0(i, g.size()){
         bool f = true;
         FOR0(j, g[0].size()){
            if(!g[i][j]){ //back edge => positive flow
               if(!f){
                  cout << ' ';
               }
               cout << j+1;
               f = false;
            }
         }
         cout << endl;
      }
   }
   public:
   void solve(const VI &scaps,const VI &tcaps)
   {
      int m = scaps.size();
      int n = tcaps.size();
      int expflow = accumulate(scaps.begin(), scaps.end(), 0);
      VI sflows(m);
      VI tflows(n);
      VVB gp(m, vector<bool>(n, true));
      while(true){
         VI path;
         if(!findSTPath(sflows, tflows,scaps, tcaps, gp, path)){
            int maxflow = accumulate(sflows.begin(), sflows.end(), 0);
            assert(maxflow <= expflow);
            if(maxflow != expflow){
               cout << "0\n";
            }else{
               done(gp);
            }
            return;
         }
         sflows[path.front()]++;
         tflows[path.back()]++;
         for(int i = 0; i < path.size()-1; i++){
            if(i%2==0){
               //team
               int team = path[i];
               int table = path[i+1];
               assert(gp[team][table]);
               gp[team][table] = false; //convert fwd edge to back edge
            }else{
               int table = path[i];
               int team = path[i+1];
               assert(!gp[team][table]);
               gp[team][table] = true; //convert back edge to fwd edge
            }
         }
      }
   }
};

int main(int argc, char **argv)
{
   while(true){
      Solver slv;
      int m,n;
      cin >> m >> n;
      if(!m) return 0;
      VI scaps(m);
      VI tcaps(n);
      FOR0(i,m){
         int x;
         cin >> x;
         scaps[i] = x;
      }
      FOR0(i,n){
         int x;
         cin >> x;
         tcaps[i] = x;
      }
      slv.solve(scaps, tcaps);
   }
   return 0;
}
