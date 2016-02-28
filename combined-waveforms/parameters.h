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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <cmath>
#include <vector>
#include <string>
#include <sstream>

class Parameters
{
public:
    enum
    {
        THRESHOLD,
        PULSESTRENGTH,
        TOPBIT,
        DISTANCE,
        STMIX
    };

public:
    float threshold, pulsestrength, topbit, distance, stmix;

public:
    Parameters() { reset(); }

    void reset()
    {
        threshold = 0.f;
        pulsestrength = 0.f;
        topbit = 0.f;
        distance = 0.f;
        stmix = 0.f;
    }

    float GetValue(int i)
    {
        switch (i)
        {
            case THRESHOLD: return threshold;
            case PULSESTRENGTH: return pulsestrength;
            case TOPBIT: return topbit;
            case DISTANCE: return distance;
            case STMIX: return stmix;
        }
    }

    void SetValue(int i, float v)
    {
        switch (i)
        {
            case THRESHOLD: threshold = v; break;
            case PULSESTRENGTH: pulsestrength = v; break;
            case TOPBIT: topbit = v; break;
            case DISTANCE: distance = v; break;
            case STMIX: stmix = v; break;
        }
    }

    std::string toString()
    {
        std::ostringstream ss;
        ss << "threshold = " << threshold << std::endl;
        ss << "pulsestrength = " << pulsestrength << std::endl;
        ss << "topbit = " << topbit << std::endl;
        ss << "distance = " << distance << std::endl;
        ss << "stmix = " << stmix << std::endl;
        return ss.str();
    }

private:
    void SimulateMix(float bitarray[12], float wa[], bool HasPulse)
    {
        float tmp[12];

        for (int sb = 0; sb < 12; sb ++)
        {
            float n = 0.f;
            float avg = 0.f;
            for (int cb = 0; cb < 12; cb ++)
            {
                const float weight = wa[sb - cb + 12];
                avg += bitarray[cb] * weight;
                n += weight;
            }
            if (HasPulse)
            {
                const float weight = wa[sb];
                avg += pulsestrength * weight;
                n += weight;
            }
            tmp[sb] = (bitarray[sb] + avg / n) * 0.5f;
        }
        for (int i = 0; i < 12; i ++)
            bitarray[i] = tmp[i];
    }

    int GetScore8(float bitarray[12])
    {
        int result = 0;
        for (int cb = 0; cb < 8; cb ++)
        {
            if (bitarray[4+cb] > threshold)
                result |= 1 << cb;
        }
        return result;
    }

    static int ScoreResult(int a, int b)
    {
        // audible error
        int v = a ^ b;
        return v;
/*      int c = 0;
        while (v != 0)
        {
            v &= v - 1;
            c ++;
        }
        return c;
*/
    }

public:
    int Score(int wave, const std::vector<int> &reference, bool print, int bestscore)
    {
        int score = 0;

        // distance weight
        float wa[12 * 2 + 1];
        for (int i = 0; i <= 12; i ++)
        {
            wa[12-i] = wa[12+i] = 1.0f / pow(distance, i);
        }

        for (unsigned int j = 0; j < 4096; j ++)
        {
            /* S */
            float bitarray[12];
            for (unsigned int i = 0; i < 12; i ++)
            {
                bitarray[i] = (j & (1 << i)) != 0 ? 1.f : 0.f;
            }

            /* T */
            if ((wave & 3) == 1)
            {
                const bool top = (j & 2048) != 0;
                for (int i = 11; i > 0; i --)
                {
                    bitarray[i] = top ? 1.f - bitarray[i-1] : bitarray[i-1];
                }
                bitarray[0] = 0.f;
            }

            /* ST */
            else if ((wave & 3) == 3)
            {
                bitarray[0] *= stmix;
                for (int i = 1; i < 12; i ++)
                {
                    bitarray[i] = bitarray[i-1] * (1.f - stmix) + bitarray[i] * stmix;
                }
            }

            // topbit for Saw
            if ((wave & 2) == 2)
            {
                bitarray[11] *= topbit;
            }

            SimulateMix(bitarray, wa, wave > 4);

            const int simval = GetScore8(bitarray);
            const int refval = reference[j];
            score += ScoreResult(simval, refval);

            if (print)
            {
                float analogval = 0.f;
                for (unsigned int i = 0; i < 12; i ++)
                {
                    float val = (bitarray[i] - threshold) * 512 + 0.5f;
                    if (val < 0.f)
                        val = 0.f;
                    else if (val > 1.f)
                        val = 1.f;
                    analogval += val * (1 << i);
                }
                analogval /= 16.f;
                std::cout << j << " "
                          << refval << " "
                          << simval << " "
                          << analogval << " "
                          << std::endl;
            }

            // halt if we already are worst than the best score
            if (score > bestscore)
            {
                return score;
            }
        }
        return score;
    }
};

#endif
