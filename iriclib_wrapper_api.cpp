#include "iriclib.h"
#include "iriclib_wrapper_api.h"

IntArrayContainer::IntArrayContainer(int size) :
	m_value {new std::vector<int> {}}
{
	m_value->assign(size, 0);
}

IntArrayContainer::~IntArrayContainer()
{
	delete m_value;
}

int IntArrayContainer::size() const
{
	return static_cast<int> (m_value->size());
}

int IntArrayContainer::value(int index) const
{
	if (index < 0) {
		return 0;
	}
	if (index >= m_value->size()) {
		return 0;
	}
	return m_value->at(index);
}

void IntArrayContainer::setValue(int index, int v)
{
	if (index < 0) {
		return;
	}
	if (index >= m_value->size()) {
		return;
	}
	(*m_value)[index] = v;
}

int* IntArrayContainer::pointer()
{
	return m_value->data();
}

RealArrayContainer::RealArrayContainer(int size) :
	m_value {new std::vector<double> {}}
{
	m_value->assign(size, 0);
}

RealArrayContainer::~RealArrayContainer()
{
	delete m_value;
}

int RealArrayContainer::size() const
{
	return static_cast<int> (m_value->size());
}

double RealArrayContainer::value(int index) const
{
	if (index < 0) {
		return 0;
	}
	if (index >= m_value->size()) {
		return 0;
	}
	return m_value->at(index);
}

void RealArrayContainer::setValue(int index, double v)
{
	if (index < 0) {
		return;
	}
	if (index >= m_value->size()) {
		return;
	}
	(*m_value)[index] = v;
}

double* RealArrayContainer::pointer()
{
	return m_value->data();
}

int cg_iRIC_Flush(const char* name, int fid_in, int* fid_out)
{
	*fid_out = fid_in;
	return cg_iRIC_Flush(name, fid_out);
}

