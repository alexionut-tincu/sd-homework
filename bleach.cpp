#include <fstream>
#include <set>

#define MAX_POW 1'000'000'000

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
	// std::ifstream fin("bleach.in");
	std::ofstream fout("bleach.out");

	FILE *fin = fopen("bleach.in", "r");

	uint64_t n, k;
	fastscan(n, fin);
	fastscan(k, fin);
	std::multiset<int64_t> enemy_ms;

	int64_t ichigo_min_pow = 0, ichigo_pow = 0;

	for (uint64_t i = 0; i < n; ++i) {
		int64_t pow;
		fastscan(pow, fin);
		enemy_ms.insert(pow);
		if (i >= k) {
			int64_t weakest = *enemy_ms.begin();
			enemy_ms.erase(enemy_ms.begin());
			if (ichigo_pow < weakest) {
				ichigo_min_pow += (weakest - ichigo_pow);
				ichigo_pow = (weakest << 1);
			} else {
				ichigo_pow += weakest;
			}
			if (ichigo_pow >= MAX_POW) {
				fout << ichigo_min_pow << '\n';
				fout.close();
				break;
			}
		}
	}
	while (!enemy_ms.empty()) {
		int64_t weakest = *enemy_ms.begin();
		enemy_ms.erase(enemy_ms.begin());
		if (ichigo_pow < weakest) {
			ichigo_min_pow += (weakest - ichigo_pow);
			ichigo_pow = (weakest << 1);
		} else {
			ichigo_pow += weakest;
		}
		if (ichigo_min_pow >= MAX_POW) {
			break;
		}
	}

	fout << ichigo_min_pow << '\n';

	fout.close();
	
	return 0;
}