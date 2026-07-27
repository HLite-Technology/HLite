#include "../include/HLITE/Utility.hpp"

#include "../include/HLITE/Preprocessor.hpp"

namespace HLITE
{
    namespace UTIL
    {
        // ===================
        // KEY COMBINE SUPPORT
        // ===================

        CombineKey::CombineKey(float maxDelay)
            : combo2Active(false), combo3Active(false), prevKey1(false), prevKey2(false), prevKey3(false)
        { (void)maxDelay; }

        void CombineKey::SetMaxDelay(float maxDelay)
        { (void)maxDelay; }

        bool CombineKey::Check2(bool key1, bool key2, float customDelay)
        {
            (void)customDelay;
            const bool key1Pressed = key1 && !prevKey1;
            const bool key2Pressed = key2 && !prevKey2;
            const bool combinationHeld = key1 && key2;
            const bool triggered = combinationHeld && !combo2Active && (key1Pressed || key2Pressed);

            combo2Active = combinationHeld;
            prevKey1 = key1;
            prevKey2 = key2;
            return triggered;
        }

        bool CombineKey::Check3(bool key1, bool key2, bool key3, float customDelay)
        {
            (void)customDelay;
            const bool key1Pressed = key1 && !prevKey1;
            const bool key2Pressed = key2 && !prevKey2;
            const bool key3Pressed = key3 && !prevKey3;
            const bool combinationHeld = key1 && key2 && key3;
            const bool triggered = combinationHeld && !combo3Active && (key1Pressed || key2Pressed || key3Pressed);

            combo3Active = combinationHeld;
            prevKey1 = key1;
            prevKey2 = key2;
            prevKey3 = key3;
            return triggered;
        }
        
        void CombineKey::Reset()
        {
            combo2Active = false;
            combo3Active = false;
            prevKey1 = false;
            prevKey2 = false;
            prevKey3 = false;
        }

        // =======================
        // DELAY SUPPORT CLASS
        // =======================

        void Delay::SetDuration(float duration) { this->duration = duration; }
        bool Delay::GetIsDone() { return isDone; }

        void Delay::Reset()
        { 
            counter = 0.0f; 
            isDone = false;
        }
        bool Delay::Update()
        {
            if (isDone) return false;

            counter += GetFrameTime();

            if (counter >= duration) {
                counter = duration;
                isDone = true;
                return true;
            }

            return false;
        }

        // =======================
        // COUNTDOWN SUPPORT CLASS
        // =======================

        bool Countdown::Update()
        {
            if (!IsWindowReady())
            {
                if (seconds != 0) seconds -= 1;
                else if (seconds > 60) seconds = 60;
                else if (seconds == 0)
                {
                    if (minutes != 0)
                    {
                        minutes -= 1;
                        seconds = 60;
                    }
                    else if (minutes > 60) minutes = 60;
                    else return false;
                }
            }
        
            if (IsWindowReady())
            {
                countDelay += GetFrameTime();
            
                if (countDelay >= setterDelay)
                {
                    countDelay = 0.0f;
                
                    if (seconds > 0) seconds -= 1;
                    else
                    {
                        if (minutes > 0)
                        {
                            minutes -= 1;
                            seconds = 59;
                        }
                        else return false; // waktu habis
                    }
                }
            }
            return true;
        }

        std::string Countdown::Str()
        {
            return std::to_string(minutes) + ":" + std::to_string(seconds);
        }
    }
}
