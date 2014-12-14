/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2013 Leandro Nini <drfiemost@users.sourceforge.net>
 * Copyright 2007-2010 Antti Lankila
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "parameters.h"

static double randomNextDouble()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

static float GetRandomValue()
{
    const float t = 1.f - (float) randomNextDouble() * 0.9f;
    return (randomNextDouble() > 0.5) ? 1.f / t : t;
}

static void Optimize(const std::vector<int> &reference, int wave, char chip)
{
    Parameters bestparams;
    switch (chip)
    {
    // 6581 R2
    case 'B':
        switch (wave)
        {
        case 3:
            // current score 3756
            bestparams.bias = 0.0204265f;
            bestparams.pulsestrength = 0.00479534f;
            bestparams.topbit = 9.47298e-23f;
            bestparams.distance = 4.51741e-19f;
            bestparams.stmix = 1.67553e-18f;
            break;
        case 5:
            // current score 6990
            bestparams.bias = 0.87429f;
            bestparams.pulsestrength = 1.0945f;
            bestparams.topbit = 1.02086f;
            bestparams.distance = 0.0205134f;
            bestparams.stmix = 2.41493e-20f;
            break;
        case 6:
            // current score 0
            bestparams.bias = 0.885907f;
            bestparams.pulsestrength = 1.5435f;
            bestparams.topbit = 1.00121e-30f;
            bestparams.distance = 0.00732082f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 506
            bestparams.bias = 1.43802e+12f;
            bestparams.pulsestrength = 1.37792e-20f;
            bestparams.topbit = 1.1408e-31f;
            bestparams.distance = 4.87454e+13f;
            bestparams.stmix = 0.346381f;
            break;
        }
        break;
    case 'C':
        switch (wave)
        {
        case 3:
            // current score 16456
            bestparams.bias = 0.0130142f;
            bestparams.pulsestrength = 7.68501e-16f;
            bestparams.topbit = 4.11629e-06f;
            bestparams.distance = 2.02978e-16f;
            bestparams.stmix = 0.00170112f;
            break;
        case 5:
            // current score 71364
            bestparams.bias = 0.91347f;
            bestparams.pulsestrength = 0.15633f;
            bestparams.topbit = 1.05786f;
            bestparams.distance = 4.72298f;
            bestparams.stmix = 7.23535e-06f;
            break;
        case 6:
            // current score 9971
            bestparams.bias = 0.905186f;
            bestparams.pulsestrength = 3.42315f;
            bestparams.topbit = 1.78614f;
            bestparams.distance = 0.0199135f;
            bestparams.stmix = 0.000204912f;
            break;
        case 7:
            // current score 3300
            bestparams.bias = 0.834368f;
            bestparams.pulsestrength = 0.00202743f;
            bestparams.topbit = 0.917633f;
            bestparams.distance = 5.67906f;
            bestparams.stmix = 0.24304f;
            break;
        }
        break;
    case 'D':
        switch (wave)
        {
        case 3:
            // current score 2740
            bestparams.bias = 0.987103f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 37.294f;
            bestparams.stmix = 0.783281f;
            break;
        case 5:
            // current score 18404
            bestparams.bias = 0.888048f;
            bestparams.pulsestrength = 2.26606f;
            bestparams.topbit = 0.99697f;
            bestparams.distance = 0.0422943f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 18839
            bestparams.bias = 0.886823f;
            bestparams.pulsestrength = 2.35161f;
            bestparams.topbit = 1.77758f;
            bestparams.distance = 0.0236612f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 428
            bestparams.bias = 0.928903f;
            bestparams.pulsestrength = 1.4555f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.0791919f;
            bestparams.stmix = 0.905484f;
            break;
        }
        break;
    case 'E':
        switch (wave)
        {
        case 3:
            // current score 721
            bestparams.bias = 0.957552f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.80014f;
            bestparams.stmix = 0.698112f;
            break;
        case 5:
            // current score 5552
            bestparams.bias = 0.916105f;
            bestparams.pulsestrength = 1.93374f;
            bestparams.topbit = 1.00139f;
            bestparams.distance = 0.0211841f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 12
            bestparams.bias = 0.935096f;
            bestparams.pulsestrength = 2.64471f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.00538012f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 120
            bestparams.bias = 0.900499f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    case 'F':
        switch (wave)
        {
        case 3:
            // current score 5504
            bestparams.bias = 6.14399e+13f;
            bestparams.pulsestrength = 8.36431e-08f;
            bestparams.topbit = 5.47766e+07f;
            bestparams.distance = 1.06191e+17f;
            bestparams.stmix = 3.55025e-19f;
            break;
        case 5:
            // current score 7350
            bestparams.bias = 0.899719f;
            bestparams.pulsestrength = 1.84894f;
            bestparams.topbit = 1.00198f;
            bestparams.distance = 0.0189322f;
            bestparams.stmix = 1.22962e-13f;
            break;
        case 6:
            // current score 594
            bestparams.bias = 0.886979f;
            bestparams.pulsestrength = 1.60832f;
            bestparams.topbit = 6.09942e-13f;
            bestparams.distance = 0.00943791f;
            bestparams.stmix = 8.956e-26f;
            break;
        case 7:
            // current score 392
            bestparams.bias = 0.977412f;
            bestparams.pulsestrength = 6.9983e-09f;
            bestparams.topbit = 2.09026e-17f;
            bestparams.distance = 1.01218e+29f;
            bestparams.stmix = 0.323086f;
            break;
        }
        break;
    case 'G':
        switch (wave)
        {
        case 3:
            // current score 1741
            bestparams.bias = 0.880592f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.327589f;
            bestparams.stmix = 0.611491f;
            break;
        case 5:
            // current score 11418
            bestparams.bias = 0.892438f;
            bestparams.pulsestrength = 2.00995f;
            bestparams.topbit = 1.00392f;
            bestparams.distance = 0.0298894f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 21096
            bestparams.bias = 0.863292f;
            bestparams.pulsestrength = 1.69239f;
            bestparams.topbit = 1.12637f;
            bestparams.distance = 0.0335683f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 78
            bestparams.bias = 0.930481f;
            bestparams.pulsestrength = 1.42322f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.0481732f;
            bestparams.stmix = 0.752611f;
            break;
        }
        break;
    case 'H':
        switch (wave)
        {
        case 3:
            // current score 2022
            bestparams.bias = 0.270037f;
            bestparams.pulsestrength = 9091.84f;
            bestparams.topbit = 2.49412e-25f;
            bestparams.distance = 2.24133e+32f;
            bestparams.stmix = 1.17664e-15f;
            break;
        case 5:
            // current score 9884
            bestparams.bias = 0.868414f;
            bestparams.pulsestrength = 6.44083e-17f;
            bestparams.topbit = 1.0791f;
            bestparams.distance = 0.0279448f;
            bestparams.stmix = 3.10603e-16f;
            break;
        case 6:
            // current score 3218
            bestparams.bias = 0.873627f;
            bestparams.pulsestrength = 0.0260634f;
            bestparams.topbit = 0.00377936f;
            bestparams.distance = 1.60806e-38f;
            bestparams.stmix = 1.04798e-11f;
            break;
        case 7:
            // current score 254
            bestparams.bias = 1.05047e+13f;
            bestparams.pulsestrength = 76.4306f;
            bestparams.topbit = 8.28681e-28f;
            bestparams.distance = 5.33129e-11f;
            bestparams.stmix = 4.9946e-08f;
            break;
        }
        break;
    case 'I':
        switch (wave)
        {
        case 3:
            // current score 770
            bestparams.bias = 0.93203f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.67192f;
            bestparams.stmix = 0.672783f;
            break;
        case 5:
            // current score 10455
            bestparams.bias = 0.883997f;
            bestparams.pulsestrength = 1.38194f;
            bestparams.topbit = 1.03288f;
            bestparams.distance = 0.0311792f;
            bestparams.stmix = 1.66796e-08f;
            break;
        case 6:
            // current score 10138
            bestparams.bias = 1.f;
            bestparams.pulsestrength = 4.09952f;
            bestparams.topbit = 0.000786858f;
            bestparams.distance = 1.43601f;
            bestparams.stmix = 6.66445e-06f;
            break;
        case 7:
            // current score 298
            bestparams.bias = 0.551408f;
            bestparams.pulsestrength = 3.71902f;
            bestparams.topbit = 5.91504e-14f;
            bestparams.distance = 37.6346f;
            bestparams.stmix = 0.0768828f;
            break;
        }
        break;
    case 'J':
        switch (wave)
        {
        case 3:
            // current score 4044
            bestparams.bias = 2.97547e+21f;
            bestparams.pulsestrength = 4.11288e-19f;
            bestparams.topbit = 2.30225f;
            bestparams.distance = 3.4145e+06f;
            bestparams.stmix = 3.1358e-34f;
            break;
        case 5:
            // current score 20546
            bestparams.bias = 0.839637f;
            bestparams.pulsestrength = 0.00379872f;
            bestparams.topbit = 1.05988f;
            bestparams.distance = 9.31775e-30f;
            bestparams.stmix = 3.01504e-19f;
            break;
        case 6:
            // current score 14224
            bestparams.bias = std::numeric_limits<float>::infinity();
            bestparams.pulsestrength = 2.8719e-08f;
            bestparams.topbit = 6.01553e+20f;
            bestparams.distance = 3.61473e-07f;
            bestparams.stmix = 4.81204e-05f;
            break;
        case 7:
            // current score 182
            bestparams.bias = 0.103622f;
            bestparams.pulsestrength = 2.98572e-20f;
            bestparams.topbit = 3.92594e-20f;
            bestparams.distance = 2.40353f;
            bestparams.stmix = 0.0116062f;
            break;
        }
        break;
    case 'K':
        switch (wave)
        {
        case 3:
            // current score 3093
            bestparams.bias = 0.000740039f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 2.9555e+19f;
            bestparams.distance = 3.16264e-35f;
            bestparams.stmix = 1.15585e-40f;
            break;
        case 5:
            // current score 27124
            bestparams.bias = 0.798028f;
            bestparams.pulsestrength = 6.4301e-08f;
            bestparams.topbit = 1.01926f;
            bestparams.distance = 0.016763f;
            bestparams.stmix = 0.0576813f;
            break;
        case 6:
            // current score 4832
            bestparams.bias = 2.13344f;
            bestparams.pulsestrength = 33.9207f;
            bestparams.topbit = 1.29393e-11f;
            bestparams.distance = 0.000620133f;
            bestparams.stmix = 0.0815829f;
            break;
        case 7:
            // current score 612
            bestparams.bias = 1.74613e+17f;
            bestparams.pulsestrength = 3.37442e+11f;
            bestparams.topbit = 2.48451e-26f;
            bestparams.distance = 0.000137998f;
            bestparams.stmix = 1.80741e-17f;
            break;
        }
        break;
    case 'L':
        switch (wave)
        {
        case 3:
            // current score 6392
            bestparams.bias = 2.59233e-06f;
            bestparams.pulsestrength = 1.9726e+16f;
            bestparams.topbit = 0.00235043f;
            bestparams.distance = 0.00116764f;
            bestparams.stmix = 3.33487e-07f;
            break;
        case 5:
            // current score 30194
            bestparams.bias = 1.18627f;
            bestparams.pulsestrength = 7.80049f;
            bestparams.topbit = 0.936008f;
            bestparams.distance = 0.0245902f;
            bestparams.stmix = 1.14416e-08f;
            break;
        case 6:
            // current score 12506
            bestparams.bias = 0.781217f;
            bestparams.pulsestrength = 1.66282e-08f;
            bestparams.topbit = 3.25438e-09f;
            bestparams.distance = 3.24208e-18f;
            bestparams.stmix = 4.40874e-07f;
            break;
        case 7:
            // current score 354
            bestparams.bias = 0.886003f;
            bestparams.pulsestrength = 0.551403f;
            bestparams.topbit = 7.29995e-17f;
            bestparams.distance = 0.0106613f;
            bestparams.stmix = 0.678726f;
            break;
        }
        break;
    case 'M':
        switch (wave)
        {
        case 3:
            // current score 2932
            bestparams.bias = std::numeric_limits<float>::infinity();
            bestparams.pulsestrength = 2.60149e+33f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.16306e-29f;
            bestparams.stmix = 0.000329613f;
            break;
        case 5:
            // current score 57192
            bestparams.bias = 4.85522e+16f;
            bestparams.pulsestrength = 16140.6f;
            bestparams.topbit = 4.73438e-16f;
            bestparams.distance = 0.075333f;
            bestparams.stmix = 1.37251e-36f;
            break;
        case 6:
            // current score 0
            bestparams.bias = 0.838245f;
            bestparams.pulsestrength = 0.631283f;
            bestparams.topbit = 8.84546e-08f;
            bestparams.distance = 0.0016716f;
            bestparams.stmix = 0.0312176f;
            break;
        case 7:
            // current score 0
            bestparams.bias = 0.983546f;
            bestparams.pulsestrength = 2.37318f;
            bestparams.topbit = 2.20815e-18f;
            bestparams.distance = 0.228075f;
            bestparams.stmix = 0.674089f;
            break;
        }
        break;
    // 6581 R3
    case 'N':
        switch (wave)
        {
        case 3:
            // current score 1128
            bestparams.bias = 0.981693f;
            bestparams.pulsestrength = 0.00152375f;
            bestparams.topbit = 2.31019e-25f;
            bestparams.distance = 9.52977f;
            bestparams.stmix = 0.727679f;
            break;
        case 5:
            // current score 32024
            bestparams.bias = 2.13986f;
            bestparams.pulsestrength = 24.8638f;
            bestparams.topbit = 0.556354f;
            bestparams.distance = 0.0361677f;
            bestparams.stmix = 9.4514e-10f;
            break;
        case 6:
            // current score 1672
            bestparams.bias = 0.899357f;
            bestparams.pulsestrength = 1.97051f;
            bestparams.topbit = 8.15184e-13f;
            bestparams.distance = 0.013821f;
            bestparams.stmix = 5.98098e-06f;
            break;
        case 7:
            // current score 906
            bestparams.bias = 0.000214995f;
            bestparams.pulsestrength = 6.38261e-17f;
            bestparams.topbit = 2.30117e-07f;
            bestparams.distance = 165.841f;
            bestparams.stmix = 6.29022e-06f;
            break;
        }
        break;
    case 'O':
        switch (wave)
        {
        case 3:
            // current score 6008
            bestparams.bias = 0.000813789f;
            bestparams.pulsestrength = 2.50114e+11f;
            bestparams.topbit = 1.41542e-35f;
            bestparams.distance = 3.39815f;
            bestparams.stmix = 8.55924e-05f;
            break;
        case 5:
            // current score 19242
            bestparams.bias = 0.807401f;
            bestparams.pulsestrength = 5.62415e-11f;
            bestparams.topbit = 1.0585f;
            bestparams.distance = 0.0285973f;
            bestparams.stmix = 0.0052592f;
            break;
        case 6:
            // current score 25914
            bestparams.bias = 3.21163e+11f;
            bestparams.pulsestrength = 0.00255188f;
            bestparams.topbit = 2.00957e-07f;
            bestparams.distance = 3.65521e+12f;
            bestparams.stmix = 6.78149e-20f;
            break;
        case 7:
            // current score 1122
            bestparams.bias = 1.69364e+10f;
            bestparams.pulsestrength = 0.00118232f;
            bestparams.topbit = 2.54963e-22f;
            bestparams.distance = 3.58493e+10f;
            bestparams.stmix = 4.85502e-14f;
            break;
        }
        break;
    case 'P':
        switch (wave)
        {
        case 3:
            // current score 2108
            bestparams.bias = 0.884009f;
            bestparams.pulsestrength = 3.21717e+08f;
            bestparams.topbit = 7.60741e-28f;
            bestparams.distance = 0.248893f;
            bestparams.stmix = 0.69366f;
            break;
        case 5:
            // current score 7590
            bestparams.bias = 0.90557f;
            bestparams.pulsestrength = 2.50365f;
            bestparams.topbit = 0.994497f;
            bestparams.distance = 0.0125821f;
            bestparams.stmix = 1.98396e-11f;
            break;
        case 6:
            // current score 44171
            bestparams.bias = std::numeric_limits<float>::infinity();
            bestparams.pulsestrength = 4.84518e+14f;
            bestparams.topbit = 4.59198e+08f;
            bestparams.distance = 1.0866e-10f;
            bestparams.stmix = 6.73737e-11f;
            break;
        case 7:
            // current score 941
            bestparams.bias = 0.706561f;
            bestparams.pulsestrength = 6.75693f;
            bestparams.topbit = 9.06785e-06f;
            bestparams.distance = 87749.7f;
            bestparams.stmix = 0.119848f;
            break;
        }
        break;
    case 'Q':
        switch (wave)
        {
        case 3:
            // current score 1190
            bestparams.bias = 0.943629f;
            bestparams.pulsestrength = 4.89634e+06f;
            bestparams.topbit = 0.00145126f;
            bestparams.distance = 1.3357f;
            bestparams.stmix = 0.702617f;
            break;
        case 5:
            // current score 12262
            bestparams.bias = 0.950206f;
            bestparams.pulsestrength = 3.21227f;
            bestparams.topbit = 0.973889f;
            bestparams.distance = 0.0167537f;
            bestparams.stmix = 0.000671572f;
            break;
        case 6:
            // current score 26080
            bestparams.bias = 8.72824e+11f;
            bestparams.pulsestrength = 1.15339e+11f;
            bestparams.topbit = 0.000211345f;
            bestparams.distance = 1.38165e+24f;
            bestparams.stmix = 7.03726e-11f;
            break;
        case 7:
            // current score 1058
            bestparams.bias = 2.60127e+09f;
            bestparams.pulsestrength = 3.69258f;
            bestparams.topbit = 1.18285e+11f;
            bestparams.distance = 1.22993e+31f;
            bestparams.stmix = 4.13322e-07f;
            break;
        }
        break;
    // 6581 R4
    case 'R':
        switch (wave)
        {
        case 3:
            // current score 12982
            bestparams.bias = 1.06512e-08f;
            bestparams.pulsestrength = 4.15713e-14f;
            bestparams.topbit = 1.68259e-11f;
            bestparams.distance = 5.15214e+16f;
            bestparams.stmix = 9.95657e-10f;
            break;
        case 5:
            // current score 38377
            bestparams.bias = 1.00364f;
            bestparams.pulsestrength = 4.28478f;
            bestparams.topbit = 0.890698f;
            bestparams.distance = 0.0602224f;
            bestparams.stmix = 1.f;
            break;
        case 6:
            // current score 28630
            bestparams.bias = 0.77661f;
            bestparams.pulsestrength = 9.08503e-17f;
            bestparams.topbit = 8.07304e-13f;
            bestparams.distance = 0.00417374f;
            bestparams.stmix = 0.00052424f;
            break;
        case 7:
            // current score 3100
            bestparams.bias = 3.82796e+10f;
            bestparams.pulsestrength = 1.01524e-10f;
            bestparams.topbit = 8.51465e-06f;
            bestparams.distance = 0.0107765f;
            bestparams.stmix = 3.36492e-10f;
            break;
        }
        break;
    // 8580
    case 'V':
        switch (wave)
        {
        case 3:
            // current score 5339
            bestparams.bias = 0.979807f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.990736f;
            bestparams.distance = 9.22678f;
            bestparams.stmix = 0.824563f;
            break;
        case 5:
            // current score 18507
            bestparams.bias = 0.909646f;
            bestparams.pulsestrength = 2.03944f;
            bestparams.topbit = 0.958471f;
            bestparams.distance = 0.175597f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 16763
            bestparams.bias = 0.918338f;
            bestparams.pulsestrength = 2.41154f;
            bestparams.topbit = 0.927047f;
            bestparams.distance = 0.171891f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 3199
            bestparams.bias = 0.984532f;
            bestparams.pulsestrength = 1.53602f;
            bestparams.topbit = 0.961933f;
            bestparams.distance = 3.46871f;
            bestparams.stmix = 0.803955f;
            break;
        }
        break;
    // 6582
    case 'W':
        switch (wave)
        {
        case 3:
            // current score 6648
            bestparams.bias = 0.986102f;
            bestparams.pulsestrength = 0.f; // 458120
            bestparams.topbit = 0.995344f;
            bestparams.distance = 8.64964f;
            bestparams.stmix = 0.957502f;
            break;
        case 5:
            // current score 24634
            bestparams.bias = 0.906838f;
            bestparams.pulsestrength = 2.23245f;
            bestparams.topbit = 0.958234f;
            bestparams.distance = 0.205228f;
            bestparams.stmix = 0.0475253f;
            break;
        case 6:
            // current score 22693
            bestparams.bias = 0.889691f;
            bestparams.pulsestrength = 1.64253f;
            bestparams.topbit = 0.977121f;
            bestparams.distance = 0.293443f;
            bestparams.stmix = 0.f; // 4.65769e-013
            break;
        case 7:
            // current score 5182
            bestparams.bias = 0.956644f;
            bestparams.pulsestrength = 1.50249f;
            bestparams.topbit = 0.943326f;
            bestparams.distance = 0.520891f;
            bestparams.stmix = 0.956507f;
            break;
        }
        break;
    default:
        break;
    }

    int bestscore = bestparams.Score(wave, reference, true, 4096 * 255);
    std::cout << "# initial score " << bestscore << std::endl << std::endl;

    Parameters p;
    for (;;)
    {
        bool changed = false;
        while (! changed)
        {
            for (int i = Parameters::BIAS; i <= Parameters::STMIX; i++)
            {
                const float oldValue = bestparams.GetValue(i);
                float newValue = oldValue;
                if (randomNextDouble() > 0.5)
                {
                    newValue *= GetRandomValue();

                    if ((i == Parameters::STMIX) && (newValue > 1.f))
                    {
                        newValue = 1.f;
                    }
                }

                p.SetValue(i, newValue);
                changed = changed || oldValue != newValue;
            }
        }
        const int score = p.Score(wave, reference, false, bestscore);
        /* accept if improvement */
        if (score <= bestscore)
        {
            bestparams = p;
            p.reset();
            bestscore = score;
            std::cout << "# current score " << score << std::endl << bestparams.toString() << std::endl << std::endl;
        }
    }
}

static std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::istringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

static std::vector<int> ReadChip(int wave, char chip)
{
    std::cout << "Reading chip: " << chip << std::endl;
    std::vector<int> result;

    std::ostringstream fileName;
    fileName << "sidwaves/WAVE" << wave << ".CSV";
    std::ifstream ifs(fileName.str().c_str(), std::ifstream::in);
    std::string line;
    while (getline(ifs, line).good())
    {
        std::vector<std::string> values = split(line, ',');
        result.push_back(atoi(values[chip - 'A'].c_str()));
    }
    return result;
}

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage " << argv[0] << " <waveform> <chip>" << std::endl;
        exit(-1);
    }

    const int wave = atoi(argv[1]);
    assert(wave == 3 || wave == 5 || wave == 6 || wave == 7); 

    const char chip = argv[2][0];
    assert(chip >= 'A' && chip <= 'Z');

    std::vector<int> reference = ReadChip(wave, chip);

#ifndef NDEBUG
    for (std::vector<int>::iterator it = reference.begin(); it != reference.end(); ++it)
        std::cout << (*it) << std::endl;
#endif

    srand(time(0));

    Optimize(reference, wave, chip);
}
