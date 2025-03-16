/**
 * @file OBDHandler.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "OBDHandler.hpp"

OBDHandler::OBDHandler(std::shared_ptr<CycleHandler> cycleHandler,
                       std::shared_ptr<Configuration> configuration) : m_cycleHandler(cycleHandler),
                                                                       m_configuration(configuration)
{
    m_infos = configuration->getObdInfoList();

    addCustomGetterFormula(0x010C, [this](const float &current) -> int32_t
                           {
                   int32_t scaledValue = static_cast<int32_t>(current * 4);
                   uint8_t A = (scaledValue / 256) & 0xFF;
                   uint8_t B = scaledValue % 256;

                   int32_t result = (A << 8) | B;

                   Serial.println("Formula Engine Speed:");
                   Serial.println(result);

                   return result; });
}

void OBDHandler::updateAll()
{
    for (auto &info : m_infos)
    {
        if (m_cycleHandler->getCycleCount() % info.m_pace == 0)
        {
            update(info);
        }
    }
}

void OBDHandler::cyclic()
{
    updateAll();
    if (m_configuration->getAdditionalDebug())
    {
        printAll();
    }
}

void OBDHandler::printAll() const
{
    for (const auto &info : m_infos)
    {
        Serial.println("---------------");
        Serial.println(info.m_description.c_str());
        Serial.println("Pid: " + String(info.m_pid));
        Serial.println("Length: " + String(info.m_length));
        Serial.println("Current: " + String(info.m_current));
        Serial.println("Min: " + String(info.m_min));
        Serial.println("Max: " + String(info.m_max));
        Serial.println("Pace: " + String(info.m_pace));
        Serial.println("Increment: " + String(info.m_increment));
        Serial.println("---------------");
    }
}

std::vector<OBDInfo> &OBDHandler::getAll()
{
    return m_infos;
}

OBDInfo *OBDHandler::getByPid(uint16_t pid)
{
    for (auto &info : m_infos)
    {
        if (info.m_pid == pid)
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

void OBDHandler::addCustomGetterFormula(uint16_t pid, std::function<int32_t(const double &)> customGetter)
{
    OBDInfo *info = getByPid(pid);
    if (info != nullptr)
    {
        info->m_formulaGetter = customGetter;
    }
}

void OBDHandler::update(OBDInfo &info)
{
    if (info.m_increasing)
    {
        info.m_current += info.m_increment;
        if (info.m_current >= info.m_max)
        {
            info.m_current = info.m_max;
            info.m_increasing = false;
        }
    }
    else
    {
        info.m_current -= info.m_increment;
        if (info.m_current <= info.m_min)
        {
            info.m_current = info.m_min;
            info.m_increasing = true;
        }
    }
}

uint32_t OBDHandler::getFormula(const OBDInfo &info) const
{
    if (info.m_formulaGetter)
    {
        return info.m_formulaGetter(info.m_current);
    }

    return info.m_current;
}

bool OBDHandler::setMin(OBDInfo &info, double min)
{
    if (min <= info.m_max && min >= info.m_defaultMin)
    {
        info.m_min = min;
        return true;
    }

    return false;
}

bool OBDHandler::setMax(OBDInfo &info, double max)
{
    if (max >= info.m_min && max <= info.m_defaultMax)
    {
        info.m_max = max;
        return true;
    }

    return false;
}

bool OBDHandler::setIncrement(OBDInfo &info, double increment)
{
    if (increment >= info.m_defaultMin && increment <= info.m_defaultMax)
    {
        info.m_increment = increment;
        return true;
    }

    return false;
}

bool OBDHandler::setPace(OBDInfo &info, uint32_t pace)
{
    if (pace >= 0)
    {
        info.m_pace = pace;
        return true;
    }

    return false;
}