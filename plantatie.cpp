#include <cmath>
#include <cstdint>
#include <fstream>
#include <vector>

void preprocess(int32_t &array, 
		int32_t &lookup,
		const size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		lookup[i][0] = i;
	}
}

int main()
{
	std::ifstream fin("plantatie.in");
	std::ofstream fout("plantatie.out");

	size_t array_side;
	uint32_t query_count;
	fin >> array_side >> query_count;

	int32_t plantation[array_side][array_side];
	for (size_t i = 0; i < array_side; ++i) {
		for (size_t j = 0; j < array_side; ++j) {
			fin >> plantation[i][j];
		}
	}
	
	int32_t lookup[array_side][array_side][(size_t)(std::log2(array_side) + 1)][(size_t)(std::log2(array_side) + 1)];
	int32_t *lookup_ptr = &lookup[0][0][0][0];
	
	
	preprocess(plantation, lookup, array_side);
}