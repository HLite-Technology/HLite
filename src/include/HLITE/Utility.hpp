#pragma once

#include <string>

namespace HLITE
{
    namespace UTIL
    {
        // Key combine support (Todo...).
        namespace Key
        {
            // Combination of 2 keys that are pressed (Todo...).
            bool isCombine_2Key(bool key1, bool key2, float maxDelay);
            // Combination of 3 keys that are pressed (Todo....).
            bool isCombine_3Key(bool key1, bool key2, bool key3, float maxDelay);
        }

        // Delay timer support.
        class Delay
        {
        public:
            Delay()
            {
                isDone = false;
                counter = 0.0f;
                duration = 2.0f; // Two seconds.
            }
            Delay(float duration) : isDone(false), counter(0.0f), duration(duration) {}

            void SetDuration(float duration);
            bool GetIsDone();

            void Reset();
            bool Update();
        private:
            bool isDone;
            float counter;
            float duration;
        };

        // Countdown timer support.
        class Countdown
        {
        public:
            Countdown() {}
            Countdown(int Minutes, int Seconds, float Delay) : 
            minutes(Minutes), seconds(Seconds), setterDelay(Delay) {}

            void SetMinutes(int Minutes) { minutes = Minutes; }
            void SetSeconds(int Seconds) { seconds = Seconds; }
            void SetDelay(float Delay) { setterDelay = Delay; }

            int GetMinutes() { return minutes; }
            int GetSeconds() { return seconds; }

            // Update the timer that will be decreased (true if active, false if the time is up).
            bool Update();
            // Getting the text form from the timer.
            std::string Str(); 
        private:
            int minutes;
            int seconds;
            float setterDelay;
            float countDelay;
        };
    }
}