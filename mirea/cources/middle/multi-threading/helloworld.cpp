#include <iostream>
#include <vector>
#include <thread>
int main() {
	const int nThreads = 16;
	std::vector<std::thread> threads;
	for (int id = 0; id < nThreads; id++)
		threads.emplace_back([threadId = id]()
		{
			std::cout << "Hello, world! #" << threadId << std::endl;
		});
	for (auto &t : threads)
		if (t.joinable())
			t.join();
	std::cout << "All of the threads have been finished!" << std::endl;
	return 0;
}
