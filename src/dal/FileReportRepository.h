#pragma once
#include "../interfaces/IReportRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FileReportRepository : public IReportRepository {
private:
    std::string filename = "data/reports.csv";

    static InspectionReport parse(std::stringstream& ss) {
        std::string id, cId, sId, d, desc, cost;
        std::getline(ss, id, ',');
        std::getline(ss, cId, ',');
        std::getline(ss, sId, ',');
        std::getline(ss, d, ',');
        std::getline(ss, desc, ',');
        std::getline(ss, cost, ',');
        return InspectionReport(std::stoi(id), 
                                std::stoi(cId), 
                                std::stoi(sId), 
                                CsvHelper::unescape(d), 
                                CsvHelper::unescape(desc), 
                                std::stod(cost));
    }

public:
    InspectionReport getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const InspectionReport& i){ return i.getReportId() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Report not found.");
    }

    std::vector<InspectionReport> getAll() override {
        return CsvHelper::readAll<InspectionReport>(filename, [](std::stringstream& ss){ return parse(ss); });
    }

    int save(const InspectionReport& entity) override {
        auto all = getAll();
        InspectionReport newObj = entity;
        if (newObj.getReportId() == 0) {
            int m = 0;
            for(const auto& i : all) if(i.getReportId() > m) m = i.getReportId();
            newObj.setReportId(m + 1);
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << newObj.serialize() << "\n";
            file.close();
        }
        return newObj.getReportId();
    }

    void update(const InspectionReport& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id=entity.getReportId()](const InspectionReport& i){ return i.getReportId() == id; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }
    
    InspectionReport findByClaim(int claimId) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [claimId](const InspectionReport& r){ return r.getClaimId() == claimId; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Report not found for claim.");
    }
};
