#pragma once
#include "../interfaces/IReportRepository.h"
#include "../interfaces/IClaimRepository.h"
#include <stdexcept>

class InspectionService {
private:
    IReportRepository& reportRepo;
    IClaimRepository& claimRepo;

public:
    InspectionService(IReportRepository& r, IClaimRepository& c)
        : reportRepo(r), claimRepo(c) {}

    InspectionReport submitReport(int surveyorId, int claimId, const std::string& date,
                                  const std::string& description, double estimatedCost) {
        // Validate if claim exists
        Claim c = claimRepo.getById(claimId);
        if (c.getStatus() != "Pending") {
            throw std::runtime_error("Can only inspect Pending claims.");
        }
        
        InspectionReport report(0, claimId, surveyorId, date, description, estimatedCost);
        report.setReportId(reportRepo.save(report));
        
        // Update claim status
        c.inspect();
        claimRepo.update(c);
        
        return report;
    }
};
