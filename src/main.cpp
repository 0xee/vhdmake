/**
 * @file   main.cpp
 * @author Lukas Schuller
 * @date   Sun Feb 23 12:00:35 2014
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


#include <iostream>
#include <fstream>
#include "DesignFile.h"
#include "ConfigFile.h"
#include "MakefileGen.h"
#include <boost/filesystem.hpp>

using namespace std;

int major = 0;
int minor = 1;

void DisplayUsage() {
    cout << endl
         << "vhdmake v" << major << "." << minor << " (c) 2014 Lukas Schuller" << endl << endl
         << "Usage: vhdmake ( (-s VHDFILE) | [-c] [CONFIGFILE] )" << endl
         << "       With no arguments, configuration file vhdmake.cfg is assumed." << endl
         << "       vhdmake -s x.vhd shows declarations and dependencies of file x.vhd." << endl
         << "       vhdmake -c [CONFIGFILE] removes all potentially generated Makefiles in the source directories." << endl
         << "Example configuration file:" << endl
         << "#----------------------------------------" << endl
         << "# I am a comment" << endl
         << "-ieee                       # ignore all dependencies to library ieee" << endl
         << "+work:  test.vhd a.vhd      # compile test.vhd and a.vhd into library work" << endl
         << "+mylib: src/mylib           # compile all VHDL files in directory src/mylib into library m" << endl  
         << "                            # IMPORTANT: if a library's name exists as directory," << endl
         << "                            # the contents of the directory might be overwritten/deleted"
         << "VCOM = vcom -2008 -work     # set variable VCOM to \"vcom -2008 -work\" " << endl 
         << "#----------------------------------------" << endl << endl
         << "Valid variables are:" << endl
         << "    VCOM: VHDL compile command. (Default: \"vcom -93 -work\")" << endl
         << "          Compilation is invoked like this: " << endl
         << "          <VCOM> <targetlib> <hdlfile>" << endl
         << "    VLIB: Command to create library. (Default: \"vlib\")" << endl
         << "    VMAP: Command to map library. (Default: \"vmap\")" << endl
         << "    RM:   File/directory delete command. (Default: \"rm -rf\")" << endl
         << "    LIBS: Target path for compiled libraries, eg. /tmp/libs (Default: \".\")" << endl
         << endl;   
}

int main(int argc, char* argv[]) {

    if(argc > 2 && argv[1] == string("-s")) {
        DesignFile df(argv[2]);
      
        cout << "Design file " << argv[2] << ":" << endl
             << "Declares: " << endl;
        auto decls = df.GetDeclarations(); 
        for(auto s : decls) {
            cout << "    " << s << endl;
        }
        cout << endl << "Uses: " << endl;
        auto deps =df.GetUsages(); 
        for(auto s : deps) {
            cout << "    " << s << endl;
        }
    } else {
        string cfgFile = "vhdmake.cfg";
        bool clean = false;
        if(argc > 1) {
            if(string(argv[1]) == "-c") {
                if(argc > 2) cfgFile = argv[2];
                clean = true;
            }
            else {
                if(argv[1][0] == '-') {
                    DisplayUsage();
                    return -1;
                }
                cfgFile = argv[1];
            }
        }

        string exePath = argv[0];
        ConfigFile::Ptr cfg(new ConfigFile(cfgFile));
        if(!cfg->IsValid()) {
            cerr << "Config file missing or invalid (maybe missing newline at end of file?), exiting..." << endl;
            return -1;
        }
        cfg->Print();
        util::StrList srcDirs = cfg->GetSourceDirs();
        srcDirs.push_back(".");
        if(clean) {
            cout << "Removing helper scripts" << endl;
            if(boost::filesystem::exists("sim.do"))
                boost::filesystem::remove("sim.do");                
            if(boost::filesystem::exists("sim_gui.do"))
                boost::filesystem::remove("sim_gui.do");                
            for(auto dir : srcDirs) {
                string mfName = dir + "/Makefile";
                cout << "Removing " << mfName << endl;
                if(boost::filesystem::exists(mfName))
                    boost::filesystem::remove(mfName);                
            }

            return 0;
        }
        auto gen = MakefileGen(cfg, exePath);

//        cout << endl << "Makefile: " << endl << endl << mf << endl;
        ofstream ofmf("Makefile");
        auto mainMf = gen.Generate();
        if(mainMf.empty()) {
            cerr << "Aborting" << endl;
            return -1;
        }
        ofmf << mainMf;
        ofmf.close();

        ofstream ofsim("sim.do");
        ofsim << gen.GenerateSimScript();
        ofsim.close();

        ofstream ofsimgui("sim_gui.do");
        ofsimgui << gen.GenerateGuiSimScript();
        ofsimgui.close();


        for(auto dir : srcDirs) {
            if(dir == "." || dir.empty()) continue;
            string mfName = dir + "/Makefile";
            ofstream helper(mfName.c_str());
            cout << "Generating helper for directory " << dir << endl;
            helper << gen.GenerateHelper(dir);
            helper.close();
        }
    }

    return 0;
}
