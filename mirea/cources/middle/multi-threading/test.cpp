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
    for (int id = 0; id < nThreads; id++)
        threads.emplace_back(
            [threadId = id]()
            {
                this_thread::sleep_for(100ms);
                cout << "Thread: " << threadId << " has been created!\n";
                cout << "Ttread: " << threadId << " Hello, world!\n";
                cout << "Thread: " << threadId << " has been finished!\n";
            });
    // ждать их выполнения:
    for (auto &t : threads)
        if (t.joinable())
            t.join();
    cout << "All threads have been finished!" << endl;
    return 0;
}
