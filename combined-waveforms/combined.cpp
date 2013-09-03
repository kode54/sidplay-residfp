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
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "parameters.h"

static double randomNextDouble()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

static float GetRandomValue()
{
    const float t = 1.f - (float) randomNextDouble() * 0.9f;
    if (randomNextDouble() > 0.5)
    {
        return 1.f / t;
    }
    else
    {
        return t;
    }
}

static void Optimize(const std::vector<int> &reference, int wave, char chip)
{
    Parameters bestparams;
    if (chip == 'D')
    {
        switch (wave)
        {
        case 3:
            // current score 3128
            bestparams.bias = 0.963895f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 11.1269f;
            bestparams.stmix = 0.684475f;
            break;
        case 5:
            // current score 19188
            bestparams.bias = 0.893101f;
            bestparams.pulsestrength = 2.26513f;
            bestparams.topbit = 0.996915f;
            bestparams.distance = 0.0476716f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 18855
            bestparams.bias = 0.886921f;
            bestparams.pulsestrength = 2.35614f;
            bestparams.topbit = 1.77836f;
            bestparams.distance = 0.0238781f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 490
            bestparams.bias = 0.941437f;
            bestparams.pulsestrength = 1.69832f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.0996135f;
            bestparams.stmix = 0.952017f;
            break;
        }
    }
    if (chip == 'E')
    {
        switch (wave)
        {
        case 3:
            // current score 765
            bestparams.bias = 0.968891f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 3.10373f;
            bestparams.stmix = 0.733387f;
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
    }
    if (chip == 'G')
    {
        switch (wave)
        {
        case 3:
            // current score 1797
            bestparams.bias = 0.881375f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.329431f;
            bestparams.stmix = 0.614679f;
            break;
        case 5:
            // current score 11934
            bestparams.bias = 0.892405f;
            bestparams.pulsestrength = 2.01004f;
            bestparams.topbit = 1.00063f;
            bestparams.distance = 0.0314119f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 21910
            bestparams.bias = 0.895202f;
            bestparams.pulsestrength = 2.30265f;
            bestparams.topbit = 1.12052f;
            bestparams.distance = 0.0325561f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 110
            bestparams.bias = 0.919953f;
            bestparams.pulsestrength = 1.24672f;
            bestparams.topbit = 0.f;
            bestparams.distance = 0.039575f;
            bestparams.stmix = 0.721436f;
            break;
        }
    }
    if (chip == 'V')
    {
        switch (wave)
        {
        case 3:
            // current score 5371
            bestparams.bias = 0.979807f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.990736f;
            bestparams.distance = 9.23845f;
            bestparams.stmix = 0.82445f;
            break;
        case 5:
            // current score 19437
            bestparams.bias = 0.923462f;
            bestparams.pulsestrength = 2.19129f;
            bestparams.topbit = 1.f;
            bestparams.distance = 0.1108298f;
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
            // current score 3331
            bestparams.bias = 0.98455f;
            bestparams.pulsestrength = 1.78641f;
            bestparams.topbit = 0.936875f;
            bestparams.distance = 2.69542f;
            bestparams.stmix = 0.780678f;
            break;
        }
    }
    if (chip == 'W')
    {
        switch (wave)
        {
        case 3:
            // current score 6859
            bestparams.bias = 0.986102f;
            bestparams.pulsestrength = 0.f;
            bestparams.topbit = 0.995207f;
            bestparams.distance = 8.9704f;
            bestparams.stmix = 0.943427f;
            break;
        case 5:
            // current score 25428
            bestparams.bias = 0.907137f;
            bestparams.pulsestrength = 2.40935f;
            bestparams.topbit = 0.947396f;
            bestparams.distance = 0.167719f;
            bestparams.stmix = 0.f;
            break;
        case 6:
            // current score 22905
            bestparams.bias = 0.890474f;
            bestparams.pulsestrength = 1.64149f;
            bestparams.topbit = 0.977121f;
            bestparams.distance = 0.308259f;
            bestparams.stmix = 0.f;
            break;
        case 7:
            // current score 5248
            bestparams.bias = 0.956644f;
            bestparams.pulsestrength = 1.50435f;
            bestparams.topbit = 0.942937f;
            bestparams.distance = 0.522595f;
            bestparams.stmix = 0.957164f;
            break;
        }
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
                float oldValue = bestparams.GetValue(i);
                float newValue = oldValue;
                if (randomNextDouble() > 0.5)
                {
                    newValue *= GetRandomValue();
                    if (i == Parameters::STMIX)
                    {
                        if (newValue > 1.f)
                            newValue = 1.f;
                    }
                }

                p.SetValue(i, newValue);
                changed = changed || oldValue != newValue;
            }
        }
        int score = p.Score(wave, reference, false, bestscore);
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
    std::stringstream ss(s);
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

    std::stringstream fileName;
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

    int wave = atoi(argv[1]);
    assert(wave == 3 || wave == 5 || wave == 6 || wave == 7); 

    char chip = argv[2][0];
    assert(chip >= 'A' && chip <= 'Z');

    std::vector<int> reference = ReadChip(wave, chip);

#ifndef NDEBUG
    for (std::vector<int>::iterator it = reference.begin(); it != reference.end(); ++it)
        std::cout << (*it) << std::endl;
#endif

    srand(time(0));

    Optimize(reference, wave, chip);
}
