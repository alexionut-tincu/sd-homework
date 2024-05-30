#include <fstream>

#define SIZE 250001

template<typename T>
void fastscan(T &number, FILE *file = stdin)
{
	bool negative = false;
	char c;
	number = 0;
	c = getc(file);
	if (c == '-')
	{
		negative = true;
		c = getc(file);
	}
	for (; (c > 47 && c < 58); c = getc(file)) {
		number = number * 10 + c - 48;
	}
	if (negative) {
		number *= -1;
	}
}

int main()
{
	FILE *fin = fopen("stramosi.in", "r");
	std::ofstream fout("stramosi.out");

	int64_t members, queries;
	fastscan(members, fin);
	fastscan(queries, fin);

	int64_t tree_depth = 0;

	int64_t ancestors[SIZE];
	for (int64_t i = 1; i <= members; ++i) {
		fastscan(ancestors[i], fin);
		tree_depth += (ancestors[i] == i - 1);
	}

	if (tree_depth == members) {
		while (queries--) {
			int64_t x, y;
			fastscan(x, fin);
			fastscan(y, fin);
			fout << ((x >= y) ? (x - y) : 0) << '\n';
		}
	}

	else {
		while (queries--) {
			int64_t x, y;
			fastscan(x, fin);
			fastscan(y, fin);

			while (y-- && x) {
				x = ancestors[x];
			}

			fout << x << '\n';
		}
	}

	return 0;
}