 *  Copyright (C) 2014 Lukas Schuller lukas@schuller.uk.to
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

vhdmake is a makefile generator for VHDL files.

For usage info call "vhdmake -h" 

Building:
        Just calling make is enough, if all dependencies are satisfied.
        Dependencies:  boost (specifically boost_system and boost_filesystem), 
        a c++11 compliant compiler (eg. gcc 4.7+) and, if you want to modify
        the parsers, the Coco/R parser generator. Installation prefix and Coco/R
        location can be set in cfg.mk

Installation:
        make install
        installs vhdmake to the path set in cfg.mk, for which you obviously
        need write permissions.

Have fun!