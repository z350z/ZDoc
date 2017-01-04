﻿// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
						Microsoft RPC

                        Hello Example

    FILE:       hellop.c

    PURPOSE:    Remote procedures that are linked with the server
                side of RPC distributed application

    FUNCTIONS:  HelloProc() - prints "hello, world" or other string
                sent by client to server

    COMMENTS:   This version of the distributed application that prints
                "hello, world" (or other string) on the server features
                a client that manages its connection to the server.
                It uses the binding handle hello_IfHandle, defined in
                the file hello.h.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "hello.h"    // header file generated by MIDL compiler

void HelloProc(IN RPC_BINDING_HANDLE hBinding,unsigned char * pszString)
{
    printf_s("%s\n", pszString);
}

void Shutdown(IN RPC_BINDING_HANDLE hBinding)
{
    RPC_STATUS status;

    printf_s("Calling RpcMgmtStopServerListening\n");
    status = RpcMgmtStopServerListening(NULL);
    printf_s("RpcMgmtStopServerListening returned: 0x%x\n", status);
    if (status)
    {
        exit(status);
    }

    printf_s("Calling RpcServerUnregisterIf\n");
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    printf_s("RpcServerUnregisterIf returned 0x%x\n", status);
    if (status)
    {
        exit(status);
    }
}

/* end file hellop.c */
