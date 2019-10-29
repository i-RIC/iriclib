#include "iriclib_cgnsfile_solutionwriterdividesolutions.h"
#include "iriclib_cgnsfile_solutionwriterstandard.h"
#include "iriclib_cgnsfile_impl.h"
#include "../error_macros.h"

#include <cgnslib.h>

#include <direct.h>
#include <sys/stat.h>

#include <assert.h>
#include <string>
#include <sstream>

using namespace iRICLib;

namespace {

const static std::string GRIDCOORD_NAME = "GridCoordinatesForSolution1";
static const std::string ZINAME = "ZoneIterativeData";

bool fileExists(const char* filename)
{
	struct _stat buf;
	int result = _stat(filename, &buf);

	return (result == 0);
}

int copyBase(int fid_in, int bid_in, int fid_out, int* bid_out)
{
	char baseName[32];
	int celldim, physdim;

	int ier = cg_base_read(fid_in, bid_in, &(baseName[0]), &celldim, &physdim);
	RETURN_IF_ERR;

	return cg_base_write(fid_out, baseName, celldim, physdim, bid_out);
}

int copyZone(int fid_in, int bid_in, int zid_in, int fid_out, int bid_out, int* zid_out)
{
	char zoneName[32];
	cgsize_t zoneSize[9];
	ZoneType_t zoneType;

	int ier = cg_zone_read(fid_in, bid_in, zid_in, &(zoneName[0]), &(zoneSize[0]));
	RETURN_IF_ERR;
	ier = cg_zone_type(fid_in, bid_in, zid_in, &zoneType);
	RETURN_IF_ERR;

	return cg_zone_write(fid_out, bid_out, zoneName, zoneSize, zoneType, zid_out);
}

int linkGrid(const char* filename_src, int fid_src, int bid_src, int zid_src, int gid_src, int fid_tgt, int bid_tgt, int zid_tgt, char* linkname = nullptr)
{
	char name[32];
	int celldim, physdim;
	cgsize_t zoneSize[9];

	std::string path;

	int ier = cg_base_read(fid_src, bid_src, &(name[0]), &celldim, &physdim);
	RETURN_IF_ERR;
	path.append(name);

	ier = cg_zone_read(fid_src, bid_src, zid_src, &(name[0]), &(zoneSize[0]));
	RETURN_IF_ERR;
	path.append("/");
	path.append(name);

	cg_grid_read(fid_src, bid_src, zid_src, gid_src, &(name[0]));
	path.append("/");
	path.append(name);

	if (linkname == nullptr) {
		linkname = &(name[0]);
	}

	ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, NULL);
	RETURN_IF_ERR;

	return cg_link_write(linkname, filename_src, path.c_str());
}

int copySections(int fid_src, int bid_src, int zid_src, int fid_tgt, int bid_tgt, int zid_tgt)
{
	int ier;
	int numSecs;

	ier = cg_nsections(fid_src, bid_src, zid_src, &numSecs);
	RETURN_IF_ERR;

	for (int S = 1; S <= numSecs; ++S) {
		ElementType_t eType;
		cgsize_t startIndex, endIndex, numCells;
		int nBndry, parentFlag;
		char secname[32];
		int newS;

		ier = cg_section_read(fid_src, bid_src, zid_src, S, secname, &eType, &startIndex, &endIndex, &nBndry, &parentFlag);
		RETURN_IF_ERR;
		ier = cg_ElementDataSize(fid_src, bid_src, zid_src, S, &numCells);
		RETURN_IF_ERR;

		std::vector<cgsize_t> elems(3 * numCells, 0);
		ier = cg_elements_read(fid_src, bid_src, zid_src, S, elems.data(), NULL);
		RETURN_IF_ERR;

		ier = cg_section_write(fid_tgt, bid_tgt, zid_tgt, secname, eType, startIndex, endIndex, nBndry, elems.data(), &newS);
		RETURN_IF_ERR;
	}
	return 0;
}

