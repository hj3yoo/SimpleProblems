#include <string>
#include <vector>
#include <thread>
#include <future>
#include <random>
#include <iostream>
#include <ctime>

using namespace std;

double approximatePi(int seedSize, int unitSize)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(-1.0, 1.0);

	int numCoordInCircle = 0;
	// Divide calculation to defined unit size to limit the memory usage
	for (int i = 0; i < ceil((double)seedSize / (double)unitSize); i++) {
		vector<double> seedList;
		int unitSeedSize = min(unitSize, seedSize - i * unitSize);

		// To prevent the adjacent seeds being used for the same calculation, 
		// populate the seedList first before calculating
		for (int j = 0; j < unitSeedSize; j++) {
			seedList.push_back(dist(mt));
			seedList.push_back(dist(mt));
		}

		// Given an arbitrary (x, y) coordinate between (-1, -1) and (1, 1),
		// If the coordinate has a distance of 1 or less from the origin,
		// The coordinate is inside the circle with the radius of 1
		for (int j = 0; j < unitSeedSize; j++) {
			double x = seedList[j];
			double y = seedList[j + unitSeedSize];
			bool inCircle = sqrt(pow(x, 2) + pow(y, 2)) <= 1;
			numCoordInCircle += inCircle;
		}
	}
	return (double)numCoordInCircle / (double)seedSize * 4.0f;
}

int main(int argc, char** argv)
{
	int numThread = atoi(argv[1]);
	int seedSize = atoi(argv[2]);
	int unitSize = argc == 3 ? 10000 : atoi(argv[3]);

	clock_t begin = clock();

	vector<future<double>> threadList(numThread);
	for (int i = 0; i < numThread; i++) {
		threadList[i] = async(approximatePi, seedSize, unitSize);
	}

	double avgSum = 0;
	for (int i = 0; i < numThread; i++) {
		avgSum += threadList[i].get();
	}

	clock_t end = clock();
	double elapsedSec = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Approx Pi: " << avgSum / (double)numThread << endl;
	cout << "Elapsed time: " << elapsedSec << "s" << endl;
	return 0;
}