/**
 * @file   DesignFile.cpp
 * @author Lukas Schuller
 * @date   Sun Feb 23 12:00:59 2014
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

#include "DesignFile.h"

#include "Utility.h"
#include "vhdl/Parser.h"

using namespace std;
using namespace util;

DesignFile::DesignFile(std::string const & source, std::string const & targetLib) : mTargetLib(targetLib) {

    mName = util::GetAbsolutePath(source);
    std::ifstream input(mName);
    if (!input)
    {
        std::cerr << "error: can't open >" << mName << "<\n";
    }
    else
    {
        try
        {
            vhdl::Scanner scanner(vhdl::coco_string_create(source.c_str()));
            vhdl::Parser parser(&scanner);

            parser.Parse(this);
        }
        catch(std::exception & e)
        {
            std::cerr << "lexer/parser exception: " << e.what() << "\n";
        }
    }
    for(string & s : mUses) {
        s = ToLower(s);
    }
    for(string & s : mDeclarations) {
        s = ToLower(s);
    }
}

void DesignFile::AddPkgUse(std::string const & name) {
    auto sep1 = name.find('.');
    auto sep2 = name.find('.', sep1+1);
    string lib = name.substr(0, sep1);
    string pkg = name.substr(sep1+1, sep2-sep1-1);
    string fullname = "pkg:" + lib + ":" + pkg;
    mUses.push_back(fullname);
}

void DesignFile::AddInstantiation(std::string entity, std::string const & arch) {
    for(char & c : entity) if(c == '.') c = ':';
    
    mUses.push_back("entity:" + entity);
    if(arch.size()) {
        mUses.push_back("arch:" + entity + ":" + arch);
    }

}

void DesignFile::AddEntityDeclaration(std::string const & name) {
    mDeclarations.push_back("entity:" + mTargetLib + ":" + name);
}

void DesignFile::AddPkgDeclaration(std::string const & name) {
        mDeclarations.push_back("pkg:" + mTargetLib + ":" + name);
}

void DesignFile::AddArchitectureDeclaration(std::string const & entity, std::string const & arch) {
    mDeclarations.push_back("arch:" + mTargetLib + ":" + entity + ":" + arch);
    mUses.push_back("entity:" + mTargetLib + ":" + entity);
}
