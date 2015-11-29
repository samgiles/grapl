/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Path.h"
#include "base/internal_logging.h"

std::string Path::normalize(const std::string& aPath) {
    std::string copy = aPath;
    normalizeInPlace(copy);
    return copy;
}

inline const bool isSeparator(const char aCharacter) {
#ifdef POSIX
    return aCharacter == '/';
#else
    return aCharacter == '/' || aCharacter == '\\';
#endif
}

void Path::normalizeInPlace(std::string& aPath) {

    if (aPath.empty()) {
        aPath.push_back('.');
        return;
    }

    uint32_t index = aPath.size();
    uint32_t lastIndex = index - 1;

    uint32_t sawDots = 0;
    uint32_t charsSinceLastSeparator = 0;
    uint32_t skip = 0;

    while(index--) {
        char currentChar = aPath.at(index);

        if (currentChar == '.') {
            sawDots++;
            charsSinceLastSeparator++;
        } else if (isSeparator(currentChar)) {
            if (charsSinceLastSeparator == 0) {

                // This check preserves the trailing slash
                if (index != lastIndex) {
                    aPath.erase(index, 1);
                }
            } else if (sawDots == 1 && charsSinceLastSeparator == 1) {
                aPath.erase(index, 2);
            } else if (sawDots == 2 && charsSinceLastSeparator == 2) {
                skip++;
                aPath.erase(index, 3);
            } else if (skip > 0) {
                skip--;
                aPath.erase(index, charsSinceLastSeparator + 1);
            }

#ifdef WIN32
            // On Windows, convert '/' to '\\'
            if (currentChar == '/') {
                aPath[index] = '\\';
            }
#endif
            charsSinceLastSeparator = 0;
            sawDots = 0;
        } else {
            charsSinceLastSeparator++;
        }
    }

    if (sawDots == 1 && charsSinceLastSeparator == 1) {
        aPath.erase(0, 2);
    }

    if (!Path::isAbsolute(aPath)) {
        while(skip--) {
            aPath.insert(0, _GR_PATH_TRAVERSAL);
        }
    }

    return;
}

bool Path::isAbsolute(const std::string& aPath) {
    if (aPath.empty()) {
        return false;
    }

    const char* data = aPath.data();

    #ifndef WIN32

    return data[0] == '/';

    #else

    // On Windows an absolute path (or more accurately, non-relative path) is something
	// that falls under any one of these definitions:
    // 1. A UNC name of any format, which always start with two backslash
    // characters ("\\").
    // 2. A disk designator with a backslash, for example "C:\" or "d:\".
    // 3. A single backslash, for example, "\directory" or "\file.txt". This is
    // also referred to as an absolute path.
    // (https://msdn.microsoft.com/en-gb/library/windows/desktop/aa365247%28v=vs.85%29.aspx#paths)

    // This covers 1 and 3, every path that begins with a '\' must be absolute
    // - we're not verifying validity of paths here..
    if (data[0] == '\\') {
        return true;
    }

    // This is safe to do - we've already checked that the string isn't empty so
    // we know that data[0] has a real character, and data[1] will be at least
    // a NULL terminator so we won't read bad memory.
    if (data[0] == '/' && data[1] == '/') {
        return true;
    }

    // By this point, all absolute paths need to be qualified by at least 3
    // characters

    if (aPath.size() >= 3) {

        // TODO: Do we really need to verify the drive letter is correct?
        if ((data[0] >= 'a' && data[0] <= 'z') ||
            (data[0] >= 'A' && data[0] <= 'Z')) {

            return data[1] == ':' && (data[2] == '\\' || data[2] == '/') ;
        }
    }

    return false;
    #endif
}
