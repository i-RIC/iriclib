%module iric
%include "cstring.i"
%include "typemaps.i"

%{
#include "../iriclib.h"
#include "../iriclib_wrapper_api.h"
%}

%cstring_bounded_output(char *strvalue, 2048);

class IntArrayContainer
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

class RealArrayContainer
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

int cg_open(const char* name, int mode, int* OUTPUT);
int cg_close(int fin);
void cg_error_print();

int cg_iRIC_Init(int fid);
int cg_iRIC_InitRead_Base(int fid, const char* basename);
int cg_iRIC_InitRead(int fid);
void cg_iRIC_SetFilename(int fid, const char* fname);
int iRIC_InitOption(int option);
int cg_iRIC_Set_ZoneId_Mul(int fid, int zoneid);

int cg_iRIC_Flush(const char* name, int fid_in, int* OUTPUT);

// iRIC GUI coorporation

int iRIC_Check_Cancel();

// Reading Calculation Conditions

int cg_iRIC_Read_Integer_Mul(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Real_Mul(int fid, const char* name, double* OUTPUT);
int cg_iRIC_Read_String_Mul(int fid, const char* name, char* strvalue);
int cg_iRIC_Read_FunctionalSize_Mul(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Read_Functional_Mul(int fid, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data);

// Writing Calculation Conditions

int cg_iRIC_Write_Integer_Mul(int fid, const char* name, int intvalue);
int cg_iRIC_Write_Real_Mul(int fid, const char* name, double realvalue);
int cg_iRIC_Write_String_Mul(int fid, const char* name, const char* value);
int cg_iRIC_Write_FunctionalWithName_String_Mul(int fid, const char* groupname, const char* name, const char* value);
int cg_iRIC_Write_Functional_Mul(int fid, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& data);

// Reading Complex Calculation Conditions

int cg_iRIC_Read_Complex_Count_Mul(int fid, const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, char* strvalue);
int cg_iRIC_Read_Complex_FunctionalSize_Mul(int fid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Read_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values);
int cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values);

// Writing Complex Calculation Conditions

int cg_iRIC_Clear_Complex_Mul(int fid);
int cg_iRIC_Write_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int intvalue);
int cg_iRIC_Write_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double realvalue);
int cg_iRIC_Write_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, const char* value);
int cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Write_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, const char* value);
int cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& values);
int cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char *groupname, IntArrayContainer& values);

// Reading Grids
int cg_iRIC_GotoGridCoord2d_Mul(int fid, int* OUTPUT, int* OUTPUT);
int cg_iRIC_GetGridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_GotoGridCoord3d_Mul(int fid, int* OUTPUT, int* OUTPUT, int* OUTPUT);
int cg_iRIC_GetGridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Read_Grid_NodeCount_Mul(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_CellCount_Mul(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_IFaceCount_Mul(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_JFaceCount_Mul(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values);
int cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values);
int cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values);
int cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values);
int cg_iRIC_Read_Grid_FunctionalDimensionSize_Mul(int fid, const char* name, const char* dimname, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, IntArrayContainer& value);
int cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, RealArrayContainer& value);
int cg_iRIC_Read_Grid_FunctionalTimeSize_Mul(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, RealArrayContainer& time);
int cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, IntArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, RealArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, IntArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, RealArrayContainer& value);

// Writing Grids

int cg_iRIC_WriteGridCoord1d_Mul(int fid, int isize, RealArrayContainer& x);
int cg_iRIC_WriteGridCoord2d_Mul(int fid, int isize, int jsize, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_WriteGridCoord3d_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_InitGrid_Mul(int fid, int zoneId);
int cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& values);
int cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& values);
int cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char *name, RealArrayContainer& values);
int cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char *name, IntArrayContainer& values);

// Reading Solutions

