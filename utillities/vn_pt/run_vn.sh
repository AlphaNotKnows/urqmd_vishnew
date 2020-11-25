#!bin/bash
#rm EVENTS_HEADFILE.dat
rm M_for_*.txt
rm Qn_*.txt
rm -rf ../Outputbyevent
mkdir ../Outputbyevent
rm -rf ../results
mkdir ../results
if [ !-e "vn_format" ] ; then
  g++ vn_format.cpp -o vn_format -O3 -std=c++11
fi
./vn_format
pid = 106
python3 compute-v2
python3 compute-v2a
python3 compute-apois $pid
python3 compute-bpois $pid
python3 vn_pt_total.py $pid


