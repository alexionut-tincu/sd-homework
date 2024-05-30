#include <fstream>

#define SIZE 250001

int main()
{
	std::ifstream fin("stramosi.in", std::ios::binary);
	std::ofstream fout("stramosi.out");

	std::streambuf* raw_buffer = fin.rdbuf();

   
	fin.seekg(0, std::ios::end);
	std::streamsize size = fin.tellg();
	fin.seekg(0, std::ios::beg);

	char *block = new char[size];
	raw_buffer->sgetn(block, size);
	char *ptr = block;

	int64_t members, queries;
	members = std::strtoll(ptr, &ptr, 10);
	queries = std::strtoll(ptr, &ptr, 10);

	int64_t tree_depth = 0;

	int64_t ancestors[SIZE];
	for (int64_t i = 1; i <= members; ++i) {
		ancestors[i] = std::strtoll(ptr, &ptr, 10);
		tree_depth += (ancestors[i] == i - 1);
	}

	if (tree_depth == members) {
		while (queries--) {
			int64_t x = std::strtoll(ptr, &ptr, 10);
            		int64_t y = std::strtoll(ptr, &ptr, 10);
			fout << ((x >= y) ? (x - y) : 0) << '\n';
		}
	}

	else {
		while (queries--) {
			int64_t x = std::strtoll(ptr, &ptr, 10);
            		int64_t y = std::strtoll(ptr, &ptr, 10);

			while (y-- && x) {
				x = ancestors[x];
			}

			fout << x << '\n';
		}
	}

	delete[] block;

	return 0;
}