#include <iostream>
#include <mutex>


class Data {
public:
	Data(int scalarData) : scalarData(scalarData) {}

	int getScalarData() const {
		return scalarData;
	}

	void setScalarData(int newData) {
		scalarData = newData;
	}
	std::mutex mutex;
private:
	int scalarData;
};


void swap_lock(Data& data1, Data& data2) {
	std::lock(data1.mutex, data2.mutex);
	std::lock_guard<std::mutex> lock1(data1.mutex, std::adopt_lock);
	std::lock_guard<std::mutex> lock2(data2.mutex, std::adopt_lock);

	int temp = data1.getScalarData();
	data1.setScalarData(data2.getScalarData());
	data2.setScalarData(temp);
}

void swap_scoped_lock(Data& data1, Data& data2) {
	std::scoped_lock lock(data1.mutex, data2.mutex);
	int temp = data1.getScalarData();
	data1.setScalarData(data2.getScalarData());
	data2.setScalarData(temp);
}

void swap_unique_lock(Data& data1, Data& data2) {
	std::unique_lock<std::mutex> lock1(data1.mutex, std::defer_lock);
	std::unique_lock<std::mutex> lock2(data2.mutex, std::defer_lock);
	std::lock(lock1, lock2);

	int temp = data1.getScalarData();
	data1.setScalarData(data2.getScalarData());
	data2.setScalarData(temp);
}

int main(int argc, char** argv) {
	return 0;
}