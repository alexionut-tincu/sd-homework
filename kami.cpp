#include <cmath>
#include <fstream>
#include <vector>

struct level_range {
	int64_t snow_sum;
	int64_t avalanche_threshold;
};

class Mountain {
public:
	Mountain(const std::vector<int64_t> &vec) : ranges_((u_int64_t) std::sqrt(vec.size()) + 2)
	{
		int64_t vec_size = (vec.size());
		size_ = std::sqrt(vec_size);

		int64_t it = 0;
		for (int64_t i = 0; i < vec_size; i += size_) {
			ranges_[it++] = {0, 0};
			Update(vec, i);
		}
	}

	void Update(const std::vector<int64_t> &vec, const int64_t pos)
	{
		int64_t idx = pos / size_;
		int64_t lower_bound = idx * size_;
		int64_t upper_bound = std::min((int64_t)(idx + 1) * size_, (int64_t) vec.size()) - 1;
		ranges_[idx] = {vec[upper_bound], vec[upper_bound] + 1};

		int64_t sum = vec[upper_bound] * 2 + 1;
		for (int64_t i = upper_bound - 1; i >= lower_bound; --i) {
			ranges_[idx].snow_sum += vec[i];
			if (vec[i] >= sum) {
				ranges_[idx].avalanche_threshold += vec[i] - sum + 1;
				sum = vec[i] * 2 + 1;
			} else {
				sum += vec[i];
			}
		}
	}

	const int64_t Query(const std::vector<int64_t> &vec, int64_t pos) const
	{
		int64_t idx = pos / size_;
		int64_t sum = vec[pos--];
		while (pos >= idx * size_) {
			if (vec[pos] >= sum) {
				return pos + 1;
			}
			sum += vec[pos--];
		}

		while (--idx >= 0 && ranges_[idx].avalanche_threshold <= sum) {
			sum += ranges_[idx].snow_sum;
		}
		if (idx < 0) {
			return 0;
		}

		pos = std::min((int64_t)(idx + 1) * size_, (int64_t) vec.size()) - 1;
		while (pos >= 0 && vec[pos] < sum) {
			sum += vec[pos--];
		}
		return pos + 1;
	}

private:
	int64_t size_;
	std::vector<level_range> ranges_;
};

int main()
{
	std::ifstream fin("kami.in");
	std::ofstream fout("kami.out");
	std::streambuf *raw_buffer = fin.rdbuf();

	fin.seekg(0, std::ios::end);
	std::streamsize size = fin.tellg();
	fin.seekg(0, std::ios::beg);

	char *block = new char[size];
	raw_buffer->sgetn(block, size);
	char *ptr = block;

	int64_t level_count;
	level_count = std::strtoll(ptr, &ptr, 10);

	std::vector<int64_t> levels(level_count);
	for (int64_t i = 0; i < level_count; ++i) {
		levels[i] = std::strtoll(ptr, &ptr, 10);
	}
	Mountain mountain(levels);

	int64_t queries;
	queries = std::strtoll(ptr, &ptr, 10);
	while (queries--) {
		int64_t type;
		type = std::strtoll(ptr, &ptr, 10);
		if (type == 0) {
			int64_t qlevel, val;
			qlevel = std::strtoll(ptr, &ptr, 10);
			val = std::strtoll(ptr, &ptr, 10);
			levels[--qlevel] = val;
			mountain.Update(levels, qlevel);
		} else if (type == 1) {
			int64_t qlevel;
			qlevel = std::strtoll(ptr, &ptr, 10);
			fout << mountain.Query(levels, --qlevel) << '\n';
		}
	}

	return 0;
}