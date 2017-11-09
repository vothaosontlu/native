/**
 * Copyright 2017 Food Tiny Project. All rights reserved.
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

#include <chrono>
#include "Date.hpp"
#include "../../lang/IllegalArgumentException/IllegalArgumentException.hpp"

/**
 * Only default constructor can refresh new time
 * Every single set value to this class will remove refreshFlag
 * - mean this class will be not available to refresh new time
 *
 */
Date::Date() {
    this->initializeDate(time(nullptr));
}

Date::Date(long int year, long int month, long int date) {
    this->initializeDate(year, month, date, 0, 0, 0);
}

Date::Date(long int year, long int month, long int date, long int hour, long int minute) {
    this->initializeDate(year, month, date, hour, minute, 0);
}

Date::Date(long int year, long int month, long int date, long int hour, long int minute, long int second) {
    this->initializeDate(year, month, date, hour, minute, second);
}

Date::Date(long long date) {
    long long timer = date;
    this->initializeDate(timer);
}

Date::Date(String inputString) {
    long long timer = Date::parse(inputString);
    this->initializeDate(timer);
}

Date::~Date() {
    if (this->backUp != nullptr) {
        free(this->backUp);
    }
}

void Date::setDate(long int date) {
    this->localTimer->tm_mday = date;
    this->updateDateStatus();
}

void Date::setHours(long int hours) {
    this->localTimer->tm_hour = hours;
    this->updateDateStatus();
}

void Date::setMinutes(long int minutes) {
    this->localTimer->tm_min = minutes;
    this->updateDateStatus();
}

void Date::setMonth(long int month) {
    this->localTimer->tm_mon = month;
    this->updateDateStatus();
}

void Date::setSeconds(long int seconds) {
    this->localTimer->tm_sec = seconds;
    this->updateDateStatus();
}

void Date::setTime(long long time) {
    this->initializeDate(time);
}

void Date::setYear(long int year) {
    // LocalTimer just keep year since 1900
    this->localTimer->tm_year = year;
    this->updateDateStatus();
}

long int Date::getDate() const {
    return this->localTimer->tm_mday;
}

long int Date::getDay() const {
    return this->localTimer->tm_wday;
}

long int Date::getHours() const {
    return this->localTimer->tm_hour;
}

long int Date::getMinutes() const {
    return this->localTimer->tm_min;
}

long int Date::getMonth() const {
    return this->localTimer->tm_mon;
}

long int Date::getSeconds() const {
    return this->localTimer->tm_sec;
}

long int Date::getYear() const {
    return this->localTimer->tm_year;
}

long long Date::getTime() const {
    return this->timer;
}

long int Date::getTimezoneOffset() const {
    return (int) -(this->localTimer->tm_gmtoff / 60);
}

boolean Date::after(Date specifiedDate) const {
    return this->timer > specifiedDate.timer;
}

boolean Date::before(Date specifiedDate) const {
    return this->timer < specifiedDate.timer;
}

long int Date::compareTo(const Date &anotherDate) const {
    long long timeOffset = this->timer - anotherDate.timer;

    if (timeOffset < 0) {
        return -1;
    }

    if (timeOffset > 0) {
        return 1;
    }

    return 0;
}

String Date::toString() const {
    return this->backUp;
}

long long Date::UTC(long int year, long int month, long int date, long int hour, long int minute, long int second) {
    Date tempDate = Date(year, month, date, hour, minute, second);
    return Date::getUTCTime(tempDate.getTime());
}

Date Date::clone() {
    Date clone = *this;
    return clone;
}

String Date::toLocaleString() const {
    string pattern = (string) "%b %d, %Y %I:%M:%S %p";
    return this->timeToString(pattern, this->localTimer);
}

String Date::toGMTString() const {
    string pattern = (string) "%d %b %Y %T GMT";

    const time_t utcTime = getUTCTime(this->timer);
    tm *utcTimer = localtime(&utcTime);

    return this->timeToString(pattern, utcTimer);
}

long int Date::hashCode() const {
    return Object::hashCode();
}

String Date::removeBracket(String inputString) {
    long int closeBracketOffSet = inputString.indexOf(')');
    long int openBracketOffSet = inputString.indexOf('(');

    while (openBracketOffSet != -1 && closeBracketOffSet > openBracketOffSet) {
        inputString = inputString.subString(0, openBracketOffSet) + inputString.subString(closeBracketOffSet + 1);
        openBracketOffSet = inputString.indexOf('(');
        closeBracketOffSet = inputString.indexOf(')');
    }

    return inputString;
}

