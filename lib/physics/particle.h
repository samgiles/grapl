/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include "math/vector.h"

namespace grapl { namespace physics {

class Particle {
    protected:
        // Holds the position of the particle in world space
        math::Vector3 mPosition;

        // Holds the linear velocity of the particle
        math::Vector3 mVelocity;

        // Holds the acceleration of the particle
        math::Vector3 mAcceleration;

        // Holds the accumulated force using D'Alembert's principle to apply
        // the accumulated acting forces
        math::Vector3 mForceAccumulator;

        // Damping is required to remove numerical instability in non-exact
        // floating point operations
        float mDamping;

        // It's better to store inverse mass - it's easier to integrate and
        // immovable objects (infinite mass) are more useful in a game
        float mInverseMass;

        void clearAccumulator();

    public:
        void update(const float aDelta);

        void addForce(const math::Vector3& aForce);
};

}}
