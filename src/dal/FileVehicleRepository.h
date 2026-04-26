#pragma once
#include "../interfaces/IVehicleRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FileVehicleRepository : public IVehicleRepository {
private:
    std::string filename = "data/vehicles.csv";

    Vehicle parse(std::stringstream& ss) {
        std::string regNo, make, model, yearStr, custId;
        std::getline(ss, regNo, ',');
        std::getline(ss, make, ',');
        std::getline(ss, model, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, custId, ',');
        return Vehicle(CsvHelper::unescape(regNo), 
                       CsvHelper::unescape(make), 
                       CsvHelper::unescape(model), 
                       std::stoi(yearStr), 
                       std::stoi(custId));
    }

public:
    Vehicle getById(std::string id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [&id](const Vehicle& v){ return v.getRegNumber() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Vehicle not found.");
    }
    
    std::vector<Vehicle> getAll() override {
        return CsvHelper::readAll<Vehicle>(filename, [this](std::stringstream& ss){ return parse(ss); });
    }

    std::string save(const Vehicle& entity) override {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << entity.serialize() << "\n";
            file.close();
        }
        return entity.getRegNumber();
    }

    void update(const Vehicle& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [regNo=entity.getRegNumber()](const Vehicle& v){ return v.getRegNumber() == regNo; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }

    void remove(std::string id) override {
        auto all = getAll();
        all.erase(std::remove_if(all.begin(), all.end(), [&id](const Vehicle& v){ return v.getRegNumber() == id; }), all.end());
        CsvHelper::writeAll(filename, all);
    }
};
