#pragma once

namespace HLITE
{
    // File access suppport.
    namespace FILE
    {
        // Access the file location dynamically.
        const char* GetPathFile(const char* Path, bool Debug);
    }
}