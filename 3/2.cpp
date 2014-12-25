#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef pair<int,int> PI;
typedef vector<string> VS;
typedef vector<bool> VB;
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
   PI find(const string &w)
   {
      FOR0(r,m){
         FOR0(c,n){
            if(match(r,c,w)){
               return PI(r+1,c+1);
            }
         }
      }
      assert(0);
      return PI(-1,-1);
   }
   bool match(int r, int c, const string &w)
   {
      FOR0(dir,8){
         if(match(r,c,w,dir)){
            return true;
         }
      }
      return false;
   }
   bool match(int r, int c, const string &w, int dir)
   {
      FOR0(i, w.size()){
         if(!in(r,c)){
            return false;
         }
         if(g[r][c] != w[i]) return false;
         next(r,c,dir);
      }
      return true;
   }
   bool in(int r, int c)
   {
      return r>=0 && c>=0 && r<m && c < n;
   }
   static void next(int &r, int &c, int dir)
   {
      assert(dir < 8);
      static int dr[] = {1,1,0,-1,-1,-1,0,1};
      static int dc[] = {0,1,1,1,0,-1,-1,-1};
      r += dr[dir];
      c += dc[dir];
   }
	public:
   char g[50][50];
   int m,n;
   void solve(const string &w)
   {
      PI l = find(w);
      cout << l.first << ' ' << l.second << endl;
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   string line;
   getline(cin, line);
   getline(cin, line);
   FOR0(t,tt){
      if(t) cout << endl;
      Solver slv;
      cin >> slv.m >> slv.n;
      FOR0(l,slv.m){
         string r;
         cin >> r;
         std::transform(r.begin(), r.end(), r.begin(), ::tolower);
         assert(slv.n == r.size());
         memcpy(slv.g[l], r.c_str(), r.size());
      }
      int k;
      cin >> k;
      FOR0(i, k){
         string w;
         cin >> w;
         std::transform(w.begin(), w.end(), w.begin(), ::tolower);
         slv.solve(w);
      }
   }
	return 0;
}
