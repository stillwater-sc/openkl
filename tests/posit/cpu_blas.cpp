// cpu_blas.cpp: example of BLAS operators using CPU
//
#include <iostream>
#include <openkl/openkl.hpp>

#include <universal/posit/posit>

int main(int argc, char* argv[])
try {
	// first step: enumerate the target devices our program could use
	openkl::klDeviceList devices;
	openkl::klDeviceQuery query = openkl::klDeviceQuery{ openkl::LOCAL_HOST, 512 };

	if (!openkl::enumerate_devices(devices, query)) {
		std::cerr << "unable to find any OpenKL devices" << std::endl;
		exit(EXIT_FAILURE);
	}

	// second: create an execution context on the device of your choice
	if (!openkl::create_context(devices[0])) {
		std::cerr << "unable to create execution context on device " << devices[0].id << std::endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < devices.size(); ++i) {
		std::cout << "Device\n"
			<< "          id : " << devices[i].id << '\n'
			<< "       class : " << devices[i].device_class << '\n'
			<< " memory size : " << devices[i].memory << " MBytes"
			<< std::endl;
	}

	std::cout << "posit<32,2> epsilon : " << std::numeric_limits< sw::unum::posit<32, 2> >::epsilon() << std::endl;
	std::cout << "posit<32,2> minpos  : " << sw::unum::minpos<32, 2>() << std::endl;

}
catch(const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}
