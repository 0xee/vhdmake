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

#include <algorithm>
#include <iterator>
#include <deque>
using namespace std;

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

    std::string GetRelativePathTo(std::string const & path1, std::string const & path2) {

        std::vector<fs::path> commonDirsInOrder;
        fs::path routeFrom1To2;
        fs::path pathA( fs::absolute( fs::path(path1)));
        fs::path pathB( fs::absolute( fs::path(path2)));
        //std::cout << "abs 1: " << pathA.native() << endl;
        //std::cout << "abs 2: " << pathB.native() << endl;
        // Parse both paths into deques of tokens. I call them "dir" because they'll
        // be the common directories unless both paths are the exact same file.
        // I also Remove the "." and ".." paths as part of the loops

        fs::path::iterator    iter;
        std::deque<fs::path> dirsA;
        std::deque<fs::path> dirsB;
        for(iter = pathA.begin(); iter != pathA.end(); ++iter) {
            std::string token = (*iter).string();
            if(token.compare("..") == 0) {      // Go up 1 level => Pop deque
                dirsA.pop_back();
            }
            else if(token.compare(".") != 0) {  // "." means "this dir" => ignore it
                dirsA.push_back( *iter);
            }
        }
        for(iter = pathB.begin(); iter != pathB.end(); ++iter) {
            std::string token = (*iter).string();
            if(token.compare("..") == 0) {      // Go up 1 level => Pop deque
                dirsB.pop_back();
            }
            else if(token.compare(".") != 0) {  // "." means "this dir" => ignore it
                dirsB.push_back( *iter);
            }
        }

        // Match entries in the 2 deques until we see a divergence
        commonDirsInOrder.clear();
        while(dirsA.size() && dirsB.size()) {
            if(dirsA.front().string() != dirsB.front().string()) {   // Diverged
                break;
            }
            commonDirsInOrder.push_back( dirsA.front());
            dirsA.pop_front();
            dirsB.pop_front();
        }

        while(dirsA.size()) {
            routeFrom1To2 /= "..";
            dirsA.pop_back();
        }

        while(dirsB.size()) {
            routeFrom1To2 /= dirsB.front();
            dirsB.pop_front();
        }

        return routeFrom1To2.native();
    }

}
