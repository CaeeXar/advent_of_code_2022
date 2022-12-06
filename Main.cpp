#include "Dayxx.h"
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"

int main()
{

	int day{6}, test{0};

	if (test) {
		if (day < 1)  dayxx::runTest();
		if (day == 1) day01::runTest();
		if (day == 2) day02::runTest();
		if (day == 3) day03::runTest();
		if (day == 4) day04::runTest();
		if (day == 5) day05::runTest();
		if (day == 6) day06::runTest();
	}
	else {
		if (day < 1)  dayxx::run();
		if (day == 1) day01::run();
		if (day == 2) day02::run();
		if (day == 3) day03::run();
		if (day == 4) day04::run();
		if (day == 5) day05::run();
		if (day == 6) day06::run();
	}

	return 0;
}