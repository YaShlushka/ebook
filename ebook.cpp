#include <iostream> 
#include <string>
#include <unordered_map>
#include <map>
#include <iomanip>

class BookmarksManager {
public:
	void Read(int user, int count) {
		if(user_to_page_.count(user)) {
			int old_page = user_to_page_[user];

			if(--users_on_page_[old_page] == 0) {
				users_on_page_.erase(old_page);
			}
		}

		user_to_page_[user] = count;
		++users_on_page_[count];
	}

	double Cheer(int user) {
		if(!user_to_page_.count(user)) {
			return 0;
		}

		if(user_to_page_.size() == 1) {
			return 1;
		}

		int user_page = user_to_page_[user];
		int count = 0;
		for (auto it = users_on_page_.begin(); it != users_on_page_.end() && it->first < user_page; ++it) {
			count += it->second;
		} // Неэффективный метод, можно уменьшить временную сложность

		return (count * 1.0) / (user_to_page_.size() - 1);
	}
// Неэффективный метод "Cheer", можно уменьшить временную сложность.

private:
	std::map<int, int> users_on_page_;
	std::unordered_map<int, int> user_to_page_;
};

int main() {
	int n;
	std::cin >> n;
	BookmarksManager manager;

	for(int i = 0; i < n; ++i) {
		std::string request_type;
		std::cin >> request_type;

		if(request_type == "READ") {
			int user_name;
			int page;
			std::cin >> user_name >> page;
			manager.Read(user_name, page);
		} else if(request_type == "CHEER") {
			int user_name;
			std::cin >> user_name;

			std::cout << std::setprecision(6) << manager.Cheer(user_name) << std::endl;
		}
	}

	return 0;
}

// Немного странный стиль кода, где-то есть пробелы, а где-то нет.
