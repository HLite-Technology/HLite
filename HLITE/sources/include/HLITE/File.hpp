#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <fstream>

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

        /// @brief # High Binary Pack (HBRICK) 
        /// @brief This is a class used to perform I/O to combine binary files.
        /// @attention I/O is automatically closed when the program ends, or you can close it manually.
        class HBrick
        {
        public:
            HBrick();
            /// @brief Constructor used to create binary pack file names directly.
            /// @param packname The name of the binary pack file with `const char*`.
            HBrick(const char* packname);
            ~HBrick();
        
            /// @brief To open a binary pack file that has been created previously.
            /// @param packname The name of the target binary pack file, using`const char*`.
            /// @return If the open is successful it will be `true`, if it fails it will be `false`, using the data type `bool`.
            bool Open(const char* packname);
            /// @brief Useful for creating binary packs.
            /// @param packname To write the name of the binary pack file, use `const char*`.
            /// @return If the create is successful it will be `true`, if it fails it will be `false`, using the data type `bool`.
            bool Create(const char* packname);
            /// @brief Useful for writing the contents of the binary pack with the files you want to combine.
            /// @param filename To write the path of the file that you want to combine into the binary pack, the path is written as `const char*`.
            /// @attention The file path you write is read `relative` to where you run the executable.
            /// @return If the write is successful it will be `true`, if it fails it will be `false`, using the data type `bool`.
            bool Write(const char* filename);
            /// @brief To check the data contents of a binary pack is available or not.
            /// @param binName The name of the data in the binary pack is filled in using`const char*`.
            /// @return If data is available then `true`, if not available then `false`, using `bool`.
            bool CheckData(const char* binName);
            /// @brief To get binary data that has been previously combined in a binary pack.
            /// @param buffer To accommodate file data recorded in the binary pack, use `std::vector<unsigned char>` or `std::vector<std::uint8_t>`.
            /// @param binName To search for the name of the target data stored in the binary pack, use `const char*`.
            /// @return If the get data is successful it will be `true`, if it fails it will be `false`, using the data type `bool`.
            bool GetData(std::vector<unsigned char>& buffer, const char* binName);
            /// @brief To delete data in the binary pack.
            /// @param binName name of the data to be searched in the binary pack, with `const char*`.
            /// @return If data is found it will be `true` if not found it will be `false`, with `bool`.
            bool DeleteData(const char* binName);
            /// @brief To duplicate files based on the data in the selected binary pack.
            /// @param filename The name of the file to be created is a duplicate, uses the `const char* data type`.
            /// @param binName The name data found in the binary pack, uses the `const char* data type`.
            /// @return If the data is found and successfully duplicated it becomes `true`, if it fails it becomes `false`, Use `bool`.
            bool CopyFile(const char* filename, const char* binName);
            /// @brief To check whether HBrick has been closed or not.
            /// @return If it has not been closed then `true`, if closed it becomes `false`. Using the data type `bool`.
            bool IsOpen() const;
            /// @brief To close I/O.
            void Unload();
        private:
            bool headerWritten;
            std::fstream brickIO;
            std::string packPath;
        };

    }
}

#endif