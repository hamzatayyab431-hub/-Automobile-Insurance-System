#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

class CsvHelper {
public:
    template <typename T>
    static std::vector<T> readAll(const std::string& filename, std::function<T(std::stringstream&)> parser) {
        std::vector<T> items;
        std::ifstream file(filename);
        if (!file.is_open()) return items;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            items.push_back(parser(ss));
        }
        return items;
    }

    template <typename T>
    static void writeAll(const std::string& filename, const std::vector<T>& items) {
        std::ofstream file(filename);
        for (const auto& i : items) {
            file << i.serialize() << "\n";
        }
    }
    static std::string escape(std::string str) {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

    static std::string unescape(std::string str) {
        for (char& c : str) if (c == ';') c = ',';
        return str;
    }
};
