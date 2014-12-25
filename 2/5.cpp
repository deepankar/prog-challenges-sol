//passed
#include <limits.h>
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
#include <sstream>
using namespace std;
typedef vector<int> VI;
typedef unsigned char uchar;
typedef vector<int> VC;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)
#if 0
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
   return;
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

class Deck
{
   uchar cards[53];
   static VS strs;
   public:
   Deck()
   {
      FOR0(i, 53){
         cards[i] = i;
      }
   }
   void shuffle(const VC &sh)
   {
      INS
      pv(sh);
      uchar *newc = new uchar[53];
      for(int npos=1;npos<=52;npos++){
         assert(sh[npos] <=52);
         newc[npos] = cards[sh[npos]];
      }
      memcpy(cards, newc, sizeof(cards));
      delete [] newc;
   }
   void pint()
   {
      INS
      if(!strs.size()){
         const char *suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
         const char *vals[] = {
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "Jack",
            "Queen",
            "King",
            "Ace"
         };
         FOR0(s, 4){
            FOR0(v, 13){
               strs.push_back(vals[v] + string(" of ") + suits[s]);
            }
         }
      }
      for(int p=1; p<=52; p++){
         cout << strs[cards[p]-1] << endl;
      }
   }
};
VS Deck::strs;

class Solver
{
   Deck transform(const vector<VC> &shuffles, const VC &ops)
   {
      INS
//      cout << "ops: ";  pv(ops);
      pv(shuffles[1]);
      pv(shuffles[2]);
      if(shuffles.size() > 3)
         pv(shuffles[3]);
      Deck d;
      FOR0(i, ops.size()){
         d.shuffle(shuffles[ops[i]]);
      }
      return d;
   }
	public:
   void solve(const vector<VC> &shuffles, const VC &ops)
   {
      INS
      Deck d = transform(shuffles, ops);
      d.pint();
   }
};

int main(int argc, char **argv)
{
	Solver slv;
	int tt;
   string line;
   cin >> tt;
   FOR0(t,tt){
      vector<VC> shuffles;
      shuffles.push_back(VC());
      if(t) cout << endl;
      int ns;
      cin >> ns;
      FOR0(s, ns){
         VC sh;
         sh.push_back(0);
         FOR0(i, 52){
            int x;
            cin >> x;
            sh.push_back(x);
         }
         shuffles.push_back(sh);
      }
      getline(cin, line);
      VC ops;
      while(getline(cin, line), line.size() && cin.good()){
         int x;
         istringstream ss(line);
         ss >> x;
         ops.push_back(x);
      }
      //cout << line << endl;
      //cout << s.solve() << "\n";
      slv.solve(shuffles, ops);
   }
	return 0;
}
