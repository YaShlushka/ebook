#include <iostream> 
#include <string>
#include <unordered_map>
#include <map>
#include <iomanip>

class BookmarksManager {
private:
    std::map<int, int> users_on_page_;
    std::unordered_map<int, int> user_to_page_;
    
    mutable std::map<int, int> prefix_sums_;
    mutable bool cache_valid_ = false;
    
    void UpdatePrefixSums() const {
        if (cache_valid_) {
            return;
        }
        
        prefix_sums_.clear();
        int running_sum = 0;
        
        for (const auto& [page, user_count] : users_on_page_) {
            running_sum += user_count;
            prefix_sums_[page] = running_sum;
        }
        
        cache_valid_ = true;
    }

public:
    void Read(int user, int page) {
        if (user_to_page_.count(user)) {
            int old_page = user_to_page_[user];

            if (--users_on_page_[old_page] == 0) {
                users_on_page_.erase(old_page);
            }
        }

        user_to_page_[user] = page;
        ++users_on_page_[page];
        
        cache_valid_ = false;
    }

    double Cheer(int user) {
        if (!user_to_page_.count(user)) {
            return 0;
        }
        
        if (user_to_page_.size() == 1) {
            return 1;
        }
        
        UpdatePrefixSums();
        
        int user_page = user_to_page_[user];
        
        auto it = prefix_sums_.lower_bound(user_page);
        int count= 0;
        
        if (it != prefix_sums_.begin()) {
            --it;
            count = it->second;
        }
        
        return (count* 1.0) / (user_to_page_.size() - 1);
    }
};

int main() {
    int n;
    std::cin >> n;
    BookmarksManager manager;

    for (int i = 0; i < n; ++i) {
        std::string request_type;
        std::cin >> request_type;

        if (request_type == "READ") {
            int user_name;
            int page;
            std::cin >> user_name >> page;
            manager.Read(user_name, page);
        } else if (request_type == "CHEER") {
            int user_name;
            std::cin >> user_name;

            std::cout << std::setprecision(6) << manager.Cheer(user_name) << std::endl;
        }
    }

    return 0;
}
