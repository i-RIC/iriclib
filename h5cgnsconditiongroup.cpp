#include "error_macros.h"
#include "h5cgnsconditiongroup.h"
#include "h5groupcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"
#include "vectorutil.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsconditiongroup_impl.h"

#include <hdf5.h>

#include <sstream>

#define CHECK_NAME_EXISTS \
	if (impl->m_names.find(name) == impl->m_names.end()) {\
		std::ostringstream ss;\
		ss << "In H5CgnsConditionGroup::readStringLen(), data with name " << name << " does not exist";\
		_iric_logger_error(ss.str());\
		return IRIC_DATA_NOT_FOUND;\
	}

using namespace iRICLib;

namespace {

std::string valuePath(const std::string& name)
{
	std::ostringstream ss;
	ss << name << "/Value";

	return ss.str();
}

} // namespace

H5CgnsConditionGroup::H5CgnsConditionGroup(const std::string& name, hid_t groupId, H5CgnsFile::Mode mode) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_mode = mode;

	H5Util::getGroupNames(impl->m_groupId, &(impl->m_names));
}

H5CgnsConditionGroup::~H5CgnsConditionGroup()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsConditionGroup::~H5CgnsConditionGroup", "H5Gclose", status);
	}

	delete impl;
}

std::string H5CgnsConditionGroup::name() const
{
	return impl->m_name;
}

H5CgnsFile::Mode H5CgnsConditionGroup::mode() const
{
	return impl->m_mode;
}

