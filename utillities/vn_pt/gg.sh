#!bin/bash
#rm EVENTS_HEADFILE.dat
rm M_for_*.txt
rm Qn_*.txt
python3 compute-v2
python3 compute-v2a
python3 compute-apois
python3 compute-bpois
python3 vn_pt_total.py


