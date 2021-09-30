//
// Created by Lby on 2017/7/31.
//

#ifndef ORZ_IO_WALKER_H
#define ORZ_IO_WALKER_H

#include <vector>
#include <string>
#include "orz_export.h"

namespace orz {
    ORZ_EXPORT std::vector<std::string> FindFiles(const std::string &path);

    ORZ_EXPORT std::vector<std::string> FindFiles(const std::string &path, std::vector<std::string> &dirs);

    ORZ_EXPORT std::vector<std::string> FindFilesRecursively(const std::string &path, int depth = -1);

    ORZ_EXPORT std::vector<std::string> FindFlodersRecursively(const std::string &path, int depth = -1);
}

#endif //ORZ_IO_WALKER_H