int H5CgnsConditionGroup::readIntegerValue(const std::string& name, int* value) const
{
	CHECK_NAME_EXISTS;

	std::vector<int> buffer;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, valuePath(name), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);

	if (ier != IRIC_NO_ERROR) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readIntegerValue(), data with name " << name << " failed to read";
		_iric_logger_error(ss.str());
		return ier;
	}

	if (buffer.size() < 1) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readIntegerValue(), data with name " << name << " size == " << buffer.size();
		_iric_logger_error(ss.str());
		return IRIC_WRONG_DATASIZE;
	}

	*value = buffer.at(0);
	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readRealValueAsFloat(const std::string& name, float* value) const
{
	double dblValue;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::readRealValueAsDouble");
	int ier = readRealValueAsDouble(name, &dblValue);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::readRealValueAsDouble", ier);
	RETURN_IF_ERR;

	*value = static_cast<float> (dblValue);
	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readRealValueAsDouble(const std::string& name, double* value) const
{
	CHECK_NAME_EXISTS;

	std::vector<double> buffer;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, valuePath(name), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);

	if (ier != IRIC_NO_ERROR) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readRealValueAsDouble(), data with name " << name << " failed to read";
		_iric_logger_error(ss.str());
		return ier;
	}

	if (buffer.size() < 1) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readRealValueAsDouble(), data with name " << name << " size == " << buffer.size();
		_iric_logger_error(ss.str());
		return IRIC_WRONG_DATASIZE;
	}

	*value = buffer.at(0);
	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readStringLen(const std::string& name, int* length) const
{
	CHECK_NAME_EXISTS;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, valuePath(name), length);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readString(const std::string& name, char* value) const
{
	CHECK_NAME_EXISTS;

	std::vector<char> buffer;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, valuePath(name), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, value);
	*(value + buffer.size()) = 0;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctionalSize(const std::string& name, int* size) const
{
	CHECK_NAME_EXISTS;

	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(impl->m_groupId, name, H5Util::userDefinedDataLabel(), &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer1(gid);

	std::vector<std::string> names;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	ier = H5Util::getGroupNames(gid, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	if (names.size() == 0) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readFunctionalSize(), no group is found for name " << name;
		_iric_logger_error(ss.str());

		return IRIC_NO_DATA;
	}

	auto firstName = names.at(0);
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	ier = H5Util::readDataArrayLength(gid, firstName, size);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctional(const std::string& name, double* x, double* y) const
{
	CHECK_NAME_EXISTS;

	int ier;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::readFunctionalWithName");
	ier = readFunctionalWithName(name, "Param", x);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::readFunctionalWithName", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::readFunctionalWithName");
	ier = readFunctionalWithName(name, "Value", y);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::readFunctionalWithName", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctionalWithName(const std::string& name, const std::string& paramName, double* data) const
{
	CHECK_NAME_EXISTS;

	std::ostringstream ss;
	ss << name << "/" << paramName;

	std::vector<double> buffer;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);

	if (ier != IRIC_NO_ERROR) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readFunctionalWithName(), data with name " << name << ", paramName " << paramName << " failed to read";
		_iric_logger_error(ss.str());
		return ier;
	}

	_vectorToPointerT(buffer, data);

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctional(const std::string& name, float* x, float* y) const
{
	CHECK_NAME_EXISTS;

	int ier;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::readFunctionalWithName");
	ier = readFunctionalWithName(name, "Param", x);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::readFunctionalWithName", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::readFunctionalWithName");
	ier = readFunctionalWithName(name, "Value", y);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::readFunctionalWithName", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctionalWithName(const std::string& name, const std::string& paramName, float* data) const
{
	CHECK_NAME_EXISTS;

	std::ostringstream ss;
	ss << name << "/" << paramName;

	std::vector<double> buffer;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);

	if (ier != IRIC_NO_ERROR) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readFunctionalWithName(), data with name " << name << ", paramName " << paramName << " failed to read";
		_iric_logger_error(ss.str());
		return ier;
	}

	for (size_t i = 0; i < buffer.size(); ++i) {
		*(data + i) = static_cast<float> (buffer.at(i));
	}

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctionalWithNameStringLen(const std::string& name, const std::string& paramName, int* length) const
{
	CHECK_NAME_EXISTS;

	std::ostringstream ss;
	ss << name << "/" << paramName;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, ss.str(), length);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::readFunctionalWithNameString(const std::string& name, const std::string& paramName, char* value) const
{
	CHECK_NAME_EXISTS;

	std::ostringstream ss;
	ss << name << "/" << paramName;

	std::vector<char> buffer;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);

	if (ier != IRIC_NO_ERROR) {
		std::ostringstream ss;
		ss << "In H5CgnsConditionGroup::readFunctionalWithNameString(), data with name " << name << ", paramName " << paramName << " failed to read";
		_iric_logger_error(ss.str());
		return ier;
	}

	_vectorToPointerT(buffer, value);
	*(value + buffer.size()) = 0;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeIntegerValue(const std::string& name, int value)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	std::string name2 = "Value";
	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::Impl::openOrCreateGroups");
	int ier = impl->openOrCreateGroups(name, name2, "I4", &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::Impl::openOrCreateGroups", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gid);

	if (impl->m_mode == H5CgnsFile::Mode::OpenModify) {
		_IRIC_LOGGER_TRACE_CALL_START("deleteDataIfExists");
		ier = H5Util::deleteDataIfExists(gid, " data");
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("deleteDataIfExists", ier);
		RETURN_IF_ERR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("writeData");
	ier = H5Util::writeData(gid, " data", value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeRealValue(const std::string& name, double value)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	std::string name2 = "Value";
	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::Impl::openOrCreateGroups");
	int ier = impl->openOrCreateGroups(name, name2, "R8", &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::Impl::openOrCreateGroups", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gid);

	if (impl->m_mode == H5CgnsFile::Mode::OpenModify) {
		_IRIC_LOGGER_TRACE_CALL_START("deleteDataIfExists");
		ier = H5Util::deleteDataIfExists(gid, " data");
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("deleteDataIfExists", ier);
		RETURN_IF_ERR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("writeData");
	ier = H5Util::writeData(gid, " data", value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeString(const std::string& name, const std::string& value)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	std::string name2 = "Value";
	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::Impl::openOrCreateGroups");
	int ier = impl->openOrCreateGroups(name, name2, "C1", &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::Impl::openOrCreateGroups", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gid);

	if (impl->m_mode == H5CgnsFile::Mode::OpenModify) {
		_IRIC_LOGGER_TRACE_CALL_START("deleteDataIfExists");
		ier = H5Util::deleteDataIfExists(gid, " data");
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("deleteDataIfExists", ier);
		RETURN_IF_ERR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("writeData");
	ier = H5Util::writeData(gid, " data", value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeData", ier);
	RETURN_IF_ERR;

	impl->m_names.insert(name);

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeFunctional(const std::string& name, int length, double* x, double* y)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	int ier;
	_IRIC_LOGGER_TRACE_CALL_START("writeFunctionalWithName");
	ier = writeFunctionalWithName(name, "Param", length, x);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeFunctionalWithName", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("writeFunctionalWithName");
	ier = writeFunctionalWithName(name, "Value", length, y);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeFunctionalWithName", ier);
	RETURN_IF_ERR;

	impl->m_names.insert(name);

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeFunctionalWithName(const std::string& name, const std::string& paramName, int length, double* data)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::Impl::openOrCreateGroups");
	int ier = impl->openOrCreateGroups(name, paramName, "R8", &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::Impl::openOrCreateGroups", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gid);

	if (impl->m_mode == H5CgnsFile::Mode::OpenModify) {
		_IRIC_LOGGER_TRACE_CALL_START("deleteDataIfExists");
		ier = H5Util::deleteDataIfExists(gid, " data");
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("deleteDataIfExists", ier);
		RETURN_IF_ERR;
	}

	std::vector<double> buffer(length);

	_pointerToVectorT(data, &buffer);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeData");
	ier = H5Util::writeData(gid, " data", buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsConditionGroup::writeFunctionalWithNameString(const std::string& name, const std::string& paramName, const std::string& value)
{
	if (impl->m_mode == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_error("In H5CgnsConditionGroup::writeIntegerValue(), the file is opened in read only mode, so not possible to write");
		return IRIC_WRONG_FILEMODE;
	}

	hid_t gid;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsConditionGroup::Impl::openOrCreateGroups");
	int ier = impl->openOrCreateGroups(name, paramName, "C1", &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsConditionGroup::Impl::openOrCreateGroups", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gid);

	if (impl->m_mode == H5CgnsFile::Mode::OpenModify) {
		_IRIC_LOGGER_TRACE_CALL_START("deleteDataIfExists");
		ier = H5Util::deleteDataIfExists(gid, " data");
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("deleteDataIfExists", ier);
		RETURN_IF_ERR;
	}
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeData");
	ier = H5Util::writeData(gid, " data", value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
