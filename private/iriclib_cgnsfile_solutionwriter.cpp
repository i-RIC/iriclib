#include "error_macros.h"
#include "iriclib.h"
#include "iriclib_cgnsfile_impl.h"
#include "iriclib_cgnsfile_solutionwriter.h"

using namespace iRICLib;

CgnsFile::SolutionWriter::SolutionWriter(CgnsFile::Impl *impl) :
	m_impl {impl}
{}

CgnsFile::SolutionWriter::~SolutionWriter()
{}

int CgnsFile::SolutionWriter::Sol_ParticleGroup_Write_GroupBegin(const char* name)
{
	clearParticleGroupData();
	m_particleGroupName = name;
	return 0;
}

int CgnsFile::SolutionWriter::Sol_ParticleGroup_Write_Pos2d(double x, double y)
{
	m_particleGroupX.push_back(x);
	m_particleGroupY.push_back(y);
	return 0;
}

int CgnsFile::SolutionWriter::Sol_ParticleGroup_Write_Pos3d(double x, double y, double z)
{
	m_particleGroupX.push_back(x);
	m_particleGroupY.push_back(y);
	m_particleGroupZ.push_back(z);
	return 0;
}

template<typename V>
int SolParticleGroupDataAddValue(const char* name, V value, std::map<std::string, std::vector<V> >* vals)
{
	std::string namestr = name;
	auto it = vals->find(namestr);
	if (it == vals->end()) {
		std::vector<V> emptyVec;
		vals->insert({namestr, emptyVec});
		it = vals->find(namestr);
	}
	auto& vec = it->second;
	vec.push_back(value);
	return 0;
}

int CgnsFile::SolutionWriter::Sol_ParticleGroup_Write_Integer(const char* name, int value)
{
	return SolParticleGroupDataAddValue(name, value, &m_particleGroupIntValues);
}

int CgnsFile::SolutionWriter::Sol_ParticleGroup_Write_Real(const char* name, double value)
{
	return SolParticleGroupDataAddValue(name, value, &m_particleGroupRealValues);
}

int CgnsFile::SolutionWriter::Sol_PolyData_Write_GroupBegin(const char* name)
{
	clearPolyData();
	m_polydataName = name;
	return 0;
}

int CgnsFile::SolutionWriter::Sol_PolyData_Write_Polygon(int num, double* x, double* y)
{
	m_polydataTypes.push_back(IRIC_POLYDATA_POLYGON);
	m_polydataSizes.push_back(num);
	for (int i = 0; i < num; ++i) {
		m_polydataX.push_back(*(x + i));
		m_polydataY.push_back(*(y + i));
	}
	return 0;
}

int CgnsFile::SolutionWriter::Sol_PolyData_Write_Polyline(int num, double* x, double* y)
{
	m_polydataTypes.push_back(IRIC_POLYDATA_POLYLINE);
	m_polydataSizes.push_back(num);
	for (int i = 0; i < num; ++i) {
		m_polydataX.push_back(*(x + i));
		m_polydataY.push_back(*(y + i));
	}
	return 0;
}

template<typename V>
int SolPolyDataAddValue(const char* name, V value, std::map<std::string, std::vector<V> >* vals)
{
	std::string namestr = name;
	auto it = vals->find(namestr);
	if (it == vals->end()) {
		std::vector<V> emptyVec;
		vals->insert({namestr, emptyVec});
		it = vals->find(namestr);
	}
	auto& vec = it->second;
	vec.push_back(value);
	return 0;
}

int CgnsFile::SolutionWriter::Sol_PolyData_Write_Integer(const char* name, int value)
{
	return SolPolyDataAddValue(name, value, &m_polydataIntValues);
}

int CgnsFile::SolutionWriter::Sol_PolyData_Write_Real(const char* name, double value)
{
	return SolPolyDataAddValue(name, value, &m_polydataRealValues);
}

CgnsFile::Impl* CgnsFile::SolutionWriter::impl() const
{
	return m_impl;
}

