#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::literals;
int main()
{
    // cout << "Main thread: " << this_thread::get_id() << endl;
    // создание тредов:
    const int nThreads = 16;
    vector<thread> threads;
    long long count = 0;
    const long long nIncrements = 10000000;
    for (int id = 0; id < nThreads; id++)
        threads.emplace_back(
            [threadId = id, &count, nIncrements]()
            {
                for (int x = nIncrements; x--; )
                    count++;
            });
    // ждать их выполнения:
    for (auto &t : threads)
        if (t.joinable())
            t.join();
    cout << "All threads have been finished!" << endl;
    cout << "count = " << count << " vs " << nThreads * nIncrements << endl;
    return 0;
}
