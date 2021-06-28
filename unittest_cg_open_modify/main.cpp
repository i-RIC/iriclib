#include <cgnslib.h>
#include <iriclib.h>

#include <iostream>
#include <vector>

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif

static int repeat_count = 100;
static int wait_secs = 3;
static int write_secs = 1;

void writeSolution(int fid, int i)
{
	cgsize_t isize, jsize;

	int ier = cg_iRIC_GotoGridCoord2d(fid, &isize, &jsize);

	std::vector<double> x, y;
	std::vector<double> vx, vy, depth;
	std::vector<int> wet;

	std::vector<double> particle_x, particle_y;
	std::vector<double> particle_vx, particle_vy;
	std::vector<int> particle_active;

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);
	ier = cg_iRIC_GetGridCoord2d(fid, x.data(), y.data());

	vx.assign(isize * jsize, 1);
	vy.assign(isize * jsize, 0.3);
	depth.assign(isize * jsize, 4);
	wet.assign(isize * jsize, 0);

	double TimeVal = i * 2.13;
	ier = cg_iRIC_Write_Sol_Time(fid, TimeVal);

	cg_iRIC_Write_Sol_GridCoord2d(fid, x.data(), y.data());

	// Vertex solutions

	depth.assign(isize * jsize, (double)i);
	cg_iRIC_Write_Sol_Real(fid, "Depth", depth.data());

	cg_iRIC_Write_Sol_Real(fid, "VelocityX", vx.data());

	cg_iRIC_Write_Sol_Real(fid, "VelocityY", vy.data());

	wet.assign(isize * jsize, i);
	cg_iRIC_Write_Sol_Integer(fid, "IBC", wet.data());

	// BaseIterativeData

	double Dist = i * - 0.2 + 20;
	cg_iRIC_Write_Sol_BaseIterative_Real(fid, "Discharge", Dist);
	int DamOpen = i;
	cg_iRIC_Write_Sol_BaseIterative_Integer(fid, "DamOpen", DamOpen);
}

int main(int, char* [])
{
	int ret, fn, ier;

	char cgnsName[] = "Case1.cgn";

	ier = cg_open(cgnsName, CG_MODE_MODIFY, &fn);
	if (ier != 0) {
		std::cout << "cg_open() failed" << std::endl;
		return 1;
	}
	ret = cg_iRIC_Init(fn);
	if (ret != 0) {
		std::cout << "cg_iRIC_Init() failed" << std::endl;
		return 1;
	}

	for (int i = 0; i < repeat_count; ++i) {

		std::cout << "Waiting for " << wait_secs << " seconds..." << std::endl;

#ifdef _MSC_VER
		Sleep(wait_secs * 1000);
#else
		sleep(wait_secs);
#endif

		ret = iRIC_Write_Sol_Start(&(cgnsName[0]));

		if (ret != 0) {
			std::cout << "iRIC_Write_Sol_Start() failed" << std::endl;
			return 1;
		}
		std::cout << "iRIC_Write_Sol_Start() succeeded" << std::endl;

		writeSolution(fn, i);

#ifdef _MSC_VER
		Sleep(write_secs * 1000);
#else
		sleep(write_secs);
#endif

		ret = cg_iRIC_Flush(&(cgnsName[0]), &fn);
		if (ret != 0) {
			std::cout << "cg_iRIC_Flush() failed" << std::endl;
			return 1;
		}

		ret = iRIC_Write_Sol_End(&(cgnsName[0]));

		if (ret != 0) {
			std::cout << "iRIC_Write_Sol_End() failed" << std::endl;
			return 1;
		}
		std::cout << "iRIC_Write_Sol_End() succeeded" << std::endl;

		std::cout << "Sol written " << i << std::endl;
	}

	return 0;
}
