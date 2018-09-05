// Copyright (c) 2015 Erwin Jansen
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef SRC_INCLUDE_JWT_JWT_H_
#define SRC_INCLUDE_JWT_JWT_H_

#include <stddef.h>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include "jwt/messagevalidator.h"

// Stack allocated signature.
#define MAX_SIGNATURE_LENGTH 256

/**
 * JSON Web Token (JWT) is a compact, URL-safe means of representing claims to
 * be transferred between two parties. The claims in a JWT are encoded as a JSON
 * object that is used as the payload of a JSON Web Signature (JWS) structure or
 * as the plaintext of a JSON Web Encryption (JWE) structure, enabling the
 * claims to be digitally signed or integrity protected with a Message
 * Authentication Code (MAC) and/or encrypted.
 *
 * This class can parse, validate and encode anf sign such tokens.
 * See the
 * [spec](http://self-issued.info/docs/draft-ietf-oauth-json-web-token.html) for
 * more details.
 */
class JWT {
   public:


    /**
     * Encodes the given json payload and optional header with the given signer.
     *
     * @param signer The MessageSigner used to sign the resulting token.
     * @param payload The payload for this token.
     * @param header The header. Note the "jwt" and "alg" fields will
     * be added if they are not there.
     * @return a char[] with a signed token. To be cleared up with calling
     * delete[]
     */
    static std::string Encode(const MessageSigner &signer, const std::string& payload, const std::string& header);

};
#endif  // SRC_INCLUDE_JWT_JWT_H_
