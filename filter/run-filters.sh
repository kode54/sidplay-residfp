#!/bin/sh

WAV="../noisetest/noise-nf.wav"

./simulate-filter.py Vhp 1 > Vhp.txt
./simulate-filter.py Vbp 1 > Vbp.txt
./simulate-filter.py Vlp 1 > Vlp.txt
./simulate-filter.py sum 1 > sum.txt
./simulate-filter.py sum_lo 1 > sum_lo.txt
./simulate-filter.py sum_hi 1 > sum_hi.txt
./simulate-filter.py sum_notch 1 > sum_notch.txt

#./simulate-filter.py Vhp $WAV > wav-Vhp.txt
#./simulate-filter.py Vbp $WAV > wav-Vbp.txt
#./simulate-filter.py Vlp $WAV > wav-Vlp.txt
#./simulate-filter.py sum $WAV > wav-sum.txt
#./simulate-filter.py sum_lo $WAV > wav-sum_lo.txt
#./simulate-filter.py sum_hi $WAV > wav-sum_hi.txt
#./simulate-filter.py sum_notch $WAV > wav-sum_notch.txt

