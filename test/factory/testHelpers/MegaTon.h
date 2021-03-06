/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MEGATON_H_
#define MEGATON_H_

#include <vector>
#include "core/string/String.h"

/**
 * Very heavyweight class. Not to be copied.
 */
class MegaTon {
public:

        MegaTon ()
        {
                thousantsOfElements.resize (1000);
        }

        std::string getHeavyProperty() const { return heavyProperty; }
        void setHeavyProperty(const std::string &heavyProperty) { this->heavyProperty = heavyProperty; }

private:

        typedef int kg;
        std::vector <kg> thousantsOfElements;
        std::string heavyProperty;
};

#endif /* MEGATON_H_ */
