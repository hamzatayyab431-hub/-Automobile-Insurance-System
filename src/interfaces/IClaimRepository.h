#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "../models/Claim.h"
#include <vector>

class IClaimRepository : public IReadRepository<Claim>,
                         public IWriteRepository<Claim> {
public:
    virtual ~IClaimRepository() = default;
    virtual std::vector<Claim> findByPolicy(int policyNo) = 0;
    virtual std::vector<Claim> findPending() = 0;
};
