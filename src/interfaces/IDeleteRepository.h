#pragma once

template <typename T, typename ID = int>
class IDeleteRepository {
public:
    virtual ~IDeleteRepository() = default;
    virtual void remove(ID id) = 0;
};
