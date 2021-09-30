//
// Created by Lby on 2017/8/7.
//

#ifndef ORZ_IO_DIR_H
#define ORZ_IO_DIR_H

#include <string>
#include <vector>
#include "orz_export.h"

namespace orz {
    ORZ_EXPORT const std::string FileSeparator();

    ORZ_EXPORT bool mkdir(const std::string &dir);

    ORZ_EXPORT bool access(const std::string &path);

    ORZ_EXPORT bool isdir(const std::string &path);

    ORZ_EXPORT bool isfile(const std::string &path);

    ORZ_EXPORT std::string join_path(const std::vector<std::string> &paths);

    /***
     * @brief Remove a file for now
     * @param filename File to remove
     * @return Return 0 only if succeed.
     */
    ORZ_EXPORT bool remove(const std::string &filename);

    /***
     * @brief Rename a file
     * @param oldname File's old name
     * @param newname File's new name
     * @return Return 0 only if succeed.
     */
    ORZ_EXPORT bool rename(const std::string &oldname, const std::string &newname);

	/**
	 * \brief copy file
	 * \param fromfile source file
	 * \param tofile dest file, or dir
	 * \param force if false, 
	 * \return return true only if success
	 */
	ORZ_EXPORT bool copy(const std::string &fromfile, const std::string &tofile, bool force = true);

    /**
	 * \brief Get current working directory
	 * \return return current working directory
	 */
    ORZ_EXPORT std::string getcwd();

    /**
	 * \brief Get current executing filename
	 * \return return current executing filename
	 */
    ORZ_EXPORT std::string getself();

    /**
	 * \brief Get current executing directory
	 * \return return current executing directory
	 */
    ORZ_EXPORT std::string getexed();

    /**
	 * \brief Change current working directory
	 * \return return true only if succeed
	 */
    ORZ_EXPORT bool cd(const std::string &path);

    /**
	 * \brief Cut file path, like /path/to/file => [/path/to, file]
	 * \return return path without tail directory
	 */
    ORZ_EXPORT std::string cut_path_tail(const std::string &path);

    /**
	 * \brief Cut file path, like /path/to/file => [/path/to, file]
	 * \param [out] tail return tail  directory
	 * \return return path without tail directory
	 */
    ORZ_EXPORT std::string cut_path_tail(const std::string &path, std::string &tail);

    /**
	 * \brief cut filename and ext, like name.ext => [name, ext]
	 * \param [out] filename return ext
	 * \return return filename without ext
	 */
    ORZ_EXPORT std::string cut_name_ext(const std::string &name_ext, std::string &ext);
}

#endif //ORZ_IO_DIR_H
