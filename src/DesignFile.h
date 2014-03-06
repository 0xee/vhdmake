/**
 * @file   DesignFile.h
 * @author Lukas Schuller
 * @date   Fri Feb 21 16:50:27 2014
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

#ifndef DESIGNFILE_H
#define DESIGNFILE_H

#include <string>
#include <list>
#include <fstream>
#include <memory>
#include <vector>


class DesignFile {
    struct Ast {
        std::string toString() {
            return "blubb";
        }
        Ast *  getFirstChild() {
            return this;
        }
        Ast *  getNextSibling() {
            return this;
        }
        int getNumberOfChildren() {
            return 0;
        }
    };
    typedef Ast* AstNode;
public:
    typedef std::shared_ptr<DesignFile> Ptr;

    DesignFile(std::string const & source, std::string const & targetLib = "work");

    DesignFile() = delete;

    std::string const & GetName() const {
        return mName;
    }

    std::string const & GetTargetLib() const {
        return mTargetLib;
    }
    
    std::list<std::string> const & GetUsages() const {
        return mUses;
    }
    std::list<std::string> const & GetDeclarations() const {
        return mDeclarations;
    }

    void AddPkgUse(std::string const & name);
    void AddInstantiation(std::string entity, std::string const & arch);
    void AddEntityDeclaration(std::string const & name);
    void AddArchitectureDeclaration(std::string const & entity, std::string const & arch);
    void AddPkgDeclaration(std::string const & name);
private:

    AstNode NodeAtPath(AstNode parent, std::vector<int> const & path);

    std::string mName, mTargetLib;
    std::list<std::string> mUses, mDeclarations;

};


#endif /* DESIGNFILE_H */
