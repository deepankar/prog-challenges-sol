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

static const int BLANK = 10;
class Solver
{
   int nb,n;
   int nsol;

   bool IsSolution(int k, int bused){
      return bused == nb;
   }

   void findNextMoves(int k, char *nxt, int &nnxt, int bused, int hused)
   {
      nnxt = 0;
      if(bused + 2*n-k-1 > nb){
         nxt[nnxt++] = BLANK;
      }

      int kk = min(k, 2*n-2-k);
      for(int i = -kk; i <=kk; i+=2){
         if(!(hused & (1 << (8+i)))){
            nxt[nnxt++] = i;
         }
      }
   }

   void backtrace(int k, int bused, int hused)
   {
      char nxt[9];
      int nnxt;
      findNextMoves(k, nxt, nnxt, bused, hused);
//      C << "k=" << k << " nnxt=" << nnxt << " hused=" << std::hex << hused << std::dec << endl;
      FOR0(i,nnxt){
         int newbused = nxt[i] != BLANK;
         int hnew = (nxt[i] == BLANK)? 0 : (1<<(8+nxt[i]));
         if(IsSolution(k+1, bused+newbused)){
         //   C << "Sol ";
         //   st.print(k+1);
            nsol++;
         }else{
            backtrace(k+1, bused+newbused, hused|hnew);
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
      backtrace(0, 0, 0);
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
