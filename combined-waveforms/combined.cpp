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

inline long getSeed()
#ifdef __MINGW32__
// MinGW's std::random_device is a PRNG seeded with a constant value
// so we use system time as a random seed.
#include <chrono>
{
    using namespace std::chrono;
    const auto now_ms = time_point_cast<std::chrono::milliseconds>(system_clock::now());
    return now_ms.time_since_epoch().count();
}
#else
{
    return std::random_device{}();
}
#endif

static std::default_random_engine prng(getSeed());
static std::normal_distribution<> normal_dist(1.0, 0.1);
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
     * In parentheses the rate of mispredicted bits (per mille).
     */
    switch (chip)
    {
    // 6581 R2
    case 'B':
        switch (wave)
        {
        case 3: // ST
            // current score 164 (1.86 °/..)
            bestparams.threshold = 0.982289f;
            bestparams.topbit = 0.00204577f;
            bestparams.distance = 4.35889f;
            bestparams.stmix = 0.77699f;
            break;
        case 5: // PT
            // current score 4388 (4.15 °/..)
            bestparams.threshold = 0.897678f;
            bestparams.pulsestrength = 1.74181f;
            bestparams.distance = 1.11487f;
            break;
        case 6: // PS
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.23982f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.01616f;
            break;
        case 7: // PST
            // current score 6 (0.12 °/..)
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
            // current score 2948 (13.61 °/..)
            bestparams.threshold = 0.881458f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.93176f;
            bestparams.stmix = 0.596385f;
            break;
        case 5:
            // current score 16822 (21.70 °/..)
            bestparams.threshold = 0.865773f;
            bestparams.pulsestrength = 2.45485f;
            bestparams.distance = 1.18802f;
            break;
        case 6:
            // current score 7557 (11.57 °/..)
            bestparams.threshold = 0.882904f;
            bestparams.pulsestrength = 2.93422f;
            bestparams.topbit = 1.76401f; // ???
            bestparams.distance = 1.1215f;
            break;
        case 7:
            // current score 854 (1.89 °/..)
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
            // current score 2112 (10.93 °/..)
            bestparams.threshold = 0.892439f;
            bestparams.topbit = 0.01f;
            bestparams.distance = 2.02026f;
            bestparams.stmix = 0.597764f;
            break;
        case 5:
            // current score 15286 (25.33 °/..)
            bestparams.threshold = 0.861778f;
            bestparams.pulsestrength = 1.67847f;
            bestparams.distance = 1.21116f;
            break;
        case 6:
            // current score 17454 (19.13 °/..)
            bestparams.threshold = 0.875914f;
            bestparams.pulsestrength = 2.09036f;
            bestparams.topbit = 1.73117f; // ???
            bestparams.distance = 1.14801f;
            break;
        case 7:
            // current score 286 (2.20 °/..)
            bestparams.threshold = 0.909059f;
            bestparams.pulsestrength = 1.26139f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.18417f;
            bestparams.stmix = 0.765175f;
            break;
        }
        break;
    // 6581 R2
    case 'E':
        switch (wave)
        {
        case 3:
            // current score 297 (2.99 °/..)
            bestparams.threshold = 0.989183f;
            bestparams.topbit = 0.f;
            bestparams.distance = 5.75852f;
            bestparams.stmix = 0.800831f;
            break;
        case 5:
            // current score 3394 (4.70 °/..)
            bestparams.threshold = 0.911411f;
            bestparams.pulsestrength = 1.81105f;
            bestparams.distance = 1.12779f;
            break;
        case 6:
            // current score 8 (0.18 °/..)
            bestparams.threshold = 0.934748f;
            bestparams.pulsestrength = 2.67037f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04926f;
            break;
        case 7:
            // current score 2 (0.61 °/..)
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
            // current score 292 (2.38 °/..)
            bestparams.threshold = 0.981921f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.44896f;
            bestparams.stmix = 0.775213f;
            break;
        case 5:
            // current score 4916 (4.73 °/..)
            bestparams.threshold = 0.900978f;
            bestparams.pulsestrength = 1.89964f;
            bestparams.distance = 1.11134f;
            break;
        case 6:
            // current score 450 (0.42 °/..)
            bestparams.threshold = 0.887483f;
            bestparams.pulsestrength = 1.7855f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04339f;
            break;
        case 7:
            // current score 6 (0.12 °/..)
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
            // current score 1721 (8.85 °/..)
            bestparams.threshold = 0.89173f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.73824f;
            bestparams.stmix = 0.58394f;
            break;
        case 5:
            // current score 8414 (10.99 °/..)
            bestparams.threshold = 0.888239f;
            bestparams.pulsestrength = 1.92029f;
            bestparams.distance = 1.15808f;
            break;
        case 6:
            // current score 18853 (27.53 °/..)
            bestparams.threshold = 0.873724f;
            bestparams.pulsestrength = 1.89335f;
            bestparams.topbit = 1.11071f; // ???
            bestparams.distance = 1.16689f;
            break;
        case 7:
            // current score 74 (0.31 °/..)
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
            // current score 254 (2.50 °/..)
            bestparams.threshold = 0.962954f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.65459f;
            bestparams.stmix = 0.598044f;
            break;
        case 5:
            // current score 2876 (3.45 °/..)
            bestparams.threshold = 0.916758f;
            bestparams.pulsestrength = 1.46627f;
            bestparams.distance = 1.15677f;
            break;
        case 6:
            // current score 424 (0.98 °/..)
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
            // current score 184 (2.08 °/..)
            bestparams.threshold = 0.982704f;
            bestparams.topbit = 0.002f;
            bestparams.distance = 4.43596f;
            bestparams.stmix = 0.775803f;
            break;
        case 5:
            // current score 8317 (7.60 °/..)
            bestparams.threshold = 0.900143f;
            bestparams.pulsestrength = 1.78118f;
            bestparams.distance = 1.17233f;
            break;
        case 6:
            // current score 598 (0.58 °/..)
            bestparams.threshold = 0.885999f;
            bestparams.pulsestrength = 1.70285f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.05316f;
            break;
        case 7:
            // current score 18 (0.24 °/..)
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
            // current score 148 (1.86 °/..)
            bestparams.threshold = 0.979544f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.98271f;
            bestparams.stmix = 0.775023f;
            break;
        case 5:
            // current score 1668 (2.81 °/..)
            bestparams.threshold = 0.906795f;
            bestparams.pulsestrength = 1.64605f;
            bestparams.distance = 1.1137f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.f;
            break;
        case 7:
            // current score 2 (0.061 °/..)
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
            // current score 1363 (4.58 °/..)
            bestparams.threshold = 0.95311f;
            bestparams.topbit = 0.00162432f;
            bestparams.distance = 2.2902f;
            bestparams.stmix = 0.773808f;
            break;
        case 5:
            // current score 9880 (11.96 °/..)
            bestparams.threshold = 0.898178f;
            bestparams.pulsestrength = 1.65533f;
            bestparams.distance = 1.17218f;
            break;
        case 6:
            // current score 2770 (4.46 °/..)
            bestparams.threshold = 0.898149f;
            bestparams.pulsestrength = 1.93365f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08271f;
            break;
        case 7:
            // current score 106 (0.37 °/..)
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
            // current score 1396 (3.51 °/..)
            bestparams.threshold = 0.977313f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.9329f;
            bestparams.stmix = 0.759047f;
            break;
        case 5:
            // current score 8688 (11.54 °/..)
            bestparams.threshold = 0.888839f;
            bestparams.pulsestrength = 1.9661f;
            bestparams.distance = 1.16099f;
            break;
        case 6:
            // current score 2370 (4.18 °/..)
            bestparams.threshold = 0.917225f;
            bestparams.pulsestrength = 2.85389f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08247f;
            break;
        case 7:
            // current score 104 (0.54 °/..)
            bestparams.threshold = 0.940333f;
            bestparams.pulsestrength = 1.62762f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.23495f;
            bestparams.stmix = 0.741104f;
            break;
        }
        break;  
    // 6581 R2
    case 'M':
        switch (wave)
        {
        case 3:
            // current score 352 (3.23 °/..)
            bestparams.threshold = 0.938881f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.07118f;
            bestparams.stmix = 0.579197f;
            break;
        case 5:
            // current score 2494 (4.73 °/..)
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
            // current score 724 (3.35693 °/..)
            bestparams.threshold = 0.964292f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.01406f;
            bestparams.stmix = 0.731952f;
            break;
        case 5:
            // current score 7202 (7.20215 °/..)
            bestparams.threshold = 0.893811f;
            bestparams.pulsestrength = 1.76483f;
            bestparams.distance = 1.15172f;
            break;
        case 6:
            // current score 872 (0.762939 °/..)
            bestparams.threshold = 0.908449f;
            bestparams.pulsestrength = 2.19373f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08931f;
            break;
        case 7:
            // current score 6 (0.12207 °/..)
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
            // current score 1116 (3.66 °/..)
            bestparams.threshold = 0.965f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.10496f;
            bestparams.stmix = 0.7285f;
            break;
        case 5:
            // current score 8422 (9.31 °/..)
            bestparams.threshold = 0.890196f;
            bestparams.pulsestrength = 1.8159f;
            bestparams.distance = 1.15424f;
            break;
        case 6:
            // current score 1970 (2.75 °/..)
            bestparams.threshold = 0.905671f;
            bestparams.pulsestrength = 2.28728f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.10118f;
            break;
        case 7:
            // current score 20 (0.31 °/..)
            bestparams.threshold = 0.935119f;
            bestparams.pulsestrength = 1.49131f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.31755f;
            bestparams.stmix = 0.567438f;
            break;
        }
        break;
    // 6581 R3
    case 'P':
        switch (wave)
        {
        case 3:
            // current score 1870 (3.66 °/..)
            bestparams.threshold = 0.981269f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.63652f;
            bestparams.stmix = 0.790753f;
            break;
        case 5:
            // current score 4448 (6.99 °/..)
            bestparams.threshold = 0.890976f;
            bestparams.pulsestrength = 2.13678f;
            bestparams.distance = 1.08794f;
            break;
        case 6:
            // current score 373 (3.91 °/..)
            bestparams.threshold = 0.936627f;
            bestparams.pulsestrength = 3.64843f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.03268f;
            break;
        case 7:
            // current score 199 (0.82 °/..)
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
            // current score 552 (3.17 °/..)
            bestparams.threshold = 0.967523f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.23339f;
            bestparams.stmix = 0.734041f;
            break;
        case 5:
            // current score 6364 (5.65 °/..)
            bestparams.threshold = 0.898159f;
            bestparams.pulsestrength = 2.03762f;
            bestparams.distance = 1.09909f;
            break;
        case 6:
            // current score 1776 (2.50 °/..)
            bestparams.threshold = 0.910486f;
            bestparams.pulsestrength = 2.41229f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.09826f;
            break;
        case 7:
            // current score 52 (0.61 °/..)
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 0.884552f;
            bestparams.topbit = 0.01f;
            bestparams.distance = 1.11527f;
            bestparams.stmix = 0.581391f;
            break;
        }
        break;
    // 6581 R4AR
    case 'R':
        switch (wave)
        {
        case 3:
            // current score 2122 (10.65 °/..)
            bestparams.threshold = 0.891812f;
            bestparams.topbit = 0.00544745f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.606976f;
            break;
        case 5:
            // current score 11861 (16.42 °/..)
            bestparams.threshold = 0.867722f;
            bestparams.pulsestrength = 1.85276f;
            bestparams.distance = 1.16489f;
            break;
        case 6:
            // current score 23828 (13.64 °/..)
            bestparams.threshold = 0.861914f;
            bestparams.pulsestrength = 1.97972f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.06608f;
            break;
        case 7:
            // current score 294 (1.22 °/..)
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
            // current score 1724 (3.78 °/..)
            bestparams.threshold = 0.973066f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.57771f;
            bestparams.stmix = 0.747192f;
            break;
        case 5:
            // current score 8362 (14.65 °/..)
            bestparams.threshold = 0.8735f;
            bestparams.pulsestrength = 1.59616f;
            bestparams.distance = 1.16818f;
            break;
        case 6:
            // current score 2366 (4.49 °/..)
            bestparams.threshold = 0.911444f;
            bestparams.pulsestrength = 2.71033f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08721f;
            break;
        case 7:
            // current score 182 (0.55 °/..)
            bestparams.threshold = 0.945696f;
            bestparams.pulsestrength = 1.67638f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.23845f;
            bestparams.stmix = 0.842977f;
            break;
        }
        break;
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 294 (3.20 °/..)
            bestparams.threshold = 0.966234f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.03172f;
            bestparams.stmix = 0.638178f;
            break;
        case 5:
            // current score 8570 (9.86 °/..)
            bestparams.threshold = 0.896664f;
            bestparams.pulsestrength = 1.69326f;
            bestparams.distance = 1.21047f;
            break;
        case 6:
            // current score 674 (0.49 °/..)
            bestparams.threshold = 0.913402f;
            bestparams.pulsestrength = 2.28726f;
            bestparams.topbit = 0.00105749f;
            bestparams.distance = 1.07898f;
            break;
        case 7:
            // current score 6 (0.12 °/..)
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
            // current score 334 (3.05 °/..)
            bestparams.threshold = 0.977027f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.90561f;
            bestparams.stmix = 0.75846f;
            break;
        case 5:
            // current score 7940 (9.06 °/..)
            bestparams.threshold = 0.908797f;
            bestparams.pulsestrength = 2.04848f;
            bestparams.distance = 1.17664f;
            break;
        case 6:
            // current score 1082 (1.59 °/..)
            bestparams.threshold = 0.901542f;
            bestparams.pulsestrength = 2.03998f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.09027f;
            break;
        case 7:
            // current score 16 (0.24 °/..)
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
            // current score 1601 (8.12 °/..)
            bestparams.threshold = 0.954367f;
            bestparams.topbit = 0.97767f;
            bestparams.distance = 2.11966f;
            bestparams.stmix = 0.973193f;
            break;
        case 5:
            // current score 19365 *** (18507) (23.86 °/..)
            bestparams.threshold = 0.901729f;
            bestparams.pulsestrength = 1.61708f;
            bestparams.distance = 1.43545f;
            break;
        case 6:
            // current score 17839 *** (16763) (20.39 °/..)
            bestparams.threshold = 0.912565f;
            bestparams.pulsestrength = 1.84866f;
            bestparams.topbit = 0.965f;
            bestparams.distance = 1.41917f;
            break;
        case 7:
            // current score 2671 (4.91 °/..)
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
            // current score 2257 (7.48 °/..)
            bestparams.threshold = 0.948256f;
            bestparams.topbit = 0.983096f;
            bestparams.distance = 1.99932f;
            bestparams.stmix = 0.998819f;
            break;
        case 5:
            // current score 23156 (32.23 °/..)
            bestparams.threshold = 0.892084f;
            bestparams.pulsestrength = 1.69486f;
            bestparams.distance = 1.52281f;
            break;
        case 6:
            // current score 24084 *** (22693) (33.69 °/..)
            bestparams.threshold = 0.89679f;
            bestparams.pulsestrength = 1.57105f;
            bestparams.topbit = 0.982496f;
            bestparams.distance = 1.62418f;
            break;
        case 7:
            // current score 4789 (5.34 °/..)
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
    unsigned int bestscore = bestparams.Score(wave, reference, true, 4096 * 255);
    std::cout << "# initial score " << bestscore << std::endl << bestparams.toString() << std::endl << std::endl;
    if (bestscore == 0)
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

                const float oldValue = bestparams.GetValue(i);
                float newValue = oldValue;

                if (GetRandomValue() > 1.0)
                {
                    //std::cout << newValue << " -> ";
                    newValue = static_cast<float>(GetRandomValue()*newValue);
                    //newValue += GetRandomValue() - 1.0;
                    //std::cout << newValue << std::endl;

                    // avoid too small values
                    if (newValue < EPSILON)
                        newValue = GetNewRandomValue();

                    // check for parameters limits
                    if ((i == Param_t::STMIX || i == Param_t::THRESHOLD) && (newValue > 1.f)
                        || (i == Param_t::DISTANCE)  && (newValue < 1.f))
                    {
                        newValue = 1.f;
                    }
                }

                p.SetValue(i, newValue);
                changed = changed || oldValue != newValue;
            }
        }

        // check new score
        const unsigned int score = p.Score(wave, reference, false, bestscore);
        if (score < bestscore)
        {
            // accept if improvement
            std::cout << "# current score " << score << std::endl << p.toString() << std::endl << std::endl;
            if (score == 0)
                exit(0);
            //p.reset();
            bestparams = p;
            bestscore = score;
        }
        else if (score == bestscore)
        {
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
