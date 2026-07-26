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
            /// @brief Checks whether two keys are combined within the allowed delay.
            /// @param key1 The state of the first key.
            /// @param key2 The state of the second key.
            /// @param maxDelay The maximum allowed interval between key presses.
            /// @return `true` if the key combination is detected; otherwise, `false`.
            bool isCombine_2Key(bool key1, bool key2, float maxDelay);
            // Combination of 3 keys that are pressed (Todo....).
            /// @brief Checks whether three keys are combined within the allowed delay.
            /// @param key1 The state of the first key.
            /// @param key2 The state of the second key.
            /// @param key3 The state of the third key.
            /// @param maxDelay The maximum allowed interval between key presses.
            /// @return `true` if the key combination is detected; otherwise, `false`.
            bool isCombine_3Key(bool key1, bool key2, bool key3, float maxDelay);
        }

        /// @brief Delay timer support.
        class Delay
        {
        public:
            /// @brief Creates a delay timer with a two-second duration.
            explicit Delay()
            {
                isDone = false;
                counter = 0.0f;
                duration = 2.0f; // Two seconds.
            }
            /// @brief Creates a delay timer with the specified duration.
            /// @param duration The timer duration in seconds.
            explicit Delay(float duration) : isDone(false), counter(0.0f), duration(duration) {}

            /// @brief To set the delay.
            /// @param duration Use the `float` data type to set the duration.
            void SetDuration(float duration);
            /// @brief Find out if the delay is over.
            /// @return `true` if it has ended and `false` if it has not ended.
            bool GetIsDone();

            /// @brief Resets the timer to its initial state.
            void Reset();
            /// @brief Advances the timer and returns whether it is complete.
            /// @return `true` if the delay has completed; otherwise, `false`.
            bool Update();
        private:
            bool isDone;
            float counter;
            float duration;
        };

        /// @brief Countdown timer support.
        class Countdown
        {
        public:
            /// @brief Creates an empty countdown timer.
            explicit Countdown() {}
            /// @brief Creates a countdown timer with the specified time and update delay.
            /// @param Minutes The initial countdown minutes.
            /// @param Seconds The initial countdown seconds.
            /// @param Delay The interval between countdown updates in seconds.
            explicit Countdown(int Minutes, int Seconds, float Delay) : 
            minutes(Minutes), seconds(Seconds), setterDelay(Delay) {}

            /// @brief Set the minutes of the timer.
            /// @param Minutes It is an `int` data type for minutes.
            void SetMinutes(int Minutes) { minutes = Minutes; }
            /// @brief Set the seconds of the timer.
            /// @param Seconds It is an `int` data type for minutes.
            void SetSeconds(int Seconds) { seconds = Seconds; }
            /// @brief Set the delay of the timer.
            /// @param Delay It is a `float` data type for setting delay.
            void SetDelay(float Delay) { setterDelay = Delay; }

            /// @brief The value is in numeric minutes.
            /// @return The minute number is `int`.
            int GetMinutes() { return minutes; }
            /// @brief The value is in numeric seconds.
            /// @return The second number is `int`.
            int GetSeconds() { return seconds; }

            /// @brief Update the timer that will be decreased.
            /// @return `true` if active, `false` if the time is up.
            bool Update();
            /// @brief Getting the text form from the timer.
            /// @return Time as a `std::string`.
            std::string Str(); 
        private:
            int minutes;
            int seconds;
            float setterDelay;
            float countDelay;
        };
    }
}