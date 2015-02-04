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

class Elephant
{
   public:
   int w, iq, i;
   Elephant(int w, int iq, int i) : w(w), iq(iq), i(i) {}
};

ostream & operator<<(ostream &os, const Elephant &e)
{
   os << '(' << e.i << ':' << e.w <<',' << e.iq;
   return os;
}
class Solver
{
   class wsort{
      public:
      bool operator()(const Elephant &p1, const Elephant &p2)
      {
         if(p1.w != p2.w){
            return p1.w < p2.w;
         }else{
            return p1.iq > p2.iq;
         }
      }
   };
   template<class T> void LCS(const vector<T> &s1, const vector<T> &s2, vector<T> &res)
   {
      VVI lcs(s1.size()+1, VI(s2.size()+1));
      FOR0(i, s1.size()){
         lcs[i][0] = 0;
      }
      FOR0(j, s2.size()){
         lcs[0][j] = 0;
      }
      int i1, i2;
      for(i1 = 1; i1 <= s1.size(); i1++){
         for(i2 = 1; i2 <= s2.size(); i2++){
            if(s1[i1-1] == s2[i2-1]){
               lcs[i1][i2] = 1 + lcs[i1-1][i2-1];
            }else{
               int o1 = lcs[i1-1][i2];
               int o2 = lcs[i1][i2-1];
               lcs[i1][i2] = max(o1,o2);
            }
         }
      }
      i1 = s1.size();
      i2 = s2.size();
      stack<T> st;
      while(i1 && i2){
         if(lcs[i1][i2] == 1 + lcs[i1-1][i2-1]){
            st.push(s1[i1-1]);
            i1--;
            i2--;
         }else if(lcs[i1][i2] == lcs[i1-1][i2]){
            i1--;
         }else{
            i2--;
         }
      }
      while(!st.empty()){
         res.push_back(st.top());
         st.pop();
      }
   }
   public:
   void solve(vector<Elephant> &el)
   {
      sort(el.begin(), el.end(), wsort());
      VI iqs(el.size());
      FOR0(i, el.size()){
         iqs[i] = el[i].iq;
      }
      VI iq_sorted = iqs;
      sort(iq_sorted.begin(), iq_sorted.end(), std::greater<int>());
      VI result; //LCS result
      LCS(iq_sorted, iqs, result);
#if 0
      pv(el);
      cout << "IsIQ "; pv(iq_sorted);
      cout << "WSIQ "; pv(iqs);
      cout << "LCSIQ "; pv(result);
#endif
      int j=0;
      int lastw = -1, lastiq = -1;
      VI res; //indices
      FOR0(i, el.size() && j < result.size()){
         if(el[i].iq == result[j]){
            if(lastw != el[i].w && lastiq != el[i].iq){
               res.push_back(el[i].i);
               lastw = el[i].w;
               lastiq = el[i].iq;
            }
            j++;
         }
      }
      cout << res.size() << endl;
      FOR0(i, res.size()){
         cout << res[i] << endl;
      }
   }
};

int main(int argc, char **argv)
{
   int w, iq;
   vector<Elephant> el;
   Solver slv;
   int i = 1;
   while(cin >> w >> iq && cin.good()){
      el.push_back(Elephant(w,iq,i));
      i++;
   }
   slv.solve(el);
   return 0;
}