int CgnsFile::SolutionWriter::stdSolParticleGroupGroupEnd(int fid, int bid, int zid, int sid)
{
	char name[Impl::NAME_MAXLENGTH];
	Impl::getParticleGroupSolName(sid, name);
	int ier = cg_goto(fid, bid, "Zone_t", zid, name, 0, NULL);
	RETURN_IF_ERR;

	std::string arrayName;

	// write X
	arrayName = m_particleGroupName;
	arrayName.append("_coordinateX");
	ier = Impl::writeArray(arrayName.c_str(), RealDouble, m_particleGroupX.size(), m_particleGroupX.data());
	RETURN_IF_ERR;

	// write Y
	arrayName = m_particleGroupName;
	arrayName.append("_coordinateY");
	ier = Impl::writeArray(arrayName.c_str(), RealDouble, m_particleGroupY.size(), m_particleGroupY.data());
	RETURN_IF_ERR;

	// write Z
	arrayName = m_particleGroupName;
	arrayName.append("_coordinateZ");
	if (m_particleGroupZ.size() > 0) {
		ier = Impl::writeArray(arrayName.c_str(), RealDouble, m_particleGroupZ.size(), m_particleGroupZ.data());
		RETURN_IF_ERR;
	}

	// write int values
	for (auto& pair : m_particleGroupIntValues) {
		auto valueName = pair.first;
		auto& values = pair.second;

		arrayName = m_particleGroupName;
		arrayName.append("__");
		arrayName.append(valueName);
		ier = Impl::writeArray(arrayName.c_str(), Integer, values.size(), values.data());
		RETURN_IF_ERR;
	}

	// write real values
	for (auto& pair : m_particleGroupRealValues) {
		auto valueName = pair.first;
		auto& values = pair.second;

		arrayName = m_particleGroupName;
		arrayName.append("__");
		arrayName.append(valueName);
		ier = Impl::writeArray(arrayName.c_str(), RealDouble, values.size(), values.data());
		RETURN_IF_ERR;
	}
	return 0;
}

int CgnsFile::SolutionWriter::stdSolPolyDataGroupEnd(int fid, int bid, int zid, int sid)
{
	char name[Impl::NAME_MAXLENGTH];
	Impl::getPolydataSolName(sid, name);
	int ier = cg_goto(fid, bid, "Zone_t", zid, name, 0, NULL);
	RETURN_IF_ERR;

	std::string arrayName;

	// write type
	arrayName = m_polydataName;
	arrayName.append("_type");
	ier = Impl::writeArray(arrayName.c_str(), Integer, m_polydataTypes.size(), m_polydataTypes.data());
	RETURN_IF_ERR;

	// write size
	arrayName = m_polydataName;
	arrayName.append("_size");
	ier = Impl::writeArray(arrayName.c_str(), Integer, m_polydataSizes.size(), m_polydataSizes.data());
	RETURN_IF_ERR;

	// write X
	arrayName = m_polydataName;
	arrayName.append("_coordinateX");
	ier = Impl::writeArray(arrayName.c_str(), RealDouble, m_polydataX.size(), m_polydataX.data());
	RETURN_IF_ERR;

	// write Y
	arrayName = m_polydataName;
	arrayName.append("_coordinateY");
	ier = Impl::writeArray(arrayName.c_str(), RealDouble, m_polydataY.size(), m_polydataY.data());
	RETURN_IF_ERR;

	// write int values
	for (auto& pair : m_polydataIntValues) {
		auto valueName = pair.first;
		auto& values = pair.second;

		arrayName = m_polydataName;
		arrayName.append("__");
		arrayName.append(valueName);
		ier = Impl::writeArray(arrayName.c_str(), Integer, values.size(), values.data());
		RETURN_IF_ERR;
	}

	// write real values
	for (auto& pair : m_polydataRealValues) {
		auto valueName = pair.first;
		auto& values = pair.second;

		arrayName = m_polydataName;
		arrayName.append("__");
		arrayName.append(valueName);
		ier = Impl::writeArray(arrayName.c_str(), RealDouble, values.size(), values.data());
		RETURN_IF_ERR;
	}
	return 0;
}

void CgnsFile::SolutionWriter::clearParticleGroupData()
{
	m_particleGroupName.clear();
	m_particleGroupX.clear();
	m_particleGroupY.clear();
	m_particleGroupZ.clear();
	m_particleGroupIntValues.clear();
	m_particleGroupRealValues.clear();
}

void CgnsFile::SolutionWriter::clearPolyData()
{
	m_polydataName.clear();
	m_polydataTypes.clear();
	m_polydataSizes.clear();
	m_polydataX.clear();
	m_polydataY.clear();
	m_polydataIntValues.clear();
	m_polydataRealValues.clear();
}
