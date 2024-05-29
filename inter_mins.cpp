#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#define MAXN 200000

constexpr int64_t int64_t_log2(int64_t n)
{
	return n <= 1 ? 0 : 1 + int64_t_log2(n >> 1);
}

template <size_t N, size_t... I>
constexpr std::array<int64_t, N + 1> make_log2_array(std::index_sequence<I...>)
{
	return {int64_t_log2(I)...};
}

template <size_t N>
constexpr auto generate_log2_array()
{
	return make_log2_array<N>(std::make_index_sequence<N + 1>{});
}

constexpr auto a_log2 = generate_log2_array<MAXN>();

class SparseTableIndexes {
public:
	SparseTableIndexes(const std::vector<int64_t> &vec) : 
		table_(a_log2[vec.size()] + 1, std::vector<uint64_t>(vec.size()))
	{
		uint64_t n = vec.size();
		uint64_t k = a_log2[n];

		for (uint64_t i = 0; i < n; ++i) {
			table_[0][i] = i;
		}

		for (uint64_t i = 1; i <= k; ++i) {
			for (uint64_t j = 0; j + (1 << i) <= n; ++j) {
				uint64_t val1 = table_[i - 1][j];
				uint64_t val2 = table_[i - 1][j + (1 << (i - 1))]; 
				bool cmp = vec[val1] < vec[val2];
				table_[i][j] = cmp * val1 + !cmp * val2;
			}
		}
	}

	const uint64_t Query(const std::vector<int64_t> &vec, const uint64_t l, const uint64_t r) const
	{
		uint64_t i = a_log2[r - l + 1];
		uint64_t idx1 = table_[i][l];
		uint64_t idx2 = table_[i][r - (1 << i) + 1];
		return (vec[idx1] < vec[idx2]) ? idx1 : idx2;
	}

private:
	std::vector<std::vector<uint64_t>> table_;
};

const int64_t max(const int64_t x, const int64_t y)
{
	return x > y ? x : y;
}

const int64_t GaussSum(int64_t l, int64_t r)
{
	l = max(0, l);
	r = max(0, r);
	return (l + r) * (r - l + 1) >> 1;
}

uint64_t CalcIntSstrings(const std::vector<int64_t> &vec,
			 const SparseTableIndexes &st,
			 const int64_t l, const int64_t r)
{
	if (l > r || l == r) {
		return 0;
	}
	int64_t min_idx = st.Query(vec, l, r);
	int64_t nums_on_l = min_idx - l;
	int64_t nums_on_r = r - min_idx;
	return GaussSum(nums_on_l - nums_on_r, nums_on_l) + CalcIntSstrings(vec, st, l, min_idx - 1) +
		CalcIntSstrings(vec, st, min_idx + 1, r);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	uint64_t n;
	std::cin >> n;
	std::vector<int64_t> vec(n);
	for (uint64_t i = 0; i < n; ++i) {
		std::cin >> vec[i];
	}

	SparseTableIndexes st(vec);
	uint64_t interesting_substrings = CalcIntSstrings(vec, st, 0, n - 1);

	std::cout << interesting_substrings;

	return 0;
}