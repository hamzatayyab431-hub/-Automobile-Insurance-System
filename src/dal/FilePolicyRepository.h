#pragma once
#include "../interfaces/IPolicyRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FilePolicyRepository : public IPolicyRepository {
private:
    std::string filename = "data/policies.csv";

    static InsurancePolicy parse(std::stringstream& ss) {
        std::string pNo, vReg, start, end, prem, cov;
        std::getline(ss, pNo, ',');
        std::getline(ss, vReg, ',');
        std::getline(ss, start, ',');
        std::getline(ss, end, ',');
        std::getline(ss, prem, ',');
        std::getline(ss, cov, ',');
        return InsurancePolicy(std::stoi(pNo), 
                               CsvHelper::unescape(vReg), 
                               CsvHelper::unescape(start), 
                               CsvHelper::unescape(end), 
                               std::stod(prem), 
                               std::stod(cov));
    }

public:
    InsurancePolicy getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const InsurancePolicy& i){ return i.getPolicyNo() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Policy not found.");
    }

    std::vector<InsurancePolicy> getAll() override {
        return CsvHelper::readAll<InsurancePolicy>(filename, [](std::stringstream& ss){ return parse(ss); });
    }

    int save(const InsurancePolicy& entity) override {
        auto all = getAll();
        InsurancePolicy newObj = entity;
        if (newObj.getPolicyNo() == 0) {
            int m = 0;
            for(const auto& i : all) if(i.getPolicyNo() > m) m = i.getPolicyNo();
            newObj.setPolicyNo(m + 1);
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << newObj.serialize() << "\n";
            file.close();
        }
        return newObj.getPolicyNo();
    }

    void update(const InsurancePolicy& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id=entity.getPolicyNo()](const InsurancePolicy& i){ return i.getPolicyNo() == id; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }
};
