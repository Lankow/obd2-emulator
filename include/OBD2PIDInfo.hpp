/**
 * @file OBD2PIDInfo.hpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#ifndef OBD2_PID_INFO_HPP
#define OBD2_PID_INFO_HPP

class OBD2PIDInfo
{
public:
    OBD2PIDInfo(std::string description, uint8_t length, double current,
                double min, double max, double increment, int pace,
                std::function<int32_t(const double &current)> formulaGetter = nullptr);

    void update();
    void printCurrent() const;
    const std::string &getDescription() const;
    uint32_t getFormula() const;
    uint8_t getLength() const;

    double getCurrent() const;
    double getMin() const;
    double getMax() const;
    double getDefaultMin() const;
    double getDefaultMax() const;

    void setMin(double min);
    void setMax(double max);

private:
    std::string m_description;
    uint8_t m_length;

    double m_current;
    double m_defaultMin;
    double m_min;
    double m_defaultMax;
    double m_max;
    double m_increment;

    int m_pace;
    bool m_increasing;
    std::function<int32_t(const double &)> m_formulaGetter;
};

#endif // OBD2_PID_INFO_HPP
