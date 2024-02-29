#ifndef __HFST_FUNCTION_EXPORT_HPP__
#define __HFST_FUNCTION_EXPORT_HPP__

namespace HFST
{
    ///////////////////////////////////////////////////////////////////////////
    // For TTK_Communication_API //////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    
    //! ReadI2CReg
    using pfn_ReadI2CReg = int (*)(unsigned char* data, unsigned int addr, unsigned int len);

    //! WriteI2CReg
    using pfn_WriteI2CReg = int (*)(unsigned char* data, unsigned int addr, unsigned int len);

    //! ResetTP
    using pfn_ResetTP = int (*)();

    //! SetI2CAddr
    using pfn_SetI2CAddr = int (*)(unsigned char Addr, unsigned char RetryTime, unsigned char NonClockStretchFlag);

    //! WriteCmd
    using pfn_WriteCmd = int (*)(unsigned char* WBuffer, unsigned short WLength);

    //! ReadCmd
    using pfn_ReadCmd = int (*)(unsigned char* RBuffer, unsigned short RLength);

    //! ReadI2CRegBeginINT
    using pfn_ReadI2CRegBeginINT = int (*)(unsigned char Addr, unsigned char length);

    //! ReadI2CRegDataINT
    using pfn_ReadI2CRegDataINT = int (*)(unsigned char* Data, unsigned char length);

    //! ReadI2CRegEndINT
    using pfn_ReadI2CRegEndINT = int (*)();

    //! GetI2CStatus_Bulk
    using pfn_GetI2CStatus_Bulk = int (*)(unsigned char* SBuff);

    //�� SetTouchLinkVoltage
    using pfn_SetTouchLinkVoltage = int (*)(unsigned short nVDD1, unsigned short nVDD2);

    //�� for control touch-link 3 voltage
    using pfn_SetTouchLink3_Voltage = int (*)(double dVDD1, double dVDD2);

    //! CheckIsA8018ICPI2CAddr
    using pfn_HFST_CheckIsA8018ICPI2CAddr = bool (*)(unsigned char);

    ///////////////////////////////////////////////////////////////////////////
    // For Bulk_API ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    
    //! USBComm_FinishEx
    using pfn_USBComm_FinishEx = int (*)();

    //! USBComm_InitEx
    using pfn_USBComm_InitEx = int (*)(unsigned int TimeOut, unsigned int nDeviceIdx);

    //! USBComm_CheckBulkInEx
    using pfn_USBComm_CheckBulkInEx = int (*)();

    //! USBComm_CheckBulkOutEx
    using pfn_USBComm_CheckBulkOutEx = int (*)();

    //! USBComm_ReadFromBulkEx
    using pfn_USBComm_ReadFromBulkEx = int (*)(unsigned char* Buffer, unsigned int BufferSize);

    //! USBComm_WriteToBulkEx
    using pfn_USBComm_WriteToBulkEx = int (*)(unsigned char* Buffer, unsigned int BufferSize);

    ///////////////////////////////////////////////////////////////////////////
    // For WinUSB_Driver API //////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    
    //! WinUSB_Driver_CheckIsConnected
    using pfn_WinUSB_Driver_CheckIsConnected = int (*)(int);

    //! WinUSB_Driver_Install
    using pfn_WinUSB_Driver_Install = int (*)(int);

    //! WinUSB_Driver_RemoveFiles
    using pfn_WinUSB_Driver_RemoveFiles = void (*)();
}


#endif //__HFST_FUNCTION_EXPORT_HPP__