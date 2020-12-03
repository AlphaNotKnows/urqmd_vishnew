#!/bin/bash
#rm EVENTS_HEADFILE.dat
rm M_for_*.txt
rm Qn_*.txt
if [ -f "../Outputbyevent" ] ; then
  rm -rf ../Outputbyevent
fi
mkdir ../Outputbyevent
if [ -f "../results" ] ; then
  rm -rf ../results
fi
mkdir ../results
if [ ! -x "./vn_format" ] ; then
  echo "compile vn_format"
  g++ vn_format.cpp -o vn_format -O3 -std=c++11
fi
echo "begin vn_format"
./vn_format
export pid=$1
echo "begin compute-v2"
python3 compute-v2
echo "begin compute-v2a"
python3 compute-v2a
echo "begin compute-apois"
python3 compute-apois $pid
echo "begin compute-bpois"
python3 compute-bpois $pid
echo "begin vn_pt_total"
python3 vn_pt_total.py $pid


