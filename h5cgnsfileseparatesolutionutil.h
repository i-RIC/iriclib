#ifndef H5CGNSFILESEPARATESOLUTIONUTIL_H
#define H5CGNSFILESEPARATESOLUTIONUTIL_H

#include <string>

namespace iRICLib {

class H5CgnsFileSeparateSolutionUtil
{
public:
	enum class Status {
		Valid,
		Broken,
		Inconsistent,
	};

	static int createResultFolderIfNotExists(const std::string& fileName);
	static int createBackupFile(const std::string& fileName);
	static int checkFileStatus(const std::string& fileName, Status* status);
	static int rebuildBaseIterativeData(const std::string& fileName);
	static int buildFromSeparateResultFiles(const std::string& fileName);

	static int clearResultFolder(const std::string& fileName);

	static std::string fileNameForSolution(const std::string& fileName, int solId);

private:
	static int getMaxSeparateResultSolutionId(const std::string& fileName, int* solutionId);
	static std::string resultFolder(const std::string& fileName);

	H5CgnsFileSeparateSolutionUtil();
};

} // namespace iRICLib

#endif // H5CGNSFILESEPARATESOLUTIONUTIL_H
