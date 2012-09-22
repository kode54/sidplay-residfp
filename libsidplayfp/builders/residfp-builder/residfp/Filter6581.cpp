/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2011-2012 Leando Nini <drfiemost@users.sourceforge.net>
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

#define FILTER6581_CPP

#include "Filter6581.h"

namespace reSIDfp
{

Filter6581::~Filter6581() {

	delete hpIntegrator;
	delete bpIntegrator;
	delete [] f0_dac;
}

void Filter6581::input(const int sample) {
	ve = (sample * voiceScaleS14 * 3 >> 10) + mixer[0][0];
}

void Filter6581::updatedCenterFrequency() {
	const int Vw = f0_dac[fc];
	hpIntegrator->setVw(Vw);
	bpIntegrator->setVw(Vw);
}

void Filter6581::updatedResonance() {
	currentResonance = gain[~res & 0xf];
}

void Filter6581::updatedMixing() {
	currentGain = gain[vol];

	int ni = 0;
	int no = 0;

	if (filt1) {
		ni++;
	} else {
		no++;
	}
	if (filt2) {
		ni++;
	} else {
		no++;
	}
	if (filt3) {
		ni++;
	} else if (!voice3off) {
		no++;
	}
	if (filtE) {
		ni++;
	} else {
		no++;
	}
	currentSummer = summer[ni];

	if (lp) {
		no++;
	}
	if (bp) {
		no++;
	}
	if (hp) {
		no++;
	}
	currentMixer = mixer[no];
}

void Filter6581::setFilterCurve(const double curvePosition) {
	delete [] f0_dac;
	f0_dac = FilterModelConfig::getInstance()->getDAC(FilterModelConfig::getInstance()->getDacZero(curvePosition));
	updatedCenterFrequency();
}

} // namespace reSIDfp
