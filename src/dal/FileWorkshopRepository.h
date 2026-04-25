#pragma once
#include "../interfaces/IWorkshopRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FileWorkshopRepository : public IWorkshopRepository {
private:
    std::string filename = "data/workshops.csv";

    static Workshop parse(std::stringstream& ss) {
        std::string idStr, n, loc;
        std::getline(ss, idStr, ',');
        std::getline(ss, n, ',');
        std::getline(ss, loc, ',');
        return Workshop(std::stoi(idStr), 
                        CsvHelper::unescape(n), 
                        CsvHelper::unescape(loc));
    }

public:
    Workshop getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const Workshop& i){ return i.getId() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Workshop not found.");
    }

    std::vector<Workshop> getAll() override {
        return CsvHelper::readAll<Workshop>(filename, [](std::stringstream& ss){ return parse(ss); });
    }

    int save(const Workshop& entity) override {
        auto all = getAll();
        Workshop newObj = entity;
        if (newObj.getId() == 0) {
            int m = 0;
            for(const auto& i : all) if(i.getId() > m) m = i.getId();
            newObj.setId(m + 1);
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << newObj.serialize() << "\n";
            file.close();
        }
        return newObj.getId();
    }

    void update(const Workshop& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id=entity.getId()](const Workshop& i){ return i.getId() == id; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }
    
    void remove(int id) override {
        auto all = getAll();
        all.erase(std::remove_if(all.begin(), all.end(), [id](const Workshop& w){ return w.getId() == id; }), all.end());
        CsvHelper::writeAll(filename, all);
    }
};
