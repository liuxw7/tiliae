/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "beanWrapper/BeanWrapper.h"
#include "core/Pointer.h"
#include "testHelpers/Country.h"
#include "testHelpers/City.h"
#include "testHelpers/Address.h"
#include "core/variant/Variant.h"
#include "beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "core/DebugContext.h"
#include "editor/LexicalEditor.h"
#include "editor/TypeEditor.h"
#include "editor/NoopEditor.h"
#include "testHelpers/Foo.h"
#include "editor/ChainEditor.h"
#include "editor/StringConstructorEditor.h"
#include "editor/StringFactoryMethodEditor.h"

using Editor::ChainEditor;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest03);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testSimple)
{
        BeanWrapper *bw = BeanWrapper::create ();
        bw->setEditor (new LexicalEditor <int, std::string>);

        Country country;

        bw->setWrappedObject (Variant (&country));

//        bw->set ("name", Variant (std::string ("Warszawa")));
        bw->set ("name", Variant (int (123)));

        BOOST_REQUIRE_EQUAL (country.getName (), "123");
        delete bw;
}

/**
 * Setter + bardziej zaawansowany edytor.
 */
BOOST_AUTO_TEST_CASE (testComplex_Object)
{
        BeanWrapper *bw = BeanWrapper::create ();

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = std::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = std::make_shared <Editor::NoopEditor> ();
        editor->setEqType (noop.get ());
        editor->setNullType (noop.get ());

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int),    new Editor::LexicalEditor <std::string, int> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), new Editor::LexicalEditor <std::string, double> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char),   new Editor::LexicalEditor <std::string, char> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool),   new Editor::LexicalEditor <std::string, bool> ()));

#ifdef WITH_CORE_STRING
        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));
#endif

        // StringCon.
        Ptr <StringConstructorEditor> strCon = std::make_shared <StringConstructorEditor> ();

        ChainEditor *chain = new ChainEditor;
        chain->addEditor (editor.get ());
        chain->addEditor (strCon.get ());

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        Foo foo;
        bw->setWrappedObject (Variant (&foo));

        bw->set ("field0", Variant ("test1"));
        bw->set ("field1", Variant ("test2"));
        bw->set ("field2", Variant ("123"));
        bw->set ("field3", Variant ("12.34"));
        bw->set ("field4", Variant ("a"));
        bw->set ("field5", Variant ("yes"));

        DebugContext ctx;
        if (!bw->set ("city", Variant ("Warszawa"), &ctx)) {
                std::cerr << ctx.getMessage () << std::endl;
        }

        BOOST_REQUIRE_EQUAL (foo.getField0 (), "test1");
        BOOST_REQUIRE_EQUAL (foo.getField1 (), "test2");
        BOOST_REQUIRE_EQUAL (foo.getField2 (), 123);
        BOOST_REQUIRE_EQUAL (foo.getField3 (), 12.34);
        BOOST_REQUIRE_EQUAL (foo.getField4 (), 'a');
        BOOST_REQUIRE_EQUAL (foo.getField5 (), true);
        BOOST_REQUIRE (foo.getCity ());
        BOOST_REQUIRE_EQUAL (foo.getCity ()->getName (), "Warszawa");

        delete bw;
}

/**
 * Zawansowane edytowaine mapy.
 */
BOOST_AUTO_TEST_CASE (testComplex_Map)
{
        Ptr <BeanWrapper> bw = Ptr <BeanWrapper> (BeanWrapper::create ());

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = std::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = std::make_shared <Editor::NoopEditor> ();
        editor->setEqType (noop.get ());
        editor->setNullType (noop.get ());

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int),    new Editor::LexicalEditor <std::string, int> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), new Editor::LexicalEditor <std::string, double> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char),   new Editor::LexicalEditor <std::string, char> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool),   new Editor::LexicalEditor <std::string, bool> ()));

#ifdef WITH_CORE_STRING
        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));
