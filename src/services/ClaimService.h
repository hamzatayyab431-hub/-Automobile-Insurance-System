#pragma once
#include "../interfaces/IClaimRepository.h"
#include "../interfaces/IWorkshopRepository.h"
#include "../interfaces/IPolicyRepository.h"

class ClaimService {
private:
    IClaimRepository& claimRepo;
    IWorkshopRepository& shopRepo;
    IPolicyRepository& polRepo;

public:
    ClaimService(IClaimRepository& c, IWorkshopRepository& s, IPolicyRepository& p)
        : claimRepo(c), shopRepo(s), polRepo(p) {}

    Claim fileClaim(int salesmanId, int policyNo, const std::string& date,
                    const std::string& description, int workshopId) {
        // Validate Policy
        polRepo.getById(policyNo); // Throws if not found
        
        // Validate Workshop if provided
        if (workshopId != 0) {
            shopRepo.getById(workshopId); // Throws if not found
        }
        
        Claim c(0, policyNo, date, description, "Pending", "", workshopId);
        c.setClaimId(claimRepo.save(c));
        return c;
    }

    void approveClaim(int managerId, int claimId, const std::string& reason) {
        Claim c = claimRepo.getById(claimId);
        c.approve(reason);
        claimRepo.update(c);
    }
    
    void rejectClaim(int managerId, int claimId, const std::string& reason) {
        Claim c = claimRepo.getById(claimId);
        c.reject(reason);
        claimRepo.update(c);
    }
};
