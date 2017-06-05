/**
 * Copyright (c) 2016 Food Tiny Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

extern "C" {
#include "../../../unit_test.h"
}

#include "Arrays.hpp"

using namespace Java::Util;

/**
 *  Those test case below assume that :
 *  The array must be sorted into ascending order according to the natural ordering of its elements
 * */
TEST(JavaUtil, ArraysBinarySearch) {
    /// Given valid byte[] to test binary search - this test case wrapped <long>, <int>, <short> also
    byte arrayByte[5] = { 1 , 2 , 3 , 4 , 5 };

    // With correct key appeared inside array, return correct position
    byte keyByte = 4;
    int positionByte = 3;
    ASSERT_EQUAL(positionByte, Arrays::binarySearch(arrayByte, keyByte, 5));

    // With correct key2 but not appear inside array, return -1
    byte keyByte2 = 101;
    int positionByte2 = -1;
    ASSERT_EQUAL(positionByte2, Arrays::binarySearch(arrayByte, keyByte2, 5));

    /// Given valid char[] to test binary search
    char arrayChar[5] = { 'a' , 'b' , 'c' , 'd' , 'e' };

    // With correct key appeared inside array, return correct position
    char keyChar = 'b';
    int positionChar = 1;
    ASSERT_EQUAL(positionChar, Arrays::binarySearch(arrayChar, keyChar, 5));

    // With correct key but not appear inside array, return -1
    char keyChar2 = 'f';
    int positionChar2 = -1;
    ASSERT_EQUAL(positionChar2, Arrays::binarySearch(arrayChar, keyChar2, 5));

    /// Given valid double[] to test binary search - this test case wrapped <float> also
    double arrayDouble[6] = { 15.5 , 17.7 , 32.9 , 51.4 , 64.3 , 69.9};

    // With correct key appeared inside array, return correct position
    double keyDouble = 15.5;
    int positionDouble = 0;
    ASSERT_EQUAL(positionDouble, Arrays::binarySearch(arrayDouble, keyDouble, 6));

    // With correct key2 but not appear inside array, return -1
    double keyDouble2 = 65;
    int positionDouble2 = -1;
    ASSERT_EQUAL(positionDouble2, Arrays::binarySearch(arrayDouble, keyDouble2, 6));

    /// Given valid Integer[] to test binary search with Object
    Integer arrayObject[5] = { Integer(1) , Integer(2) , Integer(3), Integer(4) , Integer(5) };

    // With correct key appeared inside array, return correct position
    Integer keyObject = Integer(5);
    int positionObject = 4;
    ASSERT_EQUAL(positionObject, Arrays::binarySearch(arrayObject, keyObject, 5));

    // With correct key2 but not appear inside array, return -1
    Integer keyObject2 = Integer(99);
    int positionObject2 = -1;
    ASSERT_EQUAL(positionObject2, Arrays::binarySearch(arrayObject, keyObject2, 5));

}

TEST(JavaUtil, ArraysSort) {
    /// Given valid arrayLong[] to test Arrays::sort() with arrayLongSorted[] - this test case wrapped <byte>, <int>, <short>
    long arrayLong[5] = { 5 , 2 , 4 , 1 , 7};
    long arrayLongSorted[5] = { 1 , 2 , 4 , 5 , 7 };
    Arrays::sort(arrayLong, 0, 4);

    // Test true: all elements inside arrayLong[] must be equal arrayLongSorted[]
    for (int index = 0; index < 5; ++index) {
        ASSERT_EQUAL(arrayLongSorted[index], arrayLong[index]);
    }

    /// Given valid arrayLong[] to test Arrays::sort() with arrayCharSorted[]
    char arrayChar[5] = { 'b' , 'q' , 'y' , 'z' , 'u'};
    char arrayCharSorted[5] = { 'b' , 'q' , 'u' , 'y' , 'z' };
    Arrays::sort(arrayChar, 0, 4);

    // Test true: all elements inside arrayChar[] must be equal arrayCharSorted[]
    for (int index = 0; index < 5; ++index) {
        ASSERT_EQUAL(arrayCharSorted[index], arrayChar[index]);
    }

    /// Given valid arrayFloat[] to test Arrays::sort() with arrayFloatSorted[] - this test case wrapped <double> also
    float arrayFloat[5] = { 5.1 , 12.7 , 0.2 , 22.3 , 18.5 };
    float arrayFloatSorted[5] = { 0.2 , 5.1 , 12.7 , 18.5 , 22.3 };
    Arrays::sort(arrayFloat, 0, 4);

    // Test true: all elements inside arrayFloat[] must be equal arrayFloatSorted[]
    for (int index = 0; index < 5; ++index) {
        ASSERT_EQUAL(arrayFloatSorted[index], arrayFloat[index]);
    }
}

TEST(JavaUtil, ArraysCopyOf) {
    /// Give valid arrayBoolean[] and arrayLength to test copyOf
    boolean arrayBoolean[5] = { false, false, false, false, true };
    int arrayLength = 5;

    // Test with newLength that less than arrayLength
    int newLength = 3;
    boolean *copyArray = Arrays::copyOf(arrayBoolean, arrayLength, newLength);

    boolean resultArray[] = { false, false, false };
    for (int index = 0; index < newLength; ++index) {
        ASSERT_TRUE(resultArray[index] == copyArray[index]);
    }

}