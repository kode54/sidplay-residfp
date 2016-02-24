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
            // current score 6862
            bestparams.bias = 0.875107f;
            bestparams.pulsestrength = 1.15164f;
            bestparams.topbit = 1.01654f;
            bestparams.distance = 0.0203668f;
            bestparams.stmix = 0.f;
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
    // 6581 R2 (odd)
    case 'C':
        switch (wave)
        {
        case 3:
            // current score 12420
            bestparams.bias = 0.764782f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 1.80768e-027f;
            bestparams.distance = 0.f;
            bestparams.stmix = 0.432898f;
            break;
        case 5:
            // current score 65788
            bestparams.bias = 0.91347f;
            bestparams.pulsestrength = 0.764542f;
            bestparams.topbit = 1.01631f;
            bestparams.distance = 4.61499f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 9199
            bestparams.bias = 0.877514f;
            bestparams.pulsestrength = 2.76415f;
            bestparams.topbit = 1.80281f;
            bestparams.distance = 0.0235206f;
            bestparams.stmix = 0.f;
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
    // 6581 R2 (odd)
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
            // current score 18340
            bestparams.bias = 0.888048f;
            bestparams.pulsestrength = 2.23835f;
            bestparams.topbit = 1.f;
            bestparams.distance = 0.0424011f;
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
    // 6581 R2
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
    // 6581 R2
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
    // 6581 R2 (odd)
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
    // 6581 R2
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
            // current score 8918
            bestparams.bias = 0.86434f;
            bestparams.pulsestrength = 4.4868e-026f;
            bestparams.topbit = 1.07048f;
            bestparams.distance = 0.0292144f;
            bestparams.stmix = 0.011214f;
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
    // 6581 R2
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
            // current score 9953
            bestparams.bias = 0.883997f;
            bestparams.pulsestrength = 1.31797f;
            bestparams.topbit = 1.03254f;
            bestparams.distance = 0.0375651f;
            bestparams.stmix = 4.7419e-020f;
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
    // 6581 R2
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
    // 6581 R2
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
            // current score 18810
            bestparams.bias = 0.809616f;
            bestparams.pulsestrength = 0.00781541f;
            bestparams.topbit = 1.03968f;
            bestparams.distance = 0.0279025f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 3602
            bestparams.bias = 0.938313f;
            bestparams.pulsestrength = 2.9597f;
            bestparams.topbit = 1.33806e-012f;
            bestparams.distance = 0.00624875f;
            bestparams.stmix = 4.44042e-005f;
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
    // 6581 R2
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
            // current score 13328
            bestparams.bias = 0.922333f;
            bestparams.pulsestrength = 2.60989f;
            bestparams.topbit = 0.986813f;
            bestparams.distance = 0.0332785f;
            bestparams.stmix = 0.00711337f;
            break;
        case 6:
            // current score 9320
            bestparams.bias = 0.79238f;
            bestparams.pulsestrength = 6.03516e-011f;
            bestparams.topbit = 1.26137e-007f;
            bestparams.distance = 0.0118249f;
            bestparams.stmix = 1.64637e-007f;
            break;
        case 7:
            // current score 316
            bestparams.bias = 0.886393f;
            bestparams.pulsestrength = 1.01745f;
            bestparams.topbit = 0.0536235f;
            bestparams.distance = 0.0476043f;
            bestparams.stmix = 0.453603;
            break;
        }
        break;
    // 6581 R2
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
    // 6581 R2
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
            // current score 26520
            bestparams.bias = 2.13986f;
            bestparams.pulsestrength = 26.1706f;
            bestparams.topbit = 0.579717f;
            bestparams.distance = 0.028143f;
            bestparams.stmix = 3.84897e-015f;
            break;
        case 6:
            // current score 1606
            bestparams.bias = 0.916321f;
            bestparams.pulsestrength = 2.32213f;
            bestparams.topbit = 8.47258e-013f;
            bestparams.distance = 0.0141279f;
            bestparams.stmix = 2.35569e-011f;
            break;
        case 7:
            // current score 714
            bestparams.bias = 0.000485839f;
            bestparams.pulsestrength = 1.37135e-014f;
            bestparams.topbit = 6.81849e-012f;
            bestparams.distance = 1.12518f;
            bestparams.stmix = 5.70641e-005f;
            break;
        }
        break;
    // 6581 R3
    case 'O':
        switch (wave)
        {
        case 3:
            // current score 1780
            bestparams.bias = 0.932783f;
            bestparams.pulsestrength = 1.31563e+029f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.13416f;
            bestparams.stmix = 0.631864f;
            break;
        case 5:
            // current score 19114
            bestparams.bias = 0.807401f;
            bestparams.pulsestrength = 0.0001979f;
            bestparams.topbit = 1.0587f;
            bestparams.distance = 0.0286888f;
            bestparams.stmix = 9.43233e-035f;
            break;
        case 6:
            // current score 9634
            bestparams.bias = 0.832143f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.597104f;
            bestparams.distance = 0.00320875f;
            bestparams.stmix = 0.f;
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
    // 6581 R3
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
    // 6581 R3
    case 'Q':
        switch (wave)
        {
        case 3:
            // current score 1064
            bestparams.bias = 0.956396f;
            bestparams.pulsestrength = 0.000197789f;
            bestparams.topbit = 0.00314584f;
            bestparams.distance = 2.44162f;
            bestparams.stmix = 0.696384f;
            break;
        case 5:
            // current score 9816
            bestparams.bias = 0.950206f;
            bestparams.pulsestrength = 3.29343f;
            bestparams.topbit = 0.990228f;
            bestparams.distance = 0.0125732f;
            bestparams.stmix = 2.77908e-008f;
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
    // 6581 R4AR
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
            // current score 21865
            bestparams.bias = 0.962869f;
            bestparams.pulsestrength = 3.92166f;
            bestparams.topbit = 0.956681f;
            bestparams.distance = 0.0290248f;
            bestparams.stmix = 1.08944e-023f;
            break;
        case 6:
            // current score 28440
            bestparams.bias = 0.778149f;
            bestparams.pulsestrength = 1.57868e-023f;
            bestparams.topbit = 1.09552e-021f;
            bestparams.distance = 0.00475351f;
            bestparams.stmix = 1.13812e-019f;
            break;
        case 7:
            // current score 514
            bestparams.bias = 0.880881f;
            bestparams.pulsestrength = 0.788216f;
            bestparams.topbit = 3.83015e-009f;
            bestparams.distance = 0.0284442f;
            bestparams.stmix = 0.657472f;
            break;
        }
        break;
    
    // 6581 R4AR
    case 'S':
        switch (wave)
        {
        case 3:
            // current score 6776
            bestparams.bias = 1.26849e-012f;
            bestparams.pulsestrength = 0.0012997f;
            bestparams.topbit = 3.2768e-007f;
            bestparams.distance = 4.29114e+037f;
            bestparams.stmix = 1.19368e-013f;
            break;
        case 5:
            // current score 13940
            bestparams.bias = 0.933698f;
            bestparams.pulsestrength = 2.87927f;
            bestparams.topbit = 0.976823f;
            bestparams.distance = 0.0305543f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 8834
            bestparams.bias = 0.792174f;
            bestparams.pulsestrength = 1.00617e-024f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.0121035f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 1838
            bestparams.bias = std::numeric_limits<float>::infinity();
            bestparams.pulsestrength = 7.34127e+019f;
            bestparams.topbit = 5.4315e-007f;
            bestparams.distance = std::numeric_limits<float>::infinity();
            bestparams.stmix = 0.174735f;
            break;
        }
        break;
    
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 3258
            bestparams.bias = 0.0517574f;
            bestparams.pulsestrength = 1.96004e-016f;
            bestparams.topbit = 1.38017e+008f;
            bestparams.distance = std::numeric_limits<float>::infinity();
            bestparams.stmix = 1.45766e-019f;
            break;
        case 5:
            // current score 21728
            bestparams.bias = 1.18336f;
            bestparams.pulsestrength = 7.10237f;
            bestparams.topbit = 0.868508f;
            bestparams.distance = 0.0460346f;
            bestparams.stmix = 1.12104e-043f;
            break;
        case 6:
            // current score 3388
            bestparams.bias = 0.810845f;
            bestparams.pulsestrength = 3.84649e-006f;
            bestparams.topbit = 3.48307e-033f;
            bestparams.distance = 0.00167655f;
            bestparams.stmix = 4.9965e-007f;
            break;
        case 7:
            // current score 410
            bestparams.bias = 1.37665e-008f;
            bestparams.pulsestrength = 9.19785e-027f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.f;
            bestparams.stmix = 1.83151e-009f;
            break;
        }
        break;
    // 6581 R4AR
    case 'U':
        switch (wave)
        {
        case 3:
            // current score 5490
            bestparams.bias = 8.59715e+029f;
            bestparams.pulsestrength = 7.75512e-022f;
            bestparams.topbit = 2.2947e-015f;
            bestparams.distance = std::numeric_limits<float>::infinity();
            bestparams.stmix = 1.21583e-008f;
            break;
        case 5:
            // current score 13220
            bestparams.bias = 0.949136f;
            bestparams.pulsestrength = 2.78247f;
            bestparams.topbit = 0.993624f;
            bestparams.distance = 0.0366905f;
            bestparams.stmix = 4.41635e-034f;
            break;
        case 6:
            // current score 5322
            bestparams.bias = 0.808887f;
            bestparams.pulsestrength = 5.68833e-039f;
            bestparams.topbit = 4.28356e-030f;
            bestparams.distance = 0.000821859f;
            bestparams.stmix = 1.01434e-028f;
            break;
        case 7:
            // current score 594
            bestparams.bias = 0.547587f;
            bestparams.pulsestrength = 1.44884e-023f;
            bestparams.topbit = 3.75504e-024f;
            bestparams.distance = 3.20555e+024f;
            bestparams.stmix = 0.077303f;
            break;
        }
        break;
    // 8580
    case'V':
        switch (wave)
        {
        case 3:
            // current score 5029
            bestparams.bias = 0.986102f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.993322f;
            bestparams.distance = 13.4705f;
            bestparams.stmix = 0.85413f;
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
            // current score 17694
            bestparams.bias = 0.926019f;
            bestparams.pulsestrength = 2.11011f;
            bestparams.topbit = 0.951848f;
            bestparams.distance = 0.169977f;
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
