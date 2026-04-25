#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "IDeleteRepository.h"
#include "../models/Workshop.h"

class IWorkshopRepository : public IReadRepository<Workshop>,
                            public IWriteRepository<Workshop>,
                            public IDeleteRepository<Workshop> {
public:
    virtual ~IWorkshopRepository() = default;
};