long long Date::parse(String inputString) {
    long int year = Integer::MIN_VALUE;
    long int month = -1;
    long int dayOfMonth = -1;
    long int hour = -1;
    long int minute = -1;
    long int second = -1;
    long int timeZoneOffset = -1;

    Array<String> wordTable = {
            "am", "pm",
            "monday", "tuesday", "wednesday", "thursday", "friday",
            "saturday", "sunday",
            "january", "february", "march", "april", "may", "june",
            "july", "august", "september", "october", "november", "december",
            "gmt", "ut", "utc", "est", "edt", "cst", "cdt",
            "mst", "mdt", "pst", "pdt"
    };

    Array<int> actionTable = {
            14, 1, 0, 0, 0, 0, 0, 0, 0,
            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
            10000 + 0, 10000 + 0, 10000 + 0,    // GMT/UT/UTC
            10000 + 5 * 60, 10000 + 4 * 60,     // EST/EDT
            10000 + 6 * 60, 10000 + 5 * 60,     // CST/CDT
            10000 + 7 * 60, 10000 + 6 * 60,     // MST/MDT
            10000 + 8 * 60, 10000 + 7 * 60      // PST/PDT
    };

    char previousChar = '\0';
    char currentChar;

    if (inputString.isEmpty()) {
        throw InterruptedException();
    }

    inputString = Date::removeBracket(inputString);

    long int stringLength = inputString.length();
    long int index = 0;

    while (index < stringLength) {
        currentChar = inputString.charAt(index);
        if (currentChar <= ' ' || currentChar == ',') {
            index++;
            continue;
        }
        if (currentChar >= '0' && currentChar <= '9') {
            long int currentNumber = Date::getSequenceNumber(inputString, index);
            if (index < stringLength) {
                currentChar = inputString.charAt(index);
            }

            if ((previousChar == '+' || previousChar == '-')
                && year != Integer::MIN_VALUE) {
                // timezone offset
                if (currentNumber < 24) {
                    currentNumber = currentNumber * 60; // EG. "GMT-3"
                } else {
                    currentNumber = currentNumber % 100 + currentNumber / 100 * 60; // eg "GMT-0430"
                }

                if (previousChar == '+') {
                    currentNumber = -currentNumber;
                }   // plus means east of GMT

                if (timeZoneOffset != 0 && timeZoneOffset != -1) {
                    throw InterruptedException();
                }

                timeZoneOffset = currentNumber;
            } else if (currentNumber >= 70) {
                if (year != Integer::MIN_VALUE) {
                    throw InterruptedException();
                } else if (currentChar <= ' ' || currentChar == ','
                           || currentChar == '/' || index >= stringLength) {
                    year = currentNumber;
                } else {
                    throw InterruptedException();
                }
            } else if (currentChar == ':') {
                if (hour < 0) {
                    hour = (byte) currentNumber;
                } else if (minute < 0) {
                    minute = (byte) currentNumber;
                } else {
                    throw InterruptedException();
                }
            } else if (currentChar == '/') {
                if (month < 0) {
                    month = (byte) (currentNumber - 1);
                } else if (dayOfMonth < 0) {
                    dayOfMonth = (byte) currentNumber;
                } else {
                    throw InterruptedException();
                }
            } else if (index < stringLength && currentChar != ','
                       && currentChar > ' ' && currentChar != '-') {

                throw InterruptedException();
            } else if (hour >= 0 && minute < 0) {
                minute = (byte) currentNumber;
            } else if (minute >= 0 && second < 0) {
                second = (byte) currentNumber;
            } else if (dayOfMonth < 0) {
                dayOfMonth = (byte) currentNumber;
            } else if (year == Integer::MIN_VALUE
                       && month >= 0 && dayOfMonth >= 0) {

                year = currentNumber;
            } else {
                throw InterruptedException();
            }
            previousChar = '\0';
        } else if (currentChar == '/' || currentChar == ':'
                   || currentChar == '+' || currentChar == '-') {

            previousChar = currentChar;
            index++;
        } else {
            long int sequenceStart = index - 1;
            String currentWord = Date::getSequenceChar(inputString, index);
            if (index <= sequenceStart + 1) {
                throw InterruptedException();
            }

            long int tableIndex;
            for (tableIndex = wordTable.length; --tableIndex >= 0;) {
                if (wordTable[tableIndex].regionMatches(true, 0, currentWord, 0,
                                                        currentWord.length())) {

                    long int action = actionTable[tableIndex];
                    if (action != 0) {
                        if (action == 1) {  // pm
                            if (hour > 12 || hour < 1) {
                                throw InterruptedException();
                            } else if (hour < 12) {
                                hour += 12;
                            }
                        } else if (action == 14) {  // am
                            if (hour > 12 || hour < 1) {
                                throw InterruptedException();
                            } else if (hour == 12) {
                                hour = 0;
                            }
                        } else if (action <= 13) {  // month!
                            if (month < 0) {
                                month = (byte) (action - 2);
                            } else {
                                throw InterruptedException();
                            }
                        } else {
                            timeZoneOffset = action - 10000;
                        }
                    }
                    break;
                }
            }

            if (tableIndex < 0)
                throw InterruptedException();
            previousChar = 0;
        }
    }

    if (year == Integer::MIN_VALUE || month < 0 || dayOfMonth < 0) {
        throw InterruptedException();
    }

    // Parse 2-digit years within the correct default century.
    if (year < 100) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        struct tm *currentTime = std::localtime(&now_c);

        currentTime->tm_year += 1900;
        long int defaultCenturyStart = currentTime->tm_year - 80;
        year += (defaultCenturyStart / 100) * 100;

        if (year < defaultCenturyStart) {
            year += 100;
        }
    }

    // Set time to 0 if inputString don't have time specified
    if (second < 0) {
        second = 0;
    }

    if (minute < 0) {
        minute = 0;
    }

    if (hour < 0) {
        hour = 0;
    }

    // Get timestamp
    tm localTimer = {0};

    localTimer.tm_year = year - 1900;
    localTimer.tm_mon = month;
    localTimer.tm_mday = dayOfMonth;
    localTimer.tm_hour = hour;
    localTimer.tm_min = minute;
    localTimer.tm_sec = second;

    long long result = mktime(&localTimer);

    // Add timeZoneOffset to result
    if (timeZoneOffset == -1) {
        return result;
    }

    long long offsetFromUTC = Date::getOffsetFromUTC();

    return result + (timeZoneOffset * 60) - offsetFromUTC;
}

