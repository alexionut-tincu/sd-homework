#include <bit>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

#define MOD 1'000'000'007

class RangeMaxQuery {
public:
	RangeMaxQuery(const std::vector<uint64_t> &vec) :
		table_(uint64_log2(vec.size()) + 1, std::vector<uint64_t>(vec.size()))
	{
		uint64_t n = vec.size();
		uint64_t k = uint64_log2(n);
		std::copy(vec.begin(), vec.end(), table_[0].begin());
		
		for (uint64_t i = 1; i <= k; ++i) {
			for (uint64_t j = 0; j + (1 << i) <= n; ++j) {
				uint64_t idx = i - 1;
				table_[i][j] = uint64_max(table_[idx][j], table_[idx][j + (1 << i - 1)]);
			}
		}
	}

	const uint64_t Query(const std::vector<uint64_t> &vec, const uint64_t l, const uint64_t r) const
	{
		uint64_t i = uint64_log2(r - l + 1);
		return uint64_max(table_[i][l], table_[i][r - (1 << i) + 1]);
	}

private:
	const uint64_t uint64_max(const uint64_t x, const uint64_t y) const
	{
		return x > y ? x : y;
	}

	const uint64_t uint64_log2(const uint64_t x) const
	{
		return std::bit_width(x) - 1;
	}

	std::vector<std::vector<uint64_t>> table_;
};

const uint64_t uint64_pow(uint64_t base, uint64_t pow)
{
	uint64_t sol = 1;
	while(pow) {
		sol = (pow & 1) * sol * base % MOD + !(pow & 1) * sol;
		base = base * base % MOD;
		pow >>= 1;
	}
	return sol;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	uint64_t n;
	std::cin >> n;
	std::vector<uint64_t> vec(n);
	for (uint64_t i = 0; i < n; ++i) {
		std::cin >> vec[i];
	}

	RangeMaxQuery rmq(vec);
	int64_t queries;
	std::cin >> queries;
	
	while (queries--) {
		uint64_t l, r;
		std::cin >> l >> r;

		uint64_t len = --r - --l;
		uint64_t max = rmq.Query(vec, l, r);
		
		std::cout << max * uint64_pow(2, len) % MOD << '\n';
	}

	return 0;
}