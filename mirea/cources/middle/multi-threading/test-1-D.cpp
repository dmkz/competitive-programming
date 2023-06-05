#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>
#include <mutex>
#include <condition_variable>
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
    mt19937 gen;
    // создаём вектор input и заполняем его:
    const int nJobs = 100;
    const int nThreads = thread::hardware_concurrency(); // 16;
    atomic<int> nGenerated{0};
    atomic<int> nProcessed{0};
	vector<long long> input(nJobs+nThreads);
    mutex mtx;
    condition_variable condvar;
    mutex mtx_condvar;
    auto push = [&]()
    {
        lock_guard<mutex> lock(mtx);
        auto number = uniform_int_distribution<long long>(1e17, 1e18)(gen);
        input[nGenerated++] = number;
    };
	
    auto pop = [&]()
    {
        lock_guard<mutex> lock(mtx);
        return nProcessed++;
    };
    
    auto popWithWaiting = [&]()
    {
        unique_lock<mutex> lock(mtx_condvar);
        condvar.wait(lock, [&](){return nProcessed < nGenerated;});
        return pop();
    };
    
    auto pushWithNotify = [&]()
    {
        push();
        condvar.notify_one(); // notify_all();
    };
    
    auto pushFinishSignal = [&]()
    {
        lock_guard<mutex> lock(mtx);
        input[nGenerated++] = -1;
    };
    
	vector<long long> output(nJobs);
    // создаём потоки:
    cout << "nThreads = " << nThreads << endl;
    vector<thread> threads;
    for (int id = 0; id < nThreads; id++)
    {
        threads.emplace_back(
            [threadId = id, &input, &output, &nProcessed, &popWithWaiting]()
            {
                printf("Thread: %d begin\n", threadId);
                long long totalIters = 0;
                while (true) {
                    int i = popWithWaiting();
                    long long x = input[i];
                    if (x == -1)
                        break;
                    auto [answ, iters] = numDisivors(x);
                    output[i] = answ;
                    totalIters += iters;
                }
                printf("Thread: %d end: %lld\n", threadId, totalIters);
            });
    }
    while (nGenerated < nJobs)
        pushWithNotify();
    for (int i = 0; i < nThreads; i++)
        pushFinishSignal();
    // ждать их выполнения:
    for (auto &t : threads)
        if (t.joinable())
            t.join();
    cout << "All threads have been finished!" << endl;
    return 0;
}
