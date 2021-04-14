// APIs used from Python wrapper is defined

#ifndef IRICLIB_WRAPPER_API_H
#define  IRICLIB_WRAPPER_API_H

#include "iriclib_global.h"

#include <vector>

// Containers for value array

class IRICLIBDLL IntArrayContainer
{
public:
	IntArrayContainer(int size);
	~IntArrayContainer();

	int size() const;
	int value(int index) const;
	void setValue(int index, int v);
	int* pointer();

private:
	std::vector<int>* m_value;
};

class IRICLIBDLL RealArrayContainer
{
public:
	RealArrayContainer(int size);
	~RealArrayContainer();

	int size() const;
	double value(int index) const;
	void setValue(int index, double v);
	double* pointer();

private:
	std::vector<double>* m_value;
};

int IRICLIBDLL cg_iRIC_Flush(const char* name, int fid_in, int* fid_out);

/**********************************************/
/* Reading Calculation Conditions             */
/**********************************************/

int IRICLIBDLL cg_iRIC_Read_FunctionalSize_Mul(int fid, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Functional_Mul(int fid, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data);

/**********************************************/
/* Writing Calculation Conditions             */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_Functional_Mul(int fid, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data);

/**********************************************/
/* Reading Complex Calculation Conditions     */
/**********************************************/

int IRICLIBDLL cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values);

/**********************************************/
/* Writing Complex Calculation Conditions     */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values);

/**********************************************/
/* Reading Grids                              */
/**********************************************/

int IRICLIBDLL cg_iRIC_GetGridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_GetGridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, RealArrayContainer& time);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, RealArrayContainer& value);

/**********************************************/
/* Writing Grids                              */
/**********************************************/

int IRICLIBDLL cg_iRIC_WriteGridCoord1d_Mul(int fid, int isize, RealArrayContainer& x);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d_Mul(int fid, int isize, int jsize, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values);

/**********************************************/
/* Reading Solutions                          */
/**********************************************/

int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);

/**********************************************/
/* Writing Solutions                          */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char *name, RealArrayContainer& data);

/**********************************************/
/* Reading Boundary Conditions                */
/**********************************************/

int IRICLIBDLL cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);

/**********************************************/
/* Writing Boundary Conditions                */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);

/**********************************************/
/* Writing Particles                          */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, IntArrayContainer& value);

/**********************************************/
/* Writing Polydata                           */
/**********************************************/

int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);

/***********************************************/
/* Reading Geographic Data (Polygon)           */
/***********************************************/

int IRICLIBDLL iRIC_Geo_Polygon_Read_Points(int id, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, RealArrayContainer& x, RealArrayContainer& y);

/************************************************/
/* Functions for handling single CGNS files     */
/*                                              */
/* These functions are created using            */
/* make_iriclib_singlefuncs_header.php.         */
/************************************************/

int IRICLIBDLL cg_iRIC_Read_Functional(const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Functional(const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node(const char* groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node(const char* groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_GetGridCoord2d(RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_GetGridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node(const char* name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node(const char* name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell(const char *name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell(const char *name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime(const char* name, RealArrayContainer& time);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_WriteGridCoord1d(cgsize_t isize, RealArrayContainer& x);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d(cgsize_t isize, cgsize_t jsize, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d(cgsize_t isize, cgsize_t jsize, cgsize_t ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node(const char* name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node(const char* name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell(const char *name, RealArrayContainer& values);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell(const char *name, IntArrayContainer& values);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d(int step, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d(int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer(int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer(int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer(int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer(int step, const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Real(int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real(int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real(int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real(int step, const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d(RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer(const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer(const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer(const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer(const char *name, IntArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Real(const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real(const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real(const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real(const char *name, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Read_BC_Indices(const char* type, int num, IntArrayContainer& indices);
int IRICLIBDLL cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_BC_Indices(const char* type, int num, IntArrayContainer& indices);
int IRICLIBDLL cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d(RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real(const char* name, RealArrayContainer& value);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer(const char* name, IntArrayContainer& value);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon(RealArrayContainer& x, RealArrayContainer& y);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline(RealArrayContainer& x, RealArrayContainer& y);

#endif IRICLIB_WRAPPER_API_H