#endif

        // StringCon.
        Ptr <StringConstructorEditor> strCon = std::make_shared <StringConstructorEditor> ();

        ChainEditor *chain = new ChainEditor;
        chain->addEditor (editor.get ());
        chain->addEditor (strCon.get ());

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        CityMap cityMap;
        bw->setWrappedObject (Variant (&cityMap));

        bw->set ("city01", Variant ("Warszawa"));
        bw->set ("city02", Variant ("Kraków"));
        bw->set ("city03", Variant ("Poznań"));

        BOOST_REQUIRE_EQUAL (cityMap.size (), 3U);
        BOOST_REQUIRE_EQUAL (cityMap["city01"]->getName (), "Warszawa");
        BOOST_REQUIRE_EQUAL (cityMap["city02"]->getName (), "Kraków");
        BOOST_REQUIRE_EQUAL (cityMap["city03"]->getName (), "Poznań");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testListWithBeanWrapper)
{
        Ptr <IBeanWrapper> bw = Ptr <IBeanWrapper> (BeanWrapper::create ());
        StringVector vector;

        Variant v (&vector);
        bw->add (&v, "", Variant ("iwasz"));
        bw->add (&v, "", Variant ("asia"));
        bw->add (&v, "", Variant ("gadzio"));
        bw->add (&v, "", Variant ("tmarc"));

        BOOST_REQUIRE_EQUAL (vector.size (), 4U);
        BOOST_REQUIRE_EQUAL (vector[0], "iwasz");
        BOOST_REQUIRE_EQUAL (vector[1], "asia");
        BOOST_REQUIRE_EQUAL (vector[2], "gadzio");
        BOOST_REQUIRE_EQUAL (vector[3], "tmarc");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testComplex_Vector)
{
        Ptr <BeanWrapper> bw = Ptr <BeanWrapper> (BeanWrapper::create ());

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = std::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = std::make_shared <Editor::NoopEditor> ();
        editor->setEqType (noop.get ());
        editor->setNullType (noop.get ());

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int),    new Editor::LexicalEditor <std::string, int> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), new Editor::LexicalEditor <std::string, double> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char),   new Editor::LexicalEditor <std::string, char> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool),   new Editor::LexicalEditor <std::string, bool> ()));

#ifdef WITH_CORE_STRING
        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));
#endif

        // StringCon.
        Ptr <StringConstructorEditor> strCon = std::make_shared <StringConstructorEditor> ();

        ChainEditor *chain = new ChainEditor;
        chain->addEditor (editor.get ());
        chain->addEditor (strCon.get ());

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        CityVector cityVector;
        bw->setWrappedObject (Variant (&cityVector));

        bw->add ("", Variant ("Warszawa"));
        bw->add ("", Variant ("Kraków"));
        bw->add ("", Variant ("Poznań"));

        BOOST_REQUIRE_EQUAL (cityVector.size (), 3U);
        BOOST_REQUIRE_EQUAL (cityVector[0]->getName (), "Warszawa");
        BOOST_REQUIRE_EQUAL (cityVector[1]->getName (), "Kraków");
        BOOST_REQUIRE_EQUAL (cityVector[2]->getName (), "Poznań");
}

/****************************************************************************/

static Core::Variant convertStringToInt (std::string const &input)
{
        return Core::Variant (boost::lexical_cast <int> (input));
}

static Core::Variant convertStringToCity (std::string const &input)
{
        return Core::Variant (std::make_shared <City> (input));
}

BOOST_AUTO_TEST_CASE (testWithConversionFuinctions)
{
        Ptr <BeanWrapper> bw = Ptr <BeanWrapper> (BeanWrapper::create ());

        /*--------------------------------------------------------------------------*/

        StringFactoryMethodEditor *editor = new StringFactoryMethodEditor ();
        editor->addConversion (typeid (int), convertStringToInt);
        editor->addConversion (typeid (City), convertStringToCity);

        /*--------------------------------------------------------------------------*/

        bw->setEditor (editor);

        Foo foo;
        bw->setWrappedObject (Variant (&foo));

        bw->set ("field2", Variant ("123"));

        DebugContext ctx;
        if (!bw->set ("city3", Variant ("Warszawa"), &ctx)) {
                std::cerr << ctx.getMessage () << std::endl;
        }

        BOOST_REQUIRE_EQUAL (foo.getField2 (), 123);
        BOOST_REQUIRE (foo.getCity3 ());
        BOOST_REQUIRE_EQUAL (foo.getCity3 ()->getName (), "Warszawa");
}

BOOST_AUTO_TEST_SUITE_END ();