int cg_iRIC_Read_Sol_Count_Mul(int fid, int* OUTPUT);
int cg_iRIC_Read_Sol_Time_Mul(int fid, int step, double* OUTPUT);
int cg_iRIC_Read_Sol_Iteration_Mul(int fid, int step, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(int fid, int step, const char* name, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Real_Mul(int fid, int step, const char* name, double* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_String_Mul(int fid, int step, const char* name, char* strvalue);
int cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char *name, RealArrayContainer& data);

// Writing Solutions

int cg_iRIC_Write_Sol_Time_Mul(int fid, double time);
int cg_iRIC_Write_Sol_Iteration_Mul(int fid, int index);
int cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(int fid, const char *name, int value);
int cg_iRIC_Write_Sol_BaseIterative_Real_Mul(int fid, const char *name, double value);
int cg_iRIC_Write_Sol_BaseIterative_String_Mul(int fid, const char *name, const char* value);
int cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Write_Sol_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char *name, RealArrayContainer& data);
int cg_iRIC_Write_ErrorCode_Mul(int fid, int errorcode);

// Reading Boundary Conditions

void cg_iRIC_Init_BC_Names_Mul(int fid);
void cg_iRIC_Read_BC_Count_Mul(int fid, const char* type, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize2_Mul(int fid, const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices);
int cg_iRIC_Read_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Real_Mul(int fid, const char* type, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_BC_String_Mul(int fid, const char* type, int num, const char* name, char* strvalue);
int cg_iRIC_Read_BC_FunctionalSize_Mul(int fid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Read_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, char* strvalue);

// Writing Boundary Conditions

int cg_iRIC_Clear_BC_Mul(int fid);
int cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& indices);
int cg_iRIC_Write_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int intvalue);
int cg_iRIC_Write_BC_Real_Mul(int fid, const char* type, int num, const char* name, double realvalue);
int cg_iRIC_Write_BC_String_Mul(int fid, const char* type, int num, const char* name, const char* value);
int cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Write_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, const char* value);

// Writing Particles

int cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, RealArrayContainer& value);
int cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, IntArrayContainer& value);

// Writing Particle Groups

int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(int fid, const char* name);
int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(int fid);
int cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(int fid, double x, double y);
int cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(int fid, double x, double y, double z);
int cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(int fid, const char* name, int value);
int cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(int fid, const char* name, double value);

// Writing Polydata

int cg_iRIC_Write_Sol_PolyData_GroupBegin_Mul(int fid, const char* name);
int cg_iRIC_Write_Sol_PolyData_GroupEnd_Mul(int fid);
int cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_PolyData_Integer_Mul(int fid, const char* name, int value);
int cg_iRIC_Write_Sol_PolyData_Real_Mul(int fid, const char* name, double value);

/*
// Reading Geographic Data

int cg_iRIC_Read_Geo_Count_Mul(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Geo_Filename_Mul(int fid, const char* name, int geoid, char* OUTPUT, int* OUTPUT);

// Reading Geographic Data (Polygon)

int iRIC_Geo_Polygon_Open(const char* filename, int *OUTPUT);
int iRIC_Geo_Polygon_Read_IntegerValue(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_RealValue(int id, double* OUTPUT);
int iRIC_Geo_Polygon_Read_PointCount(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_Points(int id, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_Polygon_Read_HoleCount(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_HolePointCount(int id, int holeid, int* OUTPUT);
int iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_Polygon_Close(int id);

// Reading Geographic Data (RiverSurvey)

int iRIC_Geo_RiverSurvey_Open(const char* filename, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Count(int id, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Position(int id, int pointid, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Direction(int id, int pointid, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Name(int id, int pointid, const char** name);
int iRIC_Geo_RiverSurvey_Read_RealName(int id, int pointid, double* name);
int iRIC_Geo_RiverSurvey_Read_LeftShift(int id, int pointid, double* shift);
int iRIC_Geo_RiverSurvey_Read_AltitudeCount(int id, int pointid, int* count);
int iRIC_Geo_RiverSurvey_Read_Altitudes(int id, int pointid, double* position, double* height, int* active);
int iRIC_Geo_RiverSurvey_Read_FixedPointL(int id, int pointid, int* set, double* directionX, double* directionY, int* index);
int iRIC_Geo_RiverSurvey_Read_FixedPointR(int id, int pointid, int* set, double* directionX, double* directionY, int* index);
int iRIC_Geo_RiverSurvey_Read_WaterSurfaceElevation(int id, int pointid, int *set, double* value);
int iRIC_Geo_RiverSurvey_Close(int id);
*/

