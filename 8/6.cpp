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

class Solver
{
   uint rules;
   int n;
   bool found;
   static bool bit(luint st, int k)
   {
      return (st >> k) & 1;
   }
   static void bitset(luint &st, int k, bool val)
   {
      luint mask = ~(1 << k);
      st = (st&mask) | (luint(val) << k);
   }
   bool IsSolution(int k){
      return k == n+2;
   }
   void findNextMoves(luint pst, int k, const luint st, bool *m)
   {
      int stbit = bit(st, k-2);
      FOR0(i,2){
         luint move = (i << 2) | (bit(pst, k-1) << 1) | bit(pst, k-2);
         int newbit = bit(rules, move);
         if(k < n || newbit != stbit){
            m[i] = newbit == stbit;
         }else{
            //k = n OR n+1
            //first two bits should be same as the last two, because of circular neighbors. Otherwise it's not a valid prev-state.
            m[i] = i == bit(pst, k-n);
         }
      }
   }
   // pst is of size n+2, with the circular neighbor added in the beginning and end
   void backtrace(luint pst, int k, const luint st)
   {
      if(IsSolution(k)){
         found = true;
         return;
      }
      bool m[2];
      findNextMoves(pst, k, st, m);
      FOR0(i,2){
         if(found) return;
         bitset(pst, k, i);
         if(m[i]) backtrace(pst, k+1, st);
      }
   }
   public:
   void solve(uint rules, const string &st)
   {
      this->rules = rules;
      found = false;
      n = st.size();
      luint state = 0;
      //st.back() - '0';
      FOR0(i, st.size()){
         state = (state << 1) | (st[i] - '0');
      }
   //   state = (state << 1) | (st[0] - '0');
      luint pst = 0;
      FOR0(i,4){
         pst = (i << n) | i;
         backtrace(pst, 2, state);
      }
      if(found){
         cout << "REACHABLE\n";
      }else{
         cout <<"GARDEN OF EDEN\n";
      }
   }
};

int main(int argc, char **argv)
{
   string line;
   while(getline(cin, line), line.size() && cin.good()){
      istringstream ss(line);
      uint rules;
      int n;
      string st;
      ss >> rules;
      ss >> n;
      ss >> st;
      Solver slv;
      slv.solve(rules, st);
   }
   return 0;
}
