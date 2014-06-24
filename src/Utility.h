/**
 * @file   Utility.h
 * @author Lukas Schuller
 * @date   Sat Feb 22 16:41:10 2014
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

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <boost/filesystem.hpp>
#include <vector>

namespace util {

    typedef std::vector<std::string> StrList;

    namespace fs = boost::filesystem;

    inline std::string &TrimL(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

// trim from end
    inline std::string &TrimR(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    inline std::string & Trim(std::string & s) {
        return TrimL(TrimR(s));
    }

    inline std::string Trim(std::string const & s) {
        auto s1 = s;
        return TrimL(TrimR(s1));
    }

    inline std::string ToLower(std::string const & s) {
        std::string lc;
        for(char c : s) lc += tolower(c);
        return lc;
    }

    inline std::string ToUpper(std::string const & s) {
        std::string lc;
        for(char c : s) lc += toupper(c);
        return lc;
    }

    std::vector<std::string> GetFileNames(std::string const & unresolved);    

    inline std::string GetAbsolutePath(std::string const & relative) {
        return boost::filesystem::system_complete(relative.c_str()).native();
    }

    inline std::string GetDirectory(std::string const & fileName) {
        fs::path p(fileName);
        if(fs::is_directory(fileName)) {
            return fileName;
        } else {
            return p.parent_path().native();
        }
    }

    template <typename Iterator>
    class IteratorPair {
    public:
        IteratorPair ( Iterator first, Iterator last) : f_ (first), l_ (last) {}
        Iterator begin () const { return f_; }
        Iterator end   () const { return l_; }

    private:
        Iterator f_;
        Iterator l_;
    };

    template <typename Iterator>
    IteratorPair<Iterator> Range( Iterator f, Iterator l ) {
        return IteratorPair<Iterator> ( f, l );
    }

    inline std::string Pwd() {
        return fs::current_path().native();
    }

    std::string GetRelativePathTo(std::string const & path1, std::string const & path2);

}

#endif /* UTILITY_H */
