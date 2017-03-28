/*
 * This file was aut-generated by tiliaeparser. Do not modify. Unless.
 * Include only once.
 * https://github.com/iwasz/tiliae
 */

#include <reflection/Reflection.h>
#include "Reflection_input.cc"

namespace {
using namespace Core;
using namespace Reflection;

void createReflectionDatabase_tiliae ()
{
	{
		Class *clazz = new Class ("Object", typeid (Core::Object &), new Reflection::PtrDeleter <Core::Object>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Object, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Object, void>::Level1Wrapper::newConstructorPointer ()));
		}
	}
	{
		Class *clazz = new Class ("IEditor", typeid (Editor::IEditor &), new Reflection::PtrDeleter <Editor::IEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("convert", createMethodWrapper (&Editor::IEditor::convert)));
		}
	}
	{
		Class *clazz = new Class ("JEditor", typeid (Editor::JEditor &), new Reflection::PtrDeleter <Editor::JEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IEditor");
			clazz->addMethod (new Method ("convert", createMethodWrapper (&Editor::JEditor::convert)));
			clazz->addMethod (new Method ("edit", createMethodWrapper (&Editor::JEditor::edit)));
		}
	}
	{
		Class *clazz = new Class ("ListToStringEditor", typeid (Editor::ListToStringEditor &), new Reflection::PtrDeleter <Editor::ListToStringEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("JEditor");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Editor::ListToStringEditor, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Editor::ListToStringEditor, const std::string &, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("edit", createMethodWrapper (&Editor::ListToStringEditor::edit)));
			clazz->addMethod (new Method ("getDelimiter", createMethodWrapper (&Editor::ListToStringEditor::getDelimiter)));
			clazz->addMethod (new Method ("setDelimiter", createMethodWrapper (&Editor::ListToStringEditor::setDelimiter)));
			clazz->addMethod (new Method ("getQuotation", createMethodWrapper (&Editor::ListToStringEditor::getQuotation)));
			clazz->addMethod (new Method ("setQuotation", createMethodWrapper (&Editor::ListToStringEditor::setQuotation)));
		}
	}
	{
		Class *clazz = new Class ("IFactory", typeid (Factory::IFactory &), new Reflection::PtrDeleter <Factory::IFactory>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("create", createMethodWrapper (&Factory::IFactory::create)));
		}
	}
	{
		Class *clazz = new Class ("ChainFactory", typeid (Factory::ChainFactory &), new Reflection::PtrDeleter <Factory::ChainFactory>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IFactory");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Factory::ChainFactory, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Factory::ChainFactory, _Bool>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("create", createMethodWrapper (&Factory::ChainFactory::create)));
			clazz->addMethod (new Method ("setFactories", createMethodWrapper (&Factory::ChainFactory::setFactories)));
			clazz->addMethod (new Method ("addFactory", createMethodWrapper (&Factory::ChainFactory::addFactory)));
			clazz->addMethod (new Method ("getFactories", createMethodWrapper (&Factory::ChainFactory::getFactories)));
		}
	}
	{
		Class *clazz = new Class ("K202", typeid (k202::K202 &), new Reflection::PtrDeleter <k202::K202>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addMethod (new Method ("setBeanWrapper", createMethodWrapper (&k202::K202::setBeanWrapper)));
		}
	}
	{
		Class *clazz = new Class ("K202Factory", typeid (k202::K202Factory &), new Reflection::PtrDeleter <k202::K202Factory>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IFactory");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <k202::K202Factory, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("create", createMethodWrapper (&k202::K202Factory::create)));
		}
	}
	{
		Class *clazz = new Class ("K202Proxy", typeid (k202::K202Proxy &), new Reflection::PtrDeleter <k202::K202Proxy>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <k202::K202Proxy, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("run", createMethodWrapper (&k202::K202Proxy::run)));
			clazz->addMethod (new Method ("getSourceCode", createMethodWrapper (&k202::K202Proxy::getSourceCode)));
			clazz->addMethod (new Method ("setSourceCode", createMethodWrapper (&k202::K202Proxy::setSourceCode)));
			clazz->addMethod (new Method ("getDomain", createMethodWrapper (&k202::K202Proxy::getDomain)));
			clazz->addMethod (new Method ("setDomain", createMethodWrapper (&k202::K202Proxy::setDomain)));
			clazz->addMethod (new Method ("getParamVector", createMethodWrapper (&k202::K202Proxy::getParamVector)));
			clazz->addMethod (new Method ("setParamVector", createMethodWrapper (&k202::K202Proxy::setParamVector)));
			clazz->addMethod (new Method ("getArgsMap", createMethodWrapper (&k202::K202Proxy::getArgsMap)));
			clazz->addMethod (new Method ("setArgsMap", createMethodWrapper (&k202::K202Proxy::setArgsMap)));
		}
	}
	{
		Class *clazz = new Class ("Sender", typeid (Signal::Sender &), new Reflection::PtrDeleter <Signal::Sender>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void *>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void *, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("getOwnerObject", createMethodWrapper (&Signal::Sender::getOwnerObject)));
			clazz->addMethod (new Method ("setOwnerObject", createMethodWrapper (&Signal::Sender::setOwnerObject)));
			clazz->addMethod (new Method ("getScope", createMethodWrapper (&Signal::Sender::getScope)));
			clazz->addMethod (new Method ("setScope", createMethodWrapper (&Signal::Sender::setScope)));
			clazz->addMethod (new Method ("setPath", createMethodWrapper (&Signal::Sender::setPath)));
			clazz->addMethod (new Method ("getPath", createMethodWrapper (&Signal::Sender::getPath)));
			clazz->addMethod (new Method ("getParamVector", createMethodWrapper (&Signal::Sender::getParamVector)));
			clazz->addMethod (new Method ("setParamVector", createMethodWrapper (&Signal::Sender::setParamVector)));
			clazz->addMethod (new Method ("getParamMap", createMethodWrapper (&Signal::Sender::getParamMap)));
			clazz->addMethod (new Method ("setParamMap", createMethodWrapper (&Signal::Sender::setParamMap)));
		}
	}
}

struct Sentinel_tiliae {
        Sentinel_tiliae ()
        {
                createReflectionDatabase_tiliae ();
        }
};

static Sentinel_tiliae sentinel_tiliae;
} // namespace
