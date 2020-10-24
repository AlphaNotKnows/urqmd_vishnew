#!/bin/bash
#cd integrated_vn/
#nohup ./compute-vn_pt-event_ARPs ../RESULTS/* 0 &

#nohup ./compute-vn_pt-event_RPs ../RESULTS/* 1 &

#cd ../
#cd pt_sprectra
#nohup ./compute_pt_spectra_event_RPs ../RESULTS/* 0 &
#cd ../
#cd vn_sp
nohup ./compute-vn_pt-event_ARPs ../../res/* 0 &
nohup ./compute-vn_pt-event_BPOIs ../../res/* 1 &
nohup ./compute-vn_pt-event_POIs ../../res/* 2 &
nohup ./compute-vn_pt-event_RPs ../../res/* 3 &
