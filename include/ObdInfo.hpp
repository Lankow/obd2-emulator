/**
 * @file ObdInfo.hpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#ifndef OBD_INFO_HPP
#define OBD_INFO_HPP

class ObdInfo
{
public:
    ObdInfo(uint16_t pid, uint8_t length, std::string description, double current,
            double min, double max, double increment, uint64_t pace,
            std::function<int32_t(const double &current)> formulaGetter = nullptr);

    void update();
    void printCurrent() const;
    uint32_t getFormula() const;

    uint16_t getPid() const;
    uint8_t getLength() const;
    const std::string &getDescription() const;

    double getCurrent() const;
    double getMin() const;
    double getMax() const;
    double getDefaultMin() const;
    double getDefaultMax() const;
    double getIncrement() const;
    uint64_t getPace() const;

    void setMin(double min);
    void setMax(double max);
    void setIncrement(double increment);
    void setPace(uint64_t pace);

private:
    uint16_t m_pid;
    uint8_t m_length;
    std::string m_description;

    double m_current;
    double m_defaultMin;
    double m_min;
    double m_defaultMax;
    double m_max;
    double m_increment;

    uint64_t m_pace;
    bool m_increasing;
    std::function<int32_t(const double &)> m_formulaGetter;
};

#endif // OBD2_PID_INFO_HPP
