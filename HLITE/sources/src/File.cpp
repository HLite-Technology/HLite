#include <cstdio>
#include <filesystem>
#include "../include/HLITE/Core.hpp"


namespace HLITE
{
    namespace FILE
    {
        const char* GetPathFile(const char* Path, bool Debug) 
        {
            bool isFileNotfound = false;
            static std::string finalPath;
            std::filesystem::path path1 = std::filesystem::current_path() / Path;
            std::filesystem::path path2 = std::filesystem::current_path().parent_path() / Path;
        
            if (std::filesystem::exists(path1)) finalPath = path1.string();
            else if (std::filesystem::exists(path2)) finalPath = path2.string();
            else 
            {
                finalPath.clear();
                isFileNotfound = true;
            } 
        
            if (Debug) 
            {
                if (isFileNotfound) std::fprintf(stderr,"[HLITE] Error: File or assets not found!\n");
                else std::printf("[HLITE] Path: %s\n", finalPath.data());
            }
            return finalPath.c_str();
        }
    }
}