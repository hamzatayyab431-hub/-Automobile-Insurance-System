#pragma once
#include "../interfaces/IClaimRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FileClaimRepository : public IClaimRepository {
private:
    std::string filename = "data/claims.csv";

    static Claim parse(std::stringstream& ss) {
        std::string cId, pNo, d, desc, stat, appR, wId;
        std::getline(ss, cId, ',');
        std::getline(ss, pNo, ',');
        std::getline(ss, d, ',');
        std::getline(ss, desc, ',');
        std::getline(ss, stat, ',');
        std::getline(ss, appR, ',');
        std::getline(ss, wId, ',');
        int wid_int = wId.empty() ? 0 : std::stoi(wId);
        return Claim(std::stoi(cId), 
                     std::stoi(pNo), 
                     CsvHelper::unescape(d), 
                     CsvHelper::unescape(desc), 
                     CsvHelper::unescape(stat), 
                     CsvHelper::unescape(appR), 
                     wid_int);
    }

public:
    Claim getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const Claim& i){ return i.getClaimId() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Claim not found.");
    }

    std::vector<Claim> getAll() override {
        return CsvHelper::readAll<Claim>(filename, [](std::stringstream& ss){ return parse(ss); });
    }

    int save(const Claim& entity) override {
        auto all = getAll();
        Claim newObj = entity;
        if (newObj.getClaimId() == 0) {
            int m = 0;
            for(const auto& i : all) if(i.getClaimId() > m) m = i.getClaimId();
            newObj.setClaimId(m + 1);
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << newObj.serialize() << "\n";
            file.close();
        }
        return newObj.getClaimId();
    }

    void update(const Claim& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id=entity.getClaimId()](const Claim& i){ return i.getClaimId() == id; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }
    
    std::vector<Claim> findByPolicy(int policyNo) override {
        auto all = getAll();
        std::vector<Claim> res;
        std::copy_if(all.begin(), all.end(), std::back_inserter(res), [policyNo](const Claim& c){ return c.getPolicyNo() == policyNo; });
        return res;
    }

    std::vector<Claim> findPending() override {
        auto all = getAll();
        std::vector<Claim> res;
        std::copy_if(all.begin(), all.end(), std::back_inserter(res), [](const Claim& c){ return c.getStatus() == "Pending"; });
        return res;
    }
};
