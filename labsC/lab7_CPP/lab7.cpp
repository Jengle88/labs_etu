#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define STR_SIZE 3001

class CustomStack {

public:
	CustomStack() {
		this->capacity = 5;
		this->mData = new char *[capacity]();
		this->ind = -1;
		this->allocatedData = 0;
	}

	~CustomStack() {
		for (int i = 0; i < allocatedData; ++i)
			delete[] mData[i];
		delete[] mData;
	}

	void push(const char *val) {
		if (ind + 1 == capacity)
			extend(capacity);
		else
			delete[] mData[ind + 1];
		mData[++ind] = new char[strlen(val) + 1];
		if (ind + 1 > allocatedData)
			allocatedData++;
		strcpy(mData[ind], val);
	}

	void pop() {
		if (empty()) {
			cerr << "Bad pop\n";
			return;
		}
		ind--;
	}

	char* top() const {
		if (empty()) {
			cerr << "Empty stack\n";
			return nullptr;
		}
		else
			return mData[ind];
	}

	size_t size() const {
		return ind + 1;
	}

	bool empty() const {
		return ind == -1;
	}

private:
	void extend(int n) {
		char **temp = new char *[size() + n]();
		for (int i = 0; i < size(); ++i) {
			temp[i] = mData[i];
		}
		delete[] mData;
		mData = temp;
		capacity += n;
	}
protected:
	char **mData;
	int ind;
	int capacity;
	int allocatedData;
};



int main() {
	freopen("input.txt", "r", stdin);
	CustomStack stack = CustomStack();
	char str[STR_SIZE];
	fgets(str, STR_SIZE, stdin);
	char *lstr = strchr(str, '<');
	char *rstr = strchr(str, '>');
	bool is_right = true;
	while (lstr != nullptr && rstr != nullptr) {
		lstr++;
		if (strncmp(lstr, "br", 2) == 0 || strncmp(lstr, "hr", 2) == 0) {
			lstr = strchr(rstr + 1, '<'), rstr = strchr(rstr + 1, '>');
			continue;
		}
		if (*lstr == '/') {
			if (strncmp(stack.top(), lstr + 1, rstr - lstr - 1) == 0)
				stack.pop();
			else {
				is_right = false;
				break;
			}
		}
		else
			stack.push(lstr);

		lstr = strchr(rstr + 1, '<'), rstr = strchr(rstr + 1, '>');
	}
	if (is_right && stack.empty())
		cout << "correct";
	else
		cout << "wrong";
	return 0;
}
