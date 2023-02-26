//
// Created by Vlad on 19.02.2023.
//

#include "DownloadFile.h"
#include <fstream>
#include "../ClientHandle/ClientHandle.h"


#define KILOBYTE 1024
#define MEGABYTE (KILOBYTE*1024)
#define GIGABYTE (MEGABYTE*1024)


namespace Web::Packet
{
    nlohmann::json DownloadFile::ExecutePayload(ClientHandle &clientHandle)
    {
        try
        {
            auto file = std::ifstream(m_sFileName, std::ios::in | std::ios::binary);

            if (!file.is_open())
                throw std::runtime_error("File does not exist");

            size_t szFileSize = (size_t)file.tellg();

            if (szFileSize == 0 or szFileSize >= 64*MEGABYTE)
                throw std::runtime_error("File size is to big or too small");


            // Send true to notify client that we are ready to send file
            clientHandle.m_clientSocket.SendStruct(true);

            auto buffer = std::unique_ptr<char> (new char[szFileSize]);

            file.seekg(0, std::ios::beg);
            file.read(buffer.get(), (int)szFileSize);


            clientHandle.m_clientSocket.SendBytes(buffer.get(), (int)szFileSize);
        }
        catch (const std::runtime_error& ex)
        {
            // Send false to notify client that we are not ready to send file
            clientHandle.m_clientSocket.SendStruct(false);
            throw ex;
        }

        return {};
    }

    DownloadFile::DownloadFile(const nlohmann::json &data) : BasePacket(data)
    {

    }
} // Packet