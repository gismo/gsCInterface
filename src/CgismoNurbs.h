/** @file CgismoNurbs.h

    @brief C interface umbrella for the gsNurbs module.

    Include only what you use: this header exposes the C API of the
    gsNurbs part of G+Smo without dragging in the whole library.

    This file is part of the G+Smo library.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <gsCore/gsExport.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCError.h>

#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCNurbsCreator.h>
