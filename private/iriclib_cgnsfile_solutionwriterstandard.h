#ifndef IRICLIB_CGNSFILE_SOLUTIONWRITERSTANDARD_H
#define IRICLIB_CGNSFILE_SOLUTIONWRITERSTANDARD_H

#include "iriclib_cgnsfile_baseiterativet.h"
#include "iriclib_cgnsfile_solutionwriter.h"

namespace iRICLib {

class CgnsFile::SolutionWriterStandard : public CgnsFile::SolutionWriter
{
public:
	SolutionWriterStandard(CgnsFile::Impl* impl);

	int Sol_Write_Time(double time) override;
	int Sol_Write_Iteration(int index) override;
	int Sol_Write_GridCoord2d(double *x, double *y) override;
	int Sol_Write_GridCoord3d(double *x, double *y, double *z) override;
	int Sol_Write_Integer(const char* name, int* data) override;
	int Sol_Write_Real(const char* name, double* data) override;
	int Sol_Write_Cell_Integer(const char *name, int* data) override;
	int Sol_Write_Cell_Real(const char *name, double* data) override;
	int Sol_Write_IFace_Integer(const char *name, int* data) override;
	int Sol_Write_IFace_Real(const char *name, double* data) override;
	int Sol_Write_JFace_Integer(const char *name, int* data) override;
	int Sol_Write_JFace_Real(const char *name, double* data) override;
	int Sol_Particle_Write_Pos2d(cgsize_t count, double* x, double* y) override;
	int Sol_Particle_Write_Pos3d(cgsize_t count, double* x, double* y, double* z) override;
	int Sol_Particle_Write_Real(const char* name, double* value) override;
	int Sol_Particle_Write_Integer(const char* name, int* value) override;
	int Sol_ParticleGroup_Write_GroupEnd() override;
	int Sol_PolyData_Write_GroupEnd() override;
	int Sol_Write_BaseIterative_Integer(const char *name, int value) override;
	int Sol_Write_BaseIterative_Real(const char *name, double value) override;
	int Sol_Write_BaseIterative_String(const char* name, const char* value) override;

	int Flush() override;

	static int stdSolWriteTime(double time, CgnsFile::Impl* impl);
	static int stdSolWriteIteration(int index, CgnsFile::Impl* impl);
	static int stdSolWriteGridCoord2d(double* x, double* y, int fid, int bid, int zid, int gcid, CgnsFile::Impl* impl);
	static int stdSolWriteGridCoord3d(double* x, double* y, double* z, int fid, int bid, int zid, int gcid, CgnsFile::Impl* impl);

	static int stdSolWriteBaseIterativeInteger(const char* name, int value, CgnsFile::Impl* impl);
	static int stdSolWriteBaseIterativeReal(const char* name, double value, CgnsFile::Impl* impl);
	static int stdSolWriteBaseIterativeString(const char* name, const char* value, CgnsFile::Impl* impl);

	static BaseIterativeT<int>* stdSolAddBaseIterativeInteger(const char* name, int value, CgnsFile::Impl* impl);
	static BaseIterativeT<double>* stdSolAddBaseIterativeReal(const char* name, double value, CgnsFile::Impl* impl);
	static BaseIterativeT<std::string>* stdSolAddBaseIterativeString(const char* name, const char* value, CgnsFile::Impl* impl);
	static int stdSolWriteBaseIterativeData(int num, CgnsFile::Impl* impl);

	static int stdSolParticleWritePos2d(cgsize_t count, double* x, double* y, int fid, int bid, int zid, int sid);
	static int stdSolParticleWritePos3d(cgsize_t count, double* x, double* y, double* z, int fid, int bid, int zid, int sid);
	static int stdSolParticleWriteReal(const char* name, double* value, int fid, int bid, int zid, int sid);
	static int stdSolParticleWriteInteger(const char* name, int* value, int fid, int bid, int zid, int sid);

	static void setupStringBuffer(const std::vector<std::string>& vals, cgsize_t* dims, std::vector<char>* buffer);
};

} // namespace iRICLib

#endif // IRICLIB_CGNSFILE_SOLUTIONWRITERSTANDARD_H
