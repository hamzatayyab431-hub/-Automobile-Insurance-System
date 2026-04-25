#pragma once
#include "../interfaces/ICustomerRepository.h"
#include "../interfaces/IVehicleRepository.h"
#include "../interfaces/IPolicyRepository.h"
#include <iostream>

class CustomerService {
private:
    ICustomerRepository& custRepo;
    IVehicleRepository& vehRepo;
    IPolicyRepository& polRepo;

public:
    CustomerService(ICustomerRepository& c, IVehicleRepository& v, IPolicyRepository& p)
        : custRepo(c), vehRepo(v), polRepo(p) {}

    Customer registerCustomer(int salesmanId, const std::string& name, const std::string& contact,
                              const std::string& address, const std::string& regDate) {
        Customer c(0, name, contact, address, regDate, salesmanId);
        c.setId(custRepo.save(c));
        return c;
    }

    Vehicle registerVehicle(int customerId, const std::string& regNo, const std::string& make,
                            const std::string& model, int year) {
        Vehicle v(regNo, make, model, year, customerId);
        vehRepo.save(v);
        return v;
    }

    InsurancePolicy recordPolicy(const std::string& vehicleReg, const std::string& start,
                                 const std::string& end, double premium, double cov) {
        InsurancePolicy p(0, vehicleReg, start, end, premium, cov);
        p.setPolicyNo(polRepo.save(p));
        return p;
    }
};