long long Date::getOffsetFromUTC() {
    time_t currentTime;
    struct tm *timeInfo;

    time(&currentTime);
    timeInfo = gmtime(&currentTime);
    time_t utc = mktime(timeInfo);
    timeInfo = localtime(&currentTime);
    time_t local = mktime(timeInfo);

    // Get offset in hours from UTC
    double offsetFromUTC = difftime(utc, local); // HOUR_IN_SECOND;

    return (long) offsetFromUTC;
}

long int Date::getSequenceNumber(const String &inputString, long int &index) {
    boolean isNumber;
    boolean isInRange;
    char currentChar;
    long int currentNumber = 0;
    long int lengthInputString = inputString.length();

    do {
        currentChar = inputString.charAt(index);
        isNumber = ('0' <= currentChar) && (currentChar <= '9');
        if (isNumber) {
            currentNumber = currentNumber * 10 + (currentChar - '0');
            ++index;
        }
        isInRange = index < lengthInputString;

    } while (isInRange && isNumber);

    return currentNumber;
}

String Date::getSequenceChar(const String &inputString, long int &index) {
    boolean isInRange;
    boolean isAlphabet;
    char currentChar;

    String sequenceChar = "";
    long int lengthInputString = inputString.length();

    do {
        currentChar = inputString.charAt(index);
        /* Check is the char accepted : A -> Z, a -> z */
        isAlphabet = ('A' <= currentChar && currentChar <= 'Z')
                     || ('a' <= currentChar && currentChar <= 'z');

        if (isAlphabet) {
            sequenceChar += currentChar;
            index++;
        }

        isInRange = index < lengthInputString;
    } while (isInRange && isAlphabet);

    return sequenceChar;
}

void Date::updateDateStatus() {
    // Update changes
    this->timer = mktime(this->localTimer);

    String pattern;

    if (this->backUp != nullptr) {
        free(this->backUp);
    }

#ifdef LINUX
    if (this->getTimezoneOffset() == 0) {
        pattern = (string) "%a %b %d %T UTC %Y";
    }
#endif

#ifdef WINDOWS
    if (this->getTimezoneOffset() == 0) {
        pattern = (string) "%a %b %d %T GMT %Y";
    }
#endif

    pattern = (string) "%a %b %d %T %Z %Y";
    String convertResult = this->timeToString(pattern.toString(), this->localTimer);
    this->backUp = strdup(convertResult.toCharPointer());
}

void Date::initializeDate(long int year, long int month, long int date,
                          long int hour, long int minute, long int second) {
    tm localTimer = {0};

    localTimer.tm_year = year;
    localTimer.tm_mon = month;
    localTimer.tm_mday = date;
    localTimer.tm_hour = hour;
    localTimer.tm_min = minute;
    localTimer.tm_sec = second;

    this->timer = mktime(&localTimer);
    this->localTimer = localtime(&this->timer);

    this->updateDateStatus();
}

void Date::initializeDate(long long timer) {
    this->timer = timer;
    this->localTimer = localtime(&this->timer);

    this->updateDateStatus();
}

String Date::timeToString(String pattern, tm *timeManagement) const {
    size_t size = 100;

    string holdResult = static_cast<string> (calloc(size, sizeof(char)));
    strftime(holdResult, size, pattern.toCharPointer(), timeManagement);

    String result = holdResult;
    free(holdResult);
    return result;
}

long long Date::getUTCTime(long long timer) {
    tm tempTimer = {0};
    tm *utcTimer = gmtime_r((time_t*) timer, &tempTimer);

    return mktime(utcTimer);
}

boolean Date::equals(Date obj) const {
    return this->getTime() == obj.getTime();
}

Date::Date(const Date &anotherDate) {
    this->initializeDate(anotherDate.timer);
}

Date &Date::operator=(const Date &anotherDate) {
    this->initializeDate(anotherDate.timer);
}