int copyGrid(int fid_src, int bid_src, int zid_src, int gid_src, int fid_tgt, int bid_tgt, int zid_tgt, const char* name)
{
	char gridname[32];
	int ier;
	int gid_tgt;

	ier = cg_grid_write(fid_tgt, bid_tgt, zid_tgt, name, &gid_tgt);

	ier = cg_grid_read(fid_src, bid_src, zid_src, gid_src, gridname);
	ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, gridname, 0, "end");

	int narray;
	ier = cg_narrays(&narray);

	// copying grid coordinates. this will be enough for structured grid.
	for (int aId = 1; aId <= narray; ++aId) {
		char arrayname[32];
		DataType_t datatype;
		int dim;
		cgsize_t dimvec[3];
		int datasize;

		ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, gridname, 0, "end");
		ier = cg_array_info(aId, arrayname, &datatype, &dim, dimvec);

		RETURN_IF_ERR;
		datasize = 1;
		for (int i = 0; i < dim; ++i) {
			datasize *= dimvec[i];
		}

		std::vector<double> coords;
		coords.assign(datasize, 0);
		ier = cg_array_read(aId, coords.data());
		RETURN_IF_ERR;
		ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, name, 0, "end");
		ier = cg_array_write(arrayname, datatype, dim, dimvec, coords.data());
		RETURN_IF_ERR;
	}

	ier = copySections(fid_src, bid_src, zid_src, fid_tgt, bid_tgt, zid_tgt);
	RETURN_IF_ERR;

	return 0;
}

int linkSolution(const char* filename_src, int fid_src, int bid_src, int zid_src, int sid_src, int fid_tgt, int bid_tgt, int zid_tgt, char* linkname = nullptr)
{
	char name[32];
	int celldim, physdim;
	cgsize_t zoneSize[9];
	GridLocation_t location;

	std::string path;

	int ier = cg_base_read(fid_src, bid_src, &(name[0]), &celldim, &physdim);
	RETURN_IF_ERR;
	path.append(name);

	ier = cg_zone_read(fid_src, bid_src, zid_src, &(name[0]), &(zoneSize[0]));
	RETURN_IF_ERR;
	path.append("/");
	path.append(name);

	ier = cg_sol_info(fid_src, bid_src, zid_src, sid_src, &(name[0]), &location);
	RETURN_IF_ERR;
	path.append("/");
	path.append(name);

	if (linkname == nullptr) {
		linkname = &(name[0]);
	}

	ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, NULL);
	RETURN_IF_ERR;

	return cg_link_write(linkname, filename_src, path.c_str());
}

int copyCoords(int fid_src, int bid_src, int zid_src, int cid_src, int fid_tgt, int bid_tgt, int zid_tgt, const char* name)
{
	int ier, G;

	ier = cg_grid_write(fid_tgt, bid_tgt, zid_tgt, name, &G);

	// copy all arrays inside the coords
	ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, "GridCoordinates_t", cid_src, "end");
	RETURN_IF_ERR;

	int narrays;
	ier = cg_narrays(&narrays);
	RETURN_IF_ERR;

	for (int aId = 1; aId <= narrays; ++aId) {
		char arrayname[32];
		DataType_t datatype;
		int dim;
		cgsize_t dimvec[3];
		int datasize;

		ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, "GridCoordinates_t", cid_src, "end");
		ier = cg_array_info(aId, &(arrayname[0]), &datatype, &dim, dimvec);
		RETURN_IF_ERR;
		datasize = 1;
		for (int i = 0; i < dim; ++i) {
			datasize *= dimvec[i];
		}
		std::vector<double> vals;
		vals.assign(datasize, 0);
		ier = cg_array_read(aId, vals.data());
		RETURN_IF_ERR;

		ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, "GridCoordinates_t", G, "end");
		RETURN_IF_ERR;
		ier = cg_array_write(arrayname, datatype, dim, dimvec, vals.data());
		RETURN_IF_ERR;
	}
	return 0;
}

