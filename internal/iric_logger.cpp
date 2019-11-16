#include "iric_logger.h"

#include <Poco/ConsoleChannel.h>
#include <Poco/Environment.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/LogStream.h>
#include <Poco/PatternFormatter.h>
#include <Poco/UTF8String.h>

#include <sstream>

namespace {

bool _initialized = false;

const std::string LOGGER_NAME = "iric_logger";

} // namespace

namespace iRICLib {

void _iric_logger_init()
{
	if (_initialized) {return;}

	std::vector<std::string> valid_names;
	valid_names.push_back("trace");
	valid_names.push_back("debug");
	valid_names.push_back("information");
	valid_names.push_back("notice");
	valid_names.push_back("warning");
	valid_names.push_back("error");
	valid_names.push_back("critical");
	valid_names.push_back("fatal");

	auto logLevel = Poco::UTF8::toLower(Poco::Environment::get("IRIC_LOG_LEVEL", "fatal"));

	// check if logLevel is valid
	bool ok = false;
	for (const auto& name : valid_names) {
		ok = ok || (logLevel == name);
	}

	if (! ok) {
		logLevel = "fatal";
	}

	auto& logger = Poco::Logger::root();
	auto fmt = new Poco::PatternFormatter("%p: %t");
	auto consoleChannel = new Poco::ConsoleChannel();
	logger.setChannel(new Poco::FormattingChannel(fmt, consoleChannel));
	logger.setLevel(logLevel);
	if (! ok) {
		Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_FATAL);
		s << "IRIC_LOG_LEVEL is invalid, and set to be default value: FATAL. Valid values are ";
		for (unsigned int i = 0; i < valid_names.size(); ++i) {
			if (i != 0) {s << ", ";}
			s << valid_names.at(i);
		}
		s << "." << std::endl;
	}

	_initialized = true;
}

Poco::Logger& _iric_logger_get()
{
	return Poco::Logger::get(LOGGER_NAME);
}

void _iric_logger_trace(const std::string& message)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	s << message << std::endl;
}

void _iric_logger_debug(const std::string& message)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_DEBUG);
	s << message << std::endl;
}

void _iric_logger_info(const std::string& message)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_INFORMATION);
	s << message << std::endl;
}

void _iric_logger_warn(const std::string& message)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_WARNING);
	s << message << std::endl;
}

void _iric_logger_error(const std::string& message)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_ERROR);
	s << message << std::endl;
}

void _iric_logger_error(const std::string& current, const std::string& func, int val)
{
	std::ostringstream ss;
	ss << "In " << current << "(), " << func << "() returned " << val;
	_iric_logger_error(ss.str());
}

void _iric_logger_trace_enter(const std::string& f_name)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	s << "Entered " << f_name << "()" << std::endl;
}

void _iric_logger_trace_leave(const std::string& f_name)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	s << "Leaving " << f_name << "()" << std::endl;
}

void _iric_logger_trace_call_start(const std::string& f_name, const std::string& c_name)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	s << "Entering " << f_name << "() in " << c_name << std::endl;
}

void _iric_logger_trace_call_end(const std::string& f_name, const std::string& c_name)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	s << "Returned from " << f_name << "() in " << c_name << std::endl;
}

void _iric_logger_trace_call_end(const std::string& f_name, const std::string& c_name, int ier)
{
	Poco::LogStream s(_iric_logger_get(), Poco::Message::PRIO_TRACE);
	if (ier != 0) {
		s.priority(Poco::Message::PRIO_ERROR);
	}
	s << "Returned from " << f_name << "() in " << c_name << " with value " << ier << std::endl;
}

} // namespace iRICLib
