/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2013-2016 Leandro Nini <drfiemost@users.sourceforge.net>
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

static const float EPSILON = 1e-3;

static double randomNextDouble()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

static double GetRandomValue()
{
    return 0.99 + randomNextDouble() * 0.02;
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
        case 3: // ST
            // current score 252
            bestparams.threshold = 0.973614f;
            bestparams.topbit = 0.000449258f;
            bestparams.distance = 3.36688f;
            bestparams.stmix = 0.756577f;
            break;
        case 5: // PT
            // current score 4588
            bestparams.threshold = 0.895473f;
            bestparams.pulsestrength = 1.69972f;
            bestparams.distance = 1.11579f;
            break;
        case 6: // PS
            // current score 0
            bestparams.threshold = 0.90248f;
            bestparams.pulsestrength = 1.99644f;
            bestparams.topbit = 0.00564808f;
            bestparams.distance = 1.05336f;
            break;
        case 7: // PST
            // current score 90
            bestparams.threshold = 0.915101f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.0790408f;
            bestparams.distance = 1.90109f;
            bestparams.stmix = 0.273415f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'C':
        switch (wave)
        {
        case 3:
            // current score 3056
            bestparams.threshold = 0.87979f;
            bestparams.topbit = 0.00788503f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.563378f;
            break;
        case 5:
            // current score 17604
            bestparams.threshold = 0.845924f;
            bestparams.pulsestrength = 2.f;
            bestparams.distance = 1.2144f;
            break;
        case 6:
            // current score 8017
            bestparams.threshold = 0.868725f;
            bestparams.pulsestrength = 2.56714f;
            bestparams.topbit = 1.74819f; // ???
            bestparams.distance = 1.13237f;
            break;
        case 7:
            // current score 1086
            bestparams.threshold = 0.905357f;
            bestparams.pulsestrength = 1.38637f;
            bestparams.topbit = 0.00071116f;
            bestparams.distance = 1.22794f;
            bestparams.stmix = 0.866645f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'D':
        switch (wave)
        {
        case 3:
            // current score 2142
            bestparams.threshold = 0.892439f;
            bestparams.topbit = 0.012142f;
            bestparams.distance = 2.0179f;
            bestparams.stmix = 0.59967f;
            break;
        case 5:
            // current score 15992
            bestparams.threshold = 0.859891f;
            bestparams.pulsestrength = 1.63835f;
            bestparams.distance = 1.21544f;
            break;
        case 6:
            // current score 17783
            bestparams.threshold = 0.871843f;
            bestparams.pulsestrength = 1.98482f;
            bestparams.topbit = 1.69619f; // ???
            bestparams.distance = 1.16285f;
            break;
        case 7:
            // current score 384
            bestparams.threshold = 0.933308f;
            bestparams.pulsestrength = 1.5503f;
            bestparams.topbit = 0.00289216f;
            bestparams.distance = 1.26659f;
            bestparams.stmix = 0.893189f;
            break;
        }
        break;
    // 6581 R2
    case 'E':
        switch (wave)
        {
        case 3:
            // current score 321
            bestparams.threshold = 0.979548f;
            bestparams.topbit = 0.00278351f;
            bestparams.distance = 4.03516f;
            bestparams.stmix = 0.694315f;
            break;
        case 5:
            // current score 3910
            bestparams.threshold = 0.909784f;
            bestparams.pulsestrength = 1.74387f;
            bestparams.distance = 1.13256f;
            break;
        case 6:
            // current score 12
            bestparams.threshold = 0.963397f;
            bestparams.pulsestrength = 3.48261f;
            bestparams.topbit = 0.0100176f;
            bestparams.distance = 1.03805f;
            break;
        case 7:
            // current score 94
            bestparams.threshold = 0.859407f;
            bestparams.pulsestrength = 0.1f;
            bestparams.topbit = 0.1f;
            bestparams.distance = 1.24071f;
            bestparams.stmix = 0.360057f;
            break;
        }
        break;
    // 6581 R2
    case 'F':
        switch (wave)
        {
        case 3:
            // current score 370
            bestparams.threshold = 0.963215f;
            bestparams.topbit = 0.0201509f;
            bestparams.distance = 3.02891f;
            bestparams.stmix = 0.724276f;
            break;
        case 5:
            // current score 5110
            bestparams.threshold = 0.895499f;
            bestparams.pulsestrength = 1.75894f;
            bestparams.distance = 1.11628f;
            break;
        case 6:
            // current score 586
            bestparams.threshold = 0.888223f;
            bestparams.pulsestrength = 1.76997f;
            bestparams.topbit = 0.0317089f;
            bestparams.distance = 1.04337f;
            break;
        case 7:
            // current score 296
            bestparams.threshold = 0.706498f;
            bestparams.pulsestrength = 0.482558f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.65271f;
            bestparams.stmix = 0.158851f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'G':
        switch (wave)
        {
        case 3:
            // current score 1729
            bestparams.threshold = 0.893584f;
            bestparams.topbit = 0.000115038f;
            bestparams.distance = 1.84447f;
            bestparams.stmix = 0.564274f;
            break;
        case 5:
            // current score 8678
            bestparams.threshold = 0.883257f;
            bestparams.pulsestrength = 1.83985f;
            bestparams.distance = 1.15857f;
            break;
        case 6:
            // current score 18947
            bestparams.threshold = 0.871176f;
            bestparams.pulsestrength = 1.88901f;
            bestparams.topbit = 1.11067f; // ???
            bestparams.distance = 1.16129f;
            break;
        case 7:
            // current score 74
            bestparams.threshold = 0.938259f;
            bestparams.pulsestrength = 1.57938f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.22399f;
            bestparams.stmix = 0.772182f;
            break;
        }
        break;
    // 6581 R2
    case 'H':
        switch (wave)
        {
        case 3:
            // current score 382
            bestparams.threshold = 0.976061f;
            bestparams.topbit = 0.0966611f;
            bestparams.distance = 3.3914f;
            bestparams.stmix = 0.627661f;
            break;
        case 5:
            // current score 2996
            bestparams.threshold = 0.918241f;
            bestparams.pulsestrength = 1.47768f;
            bestparams.distance = 1.15849f;
            break;
        case 6:
            // current score 456
            bestparams.threshold = 0.934666f;
            bestparams.pulsestrength = 1.97982f;
            bestparams.topbit = 0.000615941f;
            bestparams.distance = 1.11933f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 1.f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.1f;
            bestparams.distance = 0.976116f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2
    case 'I':
        switch (wave)
        {
        case 3:
            // current score 634
            bestparams.threshold = 0.942426f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.723627f;
            break;
        case 5:
            // current score 8317
            bestparams.threshold = 0.900143f;
            bestparams.pulsestrength = 1.78118f;
            bestparams.distance = 1.17233f;
            break;
        case 6:
            // current score 614
            bestparams.threshold = 0.883639f;
            bestparams.pulsestrength = 1.64368f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.05316f;
            break;
        case 7:
            // current score 266
            bestparams.threshold = 0.715014f;
            bestparams.pulsestrength = 0.0202121f;
            bestparams.topbit = 0.1f;
            bestparams.distance = 1.42197f;
            bestparams.stmix = 0.179531f;
            break;
        }
        break;
    // 6581 R2
    case 'J':
        switch (wave)
        {
        case 3:
            // current score 344
            bestparams.threshold = 0.962482f;
            bestparams.topbit = 0.000454622f;
            bestparams.distance = 2.80358f;
            bestparams.stmix = 0.670152f;
            break;
        case 5:
            // current score 1848
            bestparams.threshold = 0.909655f;
            bestparams.pulsestrength = 1.72231f;
            bestparams.distance = 1.11166f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.942627f;
            bestparams.pulsestrength = 2.96697f;
            bestparams.topbit = 0.000109042f;
            bestparams.distance = 1.f;
            break;
        case 7:
            // current score 68
            bestparams.threshold = 0.930819f;
            bestparams.pulsestrength = 0.791336f;
            bestparams.topbit = 0.419149f;
            bestparams.distance = 1.07942f;
            bestparams.stmix = 0.752688f;
            break;
        }
        break;
    // 6581 R2
    case 'K':
        switch (wave)
        {
        case 3:
            // current score 1403
            bestparams.threshold = 0.95f;
            bestparams.topbit = 0.00909682f;
            bestparams.distance = 2.18396f;
            bestparams.stmix = 0.770835f;
            break;
        case 5:
            // current score 10136
            bestparams.threshold = 0.894973f;
            bestparams.pulsestrength = 1.60745f;
            bestparams.distance = 1.17043f;
            break;
        case 6:
            // current score 2866
            bestparams.threshold = 0.889771f;
            bestparams.pulsestrength = 1.73162f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.07568f;
            break;
        case 7:
            // current score 154
            bestparams.threshold = 0.929591f;
            bestparams.pulsestrength = 1.3815f;
            bestparams.topbit = 0.0416789f;
            bestparams.distance = 1.26855f;
            bestparams.stmix = 0.496278f;
            break;
        }
        break;
    // 6581 R2
    case 'L':
        switch (wave)
        {
        case 3:
            // current score 1476
            bestparams.threshold = 0.957073f;
            bestparams.topbit = 0.00256141f;
            bestparams.distance = 2.73874f;
            bestparams.stmix = 0.717056f;
            break;
        case 5:
            // current score 8688
            bestparams.threshold = 0.888839f;
            bestparams.pulsestrength = 1.9661f;
            bestparams.distance = 1.16099f;
            break;
        case 6:
            // current score 2726
            bestparams.threshold = 0.930968f;
            bestparams.pulsestrength = 3.13701f;
            bestparams.topbit = 0.000209355f;
            bestparams.distance = 1.08531f;
            break;
        case 7:
            // current score 278
            bestparams.threshold = 0.940125f;
            bestparams.pulsestrength = 1.75998f;
            bestparams.topbit = 0.0140829f;
            bestparams.distance = 1.31978f;
            bestparams.stmix = 0.525161f;
            break;
        }
        break;  
    // 6581 R2
    case 'M':
        switch (wave)
        {
        case 3:
            // current score 372
            bestparams.threshold = 0.95f;
            bestparams.topbit = 0.00220898f;
            bestparams.distance = 2.43071f;
            bestparams.stmix = 0.578249f;
            break;
        case 5:
            // current score 2994
            bestparams.threshold = 0.8993f;
            bestparams.pulsestrength = 1.46666f;
            bestparams.distance = 1.13423f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.932373f;
            bestparams.pulsestrength = 2.65949f;
            bestparams.topbit = 0.00926223f;
            bestparams.distance = 1.0456f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.979779f;
            bestparams.pulsestrength = 2.03635f;
            bestparams.topbit = 0.00254782f;
            bestparams.distance = 1.30189f;
            bestparams.stmix = 0.923735f;
            break;
        }
        break;
    // 6581 R2
    case 'N':
        switch (wave)
        {
        case 3:
            // current score 768
            bestparams.threshold = 0.95f;
            bestparams.topbit = 0.00170154f;
            bestparams.distance = 2.5361f;
            bestparams.stmix = 0.699695f;
            break;
        case 5:
            // current score 7596
            bestparams.threshold = 0.887863f;
            bestparams.pulsestrength = 1.60235f;
            bestparams.distance = 1.15956f;
            break;
        case 6:
            // current score 1208
            bestparams.threshold = 0.896133f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.000612388f;
            bestparams.distance = 1.06817f;
            break;
        case 7:
            // current score 166
            bestparams.threshold = 0.873501f;
            bestparams.pulsestrength = 0.598301f;
            bestparams.topbit = 0.1f;
            bestparams.distance = 1.18376f;
            bestparams.stmix = 0.413963f;
            break;
        }
        break;
    // 6581 R3
    case 'O':
        switch (wave)
        {
        case 3:
            // current score 1122   
            bestparams.threshold = 0.96559f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.12002f;
            bestparams.stmix = 0.7318f;
            break;
        case 5:
            // current score 8590
            bestparams.threshold = 0.894787f;
            bestparams.pulsestrength = 1.89575f;
            bestparams.distance = 1.1532f;
            break;
        case 6:
            // current score 1970
            bestparams.threshold = 0.905671f;
            bestparams.pulsestrength = 2.28728f;
            bestparams.topbit = 0.000152146f;
            bestparams.distance = 1.10118f;
            break;
        case 7:
            // current score 142
            bestparams.threshold = 0.95f;
            bestparams.pulsestrength = 1.83368f;
            bestparams.topbit = 0.0456447f;
            bestparams.distance = 1.59347f;
            bestparams.stmix = 0.45045f;
            break;
        }
        break;
    // 6581 R3
    case 'P':
        switch (wave)
        {
        case 3:
            // current score 1910
            bestparams.threshold = 0.981024f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.56902f;
            bestparams.stmix = 0.795473f;
            break;
        case 5:
            // current score 4964
            bestparams.threshold = 0.878803f;
            bestparams.pulsestrength = 1.82076f;
            bestparams.distance = 1.09925f;
            break;
        case 6:
            // current score 373
            bestparams.threshold = 0.984585f;
            bestparams.pulsestrength = 4.8941f;
            bestparams.topbit = 0.000734592f;
            bestparams.distance = 1.02126f;
            break;
        case 7:
            // current score 225
            bestparams.threshold = 0.871012f;
            bestparams.pulsestrength = 0.0310287f;
            bestparams.topbit = 0.0165749f;
            bestparams.distance = 1.05946f;
            bestparams.stmix = 0.775271f;
            break;
        }
        break;
    // 6581 R3
    case 'Q':
        switch (wave)
        {
        case 3:
            // current score 630
            bestparams.threshold = 0.948469f;
            bestparams.topbit = 0.00462789f;
            bestparams.distance = 2.46038f;
            bestparams.stmix = 0.698403f;
            break;
        case 5:
            // current score 6638
            bestparams.threshold = 0.892369f;
            bestparams.pulsestrength = 1.87085f;
            bestparams.distance = 1.10854f;
            break;
        case 6:
            // current score 2090
            bestparams.threshold = 0.891909f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.000571249f;
            bestparams.distance = 1.08906f;
            break;
        case 7:
            // current score 52
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 0.866515f;
            bestparams.topbit = 0.0325205f;
            bestparams.distance = 1.11973f;
            bestparams.stmix = 0.581391f;
            break;
        }
        break;
    // 6581 R4AR
    case 'R':
        switch (wave)
        {
        case 3:
            // current score 2122
            bestparams.threshold = 0.891812f;
            bestparams.topbit = 0.00544745f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.606976f;
            break;
        case 5:
            // current score 11993
            bestparams.threshold = 0.8706f;
            bestparams.pulsestrength = 1.86101f;
            bestparams.distance = 1.17118f;
            break;
        case 6:
            // current score 23956
            bestparams.threshold = 0.865056f;
            bestparams.pulsestrength = 2.04874f;
            bestparams.topbit = 0.00461555f;
            bestparams.distance = 1.06608f;
            break;
        case 7:
            // current score 396
            bestparams.threshold = 0.908399f;
            bestparams.pulsestrength = 1.24511f;
            bestparams.topbit = 0.00515968f;
            bestparams.distance = 1.1723f;
            bestparams.stmix = 0.715399f;
            break;
        }
        break;
    
    // 6581 R4AR
    case 'S':
        switch (wave)
        {
        case 3:
            // current score 1736
            bestparams.threshold = 0.973066f;
            bestparams.topbit = 0.00152279f;
            bestparams.distance = 3.58049f;
            bestparams.stmix = 0.747442f;
            break;
        case 5:
            // current score 9098
            bestparams.threshold = 0.883702f;
            bestparams.pulsestrength = 1.78432f;
            bestparams.distance = 1.16401f;
            break;
        case 6:
            // current score 3388
            bestparams.threshold = 0.882424f;
            bestparams.pulsestrength = 1.99461f;
            bestparams.topbit = 0.000469949f;
            bestparams.distance = 1.09786f;
            break;
        case 7:
            // current score 486
            bestparams.threshold = 0.925405f;
            bestparams.pulsestrength = 1.76708f;
            bestparams.topbit = 0.00369888f;
            bestparams.distance = 1.73806f;
            bestparams.stmix = 0.371976f;
            break;
        }
        break;
    
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 318
            bestparams.threshold = 0.9549f;
            bestparams.topbit = 0.0125186f;
            bestparams.distance = 2.4804f;
            bestparams.stmix = 0.63263f;
            break;
        case 5:
            // current score 8792
            bestparams.threshold = 0.911201f;
            bestparams.pulsestrength = 1.97062f;
            bestparams.distance = 1.19836f;
            break;
        case 6:
            // current score 898
            bestparams.threshold = 0.896635f;
            bestparams.pulsestrength = 1.89676f;
            bestparams.topbit = 0.003771f;
            bestparams.distance = 1.08303f;
            break;
        case 7:
            // current score 20
            bestparams.threshold = 0.95f;
            bestparams.pulsestrength = 1.58708f;
            bestparams.topbit = 0.00308812f;
            bestparams.distance = 1.14963f;
            bestparams.stmix = 0.767629f;
            break;
        }
        break;
    // 6581 R4AR
    case 'U':
        switch (wave)
        {
        case 3:
            // current score 356
            bestparams.threshold = 0.97128f;
            bestparams.topbit = 0.000330284f;
            bestparams.distance = 3.45745f;
            bestparams.stmix = 0.742891f;
            break;
        case 5:
            // current score 8012
            bestparams.threshold = 0.904189f;
            bestparams.pulsestrength = 1.99222f;
            bestparams.distance = 1.17314f;
            break;
        case 6:
            // current score 1258
            bestparams.threshold = 0.898478f;
            bestparams.pulsestrength = 1.98493f;
            bestparams.topbit = 0.0168748f;
            bestparams.distance = 1.08497f;
            break;
        case 7:
            // current score 114
            bestparams.threshold = 0.955033f;
            bestparams.pulsestrength = 3.03531f;
            bestparams.topbit = 0.0725252f;
            bestparams.distance = 3.27789f;
            bestparams.stmix = 0.345691f;
            break;
        }
        break;
    // 8580
    case'V':
        switch (wave)
        {
        case 3:
            // current score 1603
            bestparams.threshold = 0.954436f;
            bestparams.topbit = 0.975231f;
            bestparams.distance = 2.1233f;
            bestparams.stmix = 0.973817f;
            break;
        case 5:
            // current score 19365 *** (18507)
            bestparams.threshold = 0.901729f;
            bestparams.pulsestrength = 1.61708f;
            bestparams.distance = 1.43545f;
            break;
        case 6:
            // current score 17839 *** (16916)
            bestparams.threshold = 0.912565f;
            bestparams.pulsestrength = 1.84866f;
            bestparams.topbit = 0.965f;
            bestparams.distance = 1.41917f;
            break;
        case 7:
            // current score 2710
            bestparams.threshold = 0.96868f;
            bestparams.pulsestrength = 0.986333f;
            bestparams.topbit = 1.f;
            bestparams.distance = 1.91108f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6582
    case 'W':
        switch (wave)
        {
        case 3:
            // current score 2257
            bestparams.threshold = 0.948256f;
            bestparams.topbit = 0.983096f;
            bestparams.distance = 1.99932f;
            bestparams.stmix = 0.998819f;
            break;
        case 5:
            // current score 23156
            bestparams.threshold = 0.892084f;
            bestparams.pulsestrength = 1.69486f;
            bestparams.distance = 1.52281f;
            break;
        case 6:
            // current score 24084 *** (22693)
            bestparams.threshold = 0.89679f;
            bestparams.pulsestrength = 1.57105f;
            bestparams.topbit = 0.982496f;
            bestparams.distance = 1.62418f;
            break;
        case 7:
            // current score 4789
            bestparams.threshold = 0.968489f;
            bestparams.pulsestrength = 1.97789f;
            bestparams.topbit = 0.921418f;
            bestparams.distance = 1.60705;
            bestparams.stmix = 0.884588f;
            break;
        }
        break;
    default:
        break;
    }

    int bestscore = bestparams.Score(wave, reference, true, 4096 * 255);
    std::cout << "# initial score " << bestscore << std::endl << bestparams.toString() << std::endl << std::endl;
    if (bestscore == 0)
        exit(0);

    Parameters p = bestparams;
    for (;;)
    {
        bool changed = false;
        while (!changed)
        {
            for (int i = Parameters::THRESHOLD; i <= Parameters::STMIX; i++)
            {
                // PULSESTRENGTH only affects pulse
                if ((i==Parameters::PULSESTRENGTH) && ((wave & 0x04) != 0x04))
                {
                    continue;
                }

                // STMIX only affects saw/triangle mix
                if ((i==Parameters::STMIX) && ((wave & 0x03) != 0x03))
                {
                    continue;
                }

                // TOPBIT only affects saw
                if ((i==Parameters::TOPBIT) && ((wave & 0x02) != 0x02))
                {
                    continue;
                }

                const float oldValue = bestparams.GetValue(i);
                float newValue = oldValue;

                if (randomNextDouble() > 0.5)
                {
                    //std::cout << newValue << " -> ";
                    newValue = (float)(GetRandomValue()*newValue);
                    //newValue += (randomNextDouble() > 0.5) ? +GetRandomValue() : -GetRandomValue();
                    //std::cout << newValue << std::endl;

                    if (newValue < EPSILON)
                        newValue = (float)randomNextDouble();

                    if ((i == Parameters::STMIX || i == Parameters::THRESHOLD) && (newValue > 1.f))
                    {
                        newValue = 1.f;
                    }
                }

                p.SetValue(i, newValue);
                changed = changed || oldValue != newValue;
            }
        }
        const int score = p.Score(wave, reference, false, bestscore);
        // accept if improvement
        if (score < bestscore)
        {
            std::cout << "# current score " << score << std::endl << p.toString() << std::endl << std::endl;
            if (score == 0)
                exit(0);
            //p.reset();
            bestparams = p;
            bestscore = score;
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
