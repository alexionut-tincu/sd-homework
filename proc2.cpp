#include <array>
#include <fstream>
#include <queue>
#include <string>

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

int main()
{
	FILE *fin = fopen("proc2.in", "r");

	int64_t n, m;
	fastscan(n, fin);
	fastscan(m, fin);

	std::priority_queue<std::array<int64_t, 2>> busy_cpus;
	std::priority_queue<int64_t> free_cpus;
	int64_t active_cpus = 0;

	int64_t sol_cpu = 0;
	std::string sol = "";
	while (m--) {
		int64_t start, duration;
		fastscan(start, fin);
		fastscan(duration, fin);

		while (!busy_cpus.empty() && -busy_cpus.top()[0] <= start) {
			free_cpus.push(-busy_cpus.top()[1]);
			busy_cpus.pop();
			--active_cpus;
		}

		sol_cpu = ++active_cpus;

		if (!free_cpus.empty()) {
			sol_cpu = -free_cpus.top();
			free_cpus.pop();
		}

		busy_cpus.push({ -(start + duration), sol_cpu });

		sol += std::to_string(sol_cpu) + "\n";
	}

	fclose(fin);
	
	std::ofstream fout("proc2.out");
	fout << sol;
	fout.close();
	
	return 0;
}