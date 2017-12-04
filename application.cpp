#pragma once

#include "Controller.h"
#include <thread>

int main()
{
	srand((unsigned)time(NULL));

	Controller c;
	c.run();

	return EXIT_SUCCESS;
}