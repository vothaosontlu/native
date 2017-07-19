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

#ifndef JAVA_UTIL_QUEUE_HPP_
#define JAVA_UTIL_QUEUE_HPP_
#include "../../Lang.hpp"
#include "../Collection/Collection.hpp"

using namespace Java::Util;

namespace Java {
    namespace Util {

        template <typename E>
        class Queue: public Collection<E> {
        private:
            Queue();
            ~Queue();

        protected:
            virtual boolean add(E &e) = 0; ///Inserts the specified element into this queue
            virtual boolean offer(E &e) = 0; ///Inserts the specified element into this queue
            virtual E peek() const = 0; ///Retrieves, but does not remove, the head of this queue, or returns NULL if this queue is empty.
            virtual E poll() = 0; ///Retrieves and removes the head of this queue, or returns NULL if this queue is empty.
            virtual E remove() = 0; ///Retrieves and removes the head of this queue
        };
    }
}

#endif //JAVA_UTIL_QUEUE_HPP_