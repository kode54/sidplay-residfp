/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 1998, 2002 by LaLa <LaLa@C64.org>
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

//
// STIL Common header
//

//
// Contains some definitions common to STIL
//

#ifndef _STILCOMM_H
#define _STILCOMM_H

#include "stildefs.h"

// convertSlashes()
//
// FUNCTION: Converts slashes to the one the OS uses to access files.
// ARGUMENTS:
//      str - what to convert
// RETURNS:
//      NONE
//
extern void convertSlashes(char *str);

// convertToSlashes()
//
// FUNCTION: Converts OS specific dir separators to slashes.
// ARGUMENTS:
//      str - what to convert
// RETURNS:
//      NONE
//
extern void convertToSlashes(char *str);

#endif // _STILCOMM_H