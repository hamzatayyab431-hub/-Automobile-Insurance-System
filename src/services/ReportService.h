#pragma once
#include "../interfaces/ICustomerRepository.h"
#include "../interfaces/IClaimRepository.h"
#include "../interfaces/IReportRepository.h"
#include "../interfaces/IVehicleRepository.h"
#include "../interfaces/IPolicyRepository.h"
#include <algorithm>

class ReportService {
private:
    ICustomerRepository& custRepo;
    IClaimRepository& claimRepo;
    IReportRepository& reportRepo;
    IVehicleRepository& vehRepo;
    IPolicyRepository& polRepo;

public:
    ReportService(ICustomerRepository& c, IClaimRepository& cl, IReportRepository& r,
                  IVehicleRepository& v, IPolicyRepository& p)
        : custRepo(c), claimRepo(cl), reportRepo(r), vehRepo(v), polRepo(p) {}

    std::vector<Customer> getNewCustomersInMonth(int salesmanId, const std::string& month) {
        std::vector<Customer> res;
        auto all = custRepo.getAll();
        for (const auto& c : all) {
            bool matchesSalesman = (salesmanId == 0 || c.getSalesmanId() == salesmanId);
            bool matchesMonth = (month.empty() || c.getRegistrationDate().find(month) != std::string::npos);
            if (matchesSalesman && matchesMonth) {
                res.push_back(c);
            }
        }
        return res;
    }

    std::vector<Claim> getPendingClaims() {
        return claimRepo.findPending();
    }

    std::vector<Claim> getClaimHistory(int customerId) {
        std::vector<Claim> history;
        std::vector<std::string> customerVehicleRegs;

        // 1. Get only this customer's vehicles
        for (const auto& v : vehRepo.getAll()) {
            if (v.getCustomerId() == customerId) {
                customerVehicleRegs.push_back(v.getRegNumber());
            }
        }

        if (customerVehicleRegs.empty()) return history;

        // 2. Get policies ONLY for those vehicles
        std::vector<int> customerPolicyNos;
        for (const auto& p : polRepo.getAll()) {
            if (std::find(customerVehicleRegs.begin(), customerVehicleRegs.end(), p.getVehicleReg()) != customerVehicleRegs.end()) {
                customerPolicyNos.push_back(p.getPolicyNo());
            }
        }

        if (customerPolicyNos.empty()) return history;

        // 3. Get claims ONLY for those policies
        for (const auto& c : claimRepo.getAll()) {
            if (std::find(customerPolicyNos.begin(), customerPolicyNos.end(), c.getPolicyNo()) != customerPolicyNos.end()) {
                history.push_back(c);
            }
        }
        return history;
    }

    InspectionReport getInspectionReport(int claimId) {
        return reportRepo.findByClaim(claimId);
    }
};
