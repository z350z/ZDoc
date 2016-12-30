﻿// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
                        Microsoft RPC
                        umarsh Example

    FILE:       umarshsu.c

    PURPOSE:    Utility functions used by client side of the RPC
                distributed application.
                This sample demonstrates the represent_as attribute.

    RELATED:    umarshs.c - server main
                umarshp.c - remote procedures
                umarshc.c - client main

    FUNCTIONS:  CHAR_STRING_to_local    - convert CHAR_STRING to WCHAR_STRING
                CHAR_STRING_from_local  - convert CHAR_STRING from WCHAR_STRING
                CHAR_STRING_free_inst   - free CHAR_STRING memory
                CHAR_STRING_free_local  - free WCHAR_STRING memory
                midl_user_allocate - user-supplied memory allocator
                midl_user_free - user-supplied routine to free memory


    COMMENTS:   This sample program generates a client and server can share
                an interface, but one side can use a different representation
                than the other.

                The client side in this example does all operations using
                character strings, and the server side does all operations
                using UNICODE strings.  Two procedures are provided, one
                defined with ASCII strings, one with UNICODE strings.
                The wire format reflects these definitions, yet the client
                and server see pure ASCII and pure UNICODE respectively.

                The [represent_as] attribute (used in the client and server
                side acf files) requires the four user-supplied functions
                whose names start with the name of the transmitted type
                (in the server side's case: CHAR_STRING)

                The [in, out] attributes applied to remote procedure
                parameters require the two user-supplied functions
                midl_user_allocate and midl_user_free.

                The other functions are utilities that are used to
                build or display the data structures.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "umarshs.h"    // header file generated by MIDL compiler for client



/*
 Description:   Allocates memory for the transmitted type and converts from
                local type to the transmitted type

 Arguments:
    pLocal:     pointer to local type
    ppWire:     pointer to the transmitted type pointer. This function should
                allocate memory for the transmitted data type.

 Return Value:  None.
*/

// Calculate size that converted data will
// require in the buffer
unsigned long __RPC_USER WCHAR_STRING_UserSize(
    ULONG __RPC_FAR * pulFlags,
    unsigned long    startingSize,
    WCHAR_STRING __RPC_FAR * pStr)
{
    return startingSize + sizeof(CHAR_STRING);
}


unsigned char * __RPC_USER WCHAR_STRING_UserMarshal(
    ULONG __RPC_FAR *pulFlags,
    unsigned char __RPC_FAR * pBufferStart,
    WCHAR_STRING __RPC_FAR * pStr)
{

    unsigned char __RPC_FAR * pCurBuffer = pBufferStart;

    size_t uSize;

    wcstombs_s(&uSize,pBufferStart,sizeof(CHAR_STRING), *pStr, sizeof(CHAR_STRING) );

    //strcpy(pBufferStart,"This is just a test");
    ((char *)pCurBuffer) += STRING_SIZE;

    printf_s("\nServer side has finished marshalling");
    return pCurBuffer;
}


unsigned char * __RPC_USER WCHAR_STRING_UserUnmarshal(
    ULONG __RPC_FAR * pulFlags,
    unsigned char __RPC_FAR * pBufferStart,
    WCHAR_STRING __RPC_FAR * pStr)
{

    size_t uSize;

    unsigned char __RPC_FAR * pCurBuffer = pBufferStart;

    mbstowcs_s(&uSize,*pStr, sizeof(CHAR_STRING), pBufferStart, sizeof(WCHAR_STRING) );
    //wcscpy(*pStr,L"This is also a test");

    ((char *)pCurBuffer) += STRING_SIZE;

    return pCurBuffer;
}


void __RPC_USER WCHAR_STRING_UserFree(
    ULONG __RPC_FAR * pulFlags,
    WCHAR_STRING __RPC_FAR * pStr
)
{
    //free(pStr);
}

// Calculate size that converted data will
// require in the buffer
unsigned long __RPC_USER WCHAR_STRING_UserSize64(
    ULONG __RPC_FAR * pulFlags,
    unsigned long    startingSize,
    WCHAR_STRING __RPC_FAR * pStr)
{
    return startingSize + sizeof(CHAR_STRING);
}


unsigned char * __RPC_USER WCHAR_STRING_UserMarshal64(
    ULONG __RPC_FAR *pulFlags,
    unsigned char __RPC_FAR * pBufferStart,
    WCHAR_STRING __RPC_FAR * pStr)
{

    unsigned char __RPC_FAR * pCurBuffer = pBufferStart;

    size_t uSize;

    wcstombs_s(&uSize,pBufferStart,sizeof(CHAR_STRING), *pStr, sizeof(CHAR_STRING) );

    //strcpy(pBufferStart,"This is just a test");
    ((char *)pCurBuffer) += STRING_SIZE;

    printf_s("\nServer side has finished marshalling");
    return pCurBuffer;
}


unsigned char * __RPC_USER WCHAR_STRING_UserUnmarshal64(
    ULONG __RPC_FAR * pulFlags,
    unsigned char __RPC_FAR * pBufferStart,
    WCHAR_STRING __RPC_FAR * pStr)
{

    size_t uSize;

    unsigned char __RPC_FAR * pCurBuffer = pBufferStart;

    mbstowcs_s(&uSize,*pStr, sizeof(CHAR_STRING), pBufferStart, sizeof(WCHAR_STRING) );
    //wcscpy(*pStr,L"This is also a test");

    ((char *)pCurBuffer) += STRING_SIZE;

    return pCurBuffer;
}


void __RPC_USER WCHAR_STRING_UserFree64(
    ULONG __RPC_FAR * pulFlags,
    WCHAR_STRING __RPC_FAR * pStr
)
{
    //free(pStr);
}

/***************************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}


/***************************************************************************/

/* end file umarshsu.c */
