/**
 * Copyright (c) 2017 Food Tiny Project. All rights reserved.
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

#ifndef JAVAX_WS_RS_CLIENTERROREXCEPTION_CLIENTERROREXCEPTION_HPP
#define JAVAX_WS_RS_CLIENTERROREXCEPTION_CLIENTERROREXCEPTION_HPP

#include "../WebApplicationException/WebApplicationException.hpp"

using namespace Java::Lang;

namespace Javax {
    namespace Ws  {
        namespace Rs {
            class ClientErrorException : public WebApplicationException {
            public:
                ClientErrorException();
                ClientErrorException(String message);
                ClientErrorException(String message, Throwable *cause);
                ClientErrorException(Throwable *cause);
            };  // class ClientErrorException
        } // namespace Rs
    }  // namespace Ws
}  // namespace Javax


#endif // JAVAX_WS_RS_CLIENTERROREXCEPTION_CLIENTERROREXCEPTION_HPP
