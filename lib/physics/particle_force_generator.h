/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

namespace grapl { namespace physics {

class ParticleForceGenerator {
    public:
        virtual void updateForce(Particle& aParticle, float aDelta) = 0;
};

}}
