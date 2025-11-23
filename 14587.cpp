#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

int main() {
    int memory_size, query_count;
    cin >> memory_size >> query_count;

    list<pair<string, string>> memory; // {name, lucky number}
    unordered_map<string, list<pair<string, string>>::iterator> mem_map;

    for (int i = 0; i < query_count; ++i) {
        string command;
        cin >> command;

        if (command == "ADD") {
            string name, num;
            cin >> name >> num;

            // No duplicates guaranteed for ADD
            if (mem_map.size() == memory_size) {
                // Remove least recently used
                auto lru = memory.back();
                mem_map.erase(lru.first);
                memory.pop_back();
            }

            // Insert at front
            memory.push_front({name, num});
            mem_map[name] = memory.begin();

        } else if (command == "ASK") {
            string name;
            cin >> name;

            if (mem_map.find(name) != mem_map.end()) {
                // Move to front
                auto it = mem_map[name];
                string num = it->second;
                memory.erase(it);
                memory.push_front({name, num});
                mem_map[name] = memory.begin();
                cout << num << endl;
            } else {
                cout << "Who?" << endl;
            }
        }
    }

    return 0;
}
