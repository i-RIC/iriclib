#include "error_macros.h"
#include "h5attributecloser.h"
#include "h5datasetcloser.h"
#include "h5dataspacecloser.h"
#include "h5datatypecloser.h"
#include "h5groupcloser.h"
#include "h5objectcloser.h"
#include "h5propertylistcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include <sstream>
#include <string>

using namespace iRICLib;

#define USERDEFINEDDATA_TYPE "MT"
#define USERDEFINEDDATA_LABEL "UserDefinedData_t"
#define INDEXARRAY_TYPE "I4"
#define INDEXARRAY_LABEL "IndexArray_t"
#define DATAARRAY_LABEL "DataArray_t"

namespace {

template <typename V>
int readValueT(hid_t groupId, const std::string& name, std::vector<V>* value, hid_t dataTypeNative)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Dopen2");
	hid_t dataSetId = H5Dopen2(groupId,name.c_str(), H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dopen2");
	if (dataSetId < 0) {
		_iric_logger_error("readValueT", "H5Dopen2", dataSetId);
		return IRIC_H5_CALL_ERROR;
	}
	H5DatasetCloser dataSetCloser(dataSetId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dget_space");
	hid_t dataSpaceId = H5Dget_space(dataSetId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dget_space");
	if (dataSpaceId < 0) {
		_iric_logger_error("readValueT", "H5Dget_space", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}
	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	int ndims = H5Sget_simple_extent_ndims(dataSpaceId);
	std::vector<hsize_t> dims(ndims);
	H5Sget_simple_extent_dims(dataSpaceId, dims.data(), nullptr);
	hsize_t size = 1;
	for (int i = 0; i < ndims; ++i) {
		size *= dims[i];
	}
	value->assign(size, 0);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dread");
	herr_t status = H5Dread(dataSetId, dataTypeNative, H5S_ALL, H5S_ALL, H5P_DEFAULT, value->data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Dread");

	if (status < 0) {
		_iric_logger_error("readValueT", "H5Dread", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int writeValueT(hid_t groupId, const std::string& name, const std::vector<V>& value, const std::vector<hsize_t>& dims, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Screate_simple");
	hid_t dataSpaceId = H5Screate_simple(static_cast<int> (dims.size()), dims.data(), nullptr);
	_IRIC_LOGGER_TRACE_CALL_END("H5Screate_simple");
	if (dataSpaceId < 0) {
		_iric_logger_error("writeValueT", "H5Screate_simple", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dcreate2");
	hid_t dataSetId = H5Dcreate2(groupId, name.c_str(), dataTypeInFile, dataSpaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dcreate2");
	if (dataSetId < 0) {
		_iric_logger_error("writeValueT", "H5Dcreate2", dataSetId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DatasetCloser dataSetCloser(dataSetId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dwrite");
	herr_t status = H5Dwrite(dataSetId, dataTypeNative, H5S_ALL, H5S_ALL, H5P_DEFAULT, value.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Dwrite");

	if (status < 0) {
		_iric_logger_error("writeValueT", "H5Dwrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int writeValueT(hid_t groupId, const std::string& name, const std::vector<V>& value, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	std::vector<hsize_t> dims;
	dims.push_back(value.size());

	_IRIC_LOGGER_TRACE_CALL_START("writeValueT");
	int ier = writeValueT(groupId, name, value, dims, dataTypeInFile, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int writeValueT(hid_t groupId, const std::string& name, const V& value, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	std::vector<V> data;
	data.push_back(value);

	_IRIC_LOGGER_TRACE_CALL_START("writeValueT");
	int ier = writeValueT<V>(groupId, name, data, dataTypeInFile, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int createGroupWithValuesT(hid_t groupId, const std::string& name, const std::string& label, const std::vector<V>& values, const std::vector<hsize_t>& dims, const std::string& typeAtt, hid_t dataTypeInFile, hid_t dataTypeNative, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Pcreate");
	hid_t groupCreationProperty = H5Pcreate(H5P_GROUP_CREATE);
	_IRIC_LOGGER_TRACE_CALL_END("H5Pcreate");

	if (groupCreationProperty < 0) {
		_iric_logger_error("createGroupWithValuesT", "H5Pcreate", groupCreationProperty);
		return IRIC_H5_CALL_ERROR;
	}

	H5PropertyListCloser groupCreationPropertyCloser(groupCreationProperty);

	_IRIC_LOGGER_TRACE_CALL_START("H5Pset_link_creation_order");
	H5Pset_link_creation_order(groupCreationProperty, H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
	_IRIC_LOGGER_TRACE_CALL_END("H5Pset_link_creation_order");

	_IRIC_LOGGER_TRACE_CALL_START("H5Gcreate2");
	hid_t newGroupId = H5Gcreate2(groupId, name.c_str(), H5P_DEFAULT, groupCreationProperty, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gcreate2");

	if (newGroupId < 0) {
		_iric_logger_error("createGroupWithValuesT", "H5Gcreate2", newGroupId);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("writeValueT");
	int ier = writeValueT(newGroupId, " data", values, dims, dataTypeInFile, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeValueT", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(newGroupId, "name", name);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(newGroupId, "label", label);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(newGroupId, "type", typeAtt);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	int flags = 1;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	H5Util::writeAttribute(newGroupId, "flags", flags);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	if (newGroup != nullptr) {
		*newGroup = newGroupId;
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
		herr_t status = H5Gclose(newGroupId);
		_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");
		if (status < 0) {
			_iric_logger_error("createGroupWithValuesT", "H5Gclose", status);
			return IRIC_H5_CALL_ERROR;
		}
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int createGroupWithValuesT(hid_t groupId, const std::string& name, const std::string& label, const std::vector<V>& values, const std::string& typeAtt, hid_t dataTypeInFile, hid_t dataTypeNative, hid_t* newGroup)
{
	std::vector<hsize_t> dims;
	dims.push_back(values.size());

	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, values, dims, typeAtt, dataTypeInFile, dataTypeNative, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int createGroupWithValueT(hid_t groupId, const std::string& name, const std::string& label, const V& value, const std::string& typeAtt, hid_t dataTypeInFile, hid_t dataTypeNative, hid_t* newGroup)
{
	std::vector<V> values;
	values.push_back(value);

	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, values, typeAtt, dataTypeInFile, dataTypeNative, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int readGroupValueT(hid_t groupId, std::vector<V>* value, hid_t dataTypeNative)
{
	_IRIC_LOGGER_TRACE_CALL_START("readValueT");
	int ier = readValueT(groupId, " data", value, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("readValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int updateGroupValueT(hid_t groupId, const std::vector<V>& value, const std::vector<hsize_t>& dims, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Ldelete");
	herr_t status = H5Ldelete(groupId, " data", H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Ldelete");

	if (status < 0) {
		_iric_logger_error("updateGroupValueT", "H5Ldelete", status);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("writeValueT");
	int ier = writeValueT(groupId, " data", value, dims, dataTypeInFile, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int updateGroupValueT(hid_t groupId, const std::vector<V>& value, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	std::vector<int> dims;
	dims.push_back(static_cast<int> (value.size()));

	_IRIC_LOGGER_TRACE_CALL_START("updateGroupValueT");
	int ier = updateGroupValueT(groupId, value, dims, dataTypeInFile, dataTypeNative);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateGroupValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int updateGroupValueT(hid_t groupId, const V& value, hid_t dataTypeNative)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Dopen2");
	hid_t dataSetId = H5Dopen2(groupId, " data", H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dopen2");

	if (dataSetId < 0) {
		_iric_logger_error("updateGroupValueT", "H5Dopen2", dataSetId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DatasetCloser datasetCloser(dataSetId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dwrite");
	herr_t status = H5Dwrite(dataSetId, dataTypeNative, H5S_ALL, H5S_ALL, H5P_DEFAULT, &value);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dwrite");

	if (status < 0) {
		_iric_logger_error("updateGroupValueT", "H5Dwrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int updateOrCreateDataArrayT(hid_t groupId, const std::string& name, const std::vector<V>& values, const std::vector<hsize_t>& dims, const std::string& typeAtt, hid_t dataTypeInFile, hid_t dataTypeNative, std::set<std::string>* names = nullptr)
{
	std::set<std::string> tmpNames;
	if (names != nullptr) {
		tmpNames = *names;
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
		int ier = H5Util::getGroupNames(groupId, &tmpNames);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
		RETURN_IF_ERR;
	}

	if (tmpNames.find(name) != tmpNames.end()) {
		hid_t gId;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = H5Util::openGroup(groupId, name, DATAARRAY_LABEL, &gId);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
		RETURN_IF_ERR;

		H5GroupCloser closer(gId);

		_IRIC_LOGGER_TRACE_CALL_START("updateGroupValueT");
		ier = updateGroupValueT(gId, values, dims, dataTypeInFile, dataTypeNative);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateGroupValueT", ier);
		RETURN_IF_ERR;
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
		int ier = createGroupWithValuesT(groupId, name, DATAARRAY_LABEL, values, dims, typeAtt, dataTypeInFile, dataTypeNative, nullptr);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
		RETURN_IF_ERR;

		tmpNames.insert(name);
		if (names != nullptr) {
			*names = tmpNames;
		}
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int updateOrCreateDataArrayT(hid_t groupId, const std::string& name, const std::vector<V>& values, const std::string& typeAtt, hid_t dataTypeInFile, hid_t dataTypeNative, std::set<std::string>* names = nullptr)
{
	std::vector<hsize_t> dims;
	dims.push_back(values.size());

	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, values, dims, typeAtt, dataTypeInFile, dataTypeNative, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

template <typename V>
int writeAttributeT(hid_t groupId, const std::string& name, const V& value, hid_t dataTypeInFile, hid_t dataTypeNative)
{
	hsize_t datalen = 1;
	_IRIC_LOGGER_TRACE_CALL_START("H5Screate_simple");
	hid_t dataSpaceId = H5Screate_simple(1, &datalen, nullptr);
	_IRIC_LOGGER_TRACE_CALL_END("H5Screate_simple");

	if (dataSpaceId < 0) {
		_iric_logger_error("writeAttributeT", "H5Screate_simple", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Acreate2");
	hid_t attId = H5Acreate2(groupId, name.c_str(), dataTypeInFile, dataSpaceId, H5P_DEFAULT, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Acreate2");
	if (attId < 0) {
		_iric_logger_error("writeAttributeT", "H5Acreate2", attId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser attributeCloser(attId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Awrite");
	herr_t status = H5Awrite(attId, dataTypeNative, &value);
	_IRIC_LOGGER_TRACE_CALL_END("H5Awrite");

	if (status < 0) {
		_iric_logger_error("writeAttributeT", "H5Awrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int copyDataType(hid_t src, hid_t* tgt)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Tget_size");
	size_t attSize = H5Tget_size(src);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tget_size");

	_IRIC_LOGGER_TRACE_CALL_START("H5Tcopy");
	*tgt = H5Tcopy(src);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tcopy");

	_IRIC_LOGGER_TRACE_CALL_START("H5Tset_size");
	herr_t status = H5Tset_size(*tgt, attSize);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tset_size");

	if (status < 0) {
		_iric_logger_error("copyDataType", "H5Tset_size", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int copyDataSpace(hid_t src, hid_t* tgt)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Scopy");
	*tgt = H5Scopy(src);
	_IRIC_LOGGER_TRACE_CALL_END("H5Scopy");

	_IRIC_LOGGER_TRACE_CALL_START("H5Sextent_copy");
	herr_t status = H5Sextent_copy(src, *tgt);
	_IRIC_LOGGER_TRACE_CALL_END("H5Sextent_copy");

	if (status < 0) {
		_iric_logger_error("copyDataSpace", "H5Sextent_copy", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int setupBuffer(hid_t dataType, hid_t dataSpace, std::vector<char>* buffer)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Tget_size");
	hsize_t dtSize = H5Tget_size(dataType);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tget_size");

	_IRIC_LOGGER_TRACE_CALL_START("H5Sget_simple_extent_ndims");
	int ndims = H5Sget_simple_extent_ndims(dataSpace);
	_IRIC_LOGGER_TRACE_CALL_END("H5Sget_simple_extent_ndims");

	std::vector<hsize_t> dims(ndims);
	_IRIC_LOGGER_TRACE_CALL_START("H5Sget_simple_extent_dims");
	H5Sget_simple_extent_dims(dataSpace, dims.data(), nullptr);
	_IRIC_LOGGER_TRACE_CALL_END("H5Sget_simple_extent_dims");

	hsize_t dsSize = 1;
	for (int i = 0; i < ndims; ++i) {
		dsSize *= dims.at(i);
	}
	hsize_t totalSize = dtSize * dsSize;
	std::ostringstream ss;
	ss << "In setupBuffer(), totalSize = " << totalSize;
	_iric_logger_debug(ss.str());

	buffer->assign(totalSize, 0);
	return true;
}

int copyAttribute(hid_t srcId, hid_t tgtId, const std::string& name)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Aopen");
	hid_t srcAttId = H5Aopen(srcId, name.c_str(), H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aopen");

	if (srcAttId < 0) {
		_iric_logger_error("copyAttribute", "H5Aopen", srcAttId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser srcAttCloser(srcAttId);

	// copying datatype
	_IRIC_LOGGER_TRACE_CALL_START("H5Aget_type");
	hid_t srcDataTypeId = H5Aget_type(srcAttId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aget_type");

	if (srcDataTypeId < 0) {
		_iric_logger_error("copyAttribute", "H5Aget_type", srcDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser srcDataTypeCloser(srcDataTypeId);

	hid_t tgtDataTypeId;

	_IRIC_LOGGER_TRACE_CALL_START("copyDataType");
	int ier = copyDataType(srcDataTypeId, &tgtDataTypeId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyDataType", ier);
	RETURN_IF_ERR;

	H5DataTypeCloser tgtDataTypeCloser(tgtDataTypeId);

	// copying dataspace
	_IRIC_LOGGER_TRACE_CALL_START("H5Aget_space");
	hid_t srcDataSpaceId = H5Aget_space(srcAttId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aget_space");

	if (srcDataSpaceId < 0) {
		_iric_logger_error("copyAttribute", "H5Aget_space", srcDataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser srcDataSpaceCloser(srcDataSpaceId);

	hid_t tgtDataSpaceId;
	_IRIC_LOGGER_TRACE_CALL_START("copyDataSpace");
	ier = copyDataSpace(srcDataSpaceId, &tgtDataSpaceId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyDataSpace", ier);
	RETURN_IF_ERR;

	H5DataSpaceCloser tgtDataSpaceCloser(tgtDataSpaceId);

	std::vector<char> buffer;
	_IRIC_LOGGER_TRACE_CALL_START("setupBuffer");
	ier = setupBuffer(srcDataTypeId, srcDataSpaceId, &buffer);
	_IRIC_LOGGER_TRACE_CALL_END("setupBuffer");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Aread");
	herr_t status = H5Aread(srcAttId, srcDataTypeId, buffer.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Aread");

	if (status < 0) {
		_iric_logger_error("copyAttribute", "H5Aread", status);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Acreate2");
	hid_t tgtAttId = H5Acreate2(tgtId, name.c_str(), tgtDataTypeId, tgtDataSpaceId, H5P_DEFAULT, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Acreate2");

	if (tgtAttId < 0) {
		_iric_logger_error("copyAttribute", "H5Acreate2", tgtAttId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser tgtAttCloser(tgtAttId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Awrite");
	status = H5Awrite(tgtAttId, srcDataTypeId, buffer.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Awrite");

	if (status < 0) {
		_iric_logger_error("copyAttribute", "H5Awrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int copyAttributes(hid_t srcId, hid_t tgtId)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Aget_num_attrs");
	int num = H5Aget_num_attrs(srcId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aget_num_attrs");

	for (int i = 0; i < num; ++i) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Aget_name_by_idx");
		size_t size = H5Aget_name_by_idx(srcId, ".", H5_INDEX_NAME, H5_ITER_INC, i, nullptr, 0, H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Aget_name_by_idx");

		std::vector<char> buffer(size);
		_IRIC_LOGGER_TRACE_CALL_START("H5Aget_name_by_idx");
		H5Aget_name_by_idx(srcId, ".", H5_INDEX_NAME, H5_ITER_INC, i, buffer.data(), buffer.size(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Aget_name_by_idx");

		_IRIC_LOGGER_TRACE_CALL_START("copyAttribute");
		int ier = copyAttribute(srcId, tgtId, buffer.data());
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyAttribute", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int copyDataset(hid_t srcId, hid_t tgtId, const std::string& name)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Dopen");
	hid_t srcDatasetId = H5Dopen(srcId, name.c_str(), H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dopen");

	if (srcDatasetId < 0) {
		_iric_logger_error("copyDataset", "H5Dopen", srcDatasetId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DatasetCloser srcDatasetCloser(srcDatasetId);

	// copying datatype
	_IRIC_LOGGER_TRACE_CALL_START("H5Dget_type");
	hid_t srcDataTypeId = H5Dget_type(srcDatasetId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dget_type");

	if (srcDataTypeId < 0) {
		_iric_logger_error("copyDataset", "H5Dget_type", srcDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser srcDataTypeCloser(srcDataTypeId);

	hid_t tgtDataTypeId;

	_IRIC_LOGGER_TRACE_CALL_START("copyDataType");
	int ier = copyDataType(srcDataTypeId, &tgtDataTypeId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyDataType", ier);
	RETURN_IF_ERR;

	H5DataTypeCloser tgtDataTypeCloser(tgtDataTypeId);

	// copying dataspace
	_IRIC_LOGGER_TRACE_CALL_START("srcDatasetId");
	hid_t srcDataSpaceId = H5Aget_space(srcDatasetId);
	_IRIC_LOGGER_TRACE_CALL_END("srcDatasetId");

	if (srcDataSpaceId < 0) {
		_iric_logger_error("copyDataset", "H5Aget_space", srcDataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser srcDataSpaceCloser(srcDataSpaceId);

	hid_t tgtDataSpaceId;
	_IRIC_LOGGER_TRACE_CALL_START("copyDataSpace");
	ier = copyDataSpace(srcDataSpaceId, &tgtDataSpaceId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyDataSpace", ier);
	RETURN_IF_ERR;

	H5DataSpaceCloser tgtDataSpaceCloser(tgtDataSpaceId);

	std::vector<char> buffer;
	_IRIC_LOGGER_TRACE_CALL_START("setupBuffer");
	ier = setupBuffer(srcDataTypeId, srcDataSpaceId, &buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("setupBuffer", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dread");
	herr_t status = H5Dread(srcDatasetId, srcDataTypeId,H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Dread");

	if (status < 0) {
		_iric_logger_error("copyDataset", "H5Dread", status);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Dcreate2");
	hid_t tgtDatasetId = H5Dcreate2(tgtId, name.c_str(), tgtDataTypeId, tgtDataSpaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dcreate2");

	H5DatasetCloser tgtDatasetCloser(tgtDatasetId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Dwrite");
	status = H5Dwrite(tgtDatasetId, srcDataTypeId, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Dwrite");

	if (status < 0) {
		_iric_logger_error("copyDataset", "H5Dwrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int copyChildren(hid_t srcGroupId, hid_t tgtGroupId)
{
	H5G_info_t info;
	_IRIC_LOGGER_TRACE_CALL_START("H5Gget_info");
	herr_t status = H5Gget_info(srcGroupId, &info);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gget_info");

	if (status < 0) {
		_iric_logger_error("copyChildren", "H5Gget_info", status);
		return IRIC_H5_CALL_ERROR;
	}

	for (hsize_t i = 0; i < info.nlinks; ++i) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		ssize_t nameLen = H5Lget_name_by_idx(srcGroupId, ".", H5_INDEX_NAME, H5_ITER_INC, i, nullptr, 0, H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		if (nameLen < 0) {continue;}

		std::vector<char> buffer(nameLen + 1);
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		H5Lget_name_by_idx(srcGroupId, ".", H5_INDEX_NAME, H5_ITER_INC, i, buffer.data(), buffer.size(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		std::string name = buffer.data();

		_IRIC_LOGGER_TRACE_CALL_START("H5Oopen");
		hid_t oid = H5Oopen(srcGroupId, name.c_str(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oopen");

		if (oid < 0) {continue;}

		H5O_info_t info;
		_IRIC_LOGGER_TRACE_CALL_START("H5Oget_info");
		status = H5Oget_info(oid, &info);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oget_info");

		_IRIC_LOGGER_TRACE_CALL_START("H5Oclose");
		H5Oclose(oid);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oclose");

		if (status < 0) {
			_iric_logger_error("copyChildren", "H5Oget_info", status);
			return IRIC_H5_CALL_ERROR;
		}

		if (info.type == H5O_TYPE_GROUP) {
			_IRIC_LOGGER_TRACE_CALL_START("H5Gopen2");
			hid_t srcChildGroupId = H5Gopen2(srcGroupId, name.c_str(), H5P_DEFAULT);
			_IRIC_LOGGER_TRACE_CALL_END("H5Gopen2");

			if (srcChildGroupId < 0) {
				_iric_logger_error("copyChildren", "H5Gopen2", srcChildGroupId);
				return IRIC_H5_CALL_ERROR;
			}

			H5GroupCloser srcChildGroupCloser(srcChildGroupId);

			_IRIC_LOGGER_TRACE_CALL_START("H5Pcreate");
			hid_t groupCreationProperty = H5Pcreate(H5P_GROUP_CREATE);
			_IRIC_LOGGER_TRACE_CALL_END("H5Pcreate");

			if (groupCreationProperty < 0) {
				_iric_logger_error("copyChildren", "H5Pcreate", groupCreationProperty);
				return IRIC_H5_CALL_ERROR;
			}

			H5PropertyListCloser groupCreationPropertyCloser(groupCreationProperty);

			_IRIC_LOGGER_TRACE_CALL_START("H5Pset_link_creation_order");
			H5Pset_link_creation_order(groupCreationProperty, H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
			_IRIC_LOGGER_TRACE_CALL_END("H5Pset_link_creation_order");

			_IRIC_LOGGER_TRACE_CALL_START("H5Gcreate2");
			hid_t tgtChildGroupId = H5Gcreate2(tgtGroupId, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
			_IRIC_LOGGER_TRACE_CALL_END("H5Gcreate2");

			if (tgtChildGroupId < 0) {
				_iric_logger_error("copyChildren", "H5Gcreate2", tgtChildGroupId);
				return IRIC_H5_CALL_ERROR;
			}

			H5GroupCloser tgtChildGroupCloser(tgtChildGroupId);

			_IRIC_LOGGER_TRACE_CALL_START("H5Util::copyGroup");
			int ier = H5Util::copyGroup(srcChildGroupId, tgtChildGroupId);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::copyGroup", ier);
			RETURN_IF_ERR;
		} else if (info.type == H5O_TYPE_DATASET) {
			_IRIC_LOGGER_TRACE_CALL_START("copyDataset");
			int ier = copyDataset(srcGroupId, tgtGroupId, name);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyDataset", ier);
			RETURN_IF_ERR;
		}
	}

	return IRIC_NO_ERROR;
}

} // namespace

std::string H5Util::indexArrayLabel()
{
	return INDEXARRAY_LABEL;
}

std::string H5Util::indexArrayType()
{
	return INDEXARRAY_TYPE;
}

std::string H5Util::dataArrayLabel()
{
	return DATAARRAY_LABEL;
}

std::string H5Util::userDefinedDataLabel()
{
	return USERDEFINEDDATA_LABEL;
}

std::string H5Util::userDefinedDataType()
{
	return USERDEFINEDDATA_TYPE;
}

int H5Util::getGroupNames(hid_t groupId, std::vector<std::string>* names)
{
	H5G_info_t info;
	_IRIC_LOGGER_TRACE_CALL_START("H5Gget_info");
	herr_t status = H5Gget_info(groupId, &info);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gget_info");

	if (status < 0) {
		_iric_logger_error("H5Util::getGroupNames", "H5Gget_info", status);
		return IRIC_H5_CALL_ERROR;
	}

	for (hsize_t i = 0; i < info.nlinks; ++i) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		ssize_t nameLen = H5Lget_name_by_idx(groupId, ".", H5_INDEX_CRT_ORDER, H5_ITER_INC, i, nullptr, 0, H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		if (nameLen < 0) {continue;}

		std::vector<char> buffer(nameLen + 1);
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		H5Lget_name_by_idx(groupId, ".", H5_INDEX_CRT_ORDER, H5_ITER_INC, i, buffer.data(), buffer.size(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		std::string name = buffer.data();

		_IRIC_LOGGER_TRACE_CALL_START("H5Oopen");
		hid_t oid = H5Oopen(groupId, name.c_str(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oopen");

		if (oid < 0) {
			_iric_logger_error("H5Util::getGroupNames", "H5Open", oid);
			return IRIC_H5_CALL_ERROR;
		}

		H5ObjectCloser objectCloser(oid);

		H5O_info_t info;
		_IRIC_LOGGER_TRACE_CALL_START("H5Oget_info");
		status = H5Oget_info(oid, &info);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oget_info");

		if (status < 0) {
			_iric_logger_error("H5Util::getGroupNames", "H5Oget_info", status);
			return IRIC_H5_CALL_ERROR;
		}

		if (info.type == H5O_TYPE_GROUP) {
			names->push_back(name);
		}
	}

	return IRIC_NO_ERROR;
}

int H5Util::getGroupNames(hid_t groupId, std::set<std::string>* names)
{
	std::vector<std::string> namesVec;

	int ier = getGroupNames(groupId, &namesVec);
	RETURN_IF_ERR;

	for (const auto& name : namesVec) {
		names->insert(name);
	}
	return IRIC_NO_ERROR;
}

int H5Util::createGroup(hid_t groupId, const std::string& name, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Pcreate");
	hid_t groupCreationProperty = H5Pcreate(H5P_GROUP_CREATE);
	_IRIC_LOGGER_TRACE_CALL_END("H5Pcreate");

	if (groupCreationProperty < 0) {
		_iric_logger_error("H5Util::createGroup", "H5Pcreate", groupCreationProperty);
		return IRIC_H5_CALL_ERROR;
	}

	H5PropertyListCloser groupCreationPropertyCloser(groupCreationProperty);

	_IRIC_LOGGER_TRACE_CALL_START("H5Pset_link_creation_order");
	H5Pset_link_creation_order(groupCreationProperty, H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
	_IRIC_LOGGER_TRACE_CALL_END("H5Pset_link_creation_order");

	_IRIC_LOGGER_TRACE_CALL_START("H5Gcreate2");
	hid_t newGroupId = H5Gcreate2(groupId, name.c_str(), H5P_DEFAULT, groupCreationProperty, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gcreate2");

	if (newGroupId < 0) {
		_iric_logger_error("H5Util::createGroup", "H5Gcreate2", newGroupId);
		return IRIC_H5_CALL_ERROR;
	}

	*newGroup = newGroupId;

	return IRIC_NO_ERROR;
}

int H5Util::createGroup(hid_t groupId, const std::string& name, const std::string& label, const std::string& type, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = createGroup(groupId, name, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::createGroup");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(*newGroup, "name", name);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(*newGroup, "label", label);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(*newGroup, "type", type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	int flags = 1;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeAttribute");
	ier = H5Util::writeAttribute(*newGroup, "flags", flags);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeAttribute", ier);

	return IRIC_NO_ERROR;
}

int H5Util::createUserDefinedDataGroup(hid_t groupId, const std::string& name, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = createGroup(groupId, name, USERDEFINEDDATA_LABEL, USERDEFINEDDATA_TYPE, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::openGroup(hid_t groupId, const std::string& name, const std::string& label, hid_t* childGroup, bool noErrorLog)
{
	*childGroup = -1;

	_IRIC_LOGGER_TRACE_CALL_START("H5Oopen");
	hid_t groupId2 = H5Oopen(groupId, name.c_str(), H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Oopen");
	if (groupId2 < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Oopen", groupId2);
		return IRIC_H5_CALL_ERROR;
	}

	// read type info
	H5O_info_t ginfo;
	_IRIC_LOGGER_TRACE_CALL_START("H5Oget_info");
	herr_t status = H5Oget_info(groupId2, &ginfo);
	_IRIC_LOGGER_TRACE_CALL_END("H5Oget_info");
	if (status < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Oget_info", status);
		return IRIC_H5_CALL_ERROR;
	}

	if (ginfo.type != H5O_TYPE_GROUP) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Oclose");
		H5Oclose(groupId2);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oclose");

		if (! noErrorLog) {
			std::ostringstream ss;
			ss << "H5Util::openGroup(), object with name " << name << " is not a group, but the type = " << ginfo.type;
			_iric_logger_error(ss.str());
		}

		return IRIC_NOT_GROUP;
	}

	// read label attribute
	_IRIC_LOGGER_TRACE_CALL_START("H5Aopen");
	hid_t attId = H5Aopen(groupId2, "label", H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aopen");

	if (attId < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Aopen", attId);

		_IRIC_LOGGER_TRACE_CALL_START("H5Oclose");
		H5Oclose(groupId2);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oclose");

		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser attCloser(attId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Aget_type");
	hid_t fileDataTypeId = H5Aget_type(attId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aget_type");

	if (fileDataTypeId < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Aget_type", fileDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser fileDataTypeCloser(fileDataTypeId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Tget_size");
	size_t labelSize = H5Tget_size(fileDataTypeId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tget_size");

	std::vector<char> buf(labelSize, 0);

	// dataTypeForMemory
	_IRIC_LOGGER_TRACE_CALL_START("H5Tcopy");
	hid_t memDataTypeId = H5Tcopy(H5T_C_S1);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tcopy");

	if (memDataTypeId < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Tcopy", memDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser memDataTypeCloser(memDataTypeId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Tset_size");
	status = H5Tset_size(memDataTypeId, labelSize);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tset_size");

	if (status < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Tset_size", status);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Aread");
	status = H5Aread(attId, memDataTypeId, buf.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Aread");

	if (status < 0) {
		_iric_logger_error("H5Util::openGroup", "H5Aread", status);
		return IRIC_H5_CALL_ERROR;
	}

	if (label != std::string(buf.data())) {
		if (!noErrorLog) {
			std::ostringstream ss;
			ss << "In H5Util::openGroup(), for group with name " << name << ", label " << label << " was expected, but actually " << buf.data();
			_iric_logger_error(ss.str());
		}
		_IRIC_LOGGER_TRACE_CALL_START("H5Oclose");
		H5Oclose(groupId2);
		_IRIC_LOGGER_TRACE_CALL_END("H5Oclose");

		return IRIC_WRONG_GROUP_LABEL;
	}

	*childGroup = groupId2;

	return IRIC_NO_ERROR;
}

int H5Util::openOrCreateGroup(hid_t groupId, const std::string& name, const std::string& label, const std::string& type, hid_t* childGroup, const std::set<std::string>& names)
{
	if (names.find(name) != names.end()) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = openGroup(groupId, name, label, childGroup, true);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
		RETURN_IF_ERR;
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
		int ier = createGroup(groupId, name, label, type, childGroup);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int H5Util::openOrCreateUserDefinedDataGroup(hid_t groupId, const std::string& name, hid_t* childGroup, const std::set<std::string>& names)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateGroup");
	int ier = openOrCreateGroup(groupId, name, USERDEFINEDDATA_LABEL, USERDEFINEDDATA_TYPE, childGroup, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openOrCreateGroup", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const int& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValueT");
	int ier = createGroupWithValueT(groupId, name, label, value, "I4", H5T_STD_I32LE, H5T_NATIVE_INT32, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const float& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValueT");
	int ier = createGroupWithValueT(groupId, name, label, value, "R4", H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const double& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValueT");
	int ier = createGroupWithValueT(groupId, name, label, value, "R8", H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::string& value, hid_t* newGroup)
{
	std::vector<char> buffer;
	buffer.assign(value.length(), 0);
	for (size_t i = 0; i < value.length(); ++i) {
		buffer[i] = value.at(i);
	}
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, label, buffer, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<char>& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, "C1", H5T_STD_I8LE, H5T_NATIVE_INT8, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<int>& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, "I4", H5T_STD_I32LE, H5T_NATIVE_INT32, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<float>& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, "R4", H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<double>& value, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, "R8", H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<char>& value, const std::vector<hsize_t>& dims, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, dims, "C1", H5T_STD_I8LE, H5T_NATIVE_INT8, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<int>& value, const std::vector<hsize_t>& dims, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, dims, "I4", H5T_STD_I32LE, H5T_NATIVE_INT32, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<float>& value, const std::vector<hsize_t>& dims, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, dims, "R4", H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createGroupWithValue(hid_t groupId, const std::string& name, const std::string& label, const std::vector<double>& value, const std::vector<hsize_t>& dims, hid_t* newGroup)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValuesT");
	int ier = createGroupWithValuesT(groupId, name, label, value, dims, "R8", H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, newGroup);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValuesT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::string& value)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<char>& value)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<int>& value)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<float>& value)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<double>& value)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<char>& value, const std::vector<hsize_t>& dims)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<int>& value, const std::vector<hsize_t>& dims)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<float>& value, const std::vector<hsize_t>& dims)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::createDataArray(hid_t groupId, const std::string& name, const std::vector<double>& value, const std::vector<hsize_t>& dims)
{
	_IRIC_LOGGER_TRACE_CALL_START("createGroupWithValue");
	int ier = createGroupWithValue(groupId, name, DATAARRAY_LABEL, value, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::string& value, std::set<std::string>* names)
{
	std::vector<char> buffer(value.length(), 0);
	for (size_t i = 0; i < value.length(); ++i) {
		buffer[i] = value.at(i);
	}
	return updateOrCreateDataArray(groupId, name, buffer, names);
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<char>& value, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, "C1", H5T_STD_I8LE, H5T_NATIVE_INT8, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<int>& value, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, "I4", H5T_STD_I32LE, H5T_NATIVE_INT32, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<float>& value, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, "R4", H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<double>& value, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, "R8", H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<std::string>& value, std::set<std::string>* names)
{
	size_t maxLen = 0;
	for (const auto& v : value) {
		auto len = v.length();
		if (len > maxLen) {maxLen = len;}
	}
	maxLen += 1; // for \0

	std::vector<hsize_t> dims;
	dims.push_back(value.size());
	dims.push_back(maxLen);

	std::vector<char> buffer;
	buffer.assign(maxLen * value.size(), 0);

	for (size_t i = 0; i < value.size(); ++i) {
		const auto& v = value.at(i);
		memcpy(buffer.data() + i * maxLen, v.data(), v.length());
	}
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, buffer, dims, "C1", H5T_STD_I8LE, H5T_NATIVE_INT8, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<char>& value, const std::vector<hsize_t>& dims, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, dims, "C1", H5T_STD_I8LE, H5T_NATIVE_INT8, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<int>& value, const std::vector<hsize_t>& dims, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, dims, "I4", H5T_STD_I32LE, H5T_NATIVE_INT32, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<float>& value, const std::vector<hsize_t>& dims, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, dims, "R4", H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::updateOrCreateDataArray(hid_t groupId, const std::string& name, const std::vector<double>& value, const std::vector<hsize_t>& dims, std::set<std::string>* names)
{
	_IRIC_LOGGER_TRACE_CALL_START("updateOrCreateDataArrayT");
	int ier = updateOrCreateDataArrayT(groupId, name, value, dims, "R8", H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("updateOrCreateDataArrayT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValueDimensions(hid_t groupId, std::vector<hsize_t>* dims)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Dopen2");
	hid_t dataSetId = H5Dopen2(groupId, " data", H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dopen2");

	if (dataSetId < 0) {
		_iric_logger_error("H5Util::readGroupValueDimensions", "H5Dopen2", dataSetId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DatasetCloser dataSetCloser(dataSetId);

	hid_t dataSpaceId = H5Dget_space(dataSetId);
	if (dataSpaceId < 0) {
		_iric_logger_error("H5Util::readGroupValueDimensions", "H5Dget_space", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	int ndims = H5Sget_simple_extent_ndims(dataSpaceId);
	dims->assign(ndims, 0);
	H5Sget_simple_extent_dims(dataSpaceId, dims->data(), nullptr);

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValueLength(hid_t groupId, int* length)
{
	std::vector<hsize_t> dims;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueDimensions");
	int ier = readGroupValueDimensions(groupId, &dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueDimensions", ier);
	RETURN_IF_ERR;

	hsize_t ret = 1;
	for (size_t i = 0; i < dims.size(); ++i) {
		ret *= dims.at(i);
	}

	*length = static_cast<int> (ret);
	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::string* value)
{
	std::vector<char> data;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
	int ier = readGroupValue(groupId, &data);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);
	RETURN_IF_ERR;

	data.push_back(0);
	*value = data.data();

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::vector<char>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueT");
	int ier = readGroupValueT(groupId, values, H5T_NATIVE_INT8);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::vector<int>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueT");
	int ier = readGroupValueT(groupId, values, H5T_NATIVE_INT32);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::vector<float>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueT");
	int ier = readGroupValueT(groupId, values, H5T_NATIVE_FLOAT);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::vector<double>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueT");
	int ier = readGroupValueT(groupId, values, H5T_NATIVE_DOUBLE);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readGroupValue(hid_t groupId, std::vector<std::string>* values)
{
	std::vector<hsize_t> dims;
	std::vector<char> buffer;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueDimensions");
	int ier = H5Util::readGroupValueDimensions(groupId, &dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueDimensions", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueT");
	ier = readGroupValueT(groupId, &buffer, H5T_NATIVE_INT8);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueT", ier);
	RETURN_IF_ERR;

	hsize_t count = dims.at(0);
	hsize_t maxLen = dims.at(1);

	std::vector<char> buffer2(maxLen);

	for (hsize_t i = 0; i < count; ++i) {
		memcpy(buffer2.data(), (buffer.data() + i * maxLen), maxLen);
		values->push_back(buffer2.data());
	}

	return IRIC_NO_ERROR;
}

int H5Util::readDataArrayValueType(hid_t groupId, const std::string& name, DataArrayValueType* type)
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	// read type attribute
	_IRIC_LOGGER_TRACE_CALL_START("H5Aopen");
	hid_t attId = H5Aopen(gId, "type", H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aopen");

	if (attId < 0) {
		_iric_logger_error("H5Util::readDataArrayValueType", "H5Aopen", attId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser attCloser(attId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Aget_type");
	hid_t fileDataTypeId = H5Aget_type(attId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aget_type");

	if (fileDataTypeId < 0) {
		_iric_logger_error("H5Util::readDataArrayValueType", "H5Aget_type", attId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser fileDataTypeCloser(fileDataTypeId);

	size_t labelSize = H5Tget_size(fileDataTypeId);

	std::vector<char> buf(labelSize, 0);

	// dataTypeForMemory
	_IRIC_LOGGER_TRACE_CALL_START("H5Tcopy");
	hid_t memDataTypeId = H5Tcopy(H5T_C_S1);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tcopy");

	if (memDataTypeId < 0) {
		_iric_logger_error("H5Util::readDataArrayValueType", "H5Tcopy", memDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser memDataTypeCloser(memDataTypeId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Tset_size");
	herr_t status = H5Tset_size(memDataTypeId, labelSize);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tset_size");

	if (status < 0) {
		_iric_logger_error("H5Util::readDataArrayValueType", "H5Tset_size", status);
		return IRIC_H5_CALL_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Aread");
	status = H5Aread(attId, memDataTypeId, buf.data());
	_IRIC_LOGGER_TRACE_CALL_END("H5Aread");

	if (status < 0) {
		_iric_logger_error("H5Util::readDataArrayValueType", "H5Aread", status);
		return IRIC_H5_CALL_ERROR;
	}

	std::string typeStr = buf.data();

	if (typeStr == "C1") {
		*type = DataArrayValueType::Char;
		return IRIC_NO_ERROR;
	} else if (typeStr == "I4") {
		*type = DataArrayValueType::Int;
		return IRIC_NO_ERROR;
	} else if (typeStr == "R4") {
		*type = DataArrayValueType::RealSingle;
		return IRIC_NO_ERROR;
	} else if (typeStr == "R8") {
		*type = DataArrayValueType::RealDouble;
		return IRIC_NO_ERROR;
	}

	std::ostringstream ss;
	ss << "In H5Util::readDataArrayValueType() << unknown type " << typeStr << " detected";
	_iric_logger_error(ss.str());

	return IRIC_WRONG_DATATYPE;
}

int H5Util::readDataArrayLength(hid_t groupId, const std::string& name, int* length)
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueLength");
	ier = readGroupValueLength(gId, length);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::string* value)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, value);
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::vector<char>* values)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, values);
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::vector<int>* values)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, values);
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::vector<float>* values)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, values);
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::vector<double>* values)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, values);
}

int H5Util::readDataArrayValue(hid_t groupId, const std::string& name, std::vector<std::string>* values)
{
	hid_t gId;
	int ier = openGroup(groupId, name, DATAARRAY_LABEL, &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	return readGroupValue(gId, values);
}

int H5Util::updateGroupValue(hid_t groupId, const int& value)
{
	return updateGroupValueT(groupId, value, H5T_NATIVE_INT32);
}

int H5Util::updateGroupValue(hid_t groupId, const float& value)
{
	return updateGroupValueT(groupId, value, H5T_NATIVE_FLOAT);
}

int H5Util::updateGroupValue(hid_t groupId, const double& value)
{
	return updateGroupValueT(groupId, value, H5T_NATIVE_DOUBLE);
}

int H5Util::readAttribute(hid_t groupId, const std::string& name, std::string* value)
{
	// read attribute
	hid_t attId = H5Aopen(groupId, name.c_str(), H5P_DEFAULT);
	if (attId < 0) {
		_iric_logger_error("H5Util::readAttribute", "H5Aopen", attId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser attCloser(attId);

	hid_t fileDataTypeId = H5Aget_type(attId);
	if (fileDataTypeId < 0) {
		_iric_logger_error("H5Util::readAttribute", "H5Aget_type", fileDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser fileDataTypeCloser(fileDataTypeId);

	size_t labelSize = H5Tget_size(fileDataTypeId);

	std::vector<char> buf(labelSize, 0);

	// dataTypeForMemory
	hid_t memDataTypeId = H5Tcopy(H5T_C_S1);
	if (memDataTypeId < 0) {
		_iric_logger_error("H5Util::readAttribute", "H5Tcopy", memDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser memDataTypeCloser(memDataTypeId);

	H5Tset_size(memDataTypeId, labelSize);

	H5Aread(attId, memDataTypeId, buf.data());

	*value = buf.data();

	return true;
}

int H5Util::writeAttribute(hid_t groupId, const std::string& name, const std::string& value)
{
	hsize_t strnum = 1;
	hsize_t datalen = value.length();

	hid_t dataSpaceId = H5Screate_simple(1, &strnum, nullptr);
	if (dataSpaceId < 0) {
		_iric_logger_error("H5Util::writeAttribute", "H5Screate_simple", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	hid_t fileDataTypeId = H5Tcopy(H5T_C_S1);
	if (fileDataTypeId < 0) {
		_iric_logger_error("H5Util::writeAttribute", "H5Tcopy", fileDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser fileDataTypeCloser(fileDataTypeId);

	H5Tset_size(fileDataTypeId, datalen + 1);

	hid_t memDataTypeId = H5Tcopy(H5T_C_S1);
	if (memDataTypeId < 0) {
		_iric_logger_error("H5Util::writeAttribute", "H5Tcopy", memDataTypeId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataTypeCloser memDataTypeCloser(memDataTypeId);

	H5Tset_size(memDataTypeId, datalen + 1);

	hid_t attId = H5Acreate2(groupId, name.c_str(), fileDataTypeId, dataSpaceId, H5P_DEFAULT, H5P_DEFAULT);
	if (attId < 0) {
		_iric_logger_error("H5Util::writeAttribute", "H5Acreate2", attId);
		return IRIC_H5_CALL_ERROR;
	}

	H5AttributeCloser attCloser(attId);

	herr_t status = H5Awrite(attId, memDataTypeId, value.data());

	if (status < 0) {
		_iric_logger_error("H5Util::writeAttribute", "H5Awrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int H5Util::writeAttribute(hid_t groupId, const std::string& name, const int& value)
{
	return writeAttributeT(groupId, name, value, H5T_STD_I32LE, H5T_NATIVE_INT32);
}

int H5Util::writeAttribute(hid_t groupId, const std::string& name, const float& value)
{
	return writeAttributeT(groupId, name, value, H5T_IEEE_F32LE, H5T_NATIVE_FLOAT);
}

int H5Util::writeAttribute(hid_t groupId, const std::string& name, const double& value)
{
	return writeAttributeT(groupId, name, value, H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE);
}

int H5Util::readData(hid_t groupId, const std::string& name, std::vector<int>* value)
{
	return readValueT(groupId, name, value, H5T_NATIVE_INT32);
}

int H5Util::readData(hid_t groupId, const std::string& name, std::vector<float>* value)
{
	return readValueT(groupId, name, value, H5T_NATIVE_FLOAT);
}

int H5Util::readData(hid_t groupId, const std::string& name, std::vector<double>* value)
{
	return readValueT(groupId, name, value, H5T_NATIVE_DOUBLE);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::string& value)
{
	hsize_t datalen = value.length();
	hid_t dataSpaceId = H5Screate_simple(1, &datalen, nullptr);
	if (dataSpaceId < 0) {
		_iric_logger_error("H5Util::writeData", "H5Screate_simple", dataSpaceId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DataSpaceCloser dataSpaceCloser(dataSpaceId);

	hid_t dataSetId = H5Dcreate2(groupId, name.c_str(), H5T_NATIVE_INT8, dataSpaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	if (dataSetId < 0) {
		_iric_logger_error("H5Util::writeData", "H5Dcreate2", dataSetId);
		return IRIC_H5_CALL_ERROR;
	}

	H5DatasetCloser dataSetCloser(dataSetId);

	herr_t status = H5Dwrite(dataSetId, H5T_NATIVE_INT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, value.data());
	if (status < 0) {
		_iric_logger_error("H5Util::writeData", "H5Dwrite", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int H5Util::writeData(hid_t groupId, const std::string& name, const int& value)
{
	return writeValueT(groupId, name, value, H5T_STD_I32LE, H5T_NATIVE_INT32);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const float& value)
{
	return writeValueT(groupId, name, value, H5T_IEEE_F32LE, H5T_NATIVE_FLOAT);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const double& value)
{
	return writeValueT(groupId, name, value, H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<int>& value)
{
	return writeValueT(groupId, name, value, H5T_STD_I32LE, H5T_NATIVE_INT32);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<float>& value)
{
	return writeValueT(groupId, name, value, H5T_IEEE_F32LE, H5T_NATIVE_FLOAT);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<double>& value)
{
	return writeValueT(groupId, name, value, H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<int>& value, const std::vector<hsize_t>& dims)
{
	return writeValueT(groupId, name, value, dims, H5T_STD_I32LE, H5T_NATIVE_INT32);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<float>& value, const std::vector<hsize_t>& dims)
{
	return writeValueT(groupId, name, value, dims, H5T_IEEE_F32LE, H5T_NATIVE_FLOAT);
}

int H5Util::writeData(hid_t groupId, const std::string& name, const std::vector<double>& value, const std::vector<hsize_t>& dims)
{
	return writeValueT(groupId, name, value, dims, H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE);
}

int H5Util::deleteData(hid_t groupId, const std::string& name)
{
	herr_t status = H5Ldelete(groupId, name.c_str(), H5P_DEFAULT);
	if (status < 0) {
		_iric_logger_error("H5Util::deleteData", "H5Ldelete", status);
		return IRIC_H5_CALL_ERROR;
	}

	return IRIC_NO_ERROR;
}

int H5Util::deleteDataIfExists(hid_t groupId, const std::string& name)
{
	std::set<std::string> names;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = getGroupNames(groupId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	if (names.find(name) == names.end()) {
		// the data does not exists
		return IRIC_NO_ERROR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::deleteData");
	ier = deleteData(groupId, name);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::deleteData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5Util::deleteAllChildren(hid_t groupId)
{
	H5G_info_t info;
	_IRIC_LOGGER_TRACE_CALL_START("H5Gget_info");
	herr_t status = H5Gget_info(groupId, &info);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gget_info");

	if (status < 0) {
		_iric_logger_error("H5Util::deleteAllChildren", "H5Gget_info", status);
		return IRIC_H5_CALL_ERROR;
	}

	std::vector<std::string> names;
	for (hsize_t i = 0; i < info.nlinks; ++i) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		ssize_t nameLen = H5Lget_name_by_idx(groupId, ".", H5_INDEX_NAME, H5_ITER_INC, i, nullptr, 0, H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		if (nameLen < 0) {continue;}

		std::vector<char> buffer(nameLen + 1);
		_IRIC_LOGGER_TRACE_CALL_START("H5Lget_name_by_idx");
		H5Lget_name_by_idx(groupId, ".", H5_INDEX_NAME, H5_ITER_INC, i, buffer.data(), buffer.size(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Lget_name_by_idx");

		std::string name = buffer.data();
		names.push_back(name);
	}

	for (const auto& name : names) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::deleteData");
		int ier = deleteData(groupId, name);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::deleteData", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int H5Util::copyGroup(hid_t srcGroupId, hid_t tgtGroupId, bool recursive)
{
	_IRIC_LOGGER_TRACE_CALL_START("copyAttributes");
	int ier = copyAttributes(srcGroupId, tgtGroupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyAttributes", ier);
	RETURN_IF_ERR;

	if (recursive) {return true;}

	_IRIC_LOGGER_TRACE_CALL_START("copyChildren");
	ier = copyChildren(srcGroupId, tgtGroupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("copyChildren", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

H5Util::H5Util()
{}

