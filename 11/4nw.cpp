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
typedef vector<lint> VLI;
typedef vector<vector<int> > VVI;
typedef vector<vector<lint> > VVLI;

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

class Solver
{
   int64_t mod(int64_t x, int64_t n){
      return (x + n)%n;
   }

   //lastrow = row for the last column
   void getPath(const VVI &parent, int lastrow, VI &path)
   {
      int nc = parent.size();
      path.clear();
      path.push_back(lastrow);
      if(nc > 1){
         for(int c = nc - 2; c >= 0; c--){
            //decide row for column c
            int r = parent[c+1][path.back()];
            path.push_back(r);
         }
      }
   }
   bool lex_smaller(const VI &v1, const VI &v2){
      assert(v1.size() == v2.size());
      for(int i = v1.size()-1; i >= 0; i--){
         if(v1[i] != v2[i]){
            return v1[i] < v2[i];
         }
      }
      return false;
   }
   class Path
   {
      public:
      VU8 path;
      Path(int nc){
         path.resize(nc);
      }
      bool operator<(const Path &p2) const
      {
         assert(path.size() == p2.path.size());
         for(int i = path.size()-1; i >= 0; i--){
            if(path[i] != p2.path[i]){
               return path[i] < p2.path[i];
            }
         }
         return false;
      }
   };
   public:
   void solve(const VVI &mat)
   {
      int nr = mat.size();
      int nc = mat[0].size();
      VLI sp1(nr);
      VLI sp2(nr);
      VLI *sp[] = {&sp1, &sp2};
      VVI parent(nc, VI(nr));
      vector<Path> paths1(nr, Path(nc));
      vector<Path> paths2(nr, Path(nc));
      vector<Path> *paths[] = {&paths1, &paths2};
      FOR0(r, nr){
         (*sp[0])[r] = mat[r][0];
      }
      for(int c = 1; c < nc; c++){
         for(int r = 0; r < nr; r++){
            int pos_r[] = {mod(r-1, nr), r, mod(r+1, nr)}; //possibilities of prev row
            sort(pos_r, pos_r+3);
            int64_t mn = LLONG_MAX;
            Path minpath(nc);
            int bestrow = -1;
            FOR0(ri, 3){
               if((*sp[0])[pos_r[ri]] <= mn){
                  if((*sp[0])[pos_r[ri]] == mn){
                     const Path &p1 = (*paths[0])[pos_r[ri]];
                     if(!(p1 < minpath))
                        continue;
                  }
                  mn = (*sp[0])[pos_r[ri]];
                  minpath = (*paths[0])[pos_r[ri]];
                  parent[c][r] = pos_r[ri];
                  bestrow = pos_r[ri];
               }
            }
            (*sp[1])[r] = mn + mat[r][c];
            minpath.path[c-1] = bestrow;
            (*paths[1])[r] = minpath;
         }
         swap(sp[0], sp[1]);
         swap(paths[0], paths[1]);
      }
      int64_t mn = LLONG_MAX;
      int mnr = -1;
      VI path;
      FOR0(r, nr){
         if((*sp[0])[r] <= mn){
            VI newpath;
            getPath(parent, r, newpath);
            if((*sp[0])[r] == mn){
               if(!lex_smaller(newpath, path)){
                  //cout << " cont ";
                  //pv(newpath);
                  continue;
               }
            }
            mn = (*sp[0])[r];
            mnr = r;
            //pv(newpath);
            path = newpath;
         }
      }
      bool first = true;
      while(!path.empty()){
         if(!first){
            cout << ' ';
         }else{
            first = false;
         }
         cout << 1+path.back();
         path.pop_back();
      }
      cout << endl << mn << endl;
   }
};

int main(int argc, char **argv)
{
   int nr, nc;
   while(cin >> nr >> nc, cin.good()){
      Solver slv;
      VVI mat(nr, VI(nc));
      FOR0(r, nr){
         FOR0(c, nc){
            cin >> mat[r][c];
         }
      }
      slv.solve(mat);
   }
   return 0;
}
