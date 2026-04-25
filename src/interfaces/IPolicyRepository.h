#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "../models/InsurancePolicy.h"

class IPolicyRepository : public IReadRepository<InsurancePolicy>,
                          public IWriteRepository<InsurancePolicy> {
public:
    virtual ~IPolicyRepository() = default;
};
