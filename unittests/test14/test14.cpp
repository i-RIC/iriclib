#include <iriclib.h>
#include <cgnslib.h>

#include <vector>
#include <iostream>

int main()
{
	int fin, ier;

	cgsize_t isize, jsize;
	std::vector<double> grid_x, grid_y, node_real, result_real;

	ier = cg_open("Case1.cgn", CG_MODE_MODIFY, &fin);
	if (ier != 0) {
		std::cout << "*** Open error of CGNS file ***" << std::endl;
		return 1;
	}
	ier = cg_iRIC_Init(fin);
	if (ier != 0) {
		std::cout << "*** Initialize error of CGNS file ***" << std::endl;
		return 1;
	}

	ier = cg_iRIC_GotoGridCoord2d(&isize, &jsize);
	int size = isize * jsize;

	grid_x.assign(size, 0);
	grid_y.assign(size, 0);
	node_real.assign(size, 0);
	result_real.assign(size, 0);

	ier = cg_iRIC_GetGridCoord2d(grid_x.data(), grid_y.data());

	if (ier != 0) {
		std::cout << "*** No grid data ***" << std::endl;
	}
	std::cout << "grid x, y: isize, jsize=" << isize << ", " << jsize << std::endl;
	ier = cg_iRIC_Read_Grid_Real_Node("node_real", node_real.data());

	for (int j = 0; j < jsize; ++j) {
		for (int i = 0; i < isize; ++i) {
			int idx = i + j * isize;
			result_real[idx] = i + j;
		}
	}
	for (int iter = 1; iter < 100; ++ iter) {
		double time = iter * 2.1;
		ier = cg_iRIC_Write_Sol_Time(time);
		ier = cg_iRIC_Write_Sol_Real("result_real", result_real.data());
	}

	ier = cg_close(fin);
}
