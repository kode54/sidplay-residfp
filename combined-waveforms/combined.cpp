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
static std::normal_distribution<> normal_dist(1.0, 0.00025);
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

    /*
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
            // current score 152 (57)
            bestparams.threshold = 0.988547385f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 5.58014059f;
            bestparams.distance2 = 5.4269886f;
            bestparams.stmix = 0.806023061f;
            break;
        case 5: // PT
            // current score 2872 (154)
            bestparams.threshold = 0.984531879f;
            bestparams.pulsestrength = 3.03670526f;
            bestparams.distance1 = 0.99342072f;
            bestparams.distance2 = 1.11435139f;
            break;
        case 6: // PS
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.23982f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.01616f;
            break;
        case 7: // PST
            // current score 0
            bestparams.threshold = 0.924151242f;
            bestparams.pulsestrength = 1.16428149f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 0.920196056f;
            bestparams.distance2 = 1.07491302f;
            bestparams.stmix = 0.793505609f;
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
            bestparams.distance1 = 1.93176f;
            bestparams.stmix = 0.596385f;
            break;
        case 5:
            // current score 11076 (341)
            bestparams.threshold = 0.933971584f;
            bestparams.pulsestrength = 3.05553484f;
            bestparams.distance1 = 1.01347399f;
            bestparams.distance2 = 1.19006455f;
            break;
        case 6:
            // current score 7251 (338)
            bestparams.threshold = 0.891877115f;
            bestparams.pulsestrength = 3.06048274f;
            bestparams.topbit = 1.69555175f; // ???
            bestparams.distance1 = 1.09586585f;
            bestparams.distance2 = 1.12208951f;
            // current score 6465 (11.78) using linear distance
            //bestparams.threshold = 0.890885f;
            //bestparams.pulsestrength = 3.1739f;
            //bestparams.topbit = 1.73974f; // ???
            //bestparams.distance1 = 0.195301f;
            break;
        case 7:
            // current score 850 (60)
            bestparams.threshold = 0.919113517f;
            bestparams.pulsestrength = 1.62892509f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.21794045f;
            bestparams.distance2 = 1.2279855f;
            bestparams.stmix = 0.896797657f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'D':
        switch (wave)
        {
        case 3:
            // current score 1958 (302)
            bestparams.threshold = 0.861116648f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.582165f;
            bestparams.distance2 = 2.23844433f;
            bestparams.stmix = 0.53945446f;
            break;
        case 5:
            // current score 9998 (374)
            bestparams.threshold = 0.919503033f;
            bestparams.pulsestrength = 2.31039476f;
            bestparams.distance1 = 1.02747607f;
            bestparams.distance2 = 1.20545173f;
            break;
        case 6:
            // current score 14149 (934)
            bestparams.threshold = 0.92074424f;
            bestparams.pulsestrength = 2.42035103f;
            bestparams.topbit = 1.14749932f; // ???
            bestparams.distance1 = 0.98591131f;
            bestparams.distance2 = 1.19843256f;
            break;
        case 7:
            // current score 258 (64)
            bestparams.threshold = 0.91076839f;
            bestparams.pulsestrength = 1.2814858f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.17647922f;
            bestparams.distance2 = 1.18998444f;
            bestparams.stmix = 0.771969795f;
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
            bestparams.distance1 = 5.75852f;
            bestparams.stmix = 0.800831f;
            break;
        case 5:
            // current score 3348 (146)
            bestparams.threshold = 0.91292721f;
            bestparams.pulsestrength = 1.83235359f;
            bestparams.distance1 = 1.12143898f;
            bestparams.distance2 = 1.12768865f;
            break;
        case 6:
            // current score 8 (6)
            bestparams.threshold = 0.934748f;
            bestparams.pulsestrength = 2.67037f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.04926f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.970328987f;
            bestparams.pulsestrength = 1.75902855f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.21010804f;
            bestparams.distance2 = 1.269436f;
            bestparams.stmix = 0.983422756f;
            break;
        }
        break;
    // 6581 R2
    case 'F':
        switch (wave)
        {
        case 3:
            // current score 240 (64)
            bestparams.threshold = 0.991197169f;
            bestparams.topbit = 0.05f;
            bestparams.distance1 = 6.59899426f;
            bestparams.distance2 = 6.54183483f;
            bestparams.stmix = 0.818105936f;
            break;
        case 5:
            // current score 3008 (57)
            bestparams.threshold = 0.959230483f;
            bestparams.pulsestrength = 2.74101543f;
            bestparams.distance1 = 1.00775206f;
            bestparams.distance2 = 1.11247838f;
            break;
        case 6:
            // current score 450 (14)
            bestparams.threshold = 0.887483f;
            bestparams.pulsestrength = 1.7855f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.04339f;
            break;
        case 7:
            // current score 6 (4)
            bestparams.threshold = 0.944511f;
            bestparams.pulsestrength = 1.57551f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.29601f;
            bestparams.stmix = 0.551461f;
            break;
        }
        break;
    // 6581 R2 (odd)
    case 'G':
        switch (wave)
        {
        case 3:
            // current score 1689 (280)
            bestparams.threshold = 0.902504623f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.91471708f;
            bestparams.distance2 = 1.67466104f;
            bestparams.stmix = 0.623763621f;
            break;
        case 5:
            // current score 6128 (130)
            bestparams.threshold = 0.93088f;
            bestparams.pulsestrength = 2.4843f;
            bestparams.distance1 = 1.0353f;
            bestparams.distance2 = 1.1484f;
            break;
        case 6:
            // current score 14243 (632)
            bestparams.threshold = 0.90988f;
            bestparams.pulsestrength = 2.26303f;
            bestparams.topbit = 1.13126f; // ???
            bestparams.distance1 = 1.0035f;
            bestparams.distance2 = 1.13801f;
            break;
        case 7:
            // current score 64 (2)
            bestparams.threshold = 0.91f;
            bestparams.pulsestrength = 1.192f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.0169f;
            bestparams.distance2 = 1.2f;
            bestparams.stmix = 0.637f;
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
            bestparams.distance1 = 2.65459f;
            bestparams.stmix = 0.598044f;
            break;
        case 5:
            // current score 2744 (91)
            bestparams.threshold = 0.919414461f;
            bestparams.pulsestrength = 1.49266505f;
            bestparams.distance1 = 1.12526083f;
            bestparams.distance2 = 1.15659571f;
            break;
        case 6:
            // current score 422 (30)
            bestparams.threshold = 0.941841662f;
            bestparams.pulsestrength = 2.20960426f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.15120029f;
            bestparams.distance2 = 1.13251173f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.98f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.1f;
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
            bestparams.threshold = 0.982668161f;
            bestparams.topbit = 0.001f;
            bestparams.distance1 = 4.43093681f;
            bestparams.distance2 = 4.43528938f;
            bestparams.stmix = 0.775906205f;
            break;
        case 5:
            // current score 6847 (171)
            bestparams.threshold = 0.943752468f;
            bestparams.pulsestrength = 2.28453493f;
            bestparams.distance1 = 1.03244841f;
            bestparams.distance2 = 1.17106056f;
            break;
        case 6:
            // current score 598 (19)
            bestparams.threshold = 0.885999f;
            bestparams.pulsestrength = 1.70285f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.05316f;
            // current score 486 (0.55)
            //bestparams.threshold = 0.8961f;
            //bestparams.pulsestrength = 1.85065f;
            //bestparams.topbit = 0.0048436f;
            //bestparams.distance1 = 0.104754f;
            break;
        case 7:
            // current score 16 (6)
            bestparams.threshold = 0.942962408f;
            bestparams.pulsestrength = 1.57235372f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.1614747f;
            bestparams.distance2 = 1.22249365f;
            bestparams.stmix = 0.581929862f;
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
            bestparams.distance1 = 3.98271f;
            bestparams.stmix = 0.775023f;
            break;
        case 5:
            // current score 1540 (102)
            bestparams.threshold = 0.9079f;
            bestparams.pulsestrength = 1.72749f;
            bestparams.distance1 = 1.12017f;
            bestparams.distance2 = 1.10793f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.95248f;
            bestparams.pulsestrength = 1.51f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.07153f;
            bestparams.distance2 = 1.09353f;
            bestparams.stmix = 1.f;
            break;
        }
        break;
    // 6581 R2
    case 'K':
        switch (wave)
        {
        case 3:
            // current score 1299 (150)
            bestparams.threshold = 0.931232035f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.78504324f;
            bestparams.distance2 = 2.21891737f;
            bestparams.stmix = 0.692269444f;
            break;
        case 5:
            // current score 8086 (386)
            bestparams.threshold = 1.f;
            bestparams.pulsestrength = 3.06605577f;
            bestparams.distance1 = 0.981742382f;
            bestparams.distance2 = 1.1532563f;
            break;
        case 6:
            // current score 2736 (142)
            bestparams.threshold = 0.896536052f;
            bestparams.pulsestrength = 1.90746009f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.0959897f;
            bestparams.distance2 = 1.08394706f;
            // current score 2706 (4.43)
            //bestparams.threshold = 0.90325f;
            //bestparams.pulsestrength = 2.04001f;
            //bestparams.topbit = 0.0336469f;
            //bestparams.distance1 = 0.107264f;
            break;
        case 7:
            // current score 106 (12)
            bestparams.threshold = 0.951241f;
            bestparams.pulsestrength = 1.70629f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.34529f;
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
            bestparams.distance1 = 4.62089f;
            bestparams.stmix = 0.778836f;
            break;
        case 5:
            // current score 6098 (134)
            bestparams.threshold = 0.924762011f;
            bestparams.pulsestrength = 2.37176347f;
            bestparams.distance1 = 1.04673755f;
            bestparams.distance2 = 1.16099727f;
            break;
        case 6:
            // current score 2212 (129)
            bestparams.threshold = 0.919602334f;
            bestparams.pulsestrength = 2.88236642f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.07599247f;
            bestparams.distance2 = 1.08375943f;
            // current score 2092 (4.06)
            //bestparams.threshold = 0.918653f;
            //bestparams.pulsestrength = 2.8652f;
            //bestparams.topbit = 0.038181f;
            //bestparams.distance1 = 0.125644f;
            break;
        case 7:
            // current score 102 (16)
            bestparams.threshold = 0.941179f;
            bestparams.pulsestrength = 1.65307f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.22544f;
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
            bestparams.distance1 = 2.07118f;
            bestparams.stmix = 0.579197f;
            break;
        case 5:
            // current score 2434 (139)
            bestparams.threshold = 0.906191885f;
            bestparams.pulsestrength = 1.59146726f;
            bestparams.distance1 = 1.127689f;
            bestparams.distance2 = 1.1314106f;
            break;
        case 6:
            // current score 0
            bestparams.threshold = 0.9f;
            bestparams.pulsestrength = 2.f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.03662f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.979779f;
            bestparams.pulsestrength = 2.03635f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.30189f;
            bestparams.stmix = 0.923735f;
            break;
        }
        break;
    // 6581 R2
    case 'N':
        switch (wave)
        {
        case 3:
            // current score 662 (104)
            bestparams.threshold = 0.981390178f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 4.37947226f;
            bestparams.distance2 = 4.3854661f;
            bestparams.stmix = 0.772289276f;
            break;
        case 5:
            // current score 4656 (74)
            bestparams.threshold = 0.945089161f;
            bestparams.pulsestrength = 2.48777676f;
            bestparams.distance1 = 1.02335358f;
            bestparams.distance2 = 1.14071643f;
            break;
        case 6:
            // current score 872 (25)
            bestparams.threshold = 0.908449f;
            bestparams.pulsestrength = 2.19373f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.08931f;
            // current score 736 (0.70)
            //bestparams.threshold = 0.910633f;
            //bestparams.pulsestrength = 2.27234f;
            //bestparams.topbit = 0.032884f;
            //bestparams.distance1 = 0.117987f;
            break;
        case 7:
            // current score 2 (2)
            bestparams.threshold = 0.911848485f;
            bestparams.pulsestrength = 1.17097521f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 0.991214871f;
            bestparams.distance2 = 1.10500252f;
            bestparams.stmix = 0.591298461f;
            break;
        }
        break;
    // 6581 R3
    case 'O':
        switch (wave)
        {
        case 3:
            // current score 1100 (118)
            bestparams.threshold = 0.967385352f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 3.22246957f;
            bestparams.distance2 = 3.13088274f;
            bestparams.stmix = 0.739427269f;
            break;
        case 5:
            // current score 6052 (99)
            bestparams.threshold = 0.929785728f;
            bestparams.pulsestrength = 2.30605006f;
            bestparams.distance1 = 1.03718281f;
            bestparams.distance2 = 1.1534183f;
            break;
        case 6:
            // current score 1826 (74)
            bestparams.threshold = 0.914386272f;
            bestparams.pulsestrength = 2.39560962f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.06825233f;
            bestparams.distance2 = 1.10218787f;
            // current score 1280 (2.38)
            //estparams.threshold = 0.915986f;
            //estparams.pulsestrength = 2.53344f;
            //estparams.topbit = 0.0255387f;
            //estparams.distance = 0.166821f;
            break;
        case 7:
            // current score 16 (8)
            bestparams.threshold = 0.943379f;
            bestparams.pulsestrength = 1.60476f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.34915f;
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
            bestparams.threshold = 0.981729865f;
            bestparams.topbit = 0.001f;
            bestparams.distance1 = 4.67945051f;
            bestparams.distance2 = 4.70896149f;
            bestparams.stmix = 0.791615963f;
            break;
        case 5:
            // current score 3748 (113)
            bestparams.threshold = 0.915575624f;
            bestparams.pulsestrength = 2.57049465f;
            bestparams.distance1 = 1.03338766f;
            bestparams.distance2 = 1.08230126f;
            // current score 3498 (10.47)
            //bestparams.threshold = 0.888239f;
            //bestparams.pulsestrength = 2.17999f;
            //bestparams.distance1 = 0.10589f;
            break;
        case 6:
            // current score 273 (76)
            bestparams.threshold = 0.926190555f;
            bestparams.pulsestrength = 3.59801102f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.05846274f;
            bestparams.distance2 = 1.03235805f;
            break;
        case 7:
            // current score 183 (19)
            bestparams.threshold = 0.918962359f;
            bestparams.pulsestrength = 1.20391202f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.15325093f;
            bestparams.distance2 = 1.22326899f;
            bestparams.stmix = 0.673512697f;
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
            bestparams.distance1 = 4.59079f;
            bestparams.stmix = 0.778088f;
            break;
        case 5:
            // current score 3740 (63)
            bestparams.threshold = 1.f;
            bestparams.pulsestrength = 3.62465143f;
            bestparams.distance1 = 0.986276627f;
            bestparams.distance2 = 1.09922075f;
            break;
        case 6:
            // current score 1712 (82)
            bestparams.threshold = 0.910486f;
            bestparams.pulsestrength = 2.42677f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.08882f;
            // current score 1050 (2.32)
            //bestparams.threshold = 0.908912f;
            //bestparams.pulsestrength = 2.40533f;
            //bestparams.topbit = 0.0173229f;
            //bestparams.distance1 = 0.146051f;
            break;
        case 7:
            // current score 38 (14)
            bestparams.threshold = 0.901118755f;
            bestparams.pulsestrength = 0.904124081f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.05176663f;
            bestparams.distance2 = 1.10776162f;
            bestparams.stmix = 0.618260384f;
            break;
        }
        break;
    // 6581 R4AR
    case 'R':
        switch (wave)
        {
        case 3:
            // current score 2070 (341)
            bestparams.threshold = 0.888629317f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.94586849f;
            bestparams.distance2 = 2.01927376f;
            bestparams.stmix = 0.600944996f;
            break;
        case 5:
            // current score 7211 (272)
            bestparams.threshold = 0.928046405f;
            bestparams.pulsestrength = 2.5883441f;
            bestparams.distance1 = 1.01187634f;
            bestparams.distance2 = 1.15885961f;
            break;
        case 6:
            // current score 23828 (447)
            bestparams.threshold = 0.861914f;
            bestparams.pulsestrength = 1.97972f;
            bestparams.topbit = 0.001f;
            bestparams.distance1 = 1.06608f;
            // current score 23644 (13.21)
            //bestparams.threshold = 0.875276f;
            //bestparams.pulsestrength = 2.24974f;
            //bestparams.topbit = 0.0547449f;
            //bestparams.distance1 = 0.101793f;
            break;
        case 7:
            // current score 274 (30)
            bestparams.threshold = 0.91457653f;
            bestparams.pulsestrength = 1.32809377f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.11845613f;
            bestparams.distance2 = 1.16926301f;
            bestparams.stmix = 0.791111946f;
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
            bestparams.distance1 = 3.57771f;
            bestparams.stmix = 0.747192f;
            break;
        case 5:
            // current score 6264 (226)
            bestparams.threshold = 0.900257707f;
            bestparams.pulsestrength = 1.89190149f;
            bestparams.distance1 = 1.05784476f;
            bestparams.distance2 = 1.1705128f;
            break;
        case 6:
            // current score 2366 (147)
            bestparams.threshold = 0.911444f;
            bestparams.pulsestrength = 2.71033f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.08721f;
            // current score 2318 (5.58)
            //bestparams.threshold = 0.90726f;
            //bestparams.pulsestrength = 2.56464f;
            //bestparams.topbit = 0.0476564f;
            //bestparams.distance1 = 0.146608f;
            break;
        case 7:
            // current score 150 (16)
            bestparams.threshold = 0.937769651f;
            bestparams.pulsestrength = 1.57481205f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.21054459f;
            bestparams.distance2 = 1.23291314f;
            bestparams.stmix = 0.740504205f;
            break;
        }
        break;
    // 6581 R4AR
    case 'T':
        switch (wave)
        {
        case 3:
            // current score 290 (101)
            bestparams.threshold = 0.965168953f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 3.04781175f;
            bestparams.distance2 = 3.81387138f;
            bestparams.stmix = 0.609185994f;
            break;
        case 5:
            // current score 6138 (221)
            bestparams.threshold = 0.991526306f;
            bestparams.pulsestrength = 2.80080104f;
            bestparams.distance1 = 0.993945718f;
            bestparams.distance2 = 1.19684732f;
            break;
        case 6:
            // current score 674 (16)
            bestparams.threshold = 0.913402f;
            bestparams.pulsestrength = 2.28726f;
            bestparams.topbit = 0.001f;
            bestparams.distance1 = 1.07898f;
            // current score 644 (0.58)
            //bestparams.threshold = 0.923058f;
            //bestparams.pulsestrength = 2.53822f;
            //bestparams.topbit = 0.0293735f;
            //bestparams.distance1 = 0.0992377f;
            break;
        case 7:
            // current score 0
            bestparams.threshold = 0.949945092f;
            bestparams.pulsestrength = 1.60713959f;
            bestparams.topbit = 0.f;//0.00195519254
            bestparams.distance1 = 1.01901114f;
            bestparams.distance2 = 1.03737819f;
            bestparams.stmix = 0.994224012f;
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
            bestparams.distance1 = 4.63783f;
            bestparams.stmix = 0.779401f;
            break;
        case 5:
            // current score 6454 (259)
            bestparams.threshold = 0.99398762f;
            bestparams.pulsestrength = 3.14190888f;
            bestparams.distance1 = 0.999676824f;
            bestparams.distance2 = 1.16238594f;
            break;
        case 6:
            // current score 1050 (48)
            bestparams.threshold = 0.903987467f;
            bestparams.pulsestrength = 2.09684706f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.09087777f;
            bestparams.distance2 = 1.08965659f;
            // current score 898 (1.43)
            //bestparams.threshold = 0.903973f;
            //bestparams.pulsestrength = 2.11696f;
            //bestparams.topbit = 0.031477f;
            //bestparams.distance1 = 0.124215f;
            break;
        case 7:
            // current score 6 (4)
            bestparams.threshold = 0.925804496f;
            bestparams.pulsestrength = 1.36537039f;
            bestparams.topbit = 0.f;
            bestparams.distance1 = 1.1688062f;
            bestparams.distance2 = 1.32638979f;
            bestparams.stmix = 0.509957671f;
            break;
        }
        break;
    // 8580
    case'V':
        switch (wave)
        {
        case 3:
            // current score 1380 (169)
            bestparams.threshold = 0.9632f;
            bestparams.topbit = 0.975f;
            bestparams.distance1 = 1.7467f;
            bestparams.distance2 = 2.36132f;
            bestparams.stmix = 0.975395f;
            break;
        case 5:
            // current score 8007 (218)
            bestparams.threshold = 0.92886f;
            bestparams.pulsestrength = 1.67696f;
            bestparams.distance1 = 1.1014f;
            bestparams.distance2 =  1.4352f;
            break;
        case 6:
            // current score 11957 (362)
            bestparams.threshold = 0.94043f;
            bestparams.pulsestrength = 1.7937f;
            bestparams.topbit = 0.981f;
            bestparams.distance1 = 1.1213f;
            bestparams.distance2 = 1.4259f;
            break;
        case 7:
            // current score 2369 (89)
            bestparams.threshold =  0.96211f;
            bestparams.pulsestrength = 0.98695f;
            bestparams.topbit = 1.00387f;
            bestparams.distance1 = 1.46499f;
            bestparams.distance2 = 1.98375f;
            bestparams.stmix = 0.77777f;
            break;
        }
        break;
    // 6582
    case 'W':
        switch (wave)
        {
        case 3:
            // current score 2201 (242)
            bestparams.threshold = 0.948997259f;
            bestparams.topbit = 0.982420206f;
            bestparams.distance1 = 2.0006547f;
            bestparams.distance2 = 2.03388166f;
            bestparams.stmix = 0.992275f;
            break;
        case 5:
            // current score 8646 (214)
            bestparams.threshold = 0.936479628f;
            bestparams.pulsestrength = 1.86489666f;
            bestparams.distance1 = 1.08213437f;
            bestparams.distance2 = 1.47512901f;
            break;
        case 6:
            // current score 15865 (551)
            bestparams.threshold = 0.921363771f;
            bestparams.pulsestrength = 1.65707111f;
            bestparams.topbit = 0.97647506f;
            bestparams.distance1 = 1.23983788f;
            bestparams.distance2 = 1.6116122f;
            break;
        case 7:
            // current score 4029 (137)
            bestparams.threshold = 0.969611585f;
            bestparams.pulsestrength = 1.87689841f;
            bestparams.topbit = 0.933950722f;
            bestparams.distance1 = 1.41893244f;
            bestparams.distance2 = 1.57378995f;
            bestparams.stmix = 0.85624212f;
            break;
        }
        break;
    default:
        break;
    }

    if (bestparams.distance2 == 0.f)
        bestparams.distance2 = bestparams.distance1;

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

                // change a parameter with 50% proability
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
                        /*|| (i == Param_t::DISTANCE)  && (newValue < 1.f)*/)
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
