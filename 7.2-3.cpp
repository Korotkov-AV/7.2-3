// 7.2-3.cpp 


#include <iostream>
#include<thread>
#include<mutex>

class Data {
public:
	int a;
	int b;
	std::mutex mA;
	std::mutex mB;

	Data(int a, int b) {
		this->a = a;
		this->b = b;
	}

	void show() {
		std::cout << "a= " << a << ", b= " << b << std::endl;
	}
};

void swap_lock(int& a, int& b, Data& ob) {
	ob.mA.lock();
	ob.mB.lock();

	std::swap(a, b);
	std::cout << "*swap*" << std::endl;

	ob.mA.unlock();
	ob.mB.unlock();
}

void swap_uniquelock(int& a, int& b, Data& ob) {
	std::unique_lock locA{ ob.mA };
	std::unique_lock locB{ ob.mB };

	std::swap(a, b);
	std::cout << "*swap*" << std::endl;
}

void swap_scopedlock(int& a, int& b, Data& ob) {
	std::scoped_lock loc{ ob.mA, ob.mB };

	std::swap(a, b);
	std::cout << "*swap*" << std::endl;
}

int main()
{
	Data numbers(1, 2);
	numbers.show();

	swap_lock(numbers.a, numbers.b, numbers);
	numbers.show();

	swap_uniquelock(numbers.a, numbers.b, numbers);
	numbers.show();

	swap_scopedlock(numbers.a, numbers.b, numbers);
	numbers.show();

	return 0;
}
