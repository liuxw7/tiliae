/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include "../../editor/LexicalEditor.h"
#include "../misc/IndexedEditor.h"
#include "../../core/Typedefs.h"
#include "../beanWrapper/BeanWrapper.h"
#include <vector>
#include <Reflection.h>
#include "../plugins/IBeanWrapperPlugin.h"
#include "../plugins/PropertyRWBeanWrapperPlugin.h"
#include "../plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "../plugins/MethodPlugin.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest05);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/****************************************************************************/

class A {
public:
        __c (void)
        virtual ~A () {}

        _m (init) void init () {}

        _m (getField) std::string const &getField () const { return field; }
        _m (setField) void setField (std::string const &field) { this->field = field; }

        /// Szuka we wszystkich, zwraca pierwszy znaleziony.
        _m (get) virtual Core::Variant get (const std::string &name) const
        {
                if (name == "name") {
                        return Variant (field);
                }
                else if (name == "pole.name") {
                        return Variant ("ala ma kota");
                }

                return Variant ();
        }

        /// Ustawia w transition.
        _m (set) virtual void set (const std::string &name, const Core::Variant &object)
        {
                if (name == "name") {
                        field = vcast <std::string> (object);
                }
                else if (name == "pole.name") {
                        field = vcast <std::string> (object);
                }
        }

private:

       std::string field;

       _e (A)
};

/**
 * Wyszedł na jaw błąd, który uniemożliwia jednoczesne stosowanie GetPut i Method
 * pluginów. Kiedy się bowiem doda do klasy metody get/set, to MethodPlugin przestaje
 * już działać.
 */
BOOST_AUTO_TEST_CASE (testComplexGetPut)
{
        A a;
        a.setField ("testowy");
        Ptr <BeanWrapper> bw = BeanWrapper::create (Variant (&a));

        BOOST_REQUIRE_EQUAL (vcast <std::string> (bw->get ("field")), "testowy");
        a.setField ("kupa");
        BOOST_REQUIRE_EQUAL (vcast <std::string> (bw->get ("name")), "kupa");
        BOOST_REQUIRE_NO_THROW (bw->get ("init"));
}

/**
 * GetPut z greedy na true.
 */
BOOST_AUTO_TEST_CASE (testGreedyGetPut)
{
//        A a;
//
///*--------------------------------------------------------------------------*/
//
//        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> (Core::Variant (&a));
//        Ptr <BeanWrapperPluginList> pluginList = boost::make_shared <BeanWrapperPluginList> ();
//
//        Ptr <IBeanWrapperPlugin> plugin = boost::make_shared <PropertyRWBeanWrapperPlugin> ();
//        pluginList->push_back (plugin);
//
//        plugin = boost::make_shared <GetPutMethodRWBeanWrapperPlugin> (true);
//        pluginList->push_back (plugin);
//
//        plugin = boost::make_shared <MethodPlugin> (MethodPlugin::METHOD);
//        pluginList->push_back (plugin);
//
//        beanWrapper->setPluginList (pluginList);
//
///*--------------------------------------------------------------------------*/
//
//        a.setField ("testowy");
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("field")), "testowy");
//        a.setField ("kupa");
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("name")), "kupa");
//        BOOST_REQUIRE_NO_THROW (beanWrapper->get ("init"));
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("pole.name")), "ala ma kota");
}


BOOST_AUTO_TEST_SUITE_END ();
