#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <atomic>
using namespace std;

long long numDisivors(long long x) {
	long long answer = 1;
	for (long long p = 2; p * p <= x; p++)
	{
		if (x % p == 0)
		{
			long long power = 1;
			x /= p;
			while (x % p == 0)
			{
				power++;
				x /= p;
			}
			answer *= (power+1);
		}
	}
	if (x > 1)
		answer *= 2;
	return answer;
}

int main() {
	double start = clock();
	// каждый поток будет считать число делителей рандомного числа порядка 10^18
	const int nJobs = 100;
	vector<long long> input(nJobs);
	mt19937 gen;
	for (auto &number : input)
		number = uniform_int_distribution<long long>(1e17, 1e18)(gen);
	vector<long long> output(nJobs);
	atomic<int> globalPosition{0};
	mutex mtx; // объект синхронизации потоков
	const int nThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads = " << nThreads << std::endl;
	vector<thread> threads;
	// создаём потоки, передавая лямбда-функцию: они будут выполнять её
	for (int id = 0; id < nThreads; id++) {
		threads.emplace_back([&input, &mtx, &output, &globalPosition, threadId = id]()
		{
			{
				// cout один на все потоки, поэтому необходимо залочить
				// при помощи mtx + lock_guard. Доступ будет залочен до следующей
				// закрывающей скобки
				lock_guard<mutex> lock(mtx);
				cout << "Thread " << threadId << " has been launched!" << endl;
			}
			// position это atomic<int>, поэтому увеличение происходит атомарно
			// и копирования в pos происходит атомарно
			int completed = 0;
			for (int threadPos; (threadPos = globalPosition++) < nJobs; )
			{
				long long number = input[threadPos];
				output[threadPos] = numDisivors(number);
				completed++;
			}
			{
				lock_guard<mutex> lock(mtx);
				cout << "Thread " << threadId << " completed "
				     << completed << " factorizations and has been finished!" << endl;
			}
		});
	}
	for (auto &t : threads)
		t.join();
	cout << "runtime = " << (clock() - start) / CLOCKS_PER_SEC << endl;
	return 0;
}
