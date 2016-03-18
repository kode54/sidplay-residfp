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

static std::default_random_engine prng(std::random_device{}());
static std::normal_distribution<> normal_dist(1.0, 0.2);
static std::normal_distribution<> normal_dist2(0.5, 0.3);

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
    switch (chip)
    {
    // 6581 R2
    case 'B':
        switch (wave)
        {
        case 3: // ST
            // current score 212
            bestparams.threshold = 0.976441f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.65501f;
            bestparams.stmix = 0.757158f;
            break;
        case 5: // PT
            // current score 4388
            bestparams.threshold = 0.897678f;
            bestparams.pulsestrength = 1.74181f;
            bestparams.distance = 1.11487f;
            break;
        case 6: // PS
            // current score 0
            bestparams.threshold = 0.90248f;
            bestparams.pulsestrength = 1.99644f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.05336f;
            break;
        case 7: // PST
            // current score 6
           bestparams.threshold = 0.952547f;
            bestparams.pulsestrength = 1.63495f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.05367f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'C':
        switch (wave)
        {
        case 3:
            // current score 2948
            bestparams.threshold = 0.881458f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.93176f;
            bestparams.stmix = 0.596385f;
            break;
        case 5:
            // current score 16954
            bestparams.threshold = 0.865807f;
            bestparams.pulsestrength = 2.45485f;
            bestparams.distance = 1.18951f;
            break;
        case 6:
            // current score 7557
            bestparams.threshold = 0.882904f;
            bestparams.pulsestrength = 2.93422f;
            bestparams.topbit = 1.76401f; // ???
            bestparams.distance = 1.1215f;
            break;
        case 7:
            // current score 854
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
            // current score 2112
            bestparams.threshold = 0.892439f;
            bestparams.topbit = 0.01f;
            bestparams.distance = 2.02026f;
            bestparams.stmix = 0.597764f;
            break;
        case 5:
            // current score 15286
            bestparams.threshold = 0.861778f;
            bestparams.pulsestrength = 1.67847f;
            bestparams.distance = 1.21116f;
            break;
        case 6:
            // current score 17556
            bestparams.threshold = 0.873167f;
            bestparams.pulsestrength = 2.0272f;
            bestparams.topbit = 1.73415f; // ???
            bestparams.distance = 1.14846f;
            break;
        case 7:
            // current score 292
            bestparams.threshold = 0.907969f;
            bestparams.pulsestrength = 1.22522f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.18728f;
            bestparams.stmix = 0.763008f;
            break;
        }
        break;
    // 6581 R2
    case 'E':
        switch (wave)
        {
        case 3:
            // current score 297
            bestparams.threshold = 0.989183f;
            bestparams.topbit = 0.f;
            bestparams.distance = 5.75852f;
            bestparams.stmix = 0.800831f;
            break;
        case 5:
            // current score 3394
            bestparams.threshold = 0.911411f;
            bestparams.pulsestrength = 1.81105f;
            bestparams.distance = 1.12779f;
            break;
        case 6:
            // current score 8
            bestparams.threshold = 0.934748f;
            bestparams.pulsestrength = 2.67037f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04926f;
            break;
        case 7:
            // current score 2
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
            // current score 304
            bestparams.threshold = 0.981921f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.4728f;
            bestparams.stmix = 0.773906f;
            break;
        case 5:
            // current score 5056
            bestparams.threshold = 0.900978f;
            bestparams.pulsestrength = 1.88077f;
            bestparams.distance = 1.11628f;
            break;
        case 6:
            // current score 450
            bestparams.threshold = 0.887483f;
            bestparams.pulsestrength = 1.7855f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.04339f;
            break;
        case 7:
            // current score 8
            bestparams.threshold = 0.944511f;
            bestparams.pulsestrength = 1.57551f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.2404f;
            bestparams.stmix = 0.589787f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'G':
        switch (wave)
        {
        case 3:
            // current score 1725
            bestparams.threshold = 0.89173f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.73936f;
            bestparams.stmix = 0.583337f;
            break;
        case 5:
            // current score 8414
            bestparams.threshold = 0.888239f;
            bestparams.pulsestrength = 1.92029f;
            bestparams.distance = 1.15808f;
            break;
        case 6:
            // current score 18853
            bestparams.threshold = 0.873724f;
            bestparams.pulsestrength = 1.89335f;
            bestparams.topbit = 1.11071f; // ???
            bestparams.distance = 1.16689f;
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
            // current score 270
            bestparams.threshold = 0.962954f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.69f;
            bestparams.stmix = 0.594274f;
            break;
        case 5:
            // current score 2876
            bestparams.threshold = 0.916758f;
            bestparams.pulsestrength = 1.46627f;
            bestparams.distance = 1.15677f;
            break;
        case 6:
            // current score 442
            bestparams.threshold = 0.94658f;
            bestparams.pulsestrength = 2.29799f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.11933f;
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
            // current score 248
            bestparams.threshold = 0.982704f;
            bestparams.topbit = 0.01f;
            bestparams.distance = 4.43594f;
            bestparams.stmix = 0.776027f;
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
            // current score 18
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
            // current score 164
            bestparams.threshold = 0.979544f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.98045f;
            bestparams.stmix = 0.7775446f;
            break;
        case 5:
            // current score 1670
            bestparams.threshold = 0.906284f;
            bestparams.pulsestrength = 1.63395f;
            bestparams.distance = 1.11483f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.f;
            break;
        case 7:
            // current score 2
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
            // current score 1373
            bestparams.threshold = 0.951236f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.22268f;
            bestparams.stmix = 0.781342f;
            break;
        case 5:
            // current score 9880
            bestparams.threshold = 0.898178f;
            bestparams.pulsestrength = 1.65533f;
            bestparams.distance = 1.17218f;
            break;
        case 6:
            // current score 2802
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.02475f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.06918f;
            break;
        case 7:
            // current score 108
            bestparams.threshold = 0.951241f;
            bestparams.pulsestrength = 1.68557f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.2721f;
            bestparams.stmix = 0.618717f;
            break;
        }
        break;
    // 6581 R2
    case 'L':
        switch (wave)
        {
        case 3:
            // current score 1396
            bestparams.threshold = 0.977313f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.9329f;
            bestparams.stmix = 0.759047f;
            break;
        case 5:
            // current score 8688
            bestparams.threshold = 0.888839f;
            bestparams.pulsestrength = 1.9661f;
            bestparams.distance = 1.16099f;
            break;
        case 6:
            // current score 2370
            bestparams.threshold = 0.917225f;
            bestparams.pulsestrength = 2.85389f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08247f;
            break;
        case 7:
            // current score 142
            bestparams.threshold = 0.920433f;
            bestparams.pulsestrength = 1.48687f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.22292f;
            bestparams.stmix = 0.549998f;
            break;
        }
        break;  
    // 6581 R2
    case 'M':
        switch (wave)
        {
        case 3:
            // current score 352
            bestparams.threshold = 0.938881f;
            bestparams.topbit = 0.f;
            bestparams.distance = 2.07118f;
            bestparams.stmix = 0.579197f;
            break;
        case 5:
            // current score 2738
            bestparams.threshold = 0.898809f;
            bestparams.pulsestrength = 1.46817f;
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
            // current score 724
            bestparams.threshold = 0.964292f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.01406f;
            bestparams.stmix = 0.731952f;
            break;
        case 5:
            // current score 7362
            bestparams.threshold = 0.893402f;
            bestparams.pulsestrength = 1.76483f;
            bestparams.distance = 1.14934f;
            break;
        case 6:
            // current score 872
            bestparams.threshold = 0.908449f;
            bestparams.pulsestrength = 2.19373f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08931f;
            break;
        case 7:
            // current score 6
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
            // current score 1116
            bestparams.threshold = 0.965f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.10496f;
            bestparams.stmix = 0.7285f;
            break;
        case 5:
            // current score 8506
            bestparams.threshold = 0.886612f;
            bestparams.pulsestrength = 1.73526f;
            bestparams.distance = 1.15707f;
            break;
        case 6:
            // current score 1970
            bestparams.threshold = 0.905671f;
            bestparams.pulsestrength = 2.28728f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.10118f;
            break;
        case 7:
            // current score 22
            bestparams.threshold = 0.935353f;
            bestparams.pulsestrength = 1.43427f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.29752f;
            bestparams.stmix = 0.597383f;
            break;
        }
        break;
    // 6581 R3
    case 'P':
        switch (wave)
        {
        case 3:
            // current score 1870
            bestparams.threshold = 0.981269f;
            bestparams.topbit = 0.f;
            bestparams.distance = 4.63652f;
            bestparams.stmix = 0.790753f;
            break;
        case 5:
            // current score 4612
            bestparams.threshold = 0.887817f;
            bestparams.pulsestrength = 2.05147f;
            bestparams.distance = 1.08986f;
            break;
        case 6:
            // current score 373
            bestparams.threshold = 0.936627f;
            bestparams.pulsestrength = 3.64843f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.03268f;
            break;
        case 7:
            // current score 203
            bestparams.threshold = 0.919673f;
            bestparams.pulsestrength = 1.20122f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.21226f;
            bestparams.stmix = 0.67696f;
            break;
        }
        break;
    // 6581 R3
    case 'Q':
        switch (wave)
        {
        case 3:
            // current score 552
            bestparams.threshold = 0.967523f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.23339f;
            bestparams.stmix = 0.734041f;
            break;
        case 5:
            // current score 6364
            bestparams.threshold = 0.898159f;
            bestparams.pulsestrength = 2.03762f;
            bestparams.distance = 1.09909f;
            break;
        case 6:
            // current score 1776
            bestparams.threshold = 0.910486f;
            bestparams.pulsestrength = 2.41229f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.09826f;
            break;
        case 7:
            // current score 52
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
            // current score 2122
            bestparams.threshold = 0.891812f;
            bestparams.topbit = 0.00544745f;
            bestparams.distance = 2.f;
            bestparams.stmix = 0.606976f;
            break;
        case 5:
            // current score 11861
            bestparams.threshold = 0.867722f;
            bestparams.pulsestrength = 1.85276f;
            bestparams.distance = 1.16489f;
            break;
        case 6:
            // current score 23828
            bestparams.threshold = 0.861914f;
            bestparams.pulsestrength = 1.97972f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.06608f;
            break;
        case 7:
            // current score 328
            bestparams.threshold = 0.917572f;
            bestparams.pulsestrength = 1.35974f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.17066f;
            bestparams.stmix = 0.81901f;
            break;
        }
        break;
    // 6581 R4AR
    case 'S':
        switch (wave)
        {
        case 3:
            // current score 1724
            bestparams.threshold = 0.973066f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.57771f;
            bestparams.stmix = 0.747192f;
            break;
        case 5:
            // current score 8744
            bestparams.threshold = 0.876435f;
            bestparams.pulsestrength = 1.64234f;
            bestparams.distance = 1.16818f;
            break;
        case 6:
            // current score 2590
            bestparams.threshold = 0.911444f;
            bestparams.pulsestrength = 2.66357f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.0923f;
            break;
        case 7:
            // current score 184
            bestparams.threshold = 0.944703f;
            bestparams.pulsestrength = 1.6761f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.24453f;
            bestparams.stmix = 0.805256f;
            break;
        }
        break;
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 294
            bestparams.threshold = 0.966234f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.03172f;
            bestparams.stmix = 0.638178f;
            break;
        case 5:
            // current score 8634
            bestparams.threshold = 0.896646f;
            bestparams.pulsestrength = 1.67985f;
            bestparams.distance = 1.21381f;
            break;
        case 6:
            // current score 744
            bestparams.threshold = 0.915335f;
            bestparams.pulsestrength = 2.30942f;
            bestparams.topbit = 0.001f;
            bestparams.distance = 1.0836f;
            break;
        case 7:
            // current score 6
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
            // current score 334
            bestparams.threshold = 0.977027f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.90561f;
            bestparams.stmix = 0.75846f;
            break;
        case 5:
            // current score 8012
            bestparams.threshold = 0.904189f;
            bestparams.pulsestrength = 1.99222f;
            bestparams.distance = 1.17314f;
            break;
        case 6:
            // current score 1146
            bestparams.threshold = 0.899956f;
            bestparams.pulsestrength = 2.00793f;
            bestparams.topbit = 0.f;
            bestparams.distance = 1.08934f;
            break;
        case 7:
            // current score 16
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
            // current score 17839 *** (16763)
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
            bestparams.distance = 1.60705f;
            bestparams.stmix = 0.884588f;
            break;
        }
        break;
    default:
        break;
    }

    unsigned int bestscore = bestparams.Score(wave, reference, true, 4096 * 255);
    std::cout << "# initial score " << bestscore << std::endl << bestparams.toString() << std::endl << std::endl;
    if (bestscore == 0)
        exit(0);

    Parameters p = bestparams;
    for (;;)
    {
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

                    if (newValue < EPSILON)
                        newValue = GetNewRandomValue();

                    if ((i == Param_t::STMIX || i == Param_t::THRESHOLD) && (newValue > 1.f))
                    {
                        newValue = 1.f;
                    }
                }

                p.SetValue(i, newValue);
                changed = changed || oldValue != newValue;
            }
        }
        const unsigned int score = p.Score(wave, reference, false, bestscore);
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

static ref_vector_t ReadChip(int wave, char chip)
{
    std::cout << "Reading chip: " << chip << std::endl;
    ref_vector_t result;

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

    ref_vector_t reference = ReadChip(wave, chip);

#ifndef NDEBUG
    for (ref_vector_t::iterator it = reference.begin(); it != reference.end(); ++it)
        std::cout << (*it) << std::endl;
#endif

    srand(time(0));

    Optimize(reference, wave, chip);
}
