/**
 * @file OBDHandler.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "OBDHandler.hpp"
#include "Constants.hpp"
#include "Configurator.hpp"

OBDHandler::OBDHandler()
{
    addNewInfo(0x010C, 2, "Engine Speed", 0.0f, 0.0f, 16383.75f, 100.0f, 1,
               [this](const float &current) -> int32_t
               {
                   int32_t scaledValue = static_cast<int32_t>(current * 4);
                   uint8_t A = (scaledValue / 256) & 0xFF;
                   uint8_t B = scaledValue % 256;

                   int32_t result = (A << 8) | B;

                   Serial.println("Formula Engine Speed:");
                   Serial.println(result);

                   return result;
               });

    addNewInfo(0x010D, 1, "Vehicle Speed", 0, 0, 255, 1, 1, NO_CUSTOM_GETTER);
}

void OBDHandler::updateAll()
{
    for (auto &info : m_infos)
    {
        if (Configurator::getCycleCount() % info.getPace() == 0)
        {
            info.update();
        }
    }
}

void OBDHandler::cyclic()
{
    updateAll();
    if (Configurator::isAdditionalDebugEnabled())
    {
        printAll();
    }
}

void OBDHandler::printAll() const
{
    for (const auto &info : m_infos)
    {
        info.printCurrent();
    }
}

std::vector<OBDInfo>& OBDHandler::getAll()
{
    return m_infos;
}

OBDInfo *OBDHandler::getByPid(uint16_t pid)
{
    for (auto &info : m_infos)
    {
        if (info.getPid() == pid)
            return &info;
    }

    return nullptr;
}

const OBDInfo *OBDHandler::getByIndex(uint8_t index) const
{
    if (m_infos.empty())
    {
        return nullptr;
    }

    uint8_t indexToDisplay = index % static_cast<uint8_t>(m_infos.size());
    return &m_infos.at(indexToDisplay);
}

void OBDHandler::addNewInfo(uint16_t pid, uint8_t length, std::string description, double current,
                            double min, double max, double increment, uint32_t pace,
                            std::function<int32_t(const double &)> customGetter)
{
    m_infos.push_back(OBDInfo(pid, length, description, current, min, max, increment, pace, customGetter));
}