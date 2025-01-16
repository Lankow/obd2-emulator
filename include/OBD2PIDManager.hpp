/**
 * @file OBD2PIDManager.hpp
 * @date   2025-01-12
 * @author Lankow
 * @version 1.0
 */
#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include <Arduino.h>
#include <vector>
#include <memory>
#include "OBD2PIDInfo.hpp"

class OBD2PIDManager
{
    public:
        explicit OBD2PIDManager();

        void updateAll();
        void printAll() const;

    private:
        std::vector<std::unique_ptr<IOBD2PIDInfo>> m_OBD2PIDInfoList;
};
#endif // DATA_STORAGE_HPP