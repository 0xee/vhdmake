/**
 * @file   MakefileGen.cpp
 * @author Lukas Schuller
 * @date   Sun Feb 23 19:44:15 2014
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

#include "MakefileGen.h"
#include "Utility.h"
#include <ctime>

using namespace std;
using namespace util;

MakefileGen::MakefileGen(ConfigFile::Ptr cfg, std::string const & exePath) :
    mCfg(cfg), mExePath(exePath) {
    if(mCfg->GetLibraries().empty()) {
            cerr << "Nothing to do..." << endl;
    } else {
        
        for(auto const & lib : mCfg->GetLibraries()) {
            auto fileNames = mCfg->GetFiles(lib);
            mLibMap[lib] = FileList();
            for(auto const & f : fileNames) {
            mLibMap[lib].push_back(DesignFile(f, lib));
            }
        }

        Generate();
    }
}


string MakefileGen::Generate() {
    string defaultRule = "all: Makefile \\\n\t\t";
    string selfRule = "Makefile: " + mCfg->GetPath() + 
        "\n\t" + mExePath + " " + mCfg->GetPath();

    string libPath = mCfg->GetLibPath();
    string libPathWithSep = libPath.size() ? libPath + '/' : "";

    string libPathRule = libPath + ": \n\tmkdir -p " + libPath + "\n\t" + mCfg->GetLibCommand() + " " + libPath + "/work";
    string libRules;
    string fileRules;
    string targets;
    try {
        for(auto const & l : mLibMap) {
            libRules += libPathWithSep + l.first + ": " + libPath + "\n\t" + mCfg->GetLibCommand() + " " + libPathWithSep + l.first + "\n\n";
            targets += libPathWithSep + l.first + " ";
            auto const & files = l.second;
            
            for(auto const & f : files) {
                
                defaultRule += f.GetName() + ".done \\\n\t\t";
                targets += f.GetName() + ".done ";
                fileRules += GenerateRule(f);
            }
        }
    } catch(exception const & e) {
        cout << "Error generating makefile: " << e.what() << endl;
        return string();
    }
    time_t now = time(0);
    string makefile = "# generated " + util::Trim(ctime(&now)) + " by vhdmake\n\n";
    makefile += defaultRule + "\n\n";
    makefile += selfRule + "\n\n";
    makefile += libPathRule + "\n\n";    
    makefile += libRules + "\n\n";
    makefile += fileRules + "\n\n";

    makefile += "clean:\n";    
    makefile += "\t" + mCfg->GetRmCommand() + " " + targets + 
        "\n\n.PHONY: clean\n"; 
    
    return makefile;
}

void MakefileGen::DepErr(DesignFile const & df, std::string const & obj) {
    cerr << "Could not resolve dependency " << obj << " from file " << df.GetName() << endl;
    throw std::runtime_error("unresolved dependency");
}

StrList MakefileGen::GetDependencies(DesignFile const & df) {
    auto usedObjects = df.GetUsages();
    StrList deps;
    for(auto o : usedObjects) {
        auto libBegin = o.find(':');
        auto libEnd = o.find(':', libBegin+1);
        string lib = o.substr(libBegin+1, libEnd-libBegin-1);
        string symName = o.substr(libEnd+1);
        if(!mCfg->IsSysLib(lib)) {

            auto & libs = mCfg->GetLibraries();
            if(find(libs.begin(), libs.end(), lib) == libs.end()) {
                DepErr(df, o);
            } else {
                cout << "Looking for " <<  o << " in library " << lib << endl;
                bool resolved = false;
                for(auto const & file : mLibMap[lib]) {
                    auto const & decls = file.GetDeclarations();
                    //cout << "Trying file " << file.GetName() << endl;

                    if(find(decls.begin(), decls.end(), o) != decls.end()) {
                        auto name = file.GetName();
                        cout << "Found " << o << " in file " << file.GetName() << endl;
                        if(name != df.GetName() && find(deps.begin(), deps.end(), name) == deps.end()) {
                            deps.push_back(name);
                        }
                        resolved = true;
                        break;
                    } 
                }
                if(!resolved) {                    
                    DepErr(df, o);
                }
            }
        } else {
            // cout << "Ignoring symbol " <<  symName << " from syslib " << lib << endl;
        }

    }
    return deps;
}


string MakefileGen::GenerateRule(DesignFile const & df) {
    auto deps = GetDependencies(df);
    string rule = df.GetName() + ".done: " + mCfg->GetLibPath() + '/' + df.GetTargetLib() + " " + df.GetName() + " ";
    for(auto & s : deps) {
        rule += s + ".done ";
    }

    string libPathWithSep = mCfg->GetLibPath().size() ? mCfg->GetLibPath() + '/' : "";


    rule += "\n\tcd " + libPathWithSep + "; " + mCfg->GetCompileCommand() + " " +
        df.GetTargetLib() + " " + df.GetName() + "\n";
    rule += "\ttouch " + df.GetName() + ".done\n"; 
    return rule + "\n";
}
