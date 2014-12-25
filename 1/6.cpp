//passed
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
   int solve(unsigned short *ram)
   {
      unsigned short regs[100];
      memset(regs, 0, sizeof(regs));
      int n = 1;
      int pc = 0;
      while(ram[pc] != 100){
         int code = ram[pc]/100;
         int d = (ram[pc]/10)%10;
         int s = ram[pc]%10;
         bool pcset = false;
         //cout << pc << endl;
         switch(code){
            case 2:
            regs[d] = s;
            break;
            case 3:
            regs[d] =(regs[d] + s) % 1000;
            break;
            case 4:
            regs[d] = (regs[d] * s) % 1000;
            break;
            case 5:
            regs[d] = regs[s];
            break;
            case 6:
            regs[d] = (regs[d] + regs[s]) % 1000;
            break;
            case 7:
            regs[d] = (((int)regs[d])*((int)regs[s])) % 1000;
            break;
            case 8:
            {
               int addr = regs[s];
               regs[d] = ram[addr];
            }
            break;
            case 9:
            {
               int addr = regs[s];
               ram[addr] = regs[d];
            }
            break;
            case 0:
            if(regs[s] != 0){
               pc = regs[d];
               pcset = true;
            }
            break;
         }
         if(!pcset){
            pc++;
         }
         n++;
      }
      return n;
   }
};

int main(int argc, char **argv)
{
	Solver s;
	int n;
      cin >> n;
      string line;
      getline(cin,line);
      getline(cin,line);
      FOR0(i, n){
         unsigned short *ram = (unsigned short *) calloc(1000, sizeof(unsigned short));
         int p = 0;
         while(cin.good() && (getline(cin, line), !line.empty())){
            ram[p++] = atoi(line.c_str());
         }
         if(i != 0) cout << endl;
         cout << s.solve(ram) << endl;
         free(ram);
      }
	return 0;
}
