#!bin/bash
#rm EVENTS_HEADFILE.dat
rm M_for_*.txt
rm Qn_*.txt
rm -rf ../Outputbyevent
mkdir ../Outputbyevent
if [ !-e "vn_format" ] ; then
  g++ vn_format.cpp -o vn_format -O3 -std=c++11
fi
./vn_format
python compute-v2
python compute-v2a
python compute-apois
python compute-bpois
python vn_pt_total.py


