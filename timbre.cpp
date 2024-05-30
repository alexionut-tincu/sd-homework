// Dupa cum stiti cu totii, Adriana este o mare colectionara de timbre. In fiecare zi se duce la magazinul de pe strada ei pentru a-si mari colectia. Intr-o zi, vanzatorul (nimeni altul decat Balaurul Arhirel) s-a gandit sa-i faca o surpriza. A scos dintr-un dulap vechi niste timbre foarte valoroase pe care erau scrise cu fir de aur si de argint numere naturale. Stiind ca fetita nu are bani prea multi, Balaurul i-a spus urmatoarele: "Eu pot sa impart timbrele in M intervale de forma [1,..,mi]. Tu poti sa iei din orice interval o singura subsecventa de maxim K elemente. Desigur, daca ai ales o subsecventa din intervalul i vei plati o anumita suma..."

// Adriana s-a gandit ca ar fi frumos sa-si numeroteze toate cele N pagini ale clasorului ei cu astfel de timbre. Fiind si o fetita pofticioasa si-a zis : "Tare as vrea sa mananc o inghetata din banii pe care ii am la mine, dar nu stiu daca o sa-mi ajunga sa platesc timbrele. Cum sa fac?"
// Cerinta

// Stiind cele M intervale, precum si costurile acestora, ajutati-o pe Adriana sa cumpere timbrele necesare numerotarii clasorului, platind o suma cat mai mica.
// Date de intrare

// Pe prima linie a fisierului timbre.in se afla N, M, si K. N reprezinta numarul de pagini ale clasorului, M reprezinta numarul de intervale, iar K lungimea maxima a unei subsecvente. Pe urmatoarele M linii se afla doua numere separate printr-un spatiu, mi si ci, unde mi reprezinta marginea superioara a intervalului i, iar ci costul acestuia.
// Date de iesire

// Pe prima linie a fisierului timbre.out se va afla Smin, reprezentand suma minima pe care trebuie sa o plateasca Adriana pentru a cumpara timbrele necesare numerotarii clasorului.
// Restrictii si precizari

//     0 < N < 1 001
//     0 < M < 10 001
//     0 < K < 1 001
//     0 < mi < 100 000
//     0 < ci < 10 000
//     pentru a numerota toate cele N pagini ale clasorului, Adriana are nevoie de timbre cu numerele de la 1 la N

#include <array>
#include <fstream>
#include <map>

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
	FILE *fin = fopen("timbre.in", "r");
	FILE *fout = fopen("timbre.out", "w");

	int64_t n, m, k;
	fastscan(n, fin);
	fastscan(m, fin);
	fastscan(k, fin);

	std::multimap<int64_t, int64_t> intervals;
	for (int64_t i = 0; i < m; ++i) {
		int64_t mi, ci;
		fastscan(mi, fin);
		fastscan(ci, fin);
		intervals.insert({ci, mi});
	}

	int64_t sol = 0;
	int64_t i = n;
	while (i > 0) {
		auto it = intervals.begin();
		while (it->second < i) {
			++it;
		}
		i -= k;
		sol += it->first;
		intervals.erase(it);
	}

	fprintf(fout, "%ld\n", sol);

	fclose(fin);
	fclose(fout);
	return 0;

}