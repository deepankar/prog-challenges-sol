#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NDEBUG 1
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

#if 0
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

static const int BLANK = 10;
class State
{
   char h[15];//max
   public:
   State() /*: nbsh(0)*/
   {
      memset(h, BLANK, sizeof(h));
   }
   void set(int i, char val){
      h[i] = val;
   }
/*   int GetNumBish(int k) const
   {
      int nbsh = 0;
      FOR0(i,k){
         nbsh += (h[i] != BLANK);
      }
      return nbsh;
   }*/
   bool find(int k, int v) const
   {
      FOR0(i, k){
         if(h[i] == v) return true;
      }
      return false;
   }
   void print(int k){
      FOR0(i, k){
         C << (int)h[i] << ' ';
      }
      C << endl;
   }
};

class Solver
{
   int nb,n;
   int nsol;

   bool IsSolution(const State &st, int k, int bused){
      return bused == nb;
   }

   void findNextMoves(const State &st, int k, char *nxt, int &nnxt, int bused)
   {
      nnxt = 0;
      if(bused + 2*n-k-1 > nb){
         nxt[nnxt++] = BLANK;
      }

      int kk = min(k, 2*n-2-k);
      for(int i = -kk; i <=kk; i+=2){
         if(!st.find(k, i)){
            nxt[nnxt++] = i;
         }
      }
   }

   void backtrace(State &st, int k, int bused)
   {
      char nxt[9];
      int nnxt;
      findNextMoves(st, k, nxt, nnxt, bused);
//      C << "k=" << k << " nnxt=" << nnxt << endl;
      FOR0(i,nnxt){
         st.set(k, nxt[i]);
         int newbused = nxt[i] != BLANK;
         if(IsSolution(st,k+1, bused+newbused)){
//            C << "Sol ";
//            st.print(k+1);
            nsol++;
         }else{
            backtrace(st, k+1, bused+newbused);
         }
      }
   }
   public:
   int solve(int n, int nb)
   {
      this->nb = nb;
      this->n = n;
      nsol=0;
      if(nb > 2*n -1){
         return 0;
      }
      if(nb == 0) return 1;
      State st;
      backtrace(st, 0, 0);
      return nsol;
   }
};

int main(int argc, char **argv)
{
   int n,k;
   while(cin >> n >> k, n){
      Solver slv;
      cout << slv.solve(n,k) << endl;
   }
   return 0;
}
