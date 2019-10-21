#pragma once
//-------------------------------------------------------------------------------------------------
// <copyright file="cabutil.h" company="Microsoft">
//    Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// 
// <summary>
//    Header for cabinet decompression helper functions
// </summary>
//-------------------------------------------------------------------------------------------------

#include <fdi.h>
#include <sys\stat.h>

#ifdef __cplusplus
extern "C" {
#endif

// structs


// callback function prototypes
typedef HRESULT (*CAB_CALLBACK_OPEN_FILE)(LPCWSTR wzFile, INT_PTR* ppFile);
typedef HRESULT (*CAB_CALLBACK_READ_FILE)(INT_PTR pFile, LPVOID pvData, DWORD cbData, DWORD* pcbRead);
typedef HRESULT (*CAB_CALLBACK_WRITE_FILE)(INT_PTR pFile, LPVOID pvData, DWORD cbData, DWORD* pcbRead);
typedef LONG (*CAB_CALLBACK_SEEK_FILE)(INT_PTR pFile, DWORD dwMove, DWORD dwMoveMethod);
typedef HRESULT (*CAB_CALLBACK_CLOSE_FILE)(INT_PTR pFile);

typedef HRESULT (*CAB_CALLBACK_BEGIN_FILE)(LPCWSTR wzFileId, FILETIME* pftFileTime, DWORD cbFileSize, LPVOID pvContext, INT_PTR* ppFile);
typedef HRESULT (*CAB_CALLBACK_END_FILE)(LPCWSTR wzFileId, LPVOID pvContext, INT_PTR pFile);
typedef HRESULT (*CAB_CALLBACK_PROGRESS)(BOOL fBeginFile, LPCWSTR wzFileId, LPVOID pvContext);

// function type with calling convention of __stdcall that .NET 1.1 understands only
// .NET 2.0 will not need this
typedef INT_PTR (FAR __stdcall *STDCALL_PFNFDINOTIFY)(FDINOTIFICATIONTYPE fdint, PFDINOTIFICATION pfdin);


// functions
HRESULT DAPI CabInitialize(
    __in BOOL fDelayLoad
    );
void DAPI CabUninitialize(
    );

HRESULT DAPI CabExtract(
    __in LPCWSTR wzCabinet,
    __in LPCWSTR wzExtractFile,
    __in LPCWSTR wzExtractDir,
    __in CAB_CALLBACK_PROGRESS pfnProgress,
    __in LPVOID pvContext
    );

HRESULT DAPI CabEnumerate(
    __in LPCWSTR wzCabinet,
    __in LPCWSTR wzEnumerateFile,
    __in STDCALL_PFNFDINOTIFY pfnNotify
    );

#ifdef __cplusplus
}
#endif
