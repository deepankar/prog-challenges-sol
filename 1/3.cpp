#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
typedef vector<int> VI;
typedef vector<string> VS;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
	public:
   int solve(VI &in)
   {
      sort(in.begin(), in.end(), std::greater<int>());
      int sum = 0;
      FOR0(i, in.size()){
         sum += in[i];
         //cout << "ini=" << in[i] << " sum=" << sum << endl;
      }
      int avg = sum/in.size();
      int rmd = sum % in.size();
      //cout << "rmd=" << rmd << endl;
      //cout << "avg=" << avg << endl;
      int trans = 0;
      for(int i = 0; i < in.size() && in[i] > avg; i++){
         int mine = avg + (i<rmd? 1 : 0);
         trans += in[i] - mine;
         //cout << "mine=" << mine << " giving " << trans << endl;
      }
      return trans;
   }
};

int main(int argc, char **argv)
{
	Solver s;
	int n;
	while(cin.good()){

      cin >> n;
      if(!cin.good() || n == 0){
         return 0;
      }
      VI spends;
      FOR0(i, n){
         int d,c;
         scanf("%d.%d", &d, &c);
         //cout <<"read " << (int)(f*100) << endl;
         spends.push_back(d*100+c);
      }
      int transfer = s.solve(spends);
      cout << "$";
      std::cout.precision(2);
      std::cout << fixed;
      cout << ((double)transfer)/100 << endl;
      cin.unsetf(ios_base::floatfield);
      //cout << line << endl;
		//cout << s.solve() << "\n";
      //s.solve();
	}
	return 0;
}
