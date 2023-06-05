#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
using namespace std;
using namespace std::literals;

pair<long long, long long> numDisivors(long long x) {
	long long answer = 1;
    long long iterations = 0;
	for (long long p = 2; p * p <= x; p++)
	{
        iterations++;
		if (x % p == 0)
		{
			long long power = 1;
			x /= p;
			while (x % p == 0)
			{
                iterations++;
				power++;
				x /= p;
			}
			answer *= (power+1);
		}
	}
	if (x > 1)
		answer *= 2;
	return {answer, iterations};
}


int main()
{
    // создаём вектор input и заполняем его:
    const int nJobs = 100;
	vector<long long> input(nJobs);
	mt19937 gen;
	for (auto &number : input)
		number = uniform_int_distribution<long long>(1e17, 1e18)(gen);
	vector<long long> output(nJobs);
    // создаём потоки:
    const int nThreads = thread::hardware_concurrency(); // 16;
    cout << "nThreads = " << nThreads << endl;
    const int segLen = (nJobs + nThreads - 1) / nThreads;
    vector<thread> threads;
    for (int id = 0; id < nThreads; id++)
    {
        const int begin = id * segLen;
        const int end = min(begin + segLen, nJobs);
        threads.emplace_back(
            [threadId = id, b = begin, e = end, &input, &output]()
            {
                cout << "Thread: " << threadId << " begin" << endl;
                long long totalIters = 0;
                for (int i = b; i < e; i++)
                {
                    long long x = input[i];
                    auto [answ, iters] = numDisivors(x);
                    output[i] = answ;
                    totalIters += iters;
                }
                cout << "Thread: " << threadId << " end: " << totalIters << endl;
            });
    }
    // ждать их выполнения:
    for (auto &t : threads)
        if (t.joinable())
            t.join();
    cout << "All threads have been finished!" << endl;
    return 0;
}
