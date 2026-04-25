#pragma once
#include "../interfaces/IStaffRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <iostream>
#include <fstream>

class FileStaffRepository : public IStaffRepository {
private:
    std::string filename = "data/staff.csv";

public:
    std::shared_ptr<Staff> getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const std::shared_ptr<Staff>& s){ return s->getId() == id; });
        if (it != all.end()) return *it;
        return nullptr;
    }

    std::vector<std::shared_ptr<Staff>> getAll() override {
        return CsvHelper::readAll<std::shared_ptr<Staff>>(filename, [](std::stringstream& ss) -> std::shared_ptr<Staff> {
            std::string idStr, name, user, pass, role;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, user, ',');
            std::getline(ss, pass, ',');
            std::getline(ss, role, ',');
            
            int id = std::stoi(idStr);
            std::string n = CsvHelper::unescape(name);
            std::string u = CsvHelper::unescape(user);
            std::string p = CsvHelper::unescape(pass);

            if (role == "Manager") return std::make_shared<Manager>(id, n, u, p);
            if (role == "Salesman") return std::make_shared<Salesman>(id, n, u, p);
            if (role == "Surveyor") return std::make_shared<Surveyor>(id, n, u, p);
            return nullptr;
        });
    }
    
    void seedInitial() {
        std::ofstream file(filename);
        file << "1,Alice Manager,alice,pass123,Manager\n";
        file << "2,Bob Salesman,bob,pass123,Salesman\n";
        file << "3,Charlie Surveyor,charlie,pass123,Surveyor\n";
    }
};
