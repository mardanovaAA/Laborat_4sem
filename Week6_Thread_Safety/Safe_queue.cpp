#include <iostream>
#include <thread>
#include <queue>
#include <mutex>


template <typename A>
class queue_thread_safety{
private:
	std::queue<A> base_queue;
	std::mutex mutex;

public:
	queue_thread_safety(std::queue<A> q): base_queue(q){};
	queue_thread_safety(): base_queue(){};

	void push(A value){
		mutex.lock();
		base_queue.push(value);
		mutex.unlock();
	}

	void pop(){
		mutex.lock();
		base_queue.pop();
		mutex.unlock();
	}

	void print_first(){
		mutex.lock();

		std::cout << base_queue.front() << std::endl;

		mutex.unlock();
	}

};

int main(){
	// queue_thread_safety<int> Queue;

	// std::thread first (&queue_thread_safety<int>::push, std::ref(Queue), 5);
	// std::thread second (&queue_thread_safety<int>::push, std::ref(Queue), 15);
	// first.join();
	// second.join();

	// std::thread third (&queue_thread_safety<int>::print_first, std::ref(Queue));
	// std::thread fourth (&queue_thread_safety<int>::print_first, std::ref(Queue));
	// Queue.pop();
	// third.join();
	// fourth.join();

}