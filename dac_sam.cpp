#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

struct WarriorPair {
	uint64_t power;
	uint64_t idx;
};

bool WarriorCmp(const WarriorPair &w1, const WarriorPair &w2)
{
	return w1.power < w2.power;
}

uint64_t uint64_min(const uint64_t x, const uint64_t y)
{
	return x < y ? x : y;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	uint64_t n;
	std::cin >> n;
	std::vector<WarriorPair> vec(n << 1);
	std::deque<WarriorPair> deq;
	std::vector<int64_t> freq(n << 1);
	
	for (uint64_t i = 0; i < n; ++i) {
		uint64_t idx = i << 1;
		std::cin >> vec[idx].power >> vec[idx + 1].power;
		vec[idx].idx = i;
		vec[idx + 1].idx = i;
	}
	std::sort(vec.begin(), vec.end(), WarriorCmp);

	uint64_t cnt = 0;
	uint64_t min_delta = -1;

	uint64_t size = n << 1;
	for (uint64_t i = 0; i < size; ++i) {
		uint64_t idx = vec[i].idx;
		deq.push_back(vec[i]);
		cnt += (++freq[idx] == 1);

		while (!deq.empty() && cnt == n) {
			min_delta = uint64_min(min_delta, deq.back().power - deq.front().power);
			idx = deq.front().idx;
			deq.pop_front();
			cnt -= (--freq[idx] == 0);
		}
	}

	std::cout << min_delta << std::endl;

	return 0;
}