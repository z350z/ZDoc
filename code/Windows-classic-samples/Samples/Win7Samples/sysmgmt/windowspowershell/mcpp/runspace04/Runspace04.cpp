﻿//
// Copyright (c) 2006 Microsoft Corporation. All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

using namespace System;
using namespace System::Collections;

using namespace System::Management::Automation;
using namespace System::Management::Automation::Runspaces;

/// <summary>
/// This sample uses the RunspaceInvoke class to execute
/// a script. This script will generate a terminating
/// exception that the caller should catch and process.
/// </summary>
/// <remarks>
/// This sample demonstrates the following:
/// 1. Creating an instance of the RunspaceInvoke class.
/// 2. Using this instance to execute a string as a PowerShell script.
/// 3. Passing input objects to the script from the calling program.
/// 4. Using PSObject to extract and display properties from the objects
///    returned by this command.
/// 5. Retrieving and displaying error records that may be generated
///    during the execution of that script.
/// 6. Catching and displaying terminating exceptions generated
///    by the script being run.
/// </remarks>
int
__cdecl main()
{
    // Define a list of patterns to use in matching.
    // Note that the fourth pattern is not a valid regular
    // expression so it will cause a terminating exception to
    // be thrown when used in select-string.
    array<String^>^ patterns = gcnew array<String^>(5)
    {
        "aa", "bc", "ab*c", "*", "abc"
    };

    // The script to run to use the patterns. Input passed
    // to the script will be available in the $input variable.
    String^ script = "$input | where { select-string $_ -inputobject 'abc' }";

    // Create an instance of the RunspaceInvoke class.
    RunspaceInvoke^ invoker = gcnew RunspaceInvoke();

    // Invoke the runspace. Because of the bad regular expression,
    // no objects will be returned. Instead, an exception will be
    // thrown.
    try
    {
        IList^ errors = nullptr;
        for each (PSObject^ result in invoker->Invoke(script, patterns, errors))
        {
            Console::WriteLine("'{0}'", result->ToString());
        }

        // Now process any error records that were generated while running the script.
        Console::WriteLine("\nThe following non-terminating errors occurred:\n");
        if ((nullptr != errors) && (errors->Count > 0))
        {
            for each (PSObject^ err in errors)
            {
                Console::WriteLine("    error: {0}", err->ToString());
            }
        }
    }
    catch(RuntimeException^ runtimeException)
    {
        // Trap any exception generated by the script. These exceptions
        // will all be derived from RuntimeException.
        Console::WriteLine("Runtime exception: {0}: {1}\n{2}",
                           runtimeException->ErrorRecord->InvocationInfo->InvocationName,
                           runtimeException->Message,
                           runtimeException->ErrorRecord->InvocationInfo->PositionMessage
                          );
    }

    Console::WriteLine("\nHit any key to exit...");
    Console::ReadKey();
}
