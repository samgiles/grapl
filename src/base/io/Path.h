/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef Path_h__
#define Path_h__

#include <string>

/**
 * OS independent file path utiltiies and representation
 */
class Path {
    public:
        /* Returns true if the given path is an absolute path */
        static bool isAbsolute(const std::string path);
};

#endif // Path_h__

