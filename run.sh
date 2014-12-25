#!/bin/bash
test=$1
./a.out < ../samples/${test}.inp > tmp.out
diff ../samples/${test}.oup tmp.out
cp ../samples/${test}.oup exp.out