int copySolution(int fid_src, int bid_src, int zid_src, int sid_src, int fid_tgt, int bid_tgt, int zid_tgt, const char* name)
{
	char solname[32];
	GridLocation_t loc;
	int ier;


	// read location info
	ier = cg_sol_info(fid_src, bid_src, zid_src, sid_src, &(solname[0]), &loc);
	RETURN_IF_ERR;

	// write location
	int sid_tgt;
	ier = cg_sol_write(fid_tgt, bid_tgt, zid_tgt, name, loc, &sid_tgt);
	RETURN_IF_ERR;

	// copy all arrays inside the solution node
	ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, "FlowSolution_t", sid_src, "end");
	RETURN_IF_ERR;

	int narrays;
	ier = cg_narrays(&narrays);
	RETURN_IF_ERR;

	for (int aId = 1; aId <= narrays; ++aId) {
		char arrayname[32];
		DataType_t datatype;
		int dim;
		cgsize_t dimvec[3];
		int datasize;

		ier = cg_goto(fid_src, bid_src, "Zone_t", zid_src, "FlowSolution_t", sid_src, "end");
		ier = cg_array_info(aId, &(arrayname[0]), &datatype, &dim, dimvec);
		RETURN_IF_ERR;
		datasize = 1;
		for (int i = 0; i < dim; ++i) {
			datasize *= dimvec[i];
		}

		if (datatype == Integer) {
			std::vector<int> vals;
			vals.assign(datasize, 0);
			ier = cg_array_read(aId, vals.data());
			RETURN_IF_ERR;
			ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, "FlowSolution_t", sid_tgt, "end");
			RETURN_IF_ERR;
			ier = cg_array_write(arrayname, datatype, dim, dimvec, vals.data());
			RETURN_IF_ERR;
		} else if (datatype == RealDouble) {
			std::vector<double> vals;
			vals.assign(datasize, 0);
			ier = cg_array_read(aId, vals.data());
			RETURN_IF_ERR;
			ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, "FlowSolution_t", sid_tgt, "end");
			RETURN_IF_ERR;
			ier = cg_array_write(arrayname, datatype, dim, dimvec, vals.data());
			RETURN_IF_ERR;
		}
	}
	return 0;
}

std::string solutionFileName(int solId)
{
	std::ostringstream oss;

	oss << "result/Solution" << solId << ".cgn";
	return oss.str();
}

void countSolutionFiles(int* count)
{
	*count = 0;

	while (true) {
		int solId = *count + 1;

		std::string solFile = solutionFileName(solId);
		bool exist = fileExists(solFile.c_str());
		if (exist) {
			*count += 1;
		} else {
			break;
		}
	}
}

} // namespace

