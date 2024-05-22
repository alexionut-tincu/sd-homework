#include <cstdint>
#include <fstream>
#include <numeric>

#define MAX_ARRRAY_SIZE 400

int main()
{
	std::ifstream fin("euclid.in");
	std::ofstream fout("euclid.out");

	uint32_t tests;
	fin >> tests;

	int32_t array[MAX_ARRRAY_SIZE][MAX_ARRRAY_SIZE];

	for (uint32_t test = 1; test <= tests; ++test) {
		uint32_t height, width, test_height, test_width;
		fin >> height >> width >> test_height >> test_width;

		

		for (uint32_t i = 0; i < height; ++i) {
			for (uint32_t j = 0; j < width; ++j) {
				fin >> array[i][j];
			}
		}

		uint32_t max_gcd = 0;

		for (uint32_t top_left_x = 0; top_left_x < height - test_height + 1; ++top_left_x) {
			for (uint32_t top_left_y = 0; top_left_y < width - test_width + 1; ++top_left_y) {
				uint32_t curr_gcd = array[top_left_x][top_left_y];

				for (uint32_t i = top_left_x; curr_gcd > max_gcd && i < top_left_x + test_height; ++i) {
					for (uint32_t j = top_left_y; curr_gcd > max_gcd && j < top_left_y + test_width; ++j) {
						curr_gcd = std::gcd(curr_gcd, array[i][j]);
					}
				}

				if (curr_gcd > max_gcd) {
					max_gcd = curr_gcd;
				}
			}
		}

		fout << "Case #" << test << ": " << max_gcd << "\n";
	}

	fin.close();
	fout.close();

	return 0;
}