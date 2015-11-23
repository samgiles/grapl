/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef Path_h__
#define Path_h__

#include "base/Error.h"
#include <string>

#ifdef WIN32
#define _SEPARATOR_CHAR '\\'
#define _SEPARATOR_STR "\\"
#else
#define _SEPARATOR_CHAR '/'
#define _SEPARATOR_STR  "/"
#endif

#define _GR_PATH_TRAVERSAL _SEPARATOR_STR ".."


/**
 * OS independent file path utiltiies and representation
 */
class Path {

    public:
        static const char SEPARATOR = _SEPARATOR_CHAR;
    public:
        /// Normalize a string, returning a newly allocated string
        static std::string normalize(const std::string aPath);

        /// Normalize a string, without allocating if possible.
        /// Will probably alter the data in aPath.
        static void normalizeInPlace(std::string* aPath);

        /* Returns true if the given path is an absolute path */
        static bool isAbsolute(const std::string aPath);

};

#undef _SEPARATOR_CHAR

#endif // Path_h__

