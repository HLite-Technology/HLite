#include <cctype>
#include <cstdio>
#include <string>
#include <algorithm>
#include <filesystem>
#include <string_view>

#include "../include/HLITE/File.hpp"

namespace
{
    std::string ToLower(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char ch)
            {
                return static_cast<char>(std::tolower(ch));
            });
        return value;
    }

    std::string ExtractFileName(const std::string& path)
    {
        const auto slash = path.find_last_of("/\\");
        return slash == std::string::npos ? path : path.substr(slash + 1);
    }

    std::string StripExtension(const std::string& name)
    {
        const auto dot = name.find_last_of('.');
        if (dot == std::string::npos || dot == 0)
            return name;
        return name.substr(0, dot);
    }

    bool MatchStoredName(const std::string& storedName, const std::string& query)
    {
        const std::string storedLower = ToLower(storedName);
        const std::string queryLower = ToLower(query);

        if (storedLower == queryLower)
            return true;

        const std::string storedFile = ToLower(ExtractFileName(storedName));
        const std::string queryFile = ToLower(ExtractFileName(query));
        if (storedFile == queryFile)
            return true;

        if (ToLower(StripExtension(storedFile)) == ToLower(StripExtension(queryFile)))
            return true;

        if (ToLower(StripExtension(storedName)) == ToLower(StripExtension(query)))
            return true;

        return false;
    }

    constexpr char HEX_CHARS[] = "0123456789abcdef";

    int HexCharToInt(char ch)
    {
        if (ch >= '0' && ch <= '9') return ch - '0';
        if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
        if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
        return -1;
    }

    std::string EncodeHex(std::string_view input)
    {
        std::string output;
        output.reserve(input.size() * 2);

        for (const unsigned char ch : input)
        {
            output.push_back(HEX_CHARS[(ch >> 4) & 0x0F]);
            output.push_back(HEX_CHARS[ch & 0x0F]);
        }

        return output;
    }

    std::string DecodeHex(std::string_view encoded)
    {
        if (encoded.size() % 2 != 0) return std::string(encoded);

        std::string output;
        output.reserve(encoded.size() / 2);

        for (std::size_t i = 0; i < encoded.size(); i += 2)
        {
            const int high = HexCharToInt(encoded[i]);
            const int low = HexCharToInt(encoded[i + 1]);

            if (high == -1 || low == -1)
                return std::string(encoded);

            output.push_back(static_cast<char>((high << 4) | low));
        }

        return output;
    }

    std::string EncodeStoredFileName(std::string_view name)
    {
        return EncodeHex(name);
    }

    std::string DecodeStoredFileName(std::string_view encodedName)
    {
        return DecodeHex(encodedName);
    }
}

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

        HBrick::HBrick() : headerWritten(false) {}

        HBrick::HBrick(const char* packname) : headerWritten(false)
        {
            if (packname != nullptr)
            {
                brickIO.open(
                    packname,
                    std::ios::binary |
                    std::ios::in |
                    std::ios::out |
                    std::ios::trunc
                );
            
                packPath = packname;
            }
        }

        HBrick::~HBrick() = default;

        bool HBrick::Open(const char* packname)
        {
            if (packname == nullptr) return false;
            if (brickIO.is_open()) brickIO.close();
        
            brickIO.clear();
        
            brickIO.open(packname,
                         std::ios::binary |
                         std::ios::in |
                         std::ios::out |
                         std::ios::ate);
            
            if (!brickIO.is_open())
                return false;
            
            packPath = packname;
            headerWritten = true;
            return true;
        }

        bool HBrick::Create(const char* packname)
        {
            if (packname == nullptr)
                return false;
        
            if (brickIO.is_open()) brickIO.close();
        
            brickIO.clear();
        
            brickIO.open(packname,
                         std::ios::binary |
                         std::ios::in |
                         std::ios::out |
                         std::ios::trunc);
            
            if (!brickIO.is_open())
                return false;
            
            packPath = packname;
            headerWritten = false;
            return true;
        }

        bool HBrick::Write(const char* filename)
        {
            constexpr std::size_t CHUNK_SIZE = 1024 * 1024;
            constexpr std::string_view header = "[BRICK]";
            constexpr std::string_view startMarker = "__PACK_START__";
            constexpr std::string_view endMarker = "__PACK_END__";
        
            if (!brickIO.is_open() || filename == nullptr)
                return false;
        
            std::ifstream filereader(filename, std::ios::binary);
        
            if (!filereader.is_open())
                return false;
        
            const std::string storedName = EncodeStoredFileName(ExtractFileName(filename));
        
            if (!headerWritten)
            {
                brickIO.clear();
                brickIO.seekp(0, std::ios::end);
            
                brickIO.write(header.data(), static_cast<std::streamsize>(header.size()));
            
                if (!brickIO) return false;
            
                headerWritten = true;
            }
        
            brickIO.put('(');
        
            if (!brickIO) return false;
        
            brickIO.write(storedName.data(), static_cast<std::streamsize>(storedName.size()));
        
            if (!brickIO) return false;
        
            brickIO.put(')');
        
            if (!brickIO) return false;
        
            brickIO.write(startMarker.data(), static_cast<std::streamsize>(startMarker.size()));
        
            if (!brickIO) return false;
        
            std::vector<char> buffer(CHUNK_SIZE);
        
            while (filereader)
            {
                filereader.read(
                    buffer.data(),
                    static_cast<std::streamsize>(buffer.size())
                );
            
                const std::streamsize count = filereader.gcount();
            
                if (count > 0)
                {
                    brickIO.write(buffer.data(), count);
                
                    if (!brickIO)
                        return false;
                }
            }
        
            if (!filereader.eof())
                return false;
        
            brickIO.write(endMarker.data(), static_cast<std::streamsize>(endMarker.size()));
        
            if (!brickIO) return false;
        
            brickIO.flush();
        
            if (!brickIO) return false;
        
            return true;
        }

        bool HBrick::CheckData(const char* binName)
        {
            constexpr std::string_view header = "[BRICK]";
            constexpr std::string_view startMarker = "__PACK_START__";
            constexpr std::string_view endMarker = "__PACK_END__";
        
            if (!brickIO.is_open() || binName == nullptr)
                return false;
        
            brickIO.clear();
        
            brickIO.seekg(0, std::ios::end);
        
            const std::streamoff fileSize = brickIO.tellg();
        
            if (fileSize <= 0)
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.seekg(0, std::ios::beg);
        
            std::string fileData(static_cast<std::size_t>(fileSize), '\0');
        
            if (!brickIO.read(
                    fileData.data(),
                    static_cast<std::streamsize>(fileData.size())))
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.clear();
            brickIO.seekg(0, std::ios::beg);
        
            if (fileData.size() < header.size() ||
                fileData.compare(0, header.size(), header) != 0)
                return false;
        
            std::size_t pos = header.size();
        
            while (pos < fileData.size())
            {
                const std::size_t openPos = fileData.find('(', pos);
            
                if (openPos == std::string::npos)
                    return false;
            
                const std::size_t closePos = fileData.find(')', openPos + 1);
            
                if (closePos == std::string::npos)
                    return false;
            
                if (closePos == openPos + 1)
                    return false;
            
                const std::string entryName = fileData.substr(openPos + 1, closePos - openPos - 1);
            
                const std::size_t payloadStart = fileData.find(startMarker.data(), closePos + 1, startMarker.size());
            
                if (payloadStart == std::string::npos)
                    return false;
            
                const std::size_t payloadDataStart = payloadStart + startMarker.size();
            
                const std::size_t payloadEnd = fileData.find(endMarker.data(), payloadDataStart, endMarker.size());
            
                if (payloadEnd == std::string::npos)
                    return false;
            
                const std::string decodedEntryName =
                    DecodeStoredFileName(entryName);
            
                if (MatchStoredName(decodedEntryName, binName) ||
                    MatchStoredName(entryName, binName))
                    return true;
            
                pos = payloadEnd + endMarker.size();
            }
        
            return false;
        }

        bool HBrick::GetData(std::vector<unsigned char>& buffer, const char* binName)
        {
            buffer.clear();
        
            if (!brickIO.is_open() || binName == nullptr)
                return false;
        
            brickIO.clear();
            brickIO.seekg(0, std::ios::end);
            const std::streamoff fileSize = brickIO.tellg();
        
            if (fileSize <= 0)
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.seekg(0, std::ios::beg);
            std::string fileData(static_cast<std::size_t>(fileSize), '\0');
        
            if (!brickIO.read(&fileData[0], fileSize))
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.clear();
            brickIO.seekg(0, std::ios::beg);
        
            const std::string_view header = "[BRICK]";
            const std::string_view startMarker = "__PACK_START__";
            const std::string_view endMarker = "__PACK_END__";
        
            std::size_t pos = 0;
            if (fileData.rfind(header.data(), 0) == 0)
                pos = header.size();
        
            while (pos < fileData.size())
            {
                const std::size_t openPos = fileData.find('(', pos);
                if (openPos == std::string::npos)
                    break;
            
                const std::size_t closePos = fileData.find(')', openPos + 1);
                if (closePos == std::string::npos)
                    break;
            
                const std::string entryName = fileData.substr(openPos + 1, closePos - openPos - 1);
                const std::size_t payloadStart = fileData.find(startMarker.data(), closePos + 1);
                if (payloadStart == std::string::npos)
                    break;
            
                const std::size_t payloadEnd = fileData.find(endMarker.data(), payloadStart + startMarker.size());
                if (payloadEnd == std::string::npos)
                    break;
            
                const std::string decodedEntryName = DecodeStoredFileName(entryName);
                if (MatchStoredName(decodedEntryName, binName) || MatchStoredName(entryName, binName))
                {
                    const auto beginIt = fileData.begin() + static_cast<std::ptrdiff_t>(payloadStart + startMarker.size());
                    const auto endIt = fileData.begin() + static_cast<std::ptrdiff_t>(payloadEnd);
                    buffer.assign(beginIt, endIt);
                    return true;
                }
            
                pos = payloadEnd + endMarker.size();
            }
        
            return false;
        }

        bool HBrick::DeleteData(const char* binName)
        {
            constexpr std::string_view header = "[BRICK]";
            constexpr std::string_view startMarker = "__PACK_START__";
            constexpr std::string_view endMarker = "__PACK_END__";
        
            if (!brickIO.is_open() || binName == nullptr || packPath.empty())
                return false;
        
            brickIO.clear();
            brickIO.seekg(0, std::ios::end);
        
            const std::streamoff fileSize = brickIO.tellg();
        
            if (fileSize <= 0)
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.seekg(0, std::ios::beg);
        
            std::string fileData(static_cast<std::size_t>(fileSize), '\0');
        
            if (!brickIO.read(fileData.data(), static_cast<std::streamsize>(fileData.size())))
            {
                brickIO.clear();
                brickIO.seekg(0, std::ios::beg);
                return false;
            }
        
            brickIO.clear();
            brickIO.seekg(0, std::ios::beg);
        
            if (fileData.size() < header.size() || fileData.compare(0, header.size(), header) != 0)
                return false;
        
            std::size_t pos = header.size();
        
            std::size_t deleteBegin = std::string::npos;
            std::size_t deleteEnd = std::string::npos;
        
            while (pos < fileData.size())
            {
                const std::size_t openPos = fileData.find('(', pos);
            
                if (openPos == std::string::npos)
                    break;
            
                const std::size_t closePos = fileData.find(')', openPos + 1);
            
                if (closePos == std::string::npos)
                    return false;
            
                if (closePos == openPos + 1)
                    return false;
            
                const std::string entryName = fileData.substr(openPos + 1, closePos - openPos - 1);
            
                const std::size_t payloadStart = fileData.find(startMarker.data(), closePos + 1);
            
                if (payloadStart == std::string::npos)
                    return false;
            
                const std::size_t payloadEnd = fileData.find(endMarker.data(), payloadStart + startMarker.size());
            
                if (payloadEnd == std::string::npos)
                    return false;
            
                const std::string decodedEntryName = DecodeStoredFileName(entryName);
            
                if (MatchStoredName(decodedEntryName, binName) ||
                    MatchStoredName(entryName, binName))
                {
                    deleteBegin = openPos;
                    deleteEnd = payloadEnd + endMarker.size();
                    break;
                }
            
                pos = payloadEnd + endMarker.size();
            }
        
            if (deleteBegin == std::string::npos)
                return false;
        
            std::string newFileData;
        
            newFileData.reserve(fileData.size() - (deleteEnd - deleteBegin));
        
            newFileData.append(fileData.data(), deleteBegin);
        
            newFileData.append(fileData.data() + deleteEnd, fileData.size() - deleteEnd);
        
            const std::filesystem::path originalPath(packPath);
        
            const std::filesystem::path tempPath = originalPath.string() + ".tmp";
        
        
            brickIO.close();
        
            if (brickIO.is_open())
                return false;
        
            {
                std::ofstream tempFile(tempPath,
                                       std::ios::binary |
                                       std::ios::trunc);
                
                if (!tempFile.is_open())
                {
                    brickIO.clear();
                
                    brickIO.open(packPath,
                                 std::ios::binary |
                                 std::ios::in |
                                 std::ios::out |
                                 std::ios::ate);
                    
                    return false;
                }
            
                tempFile.write(newFileData.data(), static_cast<std::streamsize>(newFileData.size()));
            
                if (!tempFile)
                {
                    tempFile.close();
                
                    std::error_code ec;
                    std::filesystem::remove(tempPath, ec);
                
                    brickIO.clear();
                
                    brickIO.open(packPath,
                                 std::ios::binary |
                                 std::ios::in |
                                 std::ios::out |
                                 std::ios::ate);
                    
                    return false;
                }
            
                tempFile.flush();
            
                if (!tempFile)
                {
                    tempFile.close();
                
                    std::error_code ec;
                    std::filesystem::remove(tempPath, ec);
                
                    brickIO.clear();
                
                    brickIO.open(packPath,
                                 std::ios::binary |
                                 std::ios::in |
                                 std::ios::out |
                                 std::ios::ate);
                    
                    return false;
                }
            }
        
            std::error_code ec;
        
            std::filesystem::remove(originalPath, ec);
        
            if (ec)
            {
                std::filesystem::remove(tempPath, ec);
            
                brickIO.clear();
            
                brickIO.open(packPath,
                             std::ios::binary |
                             std::ios::in |
                             std::ios::out |
                             std::ios::ate);
                
                return false;
            }
        
            std::filesystem::rename(tempPath, originalPath, ec);
        
            if (ec)
            {
                std::error_code restoreEc;
            
                std::filesystem::rename(tempPath, originalPath, restoreEc);
            
                brickIO.clear();
            
                brickIO.open(packPath,
                             std::ios::binary |
                             std::ios::in |
                             std::ios::out |
                             std::ios::ate);
                
                return false;
            }
        
            brickIO.clear();
        
            brickIO.open(packPath,
                         std::ios::binary |
                         std::ios::in |
                         std::ios::out |
                         std::ios::ate);
            
            if (!brickIO.is_open())
            {
                headerWritten = false;
                return false;
            }
        
            headerWritten = true;
        
            return true;
        }

        bool HBrick::CopyFile(const char* filename, const char* binName)
        {
            if (filename == nullptr || binName == nullptr)
                return false;
        
            std::vector<unsigned char> buffer;
        
            if (!GetData(buffer, binName))
                return false;
        
            std::ofstream dupFile(filename, std::ios::binary | std::ios::trunc);
        
            if (!dupFile.is_open()) return false;
        
            if (!buffer.empty())
            {
                dupFile.write(reinterpret_cast<const char*>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
                if (!dupFile) return false;
            }
        
            return true;
        }

        bool HBrick::IsOpen() const {return brickIO.is_open();}

        void HBrick::Unload()
        {
            if (brickIO.is_open())
                brickIO.close();
        
            brickIO.clear();
            headerWritten = false;
            packPath.clear();
        }
    }
}