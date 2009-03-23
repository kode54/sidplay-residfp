#!/usr/bin/python

import math, random
from scipy.fftpack import fft
from scipy import array
import sys

def pow2db(x):
    if x < 1e-9:
        return -99
    return math.log(x) / math.log(10) * 10

Vi  = 0
Vbp = 0
Vlp = 0
Vhp = 0

w0 = 0.0628318
distortion_rate = 1
res = 15
cft = 1.2e-4
lp_bp = 1.414

def do_filter_combined():
    Q = 0.707 + res / 15.
    global Vi, Vbp, Vlp, Vhp
    lpleak = Vi * res / 15. / 10.

    sum = Vlp + Vbp + Vhp
    Vlp += (sum - Vlp) * cft
    Vbp += (sum - Vbp) * cft
    Vhp += (sum - Vhp) * cft

    Vlp -= w0 * (Vbp - lpleak) * lp_bp
    Vbp -= w0 * Vhp
    Vhp = (Vbp + lpleak) / Q - Vlp / lp_bp - Vi * distortion_rate
    
FFT_SIZE = 8192
def main_fft(variable, level):
    global Vi

    if (variable == 'Vlp'):
        def func(): return Vlp
    elif (variable == 'Vbp'):
        def func(): return Vbp
    elif (variable == 'Vhp'):
        def func(): return Vhp
    elif (variable == 'sum'):
        def func(): return Vlp + Vbp + Vhp
    elif (variable == 'sum_lo'):
        def func(): return Vlp + Vbp
    elif (variable == 'sum_hi'):
        def func(): return       Vbp + Vhp
    elif (variable == 'sum_notch'):
        def func(): return Vlp       + Vhp
    else:
        raise RuntimeError, "Unknown variable: %s" % variable

    tmp1 = []
    Vi = level;
    for x in range(FFT_SIZE):
        do_filter_combined()
        tmp1.append(func())
        Vi = 0

    accum1 = abs(fft(tmp1) / level) ** 2

    for i in range(len(accum1)/2):
        print "%f %f" % (float(i) / FFT_SIZE * 1000000, pow2db(accum1[i]))

def main():
    return main_fft(sys.argv[1], float(sys.argv[2]))

if __name__ == '__main__':
    main()
