%module iric
%include "cstring.i"
%include "typemaps.i"

%{
#include "../iriclib.h"
#include "../iriclib_wrapper.h"
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


// from iriclib_bc.h
void cg_iRIC_Read_BC_Count_WithGridId(int fid, int gid, const char* type, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize_WithGridId(int fid, int gid, const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize2_WithGridId(int fid, int gid, const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_Integer_WithGridId(int fid, int gid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Real_WithGridId(int fid, int gid, const char* type, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_BC_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, char* strvalue);
int cg_iRIC_Read_BC_FunctionalSize_WithGridId(int fid, int gid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Clear_BC_WithGridId(int fid, int gid);
int cg_iRIC_Write_BC_Integer_WithGridId(int fid, int gid, const char* type, int num, const char* name, int value);
int cg_iRIC_Write_BC_Real_WithGridId(int fid, int gid, const char* type, int num, const char* name, double value);
int cg_iRIC_Write_BC_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* value);
int cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, const char* value);

// from iriclib_cc.h
int cg_iRIC_Read_Integer(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Real(int fid, const char* name, double* OUTPUT);
int cg_iRIC_Read_String(int fid, const char* name, char* strvalue);
int cg_iRIC_Read_FunctionalSize(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_FunctionalWithName_String(int fid, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Write_Integer(int fid, const char* name, int value);
int cg_iRIC_Write_Real(int fid, const char* name, double value);
int cg_iRIC_Write_String(int fid, const char* name, const char* value);
int cg_iRIC_Write_FunctionalWithName_String(int fid, const char* name, const char* paramname, const char* value);

// from iriclib_complex.h
int cg_iRIC_Read_Complex_Count_WithBaseId(int fid, int bid, const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Complex_Integer_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Real_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_Complex_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, char* strvalue);
int cg_iRIC_Read_Complex_FunctionalSize_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Clear_Complex_WithBaseId(int fid, int bid);
int cg_iRIC_Write_Complex_Integer_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int value);
int cg_iRIC_Write_Complex_Real_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, double value);
int cg_iRIC_Write_Complex_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* value);
int cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, const char* value);

// from iriclib_geo.h
int iRIC_Geo_Polygon_Open(const char* filename, int* OUTPUT);
int iRIC_Geo_Polygon_Read_IntegerValue(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_RealValue(int id, double* OUTPUT);
int iRIC_Geo_Polygon_Read_PointCount(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_HoleCount(int id, int* OUTPUT);
int iRIC_Geo_Polygon_Read_HolePointCount(int id, int holeid, int* OUTPUT);
int iRIC_Geo_Polygon_Close(int id);
int iRIC_Geo_RiverSurvey_Open(const char* filename, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Count(int id, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Position(int id, int pointid, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Direction(int id, int pointid, double* OUTPUT, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_Name(int id, int pointid, char* strvalue);
int iRIC_Geo_RiverSurvey_Read_RealName(int id, int pointid, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_LeftShift(int id, int pointid, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_AltitudeCount(int id, int pointid, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_FixedPointL(int id, int pointid, int* OUTPUT, double* OUTPUT, double* OUTPUT, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_FixedPointR(int id, int pointid, int* OUTPUT, double* OUTPUT, double* OUTPUT, int* OUTPUT);
int iRIC_Geo_RiverSurvey_Read_WaterSurfaceElevation(int id, int pointid, int* OUTPUT, double* OUTPUT);
int iRIC_Geo_RiverSurvey_Close(int id);

// from iriclib_geoutil.h
int cg_iRIC_Read_Geo_Count(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Geo_Filename(int fid, const char* name, int geoid, char* strvalue, int* OUTPUT);

// from iriclib_grid.h
int cg_iRIC_Read_Grid2d_Str_Size_WithGridId(int fid, int gid, int* OUTPUT, int* OUTPUT);
int cg_iRIC_Read_Grid3d_Str_Size_WithGridId(int fid, int gid, int* OUTPUT, int* OUTPUT, int* OUTPUT);
int cg_iRIC_Read_Grid_TriangleElementsSize_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_TriangleElementsSize2_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_NodeCount_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_CellCount_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_IFaceCount_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_JFaceCount_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_KFaceCount_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId(int fid, int gid, const char* name, const char* dimname, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId(int fid, int gid, const char* name, int* OUTPUT);

// from iriclib_grid_solverlib.h
int cg_iRIC_Read_Grid2d_Open_WithGridId(int fid, int gid, int* OUTPUT);
int cg_iRIC_Read_Sol_Grid2d_Open_WithGridId(int fid, int gid, int solid, int* OUTPUT);
int cg_iRIC_Read_Grid2d_Close(int grid_handle);
int cg_iRIC_Read_Grid2d_CellArea(int grid_handle, int cellId, double* OUTPUT);
int cg_iRIC_Read_Grid2d_FindCell(int grid_handle, double x, double y, int* OUTPUT);
int cg_iRIC_Read_Grid2d_CellNodeCount(int grid_handle, int cellId, int* OUTPUT);

// from iriclib_gui_coorp.h
int iRIC_Check_Cancel();

// from iriclib_init.h
int cg_iRIC_Open(const char* filename, int mode, int* OUTPUT);
int cg_iRIC_Close(int fid);
int iRIC_InitOption(int option);
int cg_iRIC_Flush(int fid);

// from iriclib_not_withbaseid.h
int cg_iRIC_Read_Complex_Count(int fid, const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Complex_Integer(int fid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_Real(int fid, const char* groupname, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_Complex_String(int fid, const char* groupname, int num, const char* name, char* strvalue);
int cg_iRIC_Read_Complex_FunctionalSize(int fid, const char* groupname, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_Complex_FunctionalWithName_String(int fid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Clear_Complex(int fid);
int cg_iRIC_Write_Complex_Integer(int fid, const char* groupname, int num, const char* name, int value);
int cg_iRIC_Write_Complex_Real(int fid, const char* groupname, int num, const char* name, double value);
int cg_iRIC_Write_Complex_String(int fid, const char* groupname, int num, const char* name, const char* value);
int cg_iRIC_Write_Complex_FunctionalWithName_String(int fid, const char* groupname, int num, const char* name, const char* paramname, const char* value);

// from iriclib_not_withgridid.h
void cg_iRIC_Read_BC_Count(int fid, const char* type, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize(int fid, const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_IndicesSize2(int fid, const char* type, int num, int* OUTPUT);
int cg_iRIC_Read_BC_Integer(int fid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_Real(int fid, const char* type, int num, const char* name, double* OUTPUT);
int cg_iRIC_Read_BC_String(int fid, const char* type, int num, const char* name, char* strvalue);
int cg_iRIC_Read_BC_FunctionalSize(int fid, const char* type, int num, const char* name, int* OUTPUT);
int cg_iRIC_Read_BC_FunctionalWithName_String(int fid, const char* type, int num, const char* name, const char* paramname, char* strvalue);
int cg_iRIC_Clear_BC(int fid);
int cg_iRIC_Write_BC_Integer(int fid, const char* type, int num, const char* name, int value);
int cg_iRIC_Write_BC_Real(int fid, const char* type, int num, const char* name, double value);
int cg_iRIC_Write_BC_String(int fid, const char* type, int num, const char* name, const char* value);
int cg_iRIC_Write_BC_FunctionalWithName_String(int fid, const char* type, int num, const char* name, const char* paramname, const char* value);
int cg_iRIC_Read_Grid2d_Str_Size(int fid, int* OUTPUT, int* OUTPUT);
int cg_iRIC_Read_Grid3d_Str_Size(int fid, int* OUTPUT, int* OUTPUT, int* OUTPUT);
int cg_iRIC_Read_Grid_TriangleElementsSize(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_TriangleElementsSize2(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_NodeCount(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_CellCount(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_IFaceCount(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_JFaceCount(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_KFaceCount(int fid, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalDimensionSize(int fid, const char* name, const char* dimname, int* OUTPUT);
int cg_iRIC_Read_Grid_FunctionalTimeSize(int fid, const char* name, int* OUTPUT);
int cg_iRIC_Read_Grid2d_Open(int fid, int* OUTPUT);
int cg_iRIC_Read_Sol_Grid2d_Open(int fid, int solid, int* OUTPUT);
int cg_iRIC_Read_Sol_Particle_Count(int fid, int step, int* OUTPUT);
int cg_iRIC_Read_Sol_ParticleGroup_Count(int fid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(int fid, const char* name);
int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd(int fid);
int cg_iRIC_Write_Sol_ParticleGroup_Pos2d(int fid, double x, double y);
int cg_iRIC_Write_Sol_ParticleGroup_Pos3d(int fid, double x, double y, double z);
int cg_iRIC_Write_Sol_ParticleGroup_Integer(int fid, const char* name, int value);
int cg_iRIC_Write_Sol_ParticleGroup_Real(int fid, const char* name, double value);
int cg_iRIC_Read_Sol_PolyData_DataCount(int fid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Sol_PolyData_CoordinateCount(int fid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Write_Sol_PolyData_GroupBegin(int fid, const char* name);
int cg_iRIC_Write_Sol_PolyData_GroupEnd(int fid);
int cg_iRIC_Write_Sol_PolyData_Integer(int fid, const char* name, int value);
int cg_iRIC_Write_Sol_PolyData_Real(int fid, const char* name, double value);

// from iriclib_sol_particle.h
int cg_iRIC_Read_Sol_Particle_Count_WithGridId(int fid, int gid, int step, int* OUTPUT);

// from iriclib_sol_particlegroup.h
int cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId(int fid, int gid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId(int fid, int gid, const char* name);
int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId(int fid, int gid);
int cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId(int fid, int gid, double x, double y);
int cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId(int fid, int gid, double x, double y, double z);
int cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId(int fid, int gid, const char* name, int value);
int cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId(int fid, int gid, const char* name, double value);

// from iriclib_sol_polydata.h
int cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(int fid, int gid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(int fid, int gid, int step, const char* groupname, int* OUTPUT);
int cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(int fid, int gid, const char* name);
int cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(int fid, int gid);
int cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(int fid, int gid, const char* name, int value);
int cg_iRIC_Write_Sol_PolyData_Real_WithGridId(int fid, int gid, const char* name, double value);

// from iriclib_solution.h
int cg_iRIC_Read_Sol_Count(int fid, int* OUTPUT);
int cg_iRIC_Read_Sol_Time(int fid, int step, double* OUTPUT);
int cg_iRIC_Read_Sol_Iteration(int fid, int step, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Integer(int fid, int step, const char* name, int* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_Real(int fid, int step, const char* name, double* OUTPUT);
int cg_iRIC_Read_Sol_BaseIterative_String(int fid, int step, const char* name, char* strvalue);
int cg_iRIC_Write_Sol_Time(int fid, double time);
int cg_iRIC_Write_Sol_Iteration(int fid, int index);
int cg_iRIC_Write_Sol_BaseIterative_Integer(int fid, const char* name, int value);
int cg_iRIC_Write_Sol_BaseIterative_Real(int fid, const char* name, double value);
int cg_iRIC_Write_Sol_BaseIterative_String(int fid, const char* name, const char* value);
int cg_iRIC_Write_ErrorCode(int fid, int errorcode);

// from iriclib_wrapper.h
int cg_iRIC_Read_BC_Indices_WithGridId(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Read_BC_Functional_WithGridId(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_BC_FunctionalWithName_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Write_BC_Indices_WithGridId(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Write_BC_Indices2_WithGridId(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Write_BC_Functional_WithGridId(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_BC_FunctionalWithName_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Functional(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_FunctionalWithName(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Write_Functional(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_FunctionalWithName(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Complex_Functional_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Complex_Node_WithGridId(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Complex_Cell_WithGridId(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Write_Complex_Functional_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Complex_Node_WithGridId(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Complex_Cell_WithGridId(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int iRIC_Geo_Polygon_Read_Points(int id, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int iRIC_Geo_RiverSurvey_Read_Altitudes(int id, int pointid, RealArrayContainer& position_arr, RealArrayContainer& height_arr, IntArrayContainer& active_arr);
int cg_iRIC_Read_Grid2d_Coords_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Grid3d_Coords_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Grid_TriangleElements_WithGridId(int fid, int gid, IntArrayContainer& id_arr);
int cg_iRIC_Read_Grid_Real_Node_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Integer_Node_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Real_Cell_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Integer_Cell_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(int fid, int gid, const char* name, const char* dimname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(int fid, int gid, const char* name, const char* dimname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalTime_WithGridId(int fid, int gid, const char* name, RealArrayContainer& time_arr);
int cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid1d_Coords_WithGridId(int fid, int isize, RealArrayContainer& x_arr, int* OUTPUT);
int cg_iRIC_Write_Grid2d_Coords_WithGridId(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, int* OUTPUT);
int cg_iRIC_Write_Grid3d_Coords_WithGridId(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr, int* OUTPUT);
int cg_iRIC_Write_Grid_Real_Node_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Integer_Node_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Real_Cell_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Integer_Cell_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid2d_InterpolateWithCell(int grid_handle, double x, double y, int cellId, IntArrayContainer& nodeids_arr, RealArrayContainer& weights_arr);
int cg_iRIC_Read_Complex_Functional(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Complex_FunctionalWithName(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Write_Complex_Functional(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Complex_FunctionalWithName(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Read_BC_Indices(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Read_BC_Functional(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_BC_FunctionalWithName(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Write_BC_Indices(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Write_BC_Indices2(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int cg_iRIC_Write_BC_Functional(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_BC_FunctionalWithName(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Complex_Node(int fid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Complex_Cell(int fid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Complex_Node(int fid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Complex_Cell(int fid, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid2d_Coords(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Grid3d_Coords(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Grid_TriangleElements(int fid, IntArrayContainer& id_arr);
int cg_iRIC_Read_Grid_Real_Node(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Integer_Node(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Real_Cell(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Integer_Cell(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalDimension_Integer(int fid, const char* name, const char* dimname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalDimension_Real(int fid, const char* name, const char* dimname, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_FunctionalTime(int fid, const char* name, RealArrayContainer& time_arr);
int cg_iRIC_Read_Grid_Functional_Integer_Node(int fid, const char* name, int dimid, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Real_Node(int fid, const char* name, int dimid, RealArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Integer_Cell(int fid, const char* name, int dimid, IntArrayContainer& v_arr);
int cg_iRIC_Read_Grid_Functional_Real_Cell(int fid, const char* name, int dimid, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid1d_Coords(int fid, int isize, RealArrayContainer& x_arr);
int cg_iRIC_Write_Grid2d_Coords(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Grid3d_Coords(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Write_Grid_Real_Node(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Integer_Node(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Real_Cell(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Grid_Integer_Cell(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Cell_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Cell_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Cell_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Cell_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Grid2d_Coords(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_Grid3d_Coords(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Write_Sol_Grid2d_Coords(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_Grid3d_Coords(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_IFace_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_IFace_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_IFace_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_IFace_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_JFace_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_JFace_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_JFace_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_JFace_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_KFace_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_KFace_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_KFace_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_KFace_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Node_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Node_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Node_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Node_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Particle_Pos2d(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_Particle_Pos3d(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_Particle_Real(int fid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Particle_Integer(int fid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Particle_Pos2d(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_Particle_Pos3d(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Write_Sol_Particle_Real(int fid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Particle_Integer(int fid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Pos2d(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Pos3d(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Real(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Integer(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Pos2d(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_PolyData_Type(int fid, int step, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Real(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Integer(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_PolyData_Polygon(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_PolyData_Polyline(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_Cell_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Cell_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Cell_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Cell_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_Grid3d_Coords_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_IFace_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_IFace_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_IFace_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_IFace_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_JFace_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_JFace_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_JFace_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_JFace_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_KFace_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_KFace_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_KFace_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_KFace_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Node_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Node_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Node_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Node_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_Particle_Real_WithGridId(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_Particle_Integer_WithGridId(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Write_Sol_Particle_Real_WithGridId(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Write_Sol_Particle_Integer_WithGridId(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Read_Sol_PolyData_Type_WithGridId(int fid, int gid, int step, const char* groupname, IntArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Real_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);

