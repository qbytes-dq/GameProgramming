//-----------------------------------------------------------------------------
// File: dpStage.h
//
// Desc: Stage Trace include file
//
// David Quesenberry
//-----------------------------------------------------------------------------
#ifndef dpStage_INCLUDED
#define dpStage_INCLUDED
//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------

// prototype trace
//#define TRACE   stagetrace 
void stagetrace( TCHAR* strFormat, ...);

//-----------------------------------------------------------------------------
// Name: dtrace()
// Desc: Diagnostic trace to OutputDebugString() (UNICODE supported)
//-----------------------------------------------------------------------------
VOID stagetrace( TCHAR* strFormat, ... )
{
    int     offset = 0;
    TCHAR   strBuf[256];
    va_list ap;

    va_start( ap, strFormat );

    offset = wsprintf( strBuf, TEXT("Pong: ") );
    offset += wvsprintf( strBuf+offset, strFormat, ap );

    OutputDebugString( strBuf );

    va_end( ap );
}

#endif