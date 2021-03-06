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

#include "../../../Test.hpp"
#include "IndexOutOfBoundsException.hpp"

using namespace Java::Lang;

TEST (JavaLangIndexOutOfBoundsException, Constructor) {
	// Constructs a new IndexOutOfBoundsException with null as its detail message.
	IndexOutOfBoundsException indexOutOfBoundsExceptionWithNullMessage;
	assertEquals("", indexOutOfBoundsExceptionWithNullMessage.getMessage());
	
	// Constructs a new IndexOutOfBoundsException with the specified detail message.
	IndexOutOfBoundsException indexOutOfBoundsExceptionWithMessage = IndexOutOfBoundsException("IndexOutOfBoundsException with the specified message");
	assertEquals("IndexOutOfBoundsException with the specified message", indexOutOfBoundsExceptionWithMessage.getMessage());
	
	// Constructs a new IndexOutOfBoundsException with the specified detail message and cause.
	IndexOutOfBoundsException indexOutOfBoundsExceptionWithMessageAndCause = IndexOutOfBoundsException("IndexOutOfBoundsException with the specified message and cause", &indexOutOfBoundsExceptionWithMessage);
	assertEquals("IndexOutOfBoundsException with the specified message and cause", indexOutOfBoundsExceptionWithMessageAndCause.getMessage());
	assertEquals("IndexOutOfBoundsException with the specified message", indexOutOfBoundsExceptionWithMessageAndCause.getCause()->getMessage());
	
	// Constructs a new IndexOutOfBoundsException with the specified cause.
	IndexOutOfBoundsException indexOutOfBoundsExceptionWithCause = IndexOutOfBoundsException(&indexOutOfBoundsExceptionWithMessageAndCause);
	assertEquals("IndexOutOfBoundsException with the specified message and cause", indexOutOfBoundsExceptionWithCause.getCause()->getMessage());
	assertEquals("IndexOutOfBoundsException with the specified message", indexOutOfBoundsExceptionWithCause.getCause()->getCause()->getMessage());
}

TEST (JavaLangIndexOutOfBoundsException, TryCatch) {
	try {
		throw IndexOutOfBoundsException("Throw IndexOutOfBoundsException");
	} catch (Exception e) {
		assertEquals("Throw IndexOutOfBoundsException", e.getMessage());
	}
}
