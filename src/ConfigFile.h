/**
 * @file   ConfigFile.h
 * @author Lukas Schuller
 * @date   Sat Feb 22 16:20:11 2014
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

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utility.h"

class ConfigFile {

public:
    typedef std::shared_ptr<ConfigFile> Ptr;

    ConfigFile(std::string const & fileName) : mPath(fileName), mValid(false) {
        mVariables["VCOM"] = "vcom -93 -work";
        mVariables["VLIB"] = "vlib";
        mVariables["RM"]   = "rm -rf";
        Read();
    }

    void Read();
    
    inline bool IsValid() const {
        return mValid;
    }

    inline util::StrList const & GetLibraries() const {
        return mLibs;
    }

    inline bool IsSysLib(std::string const & name) const {
        return std::find(mSysLibs.begin(), mSysLibs.end(), name) != mSysLibs.end();
    }

    inline std::string const & GetLibCommand() {
        return mVariables["VLIB"];
    }

    inline std::string const & GetRmCommand() {
        return mVariables["RM"];
    }

    inline std::string const & GetCompileCommand() {
        return mVariables["VCOM"];
    }

    inline util::StrList GetFiles(std::string const & library) const {        
        auto lib = mFiles.find(library);
        if(lib == mFiles.end()) {
            return util::StrList();
        }
        return lib->second;
    }

    inline void AddSysLib(std::string const & lib) {
        mSysLibs.push_back(lib);
    }

    void AddLibrary(std::string const & lib, util::StrList const & sources);

    void AddVariable(std::string const & name, std::string const & value);

    void Print(std::ostream & out = std::cout) {
        
        std::cout << "System libraries:" << std::endl;
        for(auto const & s: mSysLibs) {
            std::cout << "    " << s << std::endl;
        }


        std::cout << std::endl << "User libraries:" << std::endl;
        for(auto const & f : mFiles) {
            std::cout << std::endl << "\t" << f.first << ": " << std::endl;         
            for(auto const & s: f.second) {
                std::cout << "\t\t" << s << std::endl;
            }
        }
        
        std::cout << std::endl << "Variables:" << std::endl;
        for(auto const & s: mVariables) {
            std::cout << "    " << s.first << " = " << s.second << std::endl;
        }
        


    }

    std::string GetPath() const {
        return mPath;
    }

private:
    struct IsVhdl {
        bool operator()(std::string const & str) {
            return str.find(".vhd") == str.size()-4;
        }
    };

    bool mValid;
    std::string mPath;
    util::StrList mLibs;
    util::StrList mSysLibs;
    std::map<std::string, util::StrList> mFiles;
    std::map<std::string, std::string> mVariables;
};

#endif /* CONFIGFILE_H */

