#define TESTING

void test(int answer, int (*solve)(int, std::vector<int>), int size, std::vector<int> tree) {
	try {
		int result = (*solve)(size, tree);
		if (result != answer) {
			throw std::runtime_error("Exception, " + std::to_string(result) + " != " + std::to_string(answer));
		}
	} catch (std::runtime_error error) {
		std::cout << error.what() << '\n';
		return;
	}
	std::cout << "OK\n";
}