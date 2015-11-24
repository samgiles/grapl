/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TestHarness.h"

#include "base/io/Path.h"
#include <string>

bool assertNormalize(std::string aIn, std::string aExpected) {
    std::string result = Path::normalize(aIn);
    bool correct = result == aExpected;
    if (!correct) {
        printf("Expected '%s'.  Was actually '%s'.\n", aExpected.c_str(), result.c_str());
    }
    return correct;
}

int main(int argc, char* argv[]) {
    int rv = 0;

    /// Path::isAbsolute Tests

    rv +=
    runTest("Test empty string !isAbsolute", []() {
        return !Path::isAbsolute("");
    });

    rv +=
    runTest("Test single component is absolute", []() {
        return Path::isAbsolute("/bar");
    });

    rv +=
    runPosixOnlyTest("Test isAbsolute('/a/b/c')", []() {
        return Path::isAbsolute("/a/b/c");
    });

    rv +=
    runPosixOnlyTest("Test !isAbsolute('a/b/c')", []() {
        return !Path::isAbsolute("a/b/c");
    });

    rv +=
    runPosixOnlyTest("Test !isAbsolute('../a/b')", []() {
        return !Path::isAbsolute("../a/b");
    });

    rv +=
    runPosixOnlyTest("Test !isAbsolute('./a/b'", []() {
        return !Path::isAbsolute("./a/b");
    });

    rv +=
    runWindowsOnlyTest("Test short/invalid path", []() {
        return
            !Path::isAbsolute("C:") &&
            !Path::isAbsolute("C")  &&
            !Path::isAbsolute("F:F");
    });

    rv +=
    runWindowsOnlyTest("Test isAbsolute('<driveletter>:\\Hello')", []() {
        return
            Path::isAbsolute("a:\\Hello") &&
            Path::isAbsolute("A:\\Hello") &&
            Path::isAbsolute("z:\\Hello") &&
            Path::isAbsolute("Z:\\Hello");
    });

    // Windows supports forward slashes with this form of path
    rv +=
    runWindowsOnlyTest("Test isAbsolute('<driveletter>:/Hello')", []() {
        return
            Path::isAbsolute("a:/Hello") &&
            Path::isAbsolute("A:/Hello") &&
            Path::isAbsolute("z:/Hello") &&
            Path::isAbsolute("Z:/Hello");
    });

    rv +=
    runWindowsOnlyTest("Test isAbsolute('\\\\Path')", []() {
        return Path::isAbsolute("\\\\Path");
    });

    rv +=
    runWindowsOnlyTest("Test isAbsolute('//Path/')", []() {
        return Path::isAbsolute("//Path/");
    });

    rv +=
    runWindowsOnlyTest("Test isAbsolute('\\Single\\Slash')", []() {
        return Path::isAbsolute("\\Single\\Slash");
    });

    /*
     * This '\\?\' prefix is not used as part of the path itself. They indicate
     * that the path should be passed to the system with minimal modification,
     * which means that you cannot use forward slashes to represent path
     * separators, or a period to represent the current directory, or double
     * dots to represent the parent directory. Basically, anything using this
     * prefix kind of has to be an absolute path for it to work.
     */
    rv +=
    runWindowsOnlyTest("Test isAbsolute('\\\\?\\a:\\Long\\Path')", []() {
        return
            Path::isAbsolute("\\\\?\\a:\\Long\\Path") &&
            Path::isAbsolute("\\\\?\\UNC\\Long\\Path");
    });

    rv +=
    runWindowsOnlyTest("Test !isAbsolute('..\\File.ext')", []() {
        return !Path::isAbsolute("..\\File.ext");
    });

    rv +=
    runWindowsOnlyTest("Test !isAbsolute('.\\File.ext')", []() {
        return !Path::isAbsolute(".\\File.ext");
    });

    rv +=
    runWindowsOnlyTest("Test !isAbsolute('<driveletter>:RelativePath')", []() {
        return
            !Path::isAbsolute("A:RelativePath") &&
            !Path::isAbsolute("a:RelativePath") &&
            !Path::isAbsolute("z:RelativePath") &&
            !Path::isAbsolute("Z:RelativePath");
    });

    rv +=
    runWindowsOnlyTest("Test !isAbsolute('A\\F\\ile.ext')", []() {
        return !Path::isAbsolute("A\\F\\ile.ext");
    });

    // Path::normalizeInPlace
    rv +=
    runTest("Empty string should be normalized to a '.'", []() {
        return assertNormalize("", ".");
    });

    rv +=
    runTest("Path with '..' components should resolve", []() {
        return assertNormalize("/path/to/resolve/../here", "/path/to/here");
    });

    rv +=
    runTest("Path::normalize", []() {
        return assertNormalize("a/path/./here", "a/path/here");
    });
    rv +=
    runTest("Should normalize with a '.' trailing (preserving trailing slash state)", []() {
        return
            assertNormalize("a/path/.", "a/path") &&
            assertNormalize("a/path/./", "a/path/");
    });

    rv +=
    runTest("Should normalize with a leading '.'", []() {
        return assertNormalize("./a/path", "a/path");
    });

    rv +=
    runTest("Normalized './fixtures///b/../b/c.js' should be 'fixtures/b/c.js'", []() {
        return assertNormalize("./fixtures///b/../b/c.js", "fixtures/b/c.js");
    });

    rv +=
    runTest("Normalized '/foo/../../../bar'", []() {
        return assertNormalize("/foo/../../../bar", "/bar");
    });

    rv +=
    runTest("Normalized 'a//b//../b'", []() {
        return assertNormalize("a//b//../b", "a/b");
    });

    rv +=
    runTest("Normalized 'a//b//./c'", []() {
        return assertNormalize("a//b//./c", "a/b/c");
    });

    rv +=
    runTest("Normalized 'a//b//.'", []() {
        return assertNormalize("a//b//.", "a/b");
    });

    rv +=
    runTest("Normalized '/a/b/c' should be the same", []() {
        return assertNormalize("/a/b/c", "/a/b/c");
    });

    rv +=
    runWindowsOnlyTest("Normalize './fixtures///b/../b/c.js' to 'fixtures\\b\\c.js'", []() {
        return assertNormalize("./fixtures///b/../b/c.js", "fixtures\\b\\c.js");
    });

    return rv;
}
