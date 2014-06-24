/**
 * @file   MakefileGen.h
 * @author Lukas Schuller
 * @date   Mon Mar  3 22:07:00 2014
 * 
 * @brief  
 * 
 * @license 
 *  Copyright (C) 2014 Lukas Schuller
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAKEFILEGEN_H
#define MAKEFILEGEN_H

#include <string>
#include "DesignFile.h"
#include "Utility.h"
#include "ConfigFile.h"

class MakefileGen {


public:
    MakefileGen(ConfigFile::Ptr cfg, std::string const & exePath);

    std::string Generate();
    std::string GenerateGuiSimScript() const;
    std::string GenerateSimScript() const;
    std::string GenerateHelper(std::string const & dir) const;
private:
    void DepErr(DesignFile const & df, std::string const & obj);
    util::StrList GetDependencies(DesignFile const & df);
    std::string GenerateRule(DesignFile const & df);
    std::string GenerateHeader() const;

    std::string mExePath;
    ConfigFile::Ptr mCfg;

    typedef std::vector<DesignFile> FileList;
    std::map<std::string, FileList> mLibMap;


};


#endif /* MAKEFILEGEN_H */
