#ifndef ATLAS_INCLUDE_ALTAS_CORE_TIMER_HPP
#define ATLAS_INCLUDE_ALTAS_CORE_TIMER_HPP

#pragma once

#include "Core.hpp"

#include <iostream>
#include <chrono>


namespace atlas
{
    namespace core
    {
        template <class GenType>
        class Timer
        {
        public:
            Timer() :
                mBegin(Clock::now())
            { }

            inline void reset()
            {
                mBegin = Clock::now();
            }

            GenType elapsed() const
            {
                return std::chrono::duration_cast<Second>(
                        Clock::now() - mBegin).count();
            }

        private:
            typedef std::chrono::high_resolution_clock Clock;
            typedef std::chrono::duration<GenType, std::ratio<1>> Second;
            std::chrono::time_point<Clock> mBegin;
        };
    }
}

#endif