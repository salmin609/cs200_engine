#pragma once
#define WIN32_LEAN_AND_MEAN

#define NOGDICAPMASKS // - CC_ *, LC_*, PC_*, CP_*, TC_*, RC_
// #define NOVIRTUALKEYCODES // - VK_ *
// #define NOWINMESSAGES // - WM_ *, EM_*, LB_*, CB_*
// #define NOWINSTYLES // - WS_ *, CS_*, ES_*, LBS_*, SBS_*, CBS_*
// #define NOSYSMETRICS // - SM_ *
#define NOMENUS // - MF_ *
#define NOICONS // - IDI_ *
#define NOKEYSTATES // - MK_ *
#define NOSYSCOMMANDS // - SC_ *
#define NORASTEROPS // - Binary and Tertiary raster ops
// #define NOSHOWWINDOW // - SW_ *
#define NOEMRESOURCE // - OEM Resource values
#define NOATOM // - Atom Manager routines
#define NOCLIPBOARD // - Clipboard routines
// #define NOCOLOR // - Screen colors
#define NOCTLMGR // - Control and Dialog routines
#define NODRAWTEXT // - DrawText() and DT_*
//#define NOGDI // - All GDI definesand routines
#define NOKERNEL // - All KERNEL definesand routines
// #define NOUSER // - All USER definesand routines
// #define NONLS // - All NLS definesand routines
// #define NOMB // - MB_ * andMessageBox()
#define NOMEMMGR // - GMEM_ *, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE // - typedef METAFILEPICT
#define NOMINMAX // - Macros min(a, b) and max(a, b)
// #define NOMSG // - typedef MSGand associated routines
#define NOOPENFILE // - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL // - SB_ * andscrolling routines
#define NOSERVICE // - All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND // - Sound driver routines
#define NOTEXTMETRIC // - typedef TEXTMETRICand associated routines
#define NOWH // - SetWindowsHook and WH_*
// #define NOWINOFFSETS // - GWL_ *, GCL_*, associated routines
#define NOCOMM // - COMM driver routines
#define NOKANJI // - Kanji support stuff.
#define NOHELP // - Help engine interface.
#define NOPROFILER // - Profiler interface.
#define NODEFERWINDOWPOS // - DeferWindowPos routines
#define NOMCX // - Modem Configuration Extensions


#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_UNDEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_UNDEFINED
#undef UNICODE
#endif

//#include <dxgi1_2.h>
//#include <wrl.h>
