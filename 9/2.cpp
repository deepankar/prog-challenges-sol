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

#define FOR0(i, n) for(int i = 0; i < n; i++)

class State
{
   public:
   char w[4];
   State(){}
   uint tonum() const{
      return (w[0] << 24) | (w[1] << 16) | (w[2] << 8) | w[3];
   }
   bool operator<(const State &s) const 
   {
      return tonum() < s.tonum();
   }
   bool operator==(const State &st) const
   {
      FOR0(i,4){
         if(w[i] != st.w[i])
            return false;
      }
      return true;
   }
};

istream& operator>>(istream &os, State &st)
{
   FOR0(i,4){
      int x;
      os >> x;
      st.w[i] = x;
   }
   return os;
}

class Solver
{
   typedef enum {WHITE, GREY, BLACK} Color;
   typedef map<State, int> l_t;
   l_t l;
   void findNextMoves(const State &s, const vector<State> &forb, vector<State> &nxt)
   {
      FOR0(w, 4){
         for(int d = -1; d <=1; d+=2){
            State nx = s;
            nx.w[w] += d;
            if(nx.w[w] == -1 ){
               nx.w[w] = 9;
            }else if(nx.w[w] == 10){
               nx.w[w] = 0;
            }
            if(l.find(nx) == l.end() && find(forb.begin(), forb.end(), nx) == forb.end()){
               nxt.push_back(nx);
            }
         }
      }
   }
   public:
   int solve(const State &st, const State &end, const vector<State> &forb)
   {
      queue<State> q;
      q.push(st);
      l[st] = 0;
      while(!q.empty()){
         State s = q.front(); q.pop();
         if(s == end){
            return l[s];
         }
         vector<State> nxt;
         findNextMoves(s, forb, nxt);
         FOR0(i, nxt.size()){
            q.push(nxt[i]);
            l[nxt[i]] = l[s] + 1;
         }
      }
      return -1;
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   FOR0(t,tt){
      Solver slv;
      State st, end;
      cin >> st >> end;
      int n;
      cin >> n;
      vector<State> forb(n);;
      FOR0(i,n){
         cin >> forb[i];
      }
      cout << slv.solve(st, end, forb) << endl;
   }
   return 0;
}
