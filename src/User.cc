/*
 * Copyright (c) 2013 Mark Travis <mtravis15432+src@gmail.com>
 * All rights reserved. No warranty, explicit or implicit, provided.
 *
 * This file is part of InfiniSQL(tm).
 
 * InfiniSQL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * InfiniSQL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with InfiniSQL. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   User.cc
 * @author Mark Travis <mtravis15432+src@gmail.com>
 * @date   Mon Jan 13 14:42:44 2014
 * 
 * @brief  user record
 */

#include "User.h"
#include "Catalog.h"
#line 31 "User.cc"

User::User() : Metadata ()
{
    
}

User::User(Catalog *parentCatalogarg, std::string namearg,
           std::string &passwordarg)
    : password (passwordarg)
{
    if (parentCatalogarg->userName2Id.count(namearg))
    {
        id=-1;
        return;
    }
    parentCatalog=parentCatalogarg;
    getparents();
    id=parentCatalog->getnextuserid();
    name=namearg;
    parentCatalog->userName2Id[name]=id;
    parentCatalog->userid2User[id]=this;
}

User::User(const User &orig) : Metadata (orig)
{
    cp(orig);
}

User &User::operator= (const User &orig)
{
    (Metadata)*this=Metadata(orig);
    cp(orig);
    return *this;
}

void User::cp(const User &orig)
{
    password=orig.password;
}

User::~User()
{
    
}

void User::ser(Serdes &output)
{
    Metadata::ser(output);
    output.ser(password);
}

size_t User::sersize()
{
    return Metadata::sersize() + Serdes::sersize(password);
}

void User::des(Serdes &input)
{
    Metadata::des(input);
    input.des(password);
}

void User::getparents()
{
    parentSchema=NULL;
    parentTable=NULL;
    parentcatalogid=parentCatalog->id;
    parentschemaid=-1;
    parenttableid=-1;
}