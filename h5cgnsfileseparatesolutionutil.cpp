#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"
#include "h5cgnsfileseparatesolutionutil.h"
#include "iriclib_errorcodes.h"
#include "internal/iric_logger.h"

#include <Poco/File.h>
#include <Poco/Path.h>

#include <sstream>
#include <stdexcept>

using namespace iRICLib;

#define BACKUP_FILENAME "Case1_input.cgn"

int H5CgnsFileSeparateSolutionUtil::createResultFolderIfNotExists(const std::string& fileName)
{
	Poco::File f(resultFolder(fileName));
	try {
		if (! f.exists()) {
			f.createDirectory();
		}
		return IRIC_NO_ERROR;
	} catch (...) {
		return IRIC_FOLDER_CREATE_ERROR;
	}
}

int H5CgnsFileSeparateSolutionUtil::createBackupFile(const std::string& fileName)
{
	Poco::Path path(fileName);
	auto backup_fullpath = path.parent().append(Poco::Path(BACKUP_FILENAME)).toString();

	Poco::File file(fileName);
	try {
		file.copyTo(backup_fullpath);
		return IRIC_NO_ERROR;
	} catch (...) {
		return IRIC_FILE_COPY_FAIL;
	}
}

int H5CgnsFileSeparateSolutionUtil::checkFileStatus(const std::string& fileName, Status* status)
{
	H5CgnsFile* file = nullptr;
	try {
		file = new H5CgnsFile(fileName, H5CgnsFile::Mode::OpenReadOnly);
	} catch (...) {
		*status = Status::Broken;
		return IRIC_NO_ERROR;
	}

	int maxSolutionId;
	getMaxSeparateResultSolutionId(fileName, &maxSolutionId);

	std::vector<double> timeVals;
	file->ccBase()->biterData()->readTime(&timeVals);
	if (maxSolutionId != static_cast<int>(timeVals.size())) {
		*status = Status::Inconsistent;
		return IRIC_NO_ERROR;
	}

	*status = Status::Valid;
	return IRIC_NO_ERROR;
}

int H5CgnsFileSeparateSolutionUtil::rebuildBaseIterativeData(const std::string& fileName)
{
	H5CgnsFile file(fileName.c_str(), H5CgnsFile::Mode::OpenModify);

	for (int i = 0; i < file.baseNum(); ++i) {
		auto base = file.baseById(i + 1);
		int ier = base->biterData()->clearData();
		RETURN_IF_ERR;
	}

	int maxSolutionId;
	getMaxSeparateResultSolutionId(fileName, &maxSolutionId);

	int id = 1;
	while (id <= maxSolutionId) {
		auto fName = fileNameForSolution(fileName, id);
		H5CgnsFile resultFile(fName.c_str(), H5CgnsFile::Mode::OpenReadOnly);

		for (int i = 0; i < resultFile.baseNum(); ++i) {
			auto fromBIter = resultFile.baseById(i + 1)->biterData();
			if (fromBIter == nullptr) {continue;}

			auto toBIter = file.baseById(i + 1)->biterData();

			std::vector<std::string> names;
			int ier = fromBIter->getResultNames(&names);
			RETURN_IF_ERR;

			for (const auto& name : names) {
				H5Util::DataArrayValueType type;
				ier = fromBIter->readValueType(name, &type);
				if (type == H5Util::DataArrayValueType::Int) {
					std::vector<int> vals;
					fromBIter->readValues(name, &vals);
					for (auto v : vals) {
						toBIter->writeData(name, v);
					}
				} else if (type == H5Util::DataArrayValueType::RealDouble) {
					std::vector<double> vals;
					fromBIter->readValues(name, &vals);
					for (auto v : vals) {
						toBIter->writeData(name, v);
					}
				}
			}
		}

		++ id;
	}
	return IRIC_NO_ERROR;
}

int H5CgnsFileSeparateSolutionUtil::buildFromSeparateResultFiles(const std::string& fileName)
{
	// @todo implement this
	throw std::runtime_error("Not implemented");
}

int H5CgnsFileSeparateSolutionUtil::clearResultFolder(const std::string& fileName)
{
	auto folder = resultFolder(fileName);
	Poco::File f(folder);
	try {
		f.remove(true);
		f.createDirectory();
		return IRIC_NO_ERROR;;
	} catch (...) {
		std::ostringstream ss;
		ss << "In H5CgnsFileSeparateSolutionUtil::clearResultFolder(), removing and creating folder \"result\" failed";
		_iric_logger_error(ss.str());

		return IRIC_FOLDER_CLEAR_ERROR ;
	}
}

std::string H5CgnsFileSeparateSolutionUtil::fileNameForSolution(const std::string& fileName, int solId)
{
	std::ostringstream ss;
	ss << "Solution" << solId << ".cgn";
	auto solFileName = ss.str();

	return Poco::Path(resultFolder(fileName)).append(solFileName).toString();
}

int H5CgnsFileSeparateSolutionUtil::getMaxSeparateResultSolutionId(const std::string& fileName, int* solutionId)
{
	int prevMaxExistId = 0;
	int maxExistId = 1;

	while (true) {
		auto fName = fileNameForSolution(fileName, maxExistId);
		Poco::File f(fName);
		if (f.exists()) {
			prevMaxExistId = maxExistId;
			maxExistId *= 2;
		} else {
			maxExistId = prevMaxExistId;
			break;
		}
	}
	if (maxExistId == 0) {
		*solutionId = 0;
		return IRIC_NO_ERROR;
	}

	int left = maxExistId;
	int right = maxExistId * 2;
	while (true) {
		if (right - left == 1) {
			*solutionId = left;
			return IRIC_NO_ERROR;
		}
		int mid = (left + right) / 2;
		auto fName = fileNameForSolution(fileName, mid);
		Poco::File f(fName);
		if (f.exists()) {
			left = mid;
		} else {
			right = mid;
		}
	}
}

std::string H5CgnsFileSeparateSolutionUtil::resultFolder(const std::string& fileName)
{
	Poco::Path path(fileName);
	return path.parent().append(Poco::Path("result")).toString();
}

H5CgnsFileSeparateSolutionUtil::H5CgnsFileSeparateSolutionUtil()
{}
