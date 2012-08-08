/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Attributes.h"

namespace Container {

Attributes::Attributes () : parent (NULL)
{
        for (int i = 0; i < LAST_STRING; ++i) {
                strMapData[i] = NULL;
        }

        intData.abstract = 0;
        intData.abstractSet = 0;
        intData.lazyInit = 0;
        intData.lazyInitSet = 0;
        intData.scope = 0;
        intData.scopeSet = 0;
}

/****************************************************************************/

void Attributes::setString (AttributeName key, const char *value)
{
        strMapData[key] = value;
}

/****************************************************************************/

const char *Attributes::getString (AttributeName key, bool getFromParent) const
{
        const char *ret = strMapData[key];

        if (ret) {
                return ret;
        }

        if (getFromParent && parent) {
                return parent->getString (key);
        }

        static const char *EMPTY = "";
        return EMPTY;
}

/****************************************************************************/

void Attributes::setInt (AttributeName key, int value)
{
        switch (key) {
        case ABSTRACT_ARGUMENT:
                intData.abstract = value;
                intData.abstractSet = 1;
                break;

        case LAZYINIT_ARGUMENT:
                intData.lazyInit = value;
                intData.lazyInitSet = 1;
                break;

        case SCOPE_ARGUMENT:
                intData.scope = value;
                intData.scopeSet = 1;
                break;

        default:
                break;
        }
}

/****************************************************************************/

int Attributes::getIntPriv (AttributeName key) const
{
        switch (key) {
        case ABSTRACT_ARGUMENT:
                return (intData.abstractSet) ? (intData.abstract) : (-1);

        case LAZYINIT_ARGUMENT:
                return (intData.lazyInitSet) ? (intData.lazyInit) : (-1);

        case SCOPE_ARGUMENT:
                return (intData.scopeSet) ? (intData.scope) : (-1);

        default:
                return -1;
        }

        return -1;
}

/****************************************************************************/

int Attributes::getInt (AttributeName key, bool getFromParent) const
{
        int ret = getIntPriv (key);

        if (ret >= 0) {
               return ret;
        }

        if (getFromParent && parent) {
                return parent->getInt (key);
        }

        return 0;
}

/****************************************************************************/

bool Attributes::containsKey (AttributeName key, bool getFromParent) const
{
        bool foundInParent = false;

        if (getFromParent && parent) {
                foundInParent = parent->containsKey (key);
        }

        bool foundInChild = false;
        int iKey = static_cast <int> (key);

        if (iKey > 0 && iKey < LAST_STRING) {
                foundInChild = bool (strMapData[iKey]);
        }
        else if (iKey >= ABSTRACT_ARGUMENT && iKey <= SCOPE_ARGUMENT) {
                 foundInChild = ((iKey == ABSTRACT_ARGUMENT) && (intData.abstractSet)) ||
                                ((iKey == LAZYINIT_ARGUMENT) && (intData.lazyInitSet)) ||
                                ((iKey == SCOPE_ARGUMENT) && (intData.scopeSet));
        }

        return foundInChild || foundInParent;
}

}
