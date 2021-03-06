/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGTOMEGATONEDITOR_H_
#define STRINGTOMEGATONEDITOR_H_

#include "editor/JEditor.h"
#include <cassert>
#include "factory/testHelpers/MegaTon.h"
#include "core/variant/Variant.h"
#include "core/variant/Cast.h"
#include "core/string/String.h"

/**
 * Edytory dzialaja w jedna strone, nie tak jak w javie.
 * Ten konwertuje stringa do MegaTona.
 */
struct StringToMegatonEditor : public Editor::JEditor {

        virtual ~StringToMegatonEditor () {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL)
        {
                // Sprawdzanie typow parametrow.
                assert (ccast <std::string> (input));
                assert (output);
                assert (ccast <MegaTon *> (*output));
//                ASSERT (output-getContaining () == Core::HANDLE, "");

                std::string inStr = vcast <std::string> (input);
                MegaTon *mt = vcast <MegaTon *> (*output);

                mt->setHeavyProperty (inStr);
                return true;
        }

};

#endif /* STRINGTOMEGATONEDITOR_H_ */
