#include <iostream>
#include <iomanip>
using namespace std;

int list[3] = { 0 };
int beg = 0, cnt = 0;

bool push(int num) {
	if (3 == cnt) {
		//pop();
		return false;
	}
	list[(beg + cnt) % 3] = num;
	cnt++;
	return true;
}

void pop() {
	if (0 == cnt) {
		return;
	}
	beg = (beg + 1) % 3;
	cnt--;
}

int get(int num) {
	if (num > 4 || num < 0) return -1;
	return list[(beg + num - 1) % 3];
}

void clear() {
	cnt = 0;
}

void print(int round, int result[]) {
	round = (round > 10) ? 10 : round;
	cout << "ROUND#" << round << endl;
	cout << setw(7) << "Round";
	for (int i = 0; i < round; i++) {
		cout << setw(4) << i + 1;
	}
	cout << endl << setw(7) << " ";
	for (int i = 0; i < round; i++) {
		cout << setw(4) << result[i];
	}
	int total = 0;
	cout << endl << setw(7) << "TOTAL";
	for (int i = 0; i < round; i++) {
		total += result[i];
		cout << setw(4) << total;
	}
	cout << endl << endl;
}

int main() {
	int result[12] = { 0 };

	int round = 0;
	int hits = 0;

	while (round < 12) {
		cin >> hits;

		result[round] += hits;
		push(hits);
		
		if (2 == cnt) {
			result[round - 1] += hits;
		}
		else if (3 == cnt) {
			result[round - 1] += hits;
			if (get(1) == 10) {
				result[round - 2] += hits;
				pop();
			}
			else {
				pop(); pop();
			}
		}
		print(round+1, result);
		if (10 == hits) {
			round++;
			continue;
		}
		
		cin >> hits;
		result[round] += hits;
		push(hits);
		if (2 == cnt) {
			if (10 != result[round]) {
				clear();
			}
		}
		else if (3 == cnt) {
			result[round - 1] += hits;
			if (10 != result[round]) {
				clear();
			}
			else { pop(); }
		}
		print(round+1, result);
		round++;
	}
}