#ifndef XYCONTROL_H
#define XYCONTROL_H

#include <iostream>

#include <chrono>
#include <thread>
#include <mutex>

#include "WiringPiSim.h"


class XyControl
{


public:
    XyControl() = default;

    enum PinId : int {
        Enable, // 23
        DirectionX,
        DirectionY, // 27
        StepX,
        StepY
    };

    [[noreturn]] void run() {
        init();

        using namespace WiringPi;

        std::chrono::microseconds minDelay{950};
        std::chrono::milliseconds normalDelay{20};

        digitalWrite(Enable, LOW);

        while(true) {
            const int tx = targetX();
            const int ty = targetY();
            int cx = currentX();
            int cy = currentY();

            if(tx != cx) {
                //HIGH == ClockWise, LOW == CounterClockWise
                digitalWrite(DirectionX, tx> cx ? HIGH : LOW);
                digitalWrite(StepX, HIGH);

                std::cout << "x changed from|to|target: " << cx << "|" << cx+1 << "|" << tx << std::endl;
                cx += tx> cx ? 1 : -1;
            }

            if(ty != cy) {
                //HIGH == ClockWise, LOW == CounterClockWise
                digitalWrite(DirectionY, ty> cy ? HIGH : LOW);
                digitalWrite(StepY, HIGH);

                std::cout << "y changed from|to|target: " << cy << "|" << cy+1 << "|" << ty << std::endl;
                cy += ty> cy ? 1 : -1;
            }

            std::this_thread::sleep_for(minDelay);
            digitalWrite(StepX, LOW);
            digitalWrite(StepY, LOW);

            m_mutex.lock();
                m_currentX = cx;
                m_currentY = cy;
            m_mutex.unlock();

            const bool xReached{cx == tx};
            const bool yReached{cy == ty};

            std::this_thread::sleep_for( xReached && yReached ? normalDelay : minDelay);
        }
    }



public:
    [[nodiscard]] int currentX() noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        return m_currentX;
    }

    [[nodiscard]] int currentY() noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        return m_currentY;
    }

    [[nodiscard]] int targetX() noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        return m_targetX;
    }

    [[nodiscard]] int targetY() noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        return m_targetY;
    }

    void setTargetX(int x) noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        m_targetX = x;
    }

    void setTargetY(int y) noexcept {
        const std::lock_guard<std::mutex> guard(m_mutex);
        m_targetY = y;
    }

private:
    void init()
    {
        using namespace WiringPi;

        wiringPiSetupGpio();

        pinMode(17, OUTPUT);
        pinMode(23, OUTPUT);
        pinMode(27, OUTPUT);

        digitalWrite(17, LOW);
        digitalWrite(23, LOW);
        digitalWrite(27, LOW);
    }

private:
    std::mutex m_mutex;

    int m_currentX{0};
    int m_currentY{0};
    int m_targetX{0};
    int m_targetY{0};
};

#endif // XYCONTROL_H
