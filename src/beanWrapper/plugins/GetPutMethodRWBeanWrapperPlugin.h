/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GETPUTMETHODRWBEANWRAPPERPLUGIN_498_H
#define GETPUTMETHODRWBEANWRAPPERPLUGIN_498_H

#include "reflection/Reflection.h"
#include "IBeanWrapperPlugin.h"
#include "core/ApiMacro.h"

namespace Wrapper {

/**
 *  To jest plugin, ktory potrafi odczytac zapisac propertu do
 *  obiektow, ktore maja metody get i set. Jest to element analogiczny
 *  do PropertyRWBeanWrapperPlugin, tylko samiast setterow i getterow
 *  uzywa metod get / set.
 */
class TILIAE_API GetPutMethodRWBeanWrapperPlugin : public IBeanWrapperPlugin {
public:

        virtual ~GetPutMethodRWBeanWrapperPlugin () {}

        virtual Core::Variant get (const Core::Variant &bean,
                                   Common::IPath *path,
                                   bool *error,
                                   Core::DebugContext *ctx = NULL,
                                   Editor::IEditor *editor = NULL) const;

        virtual bool set (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Core::DebugContext *ctx = NULL,
                          Editor::IEditor *editor = NULL);

        virtual bool add (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Core::DebugContext *ctx,
                          Editor::IEditor *editor = NULL);

        virtual Core::Variant iterator (const Core::Variant &bean,
                                        Common::IPath *path,
                                        bool *error,
                                        Core::DebugContext *ctx) const;

};


} // namespace

#endif

