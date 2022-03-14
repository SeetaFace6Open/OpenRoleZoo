//
// Created by lby on 2018/1/10.
//

#ifndef ORZ_CODEC_BASE64_H
#define ORZ_CODEC_BASE64_H

#include <string>
#include "orz_export.h"

namespace orz {
    ORZ_EXPORT std::string base64_encode(const std::string &bin);
    ORZ_EXPORT std::string base64_decode(const std::string &codes);
}

#endif //ORZ_CODEC_BASE64_H
