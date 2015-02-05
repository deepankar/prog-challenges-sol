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

class Turtle
{
   public:
   int w, st;
   Turtle(int w, int st) : w(w), st(st) {}
};

ostream &operator<<(ostream &os, const Turtle &t)
{
   os << '(' << t.st << ',' <<t.w << ')';
   return os;
}

class carry_desc{
   public:
   bool operator()(const Turtle &t1, const Turtle &t2) const
   {
      int c1 = t1.st - t1.w;
      int c2 = t2.st - t2.w;
      if(c1 != c2){
         return c1 > c2;
      }
      return t1.w > t2.w;
   }
};

class Solver
{
   const vector<Turtle> *tt;
   typedef map<PI, int> cache_t;
   cache_t cache;
   //start = startIndex
   int mx(int start, int maxw)
   {
      if(start >= tt->size() || maxw <= 0) return 0;
      cache_t::iterator it = cache.find(PI(start, maxw));
      if(it != cache.end()){
         return it->second;
      }
      int without = mx(start+1, maxw);
      int res = without;
      int st_w = (*tt)[start].w;
      int st_st = (*tt)[start].st;
      int with = -1;
      if(st_w <= maxw){
         int new_maxw = min(maxw - st_w, st_st - st_w);
         with = mx(start+1, new_maxw);
         if(1+with > res){
            res = 1+with;
         }
      }
      cache[PI(start,maxw)] = res;
      return res;
   }
   public:
   int solve(vector<Turtle> &tt)
   {
      this->tt = &tt;
      cache.clear();
      sort(tt.begin(), tt.end(), carry_desc());
      return mx(0, INT_MAX);
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int w, st;
   vector<Turtle> tt;
   while(cin >> w >> st && cin.good()){
      tt.push_back(Turtle(w,st));
   }
   cout << slv.solve(tt) << endl;
   return 0;
}
