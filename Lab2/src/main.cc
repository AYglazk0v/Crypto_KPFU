#include <iostream>
#include "../inc/namespaces.hpp"

int main(int argc, char** argv) {
	Generator::Register reg(argc, argv);
	reg.runTask();
	return 0;
}