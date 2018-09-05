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
#include "jwt/jwt.h"
#include <exception>
#include <string>
#include "jwt/allocators.h"
#include "jwt/jwt_error.h"
#include "jwt/base64.h"


std::string JWT::Encode(const MessageSigner &validator, const std::string& payload, const std::string& header) {

    auto header_enc = Base64Encode::EncodeUrl(header);
    auto payload_enc = Base64Encode::EncodeUrl(payload);
    auto signed_area = header_enc + '.' + payload_enc;
    auto digest = validator.Digest(signed_area);
    return (signed_area + '.' + Base64Encode::EncodeUrl(digest));
}

