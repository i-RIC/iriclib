#include <iriclib.h>

#include <iostream>

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif

static int wait_secs = 10;

int main(int, char* [])
{
	int ret;

	char cgnsName[] = "Case1.cgn";

	ret = iRIC_Write_Sol_Start(&(cgnsName[0]));

	if (ret != 0) {
		std::cout << "iRIC_Write_Sol_Start() failed" << std::endl;
		return 1;
	}
	std::cout << "iRIC_Write_Sol_Start() succeeded" << std::endl;


	std::cout << "Waiting for " << wait_secs << " seconds..." << std::endl;


#ifdef _MSC_VER
	Sleep(wait_secs * 1000);
#else
	sleep(wait_secs);
#endif

	ret = iRIC_Write_Sol_End(&(cgnsName[0]));

	if (ret != 0) {
		std::cout << "iRIC_Write_Sol_End() failed" << std::endl;
		return 1;
	}
	std::cout << "iRIC_Write_Sol_End() succeeded" << std::endl;

	return 0;
}
