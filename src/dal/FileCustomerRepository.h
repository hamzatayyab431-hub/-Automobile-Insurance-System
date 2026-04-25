#pragma once
#include "../interfaces/ICustomerRepository.h"
#include "CsvHelper.h"
#include <algorithm>
#include <fstream>

class FileCustomerRepository : public ICustomerRepository {
private:
    std::string filename = "data/customers.csv";

    static Customer parse(std::stringstream& ss) {
        std::string id, name, contact, address, regDate, salesmanId;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, contact, ',');
        std::getline(ss, address, ',');
        std::getline(ss, regDate, ',');
        std::getline(ss, salesmanId, ',');
        return Customer(std::stoi(id), 
                        CsvHelper::unescape(name), 
                        CsvHelper::unescape(contact), 
                        CsvHelper::unescape(address), 
                        CsvHelper::unescape(regDate), 
                        std::stoi(salesmanId));
    }

public:
    Customer getById(int id) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id](const Customer& c){ return c.getId() == id; });
        if (it != all.end()) return *it;
        throw std::runtime_error("Customer not found.");
    }

    std::vector<Customer> getAll() override {
        return CsvHelper::readAll<Customer>(filename, [](std::stringstream& ss){ return parse(ss); });
    }

    int save(const Customer& entity) override {
        auto all = getAll();
        Customer newObj = entity;
        if (newObj.getId() == 0) {
            int maxId = 0;
            for(const auto& c : all) if(c.getId() > maxId) maxId = c.getId();
            newObj.setId(maxId + 1);
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << newObj.serialize() << "\n";
            file.close();
        }
        return newObj.getId();
    }

    void update(const Customer& entity) override {
        auto all = getAll();
        auto it = std::find_if(all.begin(), all.end(), [id=entity.getId()](const Customer& c){ return c.getId() == id; });
        if (it != all.end()) {
            *it = entity;
            CsvHelper::writeAll(filename, all);
        }
    }

    void remove(int id) override {
        auto all = getAll();
        all.erase(std::remove_if(all.begin(), all.end(), [id](const Customer& c){ return c.getId() == id; }), all.end());
        CsvHelper::writeAll(filename, all);
    }

    std::vector<Customer> findBySalesmanAndMonth(int salesmanId, const std::string& month) override {
        auto all = getAll();
        std::vector<Customer> result;
        std::copy_if(all.begin(), all.end(), std::back_inserter(result), [&](const Customer& c){
            return c.getSalesmanId() == salesmanId && c.getRegistrationDate().find(month) != std::string::npos;
        });
        return result;
    }
};
