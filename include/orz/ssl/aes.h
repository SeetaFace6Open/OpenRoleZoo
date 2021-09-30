//
// Created by lby on 2018/1/15.
//

#ifndef ORZ_CODEC_AES_H
#define ORZ_CODEC_AES_H

#include <string>
#include "orz/io/jug/binary.h"
#include "orz_export.h"

namespace orz {
    enum CRYPTO_MODE {
        CBC
    };

    ORZ_EXPORT std::string
    aes128_encode_block(const std::string &key, CRYPTO_MODE mode, const std::string &data, const std::string &iv = "");

    ORZ_EXPORT std::string
    aes128_decode_block(const std::string &key, CRYPTO_MODE mode, const std::string &data, const std::string &iv = "");

    // encode with PKCS7_PADDING
    ORZ_EXPORT std::string
    aes128_encode(const std::string &key, CRYPTO_MODE mode, const std::string &data, const std::string &iv = "");

    // decode with PKCS7_PADDING
    ORZ_EXPORT std::string
    aes128_decode(const std::string &key, CRYPTO_MODE mode, const std::string &data, const std::string &iv = "");

    ORZ_EXPORT void aes128_PKCS7_add_padding(std::string &data);

    ORZ_EXPORT void aes128_PKCS7_reamove_padding(std::string &data);

    // TODO: more general binary support
    ORZ_EXPORT binary
    aes128_encode_block(const std::string &key, CRYPTO_MODE mode, const binary &data, const std::string &iv = "");

    ORZ_EXPORT binary
    aes128_decode_block(const std::string &key, CRYPTO_MODE mode, const binary &data, const std::string &iv = "");

    // encode with PKCS7_PADDING
    ORZ_EXPORT binary
    aes128_encode(const std::string &key, CRYPTO_MODE mode, const binary &data, const std::string &iv = "");

    // decode with PKCS7_PADDING
    ORZ_EXPORT binary
    aes128_decode(const std::string &key, CRYPTO_MODE mode, const binary &data, const std::string &iv = "");

    ORZ_EXPORT void aes128_PKCS7_add_padding(binary &data);

    ORZ_EXPORT void aes128_PKCS7_reamove_padding(binary &data);
}


#endif //ORZ_CODEC_AES_H
