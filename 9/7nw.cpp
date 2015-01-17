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

class Train
{
   public:
   int c1, c2;
   int dep, arr;
};

ostream& operator<<(ostream&os, const Train &t)
{
   os <<t.c1 << "->" << t.c2 << " " << t.dep << "-" << t.arr;
   return os;
}
class TD
{
   public:
      const Train *t;
      int d;
      TD(const Train *t, int d) : t(t), d(d) {}
      TD() : t(NULL), d(-1) {}
      int normArrivalTime() const
      {
         return t->arr + d*24 + (t->arr < t->dep? 24: 0);
      }
      bool operator<(const TD &td) const
      {
         return normArrivalTime() > td.normArrivalTime();
      }
};
ostream& operator<<(ostream &os, const TD &td) {
   os << *td.t << " : " << td.normArrivalTime();
   return os;
}

class Solver
{
   vector<string> cityNames;
   VI best;
   public:
   int cityNum(const string &name)
   {
      VS::iterator it = find(cityNames.begin(), cityNames.end(), name);
      if(it != cityNames.end()){
         return it - cityNames.begin();
      }
      cityNames.push_back(name);
      return cityNames.size() - 1;
   }

   int solve(const vector<Train> &trains, const string & city1, const string & city2)
   {
      if(cityNames.empty()){
         return -1;
      }
      best.resize(cityNames.size(), INT_MAX);
      int c1 = cityNum(city1);
      int c2 = cityNum(city2);
      VVI out(cityNames.size()); //outgoing trains
      FOR0(i, trains.size()){
         const Train &t = trains[i];
         out[t.c1].push_back(i);
      }
      best[c1] = 0;
      priority_queue<TD> q;
      FOR0(ti, out[c1].size()){
         int t = out[c1][ti];
         TD x(&trains[t],0);
//         cout << "00AddQ: " << x << endl;
         best[trains[t].c2] = x.normArrivalTime();
         q.push(x);
      }
      while(!q.empty()){
         const TD p = q.top(); q.pop();
         //cout << "Popped: " << p << endl;
         if(p.t->c2 == c2){
            return p.d - (p.t->arr > p.t->dep? 1:0);
         }
         VI &tr = out[p.t->c2];
         FOR0(ti, tr.size()){
            const Train &t = trains[tr[ti]];
            int plus = p.t->arr >  t.dep;
            if(p.t->arr < p.t->dep) plus++;
            TD x(&t, p.d + plus);
            int arr = x.normArrivalTime();
            if(arr < best[t.c2]){
               best[t.c2] = arr;
               //cout << "AddQ: " << x << endl;
               q.push(x);
            }else{
               //cout << "Discard: "<< x << endl;
            }
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
      int nr;
      cin >> nr;
      vector<Train> trains(nr);
      int validTrains = 0;
      FOR0(i, nr){
         string c1, c2;
         cin >> c1 >> c2;
         int dep, jt;
         cin >> dep >> jt;
         int arr = (jt + dep) %24;
         if(arr == 0) arr = 24;
//         if(arr < dep) arr++;
         if(dep > 6 && dep < 18) continue;
         if(arr > 6 && arr < 18) continue;
         if(dep < 12 && arr > 12) continue;
         trains[validTrains].c1 = slv.cityNum(c1);
         trains[validTrains].c2 = slv.cityNum(c2);
         trains[validTrains].dep = dep;
         trains[validTrains].arr = arr;
         validTrains++;
      }
      trains.resize(validTrains);
      string c1, c2;
      cin >> c1 >> c2;
      int nd = slv.solve(trains,c1,c2);
      cout << "Test Case " << (t+1) <<".\n";
      if(nd == -1){
         cout << "There is no route Vladimir can take.\n";
      }else{
         cout << "Vladimir needs " << nd << " litre(s) of blood.\n";
      }
   }
   return 0;
}
