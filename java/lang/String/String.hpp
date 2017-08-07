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

#ifndef JAVA_LANG_STRING_STRING_HPP_
#define JAVA_LANG_STRING_STRING_HPP_

#include <typeinfo>
#include <regex>
#include <string>

#include "../Object/Object.hpp"
#include "../CharSequence/CharSequence.hpp"
#include "../../io/Serializable/Serializable.hpp"
#include "../../lang/Comparable/Comparable.hpp"
#include "../../lang/Number/Number.hpp"
#include "../StringBuilder/StringBuilder.hpp"
#include "../StringBuffer/StringBuffer.hpp"

using namespace Java::IO;

namespace Java {
	namespace Lang {

		class String :
				public Object,
				public virtual Serializable,
				public virtual Comparable<String>,
				public virtual CharSequence {
		private:
			string original;
			int size = 0;

		public:
            /**
             * Initializes a newly created String object
             * so that it represents an empty character sequence.
             */
			String();

            /**
             * Initializes a newly created String object
             * so that it represents the same sequence of characters as the argument.
             *
             * @param target
             */
            String(const String &target);

            /**
             * Constructs a new String by decoding the specified array of bytes.
             *
             * @param byteArray
             */
            String(Array<byte> &byteArray);

            /**
             * Allocates a new string that contains the sequence
             * of characters currently contained in the string builder.
             *
             * @param stringBuffer
             */
            String(const StringBuilder &stringBuffer);

            /**
             * Allocates a new String so that it represents the sequence
             * of characters currently contained in the character array argument.
             *
             * @param charArray
             */
            String(Array<char> &charArray);

            /**
             * Allocates a new string that contains the sequence
             * of characters currently contained in the string buffer.
             *
             * @param stringBuffer
             */
            String(const StringBuffer &stringBuffer);

            /**
             * Constructs a new String by decoding the specified array of bytes
             * using the specified charset.
             *
             * @param byteArray
             * @param charsetName
             */
            String(Array<byte> byteArray, String charsetName);

            /**
             * Constructs a new String by decoding the specified array of bytes
             * using the specified charset.
             *
             * @param byteArray
             * @param charset
             */
            // String(Array<byte> byteArray, Charset charset)

            /**
             * Allocates a new String so that it represents the sequence
             * of characters currently contained in the character array argument.
             *
             * @param charArray
             * @param share
             */
            String(Array<char> &charArray, boolean share);

            /**
             * Allocates a new String that contains characters
             * from a subarray of the character array argument.
             *
             * @param charArray
             * @param offset
             * @param count
             * @throw IndexOutOfBoundsException If the offset and count arguments index
             * characters outside the bounds of the value array
             */
            String(Array<char> &charArray, int offset, int count);

            /**
             * Allocates a new String that contains characters
             * from a subarray of the Unicode code point array argument.
             *
             * @param codePoints
             * @param offset
             * @param count
             * @throw IllegalArgumentException If any invalid Unicode
             * code point is found in codePoints
             * @throw IndexOutOfBoundsException If the offset and count
             * arguments index characters outside the bounds of the codePoints array
             */
            String(Array<int> codePoints, int offset, int count);

            /**
             * Constructs a new String by decoding the specified
             * subarray of bytes using the platform's default charset.
             *
             * @param byteArray
             * @param offset
             * @param length
             * @throwIndexOutOfBoundsException If the offset and the length arguments index
             * characters outside the bounds of the bytes array
             */
            String(Array<byte> &byteArray, int offset, int length);

            /**
             * Constructs a new String by decoding the specified
             * subarray of bytes using the specified charset
             *
             * @param byteArray
             * @param offset
             * @param length
             * @param charset
             * @throw IndexOutOfBoundsException If the offset and length arguments index
             * characters outside the bounds of the bytes array
             */
            // String(Array<byte> &byteArray, int offset, int length, Charset charset);

            /**
             * Constructs a new String by decoding the specified
             * subarray of bytes using the specified charset.
             *
             * @param bytes
             * @param offset
             * @param length
             * @param charsetName
             * @throw java.io.UnsupportedEncodingException If the named charset is not supported
             * @throw IndexOutOfBoundsException If the offset and length arguments index
             * characters outside the bounds of the bytes array
             */
            String(byte bytes[], int offset, int length, String charsetName);

            /**
             * Construct a new String from target char
             *
             * @param target
             */
            String(char target);

            /**
             * Construct a new String from specific const_string
             *
             * @param original
             */
			String(const_string original);

            /**
             * Construct a new String from specific string
             *
             * @param original
             */
			String(string original);

            /**
             * Construct a new String from specific std::string
             *
             * @param target
             */
			String(const std::string &target);

            /**
             * Destructor
             */
			~String();

		public:
            /**
             * Return size of String
             *
             * @return
             */
			int getSize() const;

            /**
             * String character at index
             *
             * @param index
             * @return String
             */
			char charAt(int index) const;

			int codePointAt();
			int codePointBefore();
			int codePointCount(int beginIndex, int endIndex);
			String clone();
			virtual int compareTo(const String &o) const override;
			int compareToIgnoreCase(String str) const;
			String concat(String str);
			boolean contains(const CharSequence &str);
			boolean contentEquals(const CharSequence &cs);
			//boolean contentEquals(const StringBuffer &str);
			static String copyValueOf(const Array<char> &data);
			static String copyValueOf(const Array<char> &data, int offset, int count);
			boolean endsWith(const String &suffix) const;
			template <class T>
			boolean equals(T anObject) const {
				if (Object::equals(anObject)) {
					return true;
				}
				if (instanceof<String>(anObject)) {
					return (boolean) string_equals(original, anObject.toString());
				}
				return true;
			}
			Array<byte> getBytes() const;
			String getStringFromIndex(int index);
			// Array<byte> getBytes(const Charset &);
			static String fromCharArray(Array<char> &chars);
			int indexOf(int ch) const;
			int indexOf(int ch, int fromIndex) const;
			int indexOf(String str) const;
			int indexOf(String str, int fromIndex) const;
			boolean isEmpty() const;
			int lastIndexOf(int ch);
			int lastIndexOf(int ch, int fromIndex);
			int lastIndexOf(String str) const;
			int lastIndexOf(String str, int fromIndex) const;
			int length() const;
			boolean matches(String regex) const;
			String replace(char oldChar, char newChar) const;
			String replaceAll(String regex, String replacement) const;
			String replaceFirst(String regex, String replacement) const;
			Array<String> split(String regex) const;
			Array<String> split(String regex, int limit) const;
			boolean startsWith(String prefix) const;
			boolean startsWith(String prefix, int toffset) const;
			Array<char> toCharArray() const;
			String toLowerCase() const;
			String toUpperCase();
			String trim();
			string toString() const;
			static String valueOf(boolean target);
			static String valueOf(char target);
			static String valueOf(string target);
			static String valueOf(short target);
			static String valueOf(int target);
			static String valueOf(long target);
			static String valueOf(float target);
			static String valueOf(double target);

			template<typename T, typename... Args>
			static String format(const String& format, T value, Args... args) {
				std::string result;
				std::string inputString(format.toString());
				std::smatch matchResult;
                std::regex reg("%(\\d+\\$)?([-#+0,(\\<]*)?(\\d+)?(\\.\\d+)?([tT])?([a-zA-Z%])");
                while (true) {
                    if (std::regex_search(inputString, matchResult, reg)) {
                        result += matchResult.prefix();
                        result += printObject(matchResult[0], value);
                        if ('%' == result.back()) {
                            inputString = matchResult.suffix().str();
                            continue;
                        }
                        return result + std::string(String::format(matchResult.suffix().str().c_str(), args...).toString());
                    } else {
                        result += inputString;
                        break;
                    }
                }
				return String(result.c_str());
			}

		private:
			static String format(const String& format);
            static std::string print(const std::string& format, short value);
			static std::string print(const std::string& format, int value);
            static std::string print(const std::string& format, long value);
            static std::string print(const std::string& format, unsigned short value);
            static std::string print(const std::string& format, unsigned int value);
            static std::string print(const std::string& format, unsigned long value);
            static std::string print(const std::string& format, double value);
            static std::string print(const std::string& format, float value);
            static std::string print(const std::string& format, char* value);

            template<typename T>
			static std::string printObject(const std::string& format, T value) {
				std::string result;
				char lastChar = format.back();
				switch (lastChar) {
					case 'd':
						if (instanceof<Number>(value))
							result = String::print(format, ((Number*)&value)->longValue());
						else if (typeid(short) == typeid(value))
							result = String::print(format, (short)value);
                        else if (typeid(int) == typeid(value))
                            result = String::print(format, (int)value);
                        else if (typeid(long) == typeid(value))
                            result = String::print(format, (long)value);
                        else if (typeid(unsigned short) == typeid(value))
                            result = String::print(format, (unsigned short)value);
                        else if (typeid(unsigned int) == typeid(value))
                            result = String::print(format, (unsigned int)value);
                        else if (typeid(unsigned long) == typeid(value))
                            result = String::print(format, (unsigned long)value);
						break;
					case 'f':
						if (instanceof<Number>(value))
							result = String::print(format, ((Number*)&value)->doubleValue());
						else if (typeid(float) == typeid(value))
                            result = String::print(format, (float)value);
                        else if (typeid(double) == typeid(value))
                            result = String::print(format, (double)value);
                        break;
					case 's':
						if (instanceof<String>(value))
							result = String::print(format, ((String*)&value)->toString());
						else if (typeid(char*) == typeid(value))
							result = String::print(format, (char*)value);
						break;
					case '%':
						result += lastChar;
						break;
				}
				return result;
			}

		public:
			boolean operator==(const String &target) const;
			boolean operator!=(const String &target) const;
			boolean operator<(const String &target) const;
			boolean operator>(const String &target) const;
			boolean operator<=(const String &target) const;
			boolean operator>=(const String &target) const;
			String operator+(const string &target);
			String operator+(const String &target);
			String operator=(const String &target);
			String operator+=(const String &target);
			String operator+=(const char &target);
			String operator+=(const_string target);
            String subString(int beginIndex);
			String subString(int from, int to);

		public:
			friend std::ostream &operator<<(std::ostream &os, const String &target) {
				os << target.original;
				return os;
			}

			friend String operator+(const_string target1, String const &target2) {
				String result;
				result = target1;
				result += target2;
				return result;
			}
		};
	}
}

#endif  // JAVA_LANG_STRING_STRING_HPP_