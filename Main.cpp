#include "Dayxx.h"
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include <iostream>
#include <string>
#include <string_view>

int main()
{
	int day{3}, test{0};

	if (test) {
		if (day < 1)  dayxx::runTest();
		if (day == 1) day01::runTest();
		if (day == 2) day02::runTest();
		if (day == 3) day03::runTest();
	}
	else {
		if (day < 1)  dayxx::run();
		if (day == 1) day01::run();
		if (day == 2) day02::run();
		if (day == 3) day03::run();
	}

	return 0;
}