/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "particle.h"
#include <math.h>

using namespace grapl::physics;

void Particle::update(float aDelta) {
    // Don't update particles with an infinite mass
    if (mInverseMass <= 0.0f) {
        return;
    }

    mPosition.addScaledVector(mVelocity, aDelta);

    Vector3 resultingAcceleration = mAcceleration;

    mVelocity.addScaledVector(resultingAcceleration, aDalta);

    mVelocity *= powf(mDamping, aDelta);
}
