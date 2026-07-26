#pragma once

namespace HLITE
{
    // File access suppport.
    namespace FILE
    {
        // Access the file location dynamically.
        /// @brief Resolves a file path for the current execution environment.
        /// @param Path The path to resolve.
        /// @param Debug Whether to resolve the path for a debug build.
        /// @return The resolved file path.
        const char* GetPathFile(const char* Path, bool Debug);
    }
}