int cg_iRIC_Read_Functional_Mul(int fid, const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Functional_Mul(fid, name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_FunctionalWithName_Mul(fid, name, paramname, data.pointer());
}

int cg_iRIC_Write_Functional_Mul(int fid, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_Functional_Mul(fid, name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_FunctionalWithName_Mul(fid, name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Complex_Functional_Mul(fid, groupname, num, name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_Complex_FunctionalWithName_Mul(fid, groupname, num, name, paramname, data.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Complex_Node_Mul(fid, groupname, values.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Complex_Cell_Mul(fid, groupname, values.pointer());
}

int cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_Complex_Functional_Mul(fid, groupname, num, name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_Complex_FunctionalWithName_Mul(fid, groupname, num, name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Complex_Node_Mul(fid, groupname, values.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Complex_Cell_Mul(fid, groupname, values.pointer());
}

int cg_iRIC_GetGridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_GetGridCoord2d_Mul(fid, x.pointer(), y.pointer());
}

int cg_iRIC_GetGridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_GetGridCoord3d_Mul(fid, x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Real_Node_Mul(fid, name, values.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Integer_Node_Mul(fid, name, values.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Real_Cell_Mul(fid, name, values.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Integer_Cell_Mul(fid, name, values.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(fid, name, dimname, value.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(fid, name, dimname, value.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, RealArrayContainer& time)
{
	return cg_iRIC_Read_Grid_FunctionalTime_Mul(fid, name, time.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(fid, name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node_Mul(fid, name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(fid, name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(fid, name, dimid, value.pointer());
}

int cg_iRIC_WriteGridCoord1d_Mul(int fid, int isize, RealArrayContainer& x)
{
	return cg_iRIC_WriteGridCoord1d_Mul(fid, static_cast<cgsize_t>(isize), x.pointer());
}

int cg_iRIC_WriteGridCoord2d_Mul(int fid, int isize, int jsize, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_WriteGridCoord2d_Mul(fid, static_cast<cgsize_t>(isize), static_cast<cgsize_t>(jsize), x.pointer(), y.pointer());
}

int cg_iRIC_WriteGridCoord3d_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_WriteGridCoord3d_Mul(fid, static_cast<cgsize_t>(isize), static_cast<cgsize_t>(jsize), static_cast<cgsize_t>(ksize), x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Real_Node_Mul(fid, name, values.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Integer_Node_Mul(fid, name, values.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Real_Cell_Mul(fid, name, values.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Integer_Cell_Mul(fid, name, values.pointer());
}

int cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Sol_GridCoord2d_Mul(fid, step, x.pointer(), y.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Read_Sol_GridCoord3d_Mul(fid, step, x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Integer_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Cell_Integer_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_IFace_Integer_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_JFace_Integer_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Real_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Cell_Real_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_IFace_Real_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_JFace_Real_Mul(fid, step, name, data.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_GridCoord2d_Mul(fid, x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Write_Sol_GridCoord3d_Mul(fid, x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Sol_Integer_Mul(int fid, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Integer_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Cell_Integer_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_IFace_Integer_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_JFace_Integer_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_Real_Mul(int fid, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Real_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Cell_Real_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_IFace_Real_Mul(fid, name, data.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_JFace_Real_Mul(fid, name, data.pointer());
}

int cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices)
{
	std::vector<cgsize_t> tmp_indices;
	tmp_indices.assign(indices.size(), 0);
	int ret = cg_iRIC_Read_BC_Indices_Mul(fid, type, num, tmp_indices.data());
	for (int i = 0; i < indices.size(); ++i) {
		indices.setValue(i, tmp_indices.at(i));
	}
	return ret;
}

int cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_BC_Functional_Mul(fid, type, num, name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_BC_FunctionalWithName_Mul(fid, type, num, name, paramname, data.pointer());
}

int cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices)
{
	std::vector<cgsize_t> tmp_indices;
	tmp_indices.assign(indices.size(), 0);
	for (int i = 0; i < indices.size(); ++i) {
		tmp_indices[i] = indices.value(i);
	}
	return cg_iRIC_Write_BC_Indices2_Mul(fid, type, num, tmp_indices.size(), tmp_indices.data());
}

int cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_BC_Functional_Mul(fid, type, num, name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_BC_FunctionalWithName_Mul(fid, type, num, name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d_Mul(fid, x.size(), x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d_Mul(fid, x.size(), x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, RealArrayContainer& value)
{
	return cg_iRIC_Write_Sol_Particle_Real_Mul(fid, name, value.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, IntArrayContainer& value)
{
	return cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, name, value.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon_Mul(fid, x.size(), x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline_Mul(fid, x.size(), x.pointer(), y.pointer());
}

int iRIC_Geo_Polygon_Read_Points(int id, RealArrayContainer& x, RealArrayContainer& y)
{
	return iRIC_Geo_Polygon_Read_Points(id, x.pointer(), y.pointer());
}

int iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, RealArrayContainer& x, RealArrayContainer& y)
{
	return iRIC_Geo_Polygon_Read_HolePoints(id, holeid, x.pointer(), y.pointer());
}

int cg_iRIC_Read_Functional(const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Functional(name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_FunctionalWithName(name, paramname, data.pointer());
}

int cg_iRIC_Write_Functional(const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_Functional(name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_FunctionalWithName(name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Complex_Functional(groupname, num, name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_Complex_FunctionalWithName(groupname, num, name, paramname, data.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node(const char* groupname, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Complex_Node(groupname, values.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Complex_Cell(groupname, values.pointer());
}

int cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_Complex_Functional(groupname, num, name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_Complex_FunctionalWithName(groupname, num, name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node(const char* groupname, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Complex_Node(groupname, values.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Complex_Cell(groupname, values.pointer());
}

int cg_iRIC_GetGridCoord2d(RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_GetGridCoord2d(x.pointer(), y.pointer());
}

int cg_iRIC_GetGridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_GetGridCoord3d(x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Read_Grid_Real_Node(const char* name, RealArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Real_Node(name, values.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node(const char* name, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Integer_Node(name, values.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell(const char *name, RealArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Real_Cell(name, values.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell(const char *name, IntArrayContainer& values)
{
	return cg_iRIC_Read_Grid_Integer_Cell(name, values.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer(name, dimname, value.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real(name, dimname, value.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime(const char* name, RealArrayContainer& time)
{
	return cg_iRIC_Read_Grid_FunctionalTime(name, time.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node(name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node(name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, IntArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell(name, dimid, value.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, RealArrayContainer& value)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell(name, dimid, value.pointer());
}

int cg_iRIC_WriteGridCoord1d(cgsize_t isize, RealArrayContainer& x)
{
	return cg_iRIC_WriteGridCoord1d(isize, x.pointer());
}

int cg_iRIC_WriteGridCoord2d(cgsize_t isize, cgsize_t jsize, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_WriteGridCoord2d(isize, jsize, x.pointer(), y.pointer());
}

int cg_iRIC_WriteGridCoord3d(cgsize_t isize, cgsize_t jsize, cgsize_t ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_WriteGridCoord3d(isize, jsize, ksize, x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Grid_Real_Node(const char* name, RealArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Real_Node(name, values.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node(const char* name, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Integer_Node(name, values.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell(const char *name, RealArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Real_Cell(name, values.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell(const char *name, IntArrayContainer& values)
{
	return cg_iRIC_Write_Grid_Integer_Cell(name, values.pointer());
}

int cg_iRIC_Read_Sol_GridCoord2d(int step, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_Sol_GridCoord2d(step, x.pointer(), y.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d(int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Read_Sol_GridCoord3d(step, x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Read_Sol_Integer(int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Integer(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Cell_Integer(int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Cell_Integer(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_IFace_Integer(int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_IFace_Integer(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_JFace_Integer(int step, const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Read_Sol_JFace_Integer(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Real(int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Real(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real(int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_Cell_Real(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real(int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_IFace_Real(step, name, data.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real(int step, const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Read_Sol_JFace_Real(step, name, data.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d(RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_GridCoord2d(x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Write_Sol_GridCoord3d(x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Sol_Integer(const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Integer(name, data.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer(const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Cell_Integer(name, data.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer(const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_IFace_Integer(name, data.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer(const char *name, IntArrayContainer& data)
{
	return cg_iRIC_Write_Sol_JFace_Integer(name, data.pointer());
}

int cg_iRIC_Write_Sol_Real(const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Real(name, data.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real(const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_Cell_Real(name, data.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real(const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_IFace_Real(name, data.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real(const char *name, RealArrayContainer& data)
{
	return cg_iRIC_Write_Sol_JFace_Real(name, data.pointer());
}

int cg_iRIC_Read_BC_Indices(const char* type, int num, IntArrayContainer& indices)
{
	std::vector<cgsize_t> tmp_indices;
	tmp_indices.assign(indices.size(), 0);
	int ret = cg_iRIC_Read_BC_Indices(type, num, tmp_indices.data());
	for (int i = 0; i < indices.size(); ++i) {
		indices.setValue(i, tmp_indices.at(i));
	}
	return ret;
}

int cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Read_BC_Functional(type, num, name, x.pointer(), y.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Read_BC_FunctionalWithName(type, num, name, paramname, data.pointer());
}

int cg_iRIC_Write_BC_Indices(const char* type, int num, IntArrayContainer& indices)
{
	std::vector<cgsize_t> tmp_indices;
	tmp_indices.assign(indices.size(), 0);
	for (int i = 0; i < indices.size(); ++i) {
		tmp_indices[i] = indices.value(i);
	}
	return cg_iRIC_Write_BC_Indices2(type, num, tmp_indices.size(), tmp_indices.data());
}

int cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y)
{
	return cg_iRIC_Write_BC_Functional(type, num, name, realarray_x.size(), realarray_x.pointer(), realarray_y.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data)
{
	return cg_iRIC_Write_BC_FunctionalWithName(type, num, name, paramname, data.size(), data.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d(RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d(x.size(), x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d(x.size(), x.pointer(), y.pointer(), z.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real(const char* name, RealArrayContainer& value)
{
	return cg_iRIC_Write_Sol_Particle_Real(name, value.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer(const char* name, IntArrayContainer& value)
{
	return cg_iRIC_Write_Sol_Particle_Integer(name, value.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon(RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon(x.size(), x.pointer(), y.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline(RealArrayContainer& x, RealArrayContainer& y)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline(x.size(), x.pointer(), y.pointer());
}
