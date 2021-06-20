#include "error_macros.h"
#include "h5cgnsfile.h"
#include "h5cgnsfilesolutionwriter.h"
#include "iriclib.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"

#include <Poco/Environment.h>
#include <Poco/File.h>

#include <sstream>

using namespace iRICLib;

namespace {

const std::string IRIC_SEPARATE_OUTPUT = "IRIC_SEPARATE_OUTPUT";

H5CgnsFileSolutionWriter::Mode writerMode = H5CgnsFileSolutionWriter::Mode::Standard;

H5CgnsFileSolutionWriter::Mode setupWriterMode()
{
	auto wm = writerMode;

	if (wm == H5CgnsFileSolutionWriter::Mode::Separate) {return wm;}

	if (! Poco::Environment::has(IRIC_SEPARATE_OUTPUT)) {return wm;}

	if (Poco::Environment::get(IRIC_SEPARATE_OUTPUT) == "1") {
		return H5CgnsFileSolutionWriter::Mode::Separate;
	}
	return wm;
}

int _checkFileIsOpen(int fid)
{
	H5CgnsFile* file;

	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	if (file == nullptr) {
		return IRIC_INVALID_FILEID;
	}

	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Open(const char* filename, int mode, int* fid)
{
	_iric_logger_init();

	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsFile::Mode m = H5CgnsFile::Mode::OpenReadOnly;

	if (mode == IRIC_MODE_WRITE) {
		m = H5CgnsFile::Mode::Create;
	} else if (mode == IRIC_MODE_MODIFY) {
		m = H5CgnsFile::Mode::OpenModify;
	}

	auto myWriterMode = setupWriterMode();

	try {
		auto f = new H5CgnsFile(filename, m);
		f->setWriterMode(myWriterMode);

		int ier = _iric_h5cgnsfiles_register(f, fid);
		RETURN_IF_ERR;

		_IRIC_LOGGER_TRACE_LEAVE();

		return IRIC_NO_ERROR;
	}  catch (...) {
		std::ostringstream ss;
		ss << "In cg_iRIC_Open(), opening " << filename << " failed";
		_iric_logger_error(ss.str());

		_IRIC_LOGGER_TRACE_LEAVE();
		return IRIC_H5_OPEN_FAIL;
	}
}

int cg_iRIC_Close(int fid)
{
	return _iric_h5cgnsfiles_unregister(fid);
}

int iRIC_InitOption(int option)
{
	if (option == IRIC_OPTION_CANCEL) {
		try {
			Poco::File f(".cancel_ok");
			f.createFile();
			return IRIC_NO_ERROR;
		} catch (...) {
			std::ostringstream ss;
			ss << "Creating .cancel_ok failed";
			_iric_logger_error(ss.str());
		}
	} else if (option == IRIC_OPTION_DIVIDESOLUTIONS) {
		writerMode = H5CgnsFileSolutionWriter::Mode::Separate;
		return IRIC_NO_ERROR;
	} else if (option == IRIC_OPTION_STDSOLUTION) {
		writerMode = H5CgnsFileSolutionWriter::Mode::Standard;
		return IRIC_NO_ERROR;
	}

	return IRIC_NO_ERROR;
}

int cg_iRIC_Flush(int fid)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	return file->flush();
}
