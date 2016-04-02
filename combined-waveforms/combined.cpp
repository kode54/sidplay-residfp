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

#include <cassert>
#include <ctime>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <random>

#include "parameters.h"

static const float EPSILON = 1e-3;

#ifdef __MINGW32__
// MinGW's std::random_device is a PRNG seeded with a constant value
// so we use system time as a random seed.
#include <chrono>
inline long getSeed()
{
    using namespace std::chrono;
    const auto now_ms = time_point_cast<std::chrono::milliseconds>(system_clock::now());
    return now_ms.time_since_epoch().count();
}
#else
inline long getSeed()
{
    return std::random_device{}();
}
#endif

static std::default_random_engine prng(getSeed());
static std::normal_distribution<> normal_dist(1.0, 0.001);
static std::normal_distribution<> normal_dist2(0.5, 0.2);

static double GetRandomValue()
{
    return normal_dist(prng);
}

static float GetNewRandomValue()
{
    return static_cast<float>(normal_dist2(prng));
}

static void Optimize(const ref_vector_t &reference, int wave, char chip)
{
    Parameters bestparams;
    
    /**
     * The score here reported is the acoustic error.
     * In parentheses the number of mispredicted bits
     * on a total of 32768.
     */
    switch (chip)
    {
    // 6581 R2
    case 'B':
        switch (wave)
        {
        case 3: // ST
            // current score 154 (59)
            bestparams.threshold = 0.988112f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 5.47431f;
            bestparams.stmix = 0.801007f;
            break;
        case 5: // PT
            // current score 4364 (140)
            bestparams.threshold = 0.900503f;
            bestparams.pulsestrength = 1.78935f;
            bestparams.distance = 1.1155f;
            break;
        case 6: // PS
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.23982f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.01616f;
            break;
        case 7: // PST
            // current score 6 (4)
            bestparams.threshold = 0.95f;
            bestparams.pulsestrength = 1.53818f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.06324f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'C':
        switch (wave)
        {
        case 3:
            // current score 2948 (446)
            bestparams.threshold = 0.881458f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.93176f;
            bestparams.stmix = 0.596385f;
            break;
        case 5:
            // current score 16670 (699)
            bestparams.threshold = 0.86984f;
            bestparams.pulsestrength = 2.51459f;
            bestparams.distance = 1.1884f;
            break;
        case 6:
            // current score 7553 (378)
            bestparams.threshold = 0.883729f;
            bestparams.pulsestrength = 2.95521f;
            bestparams.topbit = 1.7626f; // ???
            bestparams.distance = 1.12123f;
            break;
        case 7:
            // current score 854 (62)
            bestparams.threshold = 0.91971f;
            bestparams.pulsestrength = 1.63784f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.22772f;
            bestparams.stmix = 0.902137f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'D':
        switch (wave)
        {
        case 3:
            // current score 2082 (352)
            bestparams.threshold = 0.891085f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.97684f;
            bestparams.stmix = 0.604711f;
            break;
        case 5:
            // current score 15284 (828)
            bestparams.threshold = 0.862243f;
            bestparams.pulsestrength = 1.68514f;
            bestparams.distance = 1.2112f;
            break;
        case 6:
            // current score 17454 (627)
            bestparams.threshold = 0.875914f;
            bestparams.pulsestrength = 2.09036f;
            bestparams.topbit = 1.73117f; // ???
            bestparams.distance = 1.14801f;
            break;
        case 7:
            // current score 270 (70)
            bestparams.threshold = 0.912165f;
            bestparams.pulsestrength = 1.29898f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.19354f;
            bestparams.stmix = 0.776744f;
            break;
        }
        break;
    // 6581 R2
    case 'E':
        switch (wave)
        {
        case 3:
            // current score 297 (98)
            bestparams.threshold = 0.989183f;
            bestparams.topbit = 0.f;
            bestparams.distance = 5.75852f;
            bestparams.stmix = 0.800831f;
            break;
        case 5:
            // current score 3394 (154)
            bestparams.threshold = 0.911411f;
            bestparams.pulsestrength = 1.81105f;
            bestparams.distance = 1.12779f;
            break;
        case 6:
            // current score 8 (6)
            bestparams.threshold = 0.934748f;
            bestparams.pulsestrength = 2.67037f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04926f;
            break;
        case 7:
            // current score 2 (2)
            bestparams.threshold = 0.964835f;
            bestparams.pulsestrength = 1.70932f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.16942f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2
    case 'F':
        switch (wave)
        {
        case 3:
            // current score 240 (64)
            bestparams.threshold = 0.991123f;
            bestparams.topbit = 0.052f;
            bestparams.distance = 6.57138f;
            bestparams.stmix = 0.816941f;
            break;
        case 5:
            // current score 4904 (157)
            bestparams.threshold = 0.902042f;
            bestparams.pulsestrength = 1.915f;
            bestparams.distance = 1.11199f;
            break;
        case 6:
            // current score 450 (14)
            bestparams.threshold = 0.887483f;
            bestparams.pulsestrength = 1.7855f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04339f;
            break;
        case 7:
            // current score 6 (4)
            bestparams.threshold = 0.944511f;
            bestparams.pulsestrength = 1.57551f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.29601f;
            bestparams.stmix = 0.551461f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'G':
        switch (wave)
        {
        case 3:
            // current score 1721 (290)
            bestparams.threshold = 0.89173f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.73824f;
            bestparams.stmix = 0.58394f;
            break;
        case 5:
            // current score 8382 (356)
            bestparams.threshold = 0.889226f;
            bestparams.pulsestrength = 1.94562f;
            bestparams.distance = 1.15628f;
            break;
        case 6:
            // current score 18853 (902)
            bestparams.threshold = 0.873724f;
            bestparams.pulsestrength = 1.89335f;
            bestparams.topbit = 1.11071f; // ???
            bestparams.distance = 1.16689f;
            break;
        case 7:
            // current score 74 (10)
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
            // current score 254 (82)
            bestparams.threshold = 0.962954f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.65459f;
            bestparams.stmix = 0.598044f;
            break;
        case 5:
            // current score 2876 (113)
            bestparams.threshold = 0.916758f;
            bestparams.pulsestrength = 1.46627f;
            bestparams.distance = 1.15677f;
            break;
        case 6:
            // current score 424 (32)
            bestparams.threshold = 0.939555f;
            bestparams.pulsestrength = 2.10825f;
            bestparams.topbit = 0.0012384f;
            bestparams.distance = 1.13782f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.98f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.1f;
            bestparams.stmix = 0.91f;
            break;
        }
        break;
    // 6581 R2
    case 'I':
        switch (wave)
        {
        case 3:
            // current score 184 (68)
            bestparams.threshold = 0.982704f;
            bestparams.topbit = 0.002f;
            bestparams.distance = 4.43596f;
            bestparams.stmix = 0.775803f;
            break;
        case 5:
            // current score 8317 (249)
            bestparams.threshold = 0.900143f;
            bestparams.pulsestrength = 1.78118f;
            bestparams.distance = 1.17233f;
            break;
        case 6:
            // current score 598 (19)
            bestparams.threshold = 0.885999f;
            bestparams.pulsestrength = 1.70285f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.05316f;
            break;
        case 7:
            // current score 18 (8)
            bestparams.threshold = 0.943066f;
            bestparams.pulsestrength = 1.51928f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.16375f;
            bestparams.stmix = 0.662476f;
            break;
        }
        break;
    // 6581 R2
    case 'J':
        switch (wave)
        {
        case 3:
            // current score 148 (61)
            bestparams.threshold = 0.979544f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.98271f;
            bestparams.stmix = 0.775023f;
            break;
        case 5:
            // current score 1562 (110)
            bestparams.threshold = 0.91186f;
            bestparams.pulsestrength = 1.78531f;
            bestparams.distance = 1.10833f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.f;
            break;
        case 7:
            // current score 2 (2)
            bestparams.threshold = 0.950095f;
            bestparams.pulsestrength = 1.48367f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.079012f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2
    case 'K':
        switch (wave)
        {
        case 3:
            // current score 1363 (150)
            bestparams.threshold = 0.95311f;
            bestparams.topbit = 0.00162432f;
            bestparams.distance = 2.2902f;
            bestparams.stmix = 0.773808f;
            break;
        case 5:
            // current score 9880 (392)
            bestparams.threshold = 0.898178f;
            bestparams.pulsestrength = 1.65533f;
            bestparams.distance = 1.17218f;
            break;
        case 6:
            // current score 2770 (146)
            bestparams.threshold = 0.898149f;
            bestparams.pulsestrength = 1.93365f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08271f;
            break;
        case 7:
            // current score 106 (12)
            bestparams.threshold = 0.951241f;
            bestparams.pulsestrength = 1.70629f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.34529f;
            bestparams.stmix = 0.555384f;
            break;
        }
        break;
    // 6581 R2
    case 'L':
        switch (wave)
        {
        case 3:
            // current score 1356 (109)
            bestparams.threshold = 0.983135f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.62089f;
            bestparams.stmix = 0.778836f;
            break;
        case 5:
            // current score 8608 (418)
            bestparams.threshold = 0.882393f;
            bestparams.pulsestrength = 1.86069f;
            bestparams.distance = 1.162f;
            break;
        case 6:
            // current score 2370 (137)
            bestparams.threshold = 0.917225f;
            bestparams.pulsestrength = 2.85389f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08247f;
            break;
        case 7:
            // current score 102 (16)
            bestparams.threshold = 0.941179f;
            bestparams.pulsestrength = 1.65307f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.22544f;
            bestparams.stmix = 0.748047f;
            break;
        }
        break;  
    // 6581 R2
    case 'M':
        switch (wave)
        {
        case 3:
            // current score 352 (106)
            bestparams.threshold = 0.938881f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.07118f;
            bestparams.stmix = 0.579197f;
            break;
        case 5:
            // current score 2494 (155)
            bestparams.threshold = 0.905145f;
            bestparams.pulsestrength = 1.57513f;
            bestparams.distance = 1.13152f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.03662f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.979779f;
            bestparams.pulsestrength = 2.03635f;
            bestparams.topbit = 0.f;
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
            // current score 666 (106)
            bestparams.threshold = 0.981407f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.37961f;
            bestparams.stmix = 0.772477f;
            break;
        case 5:
            // current score 7186 (234)
            bestparams.threshold = 0.894419f;
            bestparams.pulsestrength = 1.77795f;
            bestparams.distance = 1.15163f;
            break;
        case 6:
            // current score 872 (25)
            bestparams.threshold = 0.908449f;
            bestparams.pulsestrength = 2.19373f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08931f;
            break;
        case 7:
            // current score 6 (4)
            bestparams.threshold = 0.937073f;
            bestparams.pulsestrength = 1.53709f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.24933f;
            bestparams.stmix = 0.540649f;
            break;
        }
        break;
    // 6581 R3
    case 'O':
        switch (wave)
        {
        case 3:
            // current score 1116 (120)
            bestparams.threshold = 0.965f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.10496f;
            bestparams.stmix = 0.7285f;
            break;
        case 5:
            // current score 8386 (297)
            bestparams.threshold = 0.891243f;
            bestparams.pulsestrength = 1.84373f;
            bestparams.distance = 1.15338f;
            break;
        case 6:
            // current score 1970 (90)
            bestparams.threshold = 0.905671f;
            bestparams.pulsestrength = 2.28728f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.10118f;
            break;
        case 7:
            // current score 16 (8)
            bestparams.threshold = 0.943379f;
            bestparams.pulsestrength = 1.60476f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.34915f;
            bestparams.stmix = 0.593137f;
            break;
        }
        break;
    // 6581 R3
    case 'P':
        switch (wave)
        {
        case 3:
            // current score 1814 (121)
            bestparams.threshold = 0.981762f;
            bestparams.topbit = 0.00005f;
            bestparams.distance = 4.68242f;
            bestparams.stmix = 0.792635f;
            break;
        case 5:
            // current score 4448 (229)
            bestparams.threshold = 0.890976f;
            bestparams.pulsestrength = 2.13678f;
            bestparams.distance = 1.08794f;
            break;
        case 6:
            // current score 373 (128)
            bestparams.threshold = 0.936627f;
            bestparams.pulsestrength = 3.64843f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.03268f;
            break;
        case 7:
            // current score 199 (27)
            bestparams.threshold = 0.919673f;
            bestparams.pulsestrength = 1.21899f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.21226f;
            bestparams.stmix = 0.662322f;
            break;
        }
        break;
    // 6581 R3
    case 'Q':
        switch (wave)
        {
        case 3:
            // current score 488 (90)
            bestparams.threshold = 0.982932f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.59079f;
            bestparams.stmix = 0.778088f;
            break;
        case 5:
            // current score 6362 (181)
            bestparams.threshold = 0.902705f;
            bestparams.pulsestrength = 2.12256f;
            bestparams.distance = 1.09913f;
            break;
        case 6:
            // current score 1712 (82)
            bestparams.threshold = 0.910486f;
            bestparams.pulsestrength = 2.42677f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08882f;
            break;
        case 7:
            // current score 50 (18)
            bestparams.threshold = 0.902089f;
            bestparams.pulsestrength = 0.929369f;
            bestparams.topbit = 0.01f;
            bestparams.distance = 1.15824f;
            bestparams.stmix = 0.551415f;
            break;
        }
        break;
    // 6581 R4AR
    case 'R':
        switch (wave)
        {
        case 3:
            // current score 2122 (349)
            bestparams.threshold = 0.891812f;
            bestparams.topbit = 0.00544745f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.606976f;
            break;
        case 5:
            // current score 11861 (538)
            bestparams.threshold = 0.867722f;
            bestparams.pulsestrength = 1.85276f;
            bestparams.distance = 1.16489f;
            break;
        case 6:
            // current score 23828 (447)
            bestparams.threshold = 0.861914f;
            bestparams.pulsestrength = 1.97972f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.06608f;
            break;
        case 7:
            // current score 294 (40)
            bestparams.threshold = 0.918853f;
            bestparams.pulsestrength = 1.39148f;
            bestparams.topbit = 0.00118932f;
            bestparams.distance = 1.17346f;
            bestparams.stmix = 0.807394f;
            break;
        }
        break;
    // 6581 R4AR
    case 'S':
        switch (wave)
        {
        case 3:
            // current score 1724 (124)
            bestparams.threshold = 0.973066f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.57771f;
            bestparams.stmix = 0.747192f;
            break;
        case 5:
            // current score 8316 (466)
            bestparams.threshold = 0.874833f;
            bestparams.pulsestrength = 1.60378f;
            bestparams.distance = 1.1728f;
            break;
        case 6:
            // current score 2366 (147)
            bestparams.threshold = 0.911444f;
            bestparams.pulsestrength = 2.71033f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08721f;
            break;
        case 7:
            // current score 152 (18)
            bestparams.threshold = 0.936758f;
            bestparams.pulsestrength = 1.57333f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.237f;
            bestparams.stmix = 0.724957f;
            break;
        }
        break;
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 294 (101)
            bestparams.threshold = 0.97026f;
            bestparams.topbit = 0.00112567f;
            bestparams.distance = 3.24432f;
            bestparams.stmix = 0.63817f;
            break;
        case 5:
            // current score 8570 (323)
            bestparams.threshold = 0.896664f;
            bestparams.pulsestrength = 1.69326f;
            bestparams.distance = 1.21047f;
            break;
        case 6:
            // current score 674 (16)
            bestparams.threshold = 0.913402f;
            bestparams.pulsestrength = 2.28726f;
            bestparams.topbit = 0.00105749f;
            bestparams.distance = 1.07898f;
            break;
        case 7:
            // current score 6 (4)
            bestparams.threshold = 0.95f;
            bestparams.pulsestrength = 1.59413f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04364f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R4AR
    case 'U':
        switch (wave)
        {
        case 3:
            // current score 294 (94)
            bestparams.threshold = 0.983248f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.63783f;
            bestparams.stmix = 0.779401f;
            break;
        case 5:
            // current score 7940 (297)
            bestparams.threshold = 0.908797f;
            bestparams.pulsestrength = 2.04848f;
            bestparams.distance = 1.17664f;
            break;
        case 6:
            // current score 1082 (52)
            bestparams.threshold = 0.901542f;
            bestparams.pulsestrength = 2.03998f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.09027f;
            break;
        case 7:
            // current score 16 (8)
            bestparams.threshold = 0.945057f;
            bestparams.pulsestrength = 1.70407f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.35223f;
            bestparams.stmix = 0.526846f;
            break;
        }
        break;
    // 8580
    case'V':
        switch (wave)
        {
        case 3:
            // current score 1595 (268)
            bestparams.threshold = 0.954174f;
            bestparams.topbit = 0.977581f;
            bestparams.distance = 2.11887f;
            bestparams.stmix = 0.971231f;
            break;
        case 5:
            // current score 19365 *** (18507) (782)
            bestparams.threshold = 0.901729f;
            bestparams.pulsestrength = 1.61708f;
            bestparams.distance = 1.43545f;
            break;
        case 6:
            // current score 17839 *** (16763) (668)
            bestparams.threshold = 0.912565f;
            bestparams.pulsestrength = 1.84866f;
            bestparams.topbit = 0.965f;
            bestparams.distance = 1.41917f;
            break;
        case 7:
            // current score 2671 (161)
            bestparams.threshold = 0.970001f;
            bestparams.pulsestrength = 0.955653f;
            bestparams.topbit = 1.00323f;
            bestparams.distance = 1.97354f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6582
    case 'W':
        switch (wave)
        {
        case 3:
            // current score 2257 (245)
            bestparams.threshold = 0.948256f;
            bestparams.topbit = 0.983096f;
            bestparams.distance = 1.99932f;
            bestparams.stmix = 0.998819f;
            break;
        case 5:
            // current score 23156 (1056)
            bestparams.threshold = 0.892084f;
            bestparams.pulsestrength = 1.69486f;
            bestparams.distance = 1.52281f;
            break;
        case 6:
            // current score 24084 *** (22693) (1104)
            bestparams.threshold = 0.89679f;
            bestparams.pulsestrength = 1.57105f;
            bestparams.topbit = 0.982496f;
            bestparams.distance = 1.62418f;
            break;
        case 7:
            // current score 4789 (175)
            bestparams.threshold = 0.968489f;
            bestparams.pulsestrength = 1.97789f;
            bestparams.topbit = 0.921418f;
            bestparams.distance = 1.60705f;
            bestparams.stmix = 0.884588f;
            break;
        }
        break;
    default:
        break;
    }

    // Calculate current score
    score_t bestscore = bestparams.Score(wave, reference, true, 4096 * 255);
    std::cout << "# initial score " << bestscore << std::endl << bestparams.toString() << std::endl << std::endl;
    if (bestscore.audible_error == 0)
        exit(0);

    /*
     * Start the Monte Carlo loop: we randomly alter parameters
     * and calculate the new score until we find the best fitting
     * waveform compared to the sampled data.
     */
    Parameters p = bestparams;
    for (;;)
    {
        // loop until at least one parameter has changed
        bool changed = false;
        while (!changed)
        {
            for (Param_t i = Param_t::THRESHOLD; i <= Param_t::STMIX; i++)
            {
                // PULSESTRENGTH only affects pulse
                if ((i==Param_t::PULSESTRENGTH) && ((wave & 0x04) != 0x04))
                {
                    continue;
                }

                // STMIX only affects saw/triangle mix
                if ((i==Param_t::STMIX) && ((wave & 0x03) != 0x03))
                {
                    continue;
                }

                // TOPBIT only affects saw
                if ((i==Param_t::TOPBIT) && ((wave & 0x02) != 0x02))
                {
                    continue;
                }

                if (GetRandomValue() > 1.)
                {
                    const float oldValue = bestparams.GetValue(i);

                    //std::cout << newValue << " -> ";
                    float newValue = static_cast<float>(GetRandomValue()*oldValue);
                    //float newValue = oldValue + GetRandomValue();
                    //std::cout << newValue << std::endl;

                    // try to avoid too small values
                    if (newValue < EPSILON)
                        newValue = GetNewRandomValue();

                    // check for parameters limits
                    if ((i == Param_t::STMIX || i == Param_t::THRESHOLD) && (newValue > 1.f)
                        || (i == Param_t::DISTANCE)  && (newValue < 1.f))
                    {
                        newValue = 1.f;
                    }

                    p.SetValue(i, newValue);
                    changed = changed || oldValue != newValue;
                }
            }
        }

        // check new score
        const score_t score = p.Score(wave, reference, false, bestscore.audible_error);
        if (bestscore.isBetter(score))
        {
            // accept if improvement
            std::cout << "# current score " << score << std::endl << p.toString() << std::endl << std::endl;
            if (score.audible_error == 0)
                exit(0);
            //p.reset();
            bestparams = p;
            bestscore = score;
        }
        else if (score.audible_error == bestscore.audible_error)
        {
            // print the rate of wrong bits
            std::cout << score.wrongBitsRate() << std::endl;

            // no improvement but use new parameters as base to increase the "entropy"
            bestparams = p;
        }
    }
}

/**
 * Split a file into lines.
 */
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

/**
 * Read sampled values for specific waveform and chip.
 */
static ref_vector_t ReadChip(int wave, char chip)
{
    std::cout << "Reading chip: " << chip << std::endl;

    std::ostringstream fileName;
    fileName << "sidwaves/WAVE" << wave << ".CSV";
    std::ifstream ifs(fileName.str().c_str(), std::ifstream::in);
    std::string line;
    ref_vector_t result;
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

    ref_vector_t reference = ReadChip(wave, chip);

#ifndef NDEBUG
    for (ref_vector_t::iterator it = reference.begin(); it != reference.end(); ++it)
        std::cout << (*it) << std::endl;
#endif

    srand(time(0));

    Optimize(reference, wave, chip);
}
