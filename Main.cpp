#include "Day01.h"
#include <iostream>
#include <string>
#include <string_view>

int main()
{
	int day{1}, test{1};

	if (test) {
		if (day == 1) day01::runTest();
	}
	else {
		if (day == 1) day01::run();
	}

	return 0;
}