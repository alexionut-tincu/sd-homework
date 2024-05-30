#include <algorithm>
#include <cstdint>
#include <fstream>
#include <vector>

template<typename T>
void fastscan(T &number, FILE *file = stdin)
{
	bool negative = false;
	int_fast8_t c;
	number = 0;
	c = fgetc(file);
	if (c == EOF) {
		number = EOF;
		return;
	}
	if (c == '-') {
		negative = true;
		c = fgetc(file);
	}
	for (; (c > 47 && c < 58); c = fgetc(file)) {
		number = number * 10 + c - 48;
	}
	if (negative) {
		number *= -1;
	}
}

struct Duplicate {
	int64_t val;
	int64_t first_idx;
	int64_t second_idx;
};

const int64_t int64_search(int64_t val, const std::vector<int64_t> &vec, 
			    int64_t l, int64_t r)
{
	for (int64_t i = l; i < r; ++i) {
		if (vec[i] == val) {
			return i;
		}
	}
	return -1;
}

int main()
{
	FILE *fin = fopen("sirbun.in", "r");
	FILE *fout = fopen("sirbun.out", "w");

	int64_t n;
	fastscan(n, fin);

	Duplicate dup = {0, 0, 0};

	int64_t sol = 0;
	std::vector<int64_t> vec(n);
	int64_t l = 0;
	fastscan(vec[0], fin);
	for (int64_t i = 1; i < n; ++i) {
		fastscan(vec[i], fin);

		int64_t idx = int64_search(vec[i], vec, l, i);
		if (idx != -1) {
			if (dup.val != 0){
				if (dup.val != vec[i]) {
					sol += (i - l) * (i - l + 1) >> 1;
					l = dup.first_idx + 1;
					dup = {vec[i], idx, i};
				} else {
					sol += (i - l) * (i - l + 1) >> 1;
					l = dup.first_idx + 1;
					dup.first_idx = dup.second_idx;
					dup.second_idx = i;
				}
			} else {
				dup = {vec[i], idx, i};
			}
		}
	}
	
	if (dup.val != 0 && dup.second_idx == n - 1) {
		sol += (dup.second_idx - dup.first_idx) * (dup.second_idx - dup.first_idx + 1) >> 1;
	}
	
	fprintf(fout, "%ld\n", sol);

	fclose(fin);
	fclose(fout);
	return 0;
}