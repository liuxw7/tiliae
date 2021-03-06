/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COUNTRY_920296_H
#define COUNTRY_920296_H

#include <list>
#include <string>
#include "core/Pointer.h"
#include "reflection/Reflection.h"
#include <vector>
#include "core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API __tiliae_reflect__ Country {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (getName) std::string getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        REFLECTION_END (Country)

};

typedef __tiliae_reflect__ std::vector <Ptr <Country> > CountryVector;
REFLECTION_COLLECTION (CountryVector)

typedef __tiliae_reflect__ std::list <Ptr <Country> > CountryList;
REFLECTION_COLLECTION (CountryList)

#endif

