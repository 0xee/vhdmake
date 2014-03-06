/**
  * @file   Utility.cpp
  * @author Lukas Schuller
  * @date   Sun Feb 23 12:41:00 2014
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


#include "Utility.h"

namespace util {

    std::vector<std::string> GetFileNames(std::string const & unresolved) {
        fs::path f(unresolved);
        std::vector<std::string> result;
        if (fs::is_directory(f)) {      
            for (fs::recursive_directory_iterator it(f), eit; it != eit; ++it) {
                if (!fs::is_directory(it->path())) {
                    result.push_back(it->path().native());
                }       
            }
        }
        else {
            result.push_back(f.native());
        }

        return result;
    }

}
