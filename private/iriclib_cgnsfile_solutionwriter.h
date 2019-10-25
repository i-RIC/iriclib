#ifndef IRICLIB_CGNSFILE_SOLUTIONWRITER_H
#define IRICLIB_CGNSFILE_SOLUTIONWRITER_H

#include "../iriclib_cgnsfile.h"

#include <map>
#include <string>
#include <vector>

namespace iRICLib {

class CgnsFile::SolutionWriter
{
public:
	SolutionWriter(CgnsFile::Impl* impl);
	virtual ~SolutionWriter();

	virtual int Sol_Write_Time(double time) = 0;
	virtual int Sol_Write_Iteration(int index) = 0;
	virtual int Sol_Write_GridCoord2d(double *x, double *y) = 0;
	virtual int Sol_Write_GridCoord3d(double *x, double *y, double *z) = 0;
	virtual int Sol_Write_Integer(const char *name, int* data) = 0;
	virtual int Sol_Write_Real(const char *name, double* data) = 0;
	virtual int Sol_Write_Cell_Integer(const char *name, int* data) = 0;
	virtual int Sol_Write_Cell_Real(const char *name, double* data) = 0;
	virtual int Sol_Write_IFace_Integer(const char *name, int* data) = 0;
	virtual int Sol_Write_IFace_Real(const char *name, double* data) = 0;
	virtual int Sol_Write_JFace_Integer(const char *name, int* data) = 0;
	virtual int Sol_Write_JFace_Real(const char *name, double* data) = 0;
	virtual int Sol_Particle_Write_Pos2d(cgsize_t count, double* x, double* y) = 0;
	virtual int Sol_Particle_Write_Pos3d(cgsize_t count, double* x, double* y, double* z) = 0;
	virtual int Sol_Particle_Write_Real(const char* name, double* value) = 0;
	virtual int Sol_Particle_Write_Integer(const char* name, int* value) = 0;
	int Sol_PolyData_Write_GroupBegin(const char* name);
	virtual int Sol_PolyData_Write_GroupEnd() = 0;
	int Sol_PolyData_Write_Polygon(int num, double* x, double* y);
	int Sol_PolyData_Write_Polyline(int num, double* x, double* y);
	int Sol_PolyData_Write_Integer(const char* name, int value);
	int Sol_PolyData_Write_Real(const char* name, double value);

	virtual int Flush() = 0;

protected:
	CgnsFile::Impl* impl() const;
	int stdSolPolyDataGroupEnd(int fid, int bid, int zid, int sid);
	void clearPolyData();

	std::string m_polydataName;
	std::vector<int> m_polydataTypes;
	std::vector<int> m_polydataSizes;
	std::vector<double> m_polydataX;
	std::vector<double> m_polydataY;
	std::map<std::string, std::vector<int> > m_polydataIntValues;
	std::map<std::string, std::vector<double> > m_polydataRealValues;

private:
	CgnsFile::Impl* m_impl;
};

} // namespace iRICLib

#endif // IRICLIB_CGNSFILE_SOLUTIONWRITER_H
