#include <windows.h>
#include <iostream>
#include <format>
#include "HFST_Connector.hpp"
#include "HFST_RawReader.hpp"
#include "HFST_CommonHeader.hpp"
#include "HFST_Bridge.hpp"
int main(int argc, char* argv[])
{
    HFST::Connector connector;
    if (!connector.Connect())
    {
        std::cout << "Connect failed!" << std::endl;
        system("pause");
        return 0;
    }

    HFST::IC_Info info = connector.IC_GetInfo();
    HFST::RAW::ChannelRaw<short> raw;
    HFST::RAW::Frame<short> frame;

    std::unique_ptr<HFST::RawReader> pRawReader = HFST::CreateRawReader(info);

    //CONSOLE_SCREEN_BUFFER_INFO sInfo;
    //GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sInfo);
    while (1)
    {
        //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), sInfo.dwCursorPosition);
        pRawReader->ReadChannelRaw(raw);
        pRawReader->PrintChannel(std::cout, raw);

        /*pRawReader->ReadFrame(frame);
        pRawReader->PrintFrame(std::cout, frame);*/

        Sleep(100);

    }
    return 0;
}