CgnsFile::SolutionWriterDivideSolutions::SolutionWriterDivideSolutions(CgnsFile::Impl* impl) :
	CgnsFile::SolutionWriter(impl),
	m_fileId {0},
	m_baseId {0},
	m_zoneId {0}
{
	_mkdir("result");
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Time(double time)
{
	int ier = closeFileIfOpen();
	RETURN_IF_ERR;

	Impl* i = impl();
	// now time is not written to original CGNS file
	// ier = CgnsFile::SolutionWriterStandard::stdSolWriteTime(time, i);
	// RETURN_IF_ERR;

	m_fileName = solutionFileName(i->m_solId);

	ier = setupSolutionFile(m_fileName, i, &m_fileId, &m_baseId, &m_zoneId);
	RETURN_IF_ERR;

	ier = cg_biter_write(m_fileId, m_baseId, CgnsFile::Impl::BINAME.c_str(), 1);
	RETURN_IF_ERR;

	ier = cg_goto(m_fileId, m_baseId, "BaseIterativeData_t", 1, NULL);
	RETURN_IF_ERR;

	cgsize_t dimVec = 1;
	ier = cg_array_write("TimeValues", RealDouble, 1, &dimVec, &time);
	RETURN_IF_ERR;

	ier = cg_ziter_write(m_fileId, m_baseId, m_zoneId, ZINAME.c_str());
	RETURN_IF_ERR;

	std::vector<std::string> sols;
	std::vector<std::string> cellsols;
	std::vector<std::string> ifacesols;
	std::vector<std::string> jfacesols;
	ier = Impl::addSolutionNode(m_fileId, m_baseId, m_zoneId, 1, &sols, &cellsols, &ifacesols, &jfacesols);
	RETURN_IF_ERR;

	// Vertex

	char solname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getSolName(i->m_solId, solname);

	// CellCenter

	char cellsolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getCellSolName(i->m_solId, cellsolname);

	i->m_cellSolPointers.push_back(cellsolname);
	ier = CgnsFile::Impl::writeFlowCellSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_cellSolPointers);
	RETURN_IF_ERR;

	// IFaceCenter

	char ifacesolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getIFaceSolName(i->m_solId, ifacesolname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 3, i->m_fileId, i->m_baseId, i->m_zoneId, ifacesolname);
	RETURN_IF_ERR;

	i->m_ifaceSolPointers.push_back(ifacesolname);
	ier = CgnsFile::Impl::writeFlowIFaceSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_ifaceSolPointers);
	RETURN_IF_ERR;

	// JFaceCenter

	char jfacesolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getJFaceSolName(i->m_solId, jfacesolname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 4, i->m_fileId, i->m_baseId, i->m_zoneId, jfacesolname);
	RETURN_IF_ERR;

	i->m_jfaceSolPointers.push_back(jfacesolname);
	ier = CgnsFile::Impl::writeFlowJFaceSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_jfaceSolPointers);
	RETURN_IF_ERR;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Iteration(int index)
{
	int ier = closeFileIfOpen();
	RETURN_IF_ERR;

	Impl* i = impl();
	// now iteration is not written to original CGNS file
	// ier = CgnsFile::SolutionWriterStandard::stdSolWriteIteration(index, i);
	// RETURN_IF_ERR;

	m_fileName = solutionFileName(i->m_solId);

	ier = setupSolutionFile(m_fileName, i, &m_fileId, &m_baseId, &m_zoneId);
	RETURN_IF_ERR;

	ier = cg_biter_write(m_fileId, m_baseId, CgnsFile::Impl::BINAME.c_str(), 1);
	cg_goto(m_fileId, m_baseId, "BaseIterativeData_t", 1, NULL);
	cgsize_t dimVec = 1;
	ier = cg_array_write("IterationValues", Integer, 1, &dimVec, &index);
	RETURN_IF_ERR;

	ier = cg_ziter_write(m_fileId, m_baseId, m_zoneId, ZINAME.c_str());
	RETURN_IF_ERR;

	std::vector<std::string> sols;
	std::vector<std::string> cellsols;
	std::vector<std::string> ifacesols;
	std::vector<std::string> jfacesols;
	ier = Impl::addSolutionNode(m_fileId, m_baseId, m_zoneId, 1, &sols, &cellsols, &ifacesols, &jfacesols);
	RETURN_IF_ERR;

	// Vertex

	char solname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getSolName(i->m_solId, solname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 1, i->m_fileId, i->m_baseId, i->m_zoneId, solname);
	RETURN_IF_ERR;

	i->m_solPointers.push_back(solname);
	ier = CgnsFile::Impl::writeFlowSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_solPointers);
	RETURN_IF_ERR;

	// CellCenter

	char cellsolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getCellSolName(i->m_solId, cellsolname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 2, i->m_fileId, i->m_baseId, i->m_zoneId, cellsolname);
	RETURN_IF_ERR;

	i->m_cellSolPointers.push_back(cellsolname);
	ier = CgnsFile::Impl::writeFlowCellSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_cellSolPointers);
	RETURN_IF_ERR;

	// IFaceCenter

	char ifacesolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getIFaceSolName(i->m_solId, ifacesolname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 3, i->m_fileId, i->m_baseId, i->m_zoneId, ifacesolname);
	RETURN_IF_ERR;

	i->m_ifaceSolPointers.push_back(ifacesolname);
	ier = CgnsFile::Impl::writeFlowIFaceSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_ifaceSolPointers);
	RETURN_IF_ERR;


	// JFaceCenter

	char jfacesolname[CgnsFile::Impl::NAME_MAXLENGTH];
	CgnsFile::Impl::getJFaceSolName(i->m_solId, jfacesolname);

	ier = linkSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 4, i->m_fileId, i->m_baseId, i->m_zoneId, jfacesolname);
	RETURN_IF_ERR;

	i->m_jfaceSolPointers.push_back(jfacesolname);
	ier = CgnsFile::Impl::writeFlowJFaceSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_jfaceSolPointers);
	RETURN_IF_ERR;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_GridCoord2d(double *x, double *y)
{
	std::vector<std::string> coords;
	int ier = Impl::addSolutionGridCoordNode(m_fileId, m_baseId, m_zoneId, 1, &coords);
	RETURN_IF_ERR;

	Impl* i = impl();
	ier = CgnsFile::SolutionWriterStandard::stdSolWriteGridCoord2d(x, y, m_fileId, m_baseId, m_zoneId, 2, i);
	RETURN_IF_ERR;
	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_GridCoord3d(double *x, double *y, double *z)
{
	std::vector<std::string> coords;
	int ier = Impl::addSolutionGridCoordNode(m_fileId, m_baseId, m_zoneId, 1, &coords);
	RETURN_IF_ERR;

	Impl* i = impl();
	ier = CgnsFile::SolutionWriterStandard::stdSolWriteGridCoord3d(x, y, z, m_fileId, m_baseId, m_zoneId, 2, i);
	RETURN_IF_ERR;
	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Integer(const char *name, int* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::VERTEX_SOLUTION_ID, Integer, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Cell_Integer(const char *name, int* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::CELL_SOLUTION_ID, Integer, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_IFace_Integer(const char *name, int* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::IFACE_2D_SOLUTION_ID, Integer, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_JFace_Integer(const char *name, int* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::JFACE_2D_SOLUTION_ID, Integer, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Real(const char *name, double* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::VERTEX_SOLUTION_ID, RealDouble, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_Cell_Real(const char *name, double* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::CELL_SOLUTION_ID, RealDouble, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_IFace_Real(const char *name, double* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::IFACE_2D_SOLUTION_ID, RealDouble, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_JFace_Real(const char *name, double* data)
{
	int F;
	return cg_field_write(m_fileId, m_baseId, m_zoneId, CgnsFile::Impl::JFACE_2D_SOLUTION_ID, RealDouble, name, data, &F);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Particle_Write_Pos2d(cgsize_t count, double* x, double* y)
{
	SolutionWriterStandard::stdSolParticleWritePos2d(count, x, y, m_fileId, m_baseId, m_zoneId, 1);
	Impl* i = impl();
	char linkname[Impl::NAME_MAXLENGTH];
	Impl::getParticleSolName(i->m_solId, linkname);
	return linkParticleSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 1, i->m_fileId, i->m_baseId, i->m_zoneId, linkname);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Particle_Write_Pos3d(cgsize_t count, double* x, double* y, double* z)
{
	SolutionWriterStandard::stdSolParticleWritePos3d(count, x, y, z, m_fileId, m_baseId, m_zoneId, 1);
	Impl* i = impl();
	char linkname[Impl::NAME_MAXLENGTH];
	Impl::getParticleSolName(i->m_solId, linkname);
	return linkParticleSolution(m_fileName.c_str(), m_fileId, m_baseId, m_zoneId, 1, i->m_fileId, i->m_baseId, i->m_zoneId, linkname);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Particle_Write_Real(const char* name, double* value)
{
	return SolutionWriterStandard::stdSolParticleWriteReal(name, value, m_fileId, m_baseId, m_zoneId, 1);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Particle_Write_Integer(const char* name, int* value)
{
	return SolutionWriterStandard::stdSolParticleWriteInteger(name, value, m_fileId, m_baseId, m_zoneId, 1);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_PolyData_Write_GroupEnd()
{
	return stdSolPolyDataGroupEnd(m_fileId, m_baseId, m_zoneId, 1);
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_BaseIterative_Integer(const char *name, int value)
{
	int ier;

	ier = cg_goto(m_fileId, m_baseId, "BaseIterativeData_t", 1, NULL);
	RETURN_IF_ERR;

	cgsize_t dimVec = 1;
	ier = cg_array_write(name, Integer, 1, &dimVec, &value);
	RETURN_IF_ERR;

	// ier = SolutionWriterStandard::stdSolWriteBaseIterativeInteger(name, value, impl());
	// RETURN_IF_ERR;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Sol_Write_BaseIterative_Real(const char *name, double value)
{
	int ier;

	ier = cg_goto(m_fileId, m_baseId, "BaseIterativeData_t", 1, NULL);
	RETURN_IF_ERR;

	cgsize_t dimVec = 1;
	ier = cg_array_write(name, RealDouble, 1, &dimVec, &value);
	RETURN_IF_ERR;

	// ier = SolutionWriterStandard::stdSolWriteBaseIterativeReal(name, value, impl());
	// RETURN_IF_ERR;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::Flush()
{
	return closeFileIfOpen();
}

int CgnsFile::SolutionWriterDivideSolutions::LinkSolutions(int* progress, int* invaliddata_id)
{
	*invaliddata_id = 0;

	Impl* i = impl();
	std::string origName = i->m_fileName;

	int solCount;
	countSolutionFiles(&solCount);

	*progress = 0;
	int ier;

	ier = cg_biter_write(i->m_fileId, i->m_baseId, "BaseIterativeData_t", solCount);

	for (int solId = 1; solId <= solCount; ++solId) {
		int fn;

		std::string cgnsName = solutionFileName(solId);

		ier = cg_open(cgnsName.c_str(), CG_MODE_READ, &fn);
		if (ier != 0) {
			*invaliddata_id = solId;
			break;
		}

		CgnsFile tmpf;
		tmpf.setFileId(fn);
		tmpf.InitRead();

		// Copy base iterative data values
		ier = cg_goto(fn, tmpf.baseId(), "BaseIterativeData_t", 1, NULL);
		RETURN_IF_ERR;

		int narr;
		ier = cg_narrays(&narr);
		for (int aId = 1; aId <= narr; ++aId) {
			char arrayname[CgnsFile::Impl::NAME_MAXLENGTH];
			DataType_t datatype;
			int dim;
			cgsize_t dimvec;

			ier = cg_goto(fn, tmpf.baseId(), "BaseIterativeData_t", 1, NULL);
			RETURN_IF_ERR;
			ier = cg_array_info(aId, arrayname, &datatype, &dim, &dimvec);
			RETURN_IF_ERR;
			if (datatype == RealDouble) {
				double v;
				cg_array_read(aId, &v);
				CgnsFile::SolutionWriterStandard::stdSolWriteBaseIterativeReal(arrayname, v, impl());
			} else if (datatype == Integer) {
				int v;
				cg_array_read(aId, &v);
				CgnsFile::SolutionWriterStandard::stdSolWriteBaseIterativeInteger(arrayname, v, impl());
			}
		}
		// Link solutions

		// @todo link grid

		char solname[CgnsFile::Impl::NAME_MAXLENGTH];

		// solution at nodes
		CgnsFile::Impl::getSolName(solId, solname);
		ier = linkSolution(cgnsName.c_str(), fn, tmpf.baseId(), tmpf.zoneId(), 1, i->m_fileId, i->m_baseId, i->m_zoneId, solname);
		RETURN_IF_ERR;
		i->m_solPointers.push_back(solname);

		// solution at cells
		CgnsFile::Impl::getCellSolName(solId, solname);
		ier = linkSolution(cgnsName.c_str(), fn, tmpf.baseId(), tmpf.zoneId(), 2, i->m_fileId, i->m_baseId, i->m_zoneId, solname);
		i->m_cellSolPointers.push_back(solname);

		ier = cg_close(fn);
		*progress = 100 * solId / solCount;
	}

	// @todo gridPointers

	ier = CgnsFile::Impl::writeFlowSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_solPointers);
	RETURN_IF_ERR;
	ier = CgnsFile::Impl::writeFlowCellSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_cellSolPointers);
	RETURN_IF_ERR;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::CombineSolutions(int* progress, int* invaliddata_id, int maxid)
{
	*invaliddata_id = 0;

	Impl* i = impl();
	std::string origName = i->m_fileName;

	int solCount;

	if (maxid == -1) {
		countSolutionFiles(&solCount);
	} else {
		solCount = maxid;
	}

	*progress = 0;
	int ier;

	for (int solId = 1; solId <= solCount; ++solId) {
		int fn;

		std::string cgnsName = solutionFileName(solId);

		ier = cg_open(cgnsName.c_str(), CG_MODE_READ, &fn);
		if (ier != 0) {
			*invaliddata_id = solId;
			solCount = solId - 1;
			break;
		}

		CgnsFile tmpf;
		tmpf.setFileId(fn);
		tmpf.InitRead();

		// Copy base iterative data values
		ier = cg_goto(fn, tmpf.baseId(), "BaseIterativeData_t", 1, NULL);
		RETURN_IF_ERR;

		int narr;
		ier = cg_narrays(&narr);
		for (int aId = 1; aId <= narr; ++aId) {
			char arrayname[CgnsFile::Impl::NAME_MAXLENGTH];
			DataType_t datatype;
			int dim;
			cgsize_t dimvec;

			ier = cg_goto(fn, tmpf.baseId(), "BaseIterativeData_t", 1, NULL);
			RETURN_IF_ERR;
			ier = cg_array_info(aId, arrayname, &datatype, &dim, &dimvec);
			RETURN_IF_ERR;
			if (datatype == RealDouble) {
				double v;
				cg_array_read(aId, &v);
				CgnsFile::SolutionWriterStandard::stdSolAddBaseIterativeReal(arrayname, v, impl());
			} else if (datatype == Integer) {
				int v;
				cg_array_read(aId, &v);
				CgnsFile::SolutionWriterStandard::stdSolAddBaseIterativeInteger(arrayname, v, impl());
			}
		}

		int ncoords;
		ier = cg_ncoords(fn, tmpf.baseId(), tmpf.zoneId(), &ncoords);
		if (ncoords > 1) {
			// Copy grid
			char coordsname[CgnsFile::Impl::NAME_MAXLENGTH];
			CgnsFile::Impl::getSolGridCoordName(solId, coordsname);
			ier = copyCoords(fn, tmpf.baseId(), tmpf.zoneId(), 2, i->m_fileId, i->m_baseId, i->m_zoneId, coordsname);
			RETURN_IF_ERR;
			i->m_solGridCoordPointers.push_back(coordsname);
		}

		// Copy solutions
		char solname[CgnsFile::Impl::NAME_MAXLENGTH];

		// solution at nodes
		CgnsFile::Impl::getSolName(solId, solname);
		ier = copySolution(fn, tmpf.baseId(), tmpf.zoneId(), 1, i->m_fileId, i->m_baseId, i->m_zoneId, solname);
		RETURN_IF_ERR;
		i->m_solPointers.push_back(solname);

		// solution at cells
		CgnsFile::Impl::getCellSolName(solId, solname);
		ier = copySolution(fn, tmpf.baseId(), tmpf.zoneId(), 2, i->m_fileId, i->m_baseId, i->m_zoneId, solname);
		i->m_cellSolPointers.push_back(solname);

		// @todo copy particle solutions if exists

		ier = cg_close(fn);
		*progress = 100 * solId / solCount;
	}

	if (i->m_solGridCoordPointers.size() > 0) {
		ier = CgnsFile::Impl::writeGridCoordinatesPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_solGridCoordPointers);
	}
	ier = CgnsFile::Impl::writeFlowSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_solPointers);
	RETURN_IF_ERR;

	ier = CgnsFile::Impl::writeFlowCellSolutionPointers(i->m_fileId, i->m_baseId, i->m_zoneId, i->m_cellSolPointers);
	RETURN_IF_ERR;

	if (solCount > 0) {
		ier = CgnsFile::SolutionWriterStandard::stdSolWriteBaseIterativeData(solCount, impl());
		RETURN_IF_ERR;
	}

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::closeFileIfOpen()
{
	if (m_fileId == 0) {return 0;}

	int ier = cg_close(m_fileId);
	RETURN_IF_ERR;
	m_fileId = 0;

	return 0;
}

int CgnsFile::SolutionWriterDivideSolutions::setupSolutionFile(const std::string& solFileName, CgnsFile::Impl* i, int* fileId, int* baseId, int* zoneId)
{
	int fileType;
	int ier = cg_get_file_type(i->m_fileId, &fileType);
	RETURN_IF_ERR;
	cg_set_file_type(fileType);

	ier = cg_open(solFileName.c_str(), CG_MODE_WRITE, fileId);
	RETURN_IF_ERR;

	ier = copyBase(i->m_fileId, i->m_baseId, *fileId, baseId);
	RETURN_IF_ERR;

	ier = copyZone(i->m_fileId, i->m_baseId, i->m_zoneId, *fileId, *baseId, zoneId);
	RETURN_IF_ERR;

//	std::string srcFileName = "../";
//	srcFileName.append(i->m_fileName);

//	ier = linkGrid(srcFileName.c_str(), i->m_fileId, i->m_baseId, i->m_zoneId, 1, *fileId, *baseId, *zoneId, nullptr);
	ier = copyGrid(i->m_fileId, i->m_baseId, i->m_zoneId, 1, *fileId, *baseId, *zoneId, "GridCoordinates");

	RETURN_IF_ERR;

	cg_close(*fileId);

	cg_set_file_type(CG_FILE_NONE);

	return cg_open(solFileName.c_str(), CG_MODE_MODIFY, fileId);
}

int CgnsFile::SolutionWriterDivideSolutions::linkParticleSolution(const char* filename_src, int fid_src, int bid_src, int zid_src, int sid_src, int fid_tgt, int bid_tgt, int zid_tgt, const char* linkname)
{
	char name[32];
	int celldim, physdim;
	cgsize_t zoneSize[9];

	std::string path;

	int ier = cg_base_read(fid_src, bid_src, &(name[0]), &celldim, &physdim);
	RETURN_IF_ERR;
	path.append(name);

	ier = cg_zone_read(fid_src, bid_src, zid_src, &(name[0]), &(zoneSize[0]));
	RETURN_IF_ERR;
	path.append("/");
	path.append(name);

	CgnsFile::Impl::getParticleSolName(sid_src, name);
	path.append("/");
	path.append(name);

	if (linkname == nullptr) {
		linkname = &(name[0]);
	}

	ier = cg_goto(fid_tgt, bid_tgt, "Zone_t", zid_tgt, NULL);
	RETURN_IF_ERR;

	return cg_link_write(linkname, filename_src, path.c_str());
}
