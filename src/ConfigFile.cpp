/**
 * @file   ConfigFile.cpp
 * @author Lukas Schuller
 * @date   Wed Mar  5 20:28:25 2014
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

#include "ConfigFile.h"
#include "cfg/Parser.h"
using namespace std;


void ConfigFile::Read() {
    cfg::Scanner scanner(cfg::coco_string_create(mPath.c_str()));
            cfg::Parser parser(&scanner);

            parser.Parse(this);
            mValid = parser.errors->count == 0;


}

void ConfigFile::AddLibrary(string const & lib, util::StrList const & sources) {
        auto libIter = mFiles.find(lib);
        if(libIter == mFiles.end()) {
            mLibs.push_back(lib);    
            mFiles[lib] = util::StrList();
            libIter = mFiles.find(lib);
        }
        
        util::StrList resolvedNames;
        for(std::string src : sources) {
            auto paths = util::GetFileNames(src);
            std::copy_if(paths.begin(), paths.end(), back_inserter(resolvedNames), IsVhdl());
        }

        libIter->second = resolvedNames;

    }

void ConfigFile::AddVariable(string const & name, string const & value) {
    mVariables[util::ToUpper(name)] = value;
}
