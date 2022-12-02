#include "Day01.h"
#include "Day02.h"
#include <iostream>
#include <string>
#include <string_view>

int main()
{
	int day{2}, test{1};

	if (test) {
		if (day == 1) day01::runTest();
		if (day == 2) day02::runTest();
	}
	else {
		if (day == 1) day01::run();
		if (day == 2) day02::runTest();
	}

	return 0;
}