int cg_iRIC_Set_ZoneId(int zoneid);
int cg_iRIC_Read_Integer(const char* name, int* OUTPUT);
int cg_iRIC_Read_Real(const char* name, double* OUTPUT);
int cg_iRIC_Read_String(const char* name, char* strvalue);
int cg_iRIC_Read_FunctionalSize(const char* name, int* OUTPUT);
int cg_iRIC_Read_Functional(const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Read_FunctionalWithName_String(const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Write_Integer(const char* name, int intvalue);
int cg_iRIC_Write_Real(const char* name, double realvalue);
int cg_iRIC_Write_String(const char* name, const char* value);
int cg_iRIC_Write_Functional(const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Write_FunctionalWithName_String(const char* groupname, const char* name, const char* value);
int cg_iRIC_Read_Complex_Count(const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Complex_Integer(const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Real(const char* groupname, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_Complex_String(const char* groupname, int num, const char* name, char* strvalue);
int cg_iRIC_Read_Complex_FunctionalSize(const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Read_Complex_FunctionalWithName_String(const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Read_Grid_Complex_Node(const char* groupname, IntArrayContainer& values);
int cg_iRIC_Read_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values);
int cg_iRIC_Clear_Complex();
int cg_iRIC_Write_Complex_Integer(const char* groupname, int num, const char* name, int intvalue);
int cg_iRIC_Write_Complex_Real(const char* groupname, int num, const char* name, double realvalue);
int cg_iRIC_Write_Complex_String(const char* groupname, int num, const char* name, const char* value);
int cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Write_Complex_FunctionalWithName_String(const char* groupname, int num, const char* name, const char* paramname, const char* value);
int cg_iRIC_Write_Grid_Complex_Node(const char* groupname, IntArrayContainer& values);
int cg_iRIC_Write_Grid_Complex_Cell(const char *groupname, IntArrayContainer& values);
int cg_iRIC_GotoGridCoord2d(int* OUTPUT, int* OUTPUT);
int cg_iRIC_GetGridCoord2d(RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_GotoGridCoord3d(int* OUTPUT, int* OUTPUT, int* OUTPUT);
int cg_iRIC_GetGridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Read_Grid_NodeCount(int* OUTPUT);
int cg_iRIC_Read_Grid_CellCount(int* OUTPUT);
int cg_iRIC_Read_Grid_IFaceCount(int* OUTPUT);
int cg_iRIC_Read_Grid_JFaceCount(int* OUTPUT);
int cg_iRIC_Read_Grid_Real_Node(const char* name, RealArrayContainer& values);
int cg_iRIC_Read_Grid_Integer_Node(const char* name, IntArrayContainer& values);
int cg_iRIC_Read_Grid_Real_Cell(const char *name, RealArrayContainer& values);
int cg_iRIC_Read_Grid_Integer_Cell(const char *name, IntArrayContainer& values);
int cg_iRIC_Read_Grid_FunctionalDimensionSize(const char* name, const char* dimname, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, IntArrayContainer& value);
int cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, RealArrayContainer& value);
int cg_iRIC_Read_Grid_FunctionalTimeSize(const char* name, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalTime(const char* name, RealArrayContainer& time);
int cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, IntArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, RealArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, IntArrayContainer& value);
int cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, RealArrayContainer& value);
int cg_iRIC_WriteGridCoord1d(int isize, RealArrayContainer& x);
int cg_iRIC_WriteGridCoord2d(int isize, int jsize, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_WriteGridCoord3d(int isize, int jsize, int ksize, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_InitGrid(int zoneId);
int cg_iRIC_Write_Grid_Real_Node(const char* name, RealArrayContainer& values);
int cg_iRIC_Write_Grid_Integer_Node(const char* name, IntArrayContainer& values);
int cg_iRIC_Write_Grid_Real_Cell(const char *name, RealArrayContainer& values);
int cg_iRIC_Write_Grid_Integer_Cell(const char *name, IntArrayContainer& values);
int cg_iRIC_Read_Sol_Count(int* OUTPUT);
int cg_iRIC_Read_Sol_Time(int step, double* OUTPUT);
int cg_iRIC_Read_Sol_Iteration(int step, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Integer(int step, const char* name, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Real(int step, const char* name, double* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_String(int step, const char* name, char* strvalue);
int cg_iRIC_Read_Sol_GridCoord2d(int step, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_Sol_GridCoord3d(int step, RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Read_Sol_Integer(int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_Cell_Integer(int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_IFace_Integer(int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_JFace_Integer(int step, const char *name, IntArrayContainer& data);
int cg_iRIC_Read_Sol_Real(int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_Cell_Real(int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_IFace_Real(int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Read_Sol_JFace_Real(int step, const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_Time(double time);
int cg_iRIC_Write_Sol_Iteration(int index);
int cg_iRIC_Write_Sol_BaseIterative_Integer(const char *name, int value);
int cg_iRIC_Write_Sol_BaseIterative_Real(const char *name, double value);
int cg_iRIC_Write_Sol_BaseIterative_String(const char *name, const char* value);
int cg_iRIC_Write_Sol_GridCoord2d(RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_GridCoord3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Write_Sol_Integer(const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_Cell_Integer(const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_IFace_Integer(const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_JFace_Integer(const char *name, IntArrayContainer& data);
int cg_iRIC_Write_Sol_Real(const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_Cell_Real(const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_IFace_Real(const char *name, RealArrayContainer& data);
int cg_iRIC_Write_Sol_JFace_Real(const char *name, RealArrayContainer& data);
int cg_iRIC_Write_ErrorCode(int errorcode);
void cg_iRIC_Init_BC_Names();
void cg_iRIC_Read_BC_Count(const char* type, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize2(const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_Indices(const char* type, int num, IntArrayContainer& indices);
int cg_iRIC_Read_BC_Integer(const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Real(const char* type, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_BC_String(const char* type, int num, const char* name, char* strvalue);
int cg_iRIC_Read_BC_FunctionalSize(const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Read_BC_FunctionalWithName_String(const char* type, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Clear_BC();
int cg_iRIC_Write_BC_Indices(const char* type, int num, IntArrayContainer& indices);
int cg_iRIC_Write_BC_Integer(const char* type, int num, const char* name, int intvalue);
int cg_iRIC_Write_BC_Real(const char* type, int num, const char* name, double realvalue);
int cg_iRIC_Write_BC_String(const char* type, int num, const char* name, const char* value);
int cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& realarray_x, RealArrayContainer& realarray_y);
int cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& data);
int cg_iRIC_Write_BC_FunctionalWithName_String(const char* type, int num, const char* name, const char* paramname, const char* value);
int cg_iRIC_Write_Sol_Particle_Pos2d(RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_Particle_Pos3d(RealArrayContainer& x, RealArrayContainer& y, RealArrayContainer& z);
int cg_iRIC_Write_Sol_Particle_Real(const char* name, RealArrayContainer& value);
int cg_iRIC_Write_Sol_Particle_Integer(const char* name, IntArrayContainer& value);
int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(const char* name);
int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd();
int cg_iRIC_Write_Sol_ParticleGroup_Pos2d(double x, double y);
int cg_iRIC_Write_Sol_ParticleGroup_Pos3d(double x, double y, double z);
int cg_iRIC_Write_Sol_ParticleGroup_Integer(const char* name, int value);
int cg_iRIC_Write_Sol_ParticleGroup_Real(const char* name, double value);
int cg_iRIC_Write_Sol_PolyData_GroupBegin(const char* name);
int cg_iRIC_Write_Sol_PolyData_GroupEnd();
int cg_iRIC_Write_Sol_PolyData_Polygon(RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_PolyData_Polyline(RealArrayContainer& x, RealArrayContainer& y);
int cg_iRIC_Write_Sol_PolyData_Integer(const char* name, int value);
int cg_iRIC_Write_Sol_PolyData_Real(const char* name, double value);
/*
int cg_iRIC_Read_Geo_Count(const char* name, int* count);
int cg_iRIC_Read_Geo_Filename(const char* name, int geoid, char* filename, int* type);
*/
