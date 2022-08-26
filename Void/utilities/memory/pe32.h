#pragma once
// actual structures WINNT v10.0, unions omitted
// @credits: https://www.vergiliusproject.com/kernels/x86/Windows%2010

#include <windows.h>
#pragma pack(push, 8)

//0x58 bytes (sizeof)
struct _PEB_LDR_DATA
{
	ULONG Length; //0x0
	UCHAR Initialized; //0x4
	VOID* SsHandle; //0x8
	_LIST_ENTRY InLoadOrderModuleList; //0x10
	_LIST_ENTRY InMemoryOrderModuleList; //0x20
	_LIST_ENTRY InInitializationOrderModuleList; //0x30
	VOID* EntryInProgress; //0x40
	UCHAR ShutdownInProgress; //0x48
	VOID* ShutdownThreadId; //0x50
};

static_assert(sizeof(_PEB_LDR_DATA) == 0x58);

//0x10 bytes (sizeof)
struct _UNICODE_STRING
{
	USHORT Length; //0x0
	USHORT MaximumLength; //0x2
	WCHAR* Buffer; //0x8
};

static_assert(sizeof(_UNICODE_STRING) == 0x10);

//0x18 bytes (sizeof)
struct _CURDIR
{
	_UNICODE_STRING DosPath; //0x0
	VOID* Handle; //0x10
};

static_assert(sizeof(_CURDIR) == 0x18);

//0x10 bytes (sizeof)
struct _STRING
{
	USHORT Length; //0x0
	USHORT MaximumLength; //0x2
	CHAR* Buffer; //0x8
};

static_assert(sizeof(_STRING) == 0x10);

//0x18 bytes (sizeof)
struct _RTL_DRIVE_LETTER_CURDIR
{
	USHORT Flags; //0x0
	USHORT Length; //0x2
	ULONG TimeStamp; //0x4
	_STRING DosPath; //0x8
};

static_assert(sizeof(_RTL_DRIVE_LETTER_CURDIR) == 0x18);

//0x18 bytes (sizeof)
struct _RTL_BALANCED_NODE
{
	_RTL_BALANCED_NODE* Children[2]; //0x0
	ULONGLONG ParentValue; //0x10
};

static_assert(sizeof(_RTL_BALANCED_NODE) == 0x18);

//0x440 bytes (sizeof)
struct _RTL_USER_PROCESS_PARAMETERS
{
	ULONG MaximumLength; //0x0
	ULONG Length; //0x4
	ULONG Flags; //0x8
	ULONG DebugFlags; //0xc
	VOID* ConsoleHandle; //0x10
	ULONG ConsoleFlags; //0x18
	VOID* StandardInput; //0x20
	VOID* StandardOutput; //0x28_PEB32
	VOID* StandardError; //0x30
	_CURDIR CurrentDirectory; //0x38
	_UNICODE_STRING DllPath; //0x50
	_UNICODE_STRING ImagePathName; //0x60
	_UNICODE_STRING CommandLine; //0x70
	VOID* Environment; //0x80
	ULONG StartingX; //0x88
	ULONG StartingY; //0x8c
	ULONG CountX; //0x90
	ULONG CountY; //0x94
	ULONG CountCharsX; //0x98
	ULONG CountCharsY; //0x9c
	ULONG FillAttribute; //0xa0
	ULONG WindowFlags; //0xa4
	ULONG ShowWindowFlags; //0xa8
	_UNICODE_STRING WindowTitle; //0xb0
	_UNICODE_STRING DesktopInfo; //0xc0
	_UNICODE_STRING ShellInfo; //0xd0
	_UNICODE_STRING RuntimeData; //0xe0
	_RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32]; //0xf0
	ULONGLONG EnvironmentSize; //0x3f0
	ULONGLONG EnvironmentVersion; //0x3f8
	VOID* PackageDependencyData; //0x400
	ULONG ProcessGroupId; //0x408
	ULONG LoaderThreads; //0x40c
	_UNICODE_STRING RedirectionDllName; //0x410
	_UNICODE_STRING HeapPartitionName; //0x420
	ULONGLONG* DefaultThreadpoolCpuSetMasks; //0x430
	ULONG DefaultThreadpoolCpuSetMaskCount; //0x438
	ULONG DefaultThreadpoolThreadMaximum; //0x43c
};

static_assert(sizeof(_RTL_USER_PROCESS_PARAMETERS) == 0x440);

//0x120 bytes (sizeof)
struct _LDR_DATA_TABLE_ENTRY
{
	_LIST_ENTRY InLoadOrderLinks; //0x0
	_LIST_ENTRY InMemoryOrderLinks; //0x10
	_LIST_ENTRY InInitializationOrderLinks; //0x20
	VOID* DllBase; //0x30
	VOID* EntryPoint; //0x38
	ULONG SizeOfImage; //0x40
	_UNICODE_STRING FullDllName; //0x48
	_UNICODE_STRING BaseDllName; //0x58
	UCHAR FlagGroup[4]; //0x68
	USHORT ObsoleteLoadCount; //0x6c
	USHORT TlsIndex; //0x6e
	_LIST_ENTRY HashLinks; //0x70
	ULONG TimeDateStamp; //0x80
	_ACTIVATION_CONTEXT* EntryPointActivationContext; //0x88
	VOID* Lock; //0x90
	struct _LDR_DDAG_NODE* DdagNode; //0x98
	_LIST_ENTRY NodeModuleLink; //0xa0
	struct _LDRP_LOAD_CONTEXT* LoadContext; //0xb0
	VOID* ParentDllBase; //0xb8
	VOID* SwitchBackContext; //0xc0
	_RTL_BALANCED_NODE BaseAddressIndexNode; //0xc8
	_RTL_BALANCED_NODE MappingInfoIndexNode; //0xe0
	ULONGLONG OriginalBase; //0xf8
	_LARGE_INTEGER LoadTime; //0x100
	ULONG BaseNameHashValue; //0x108
	enum _LDR_DLL_LOAD_REASON LoadReason; //0x10c
	ULONG ImplicitPathOptions; //0x110
	ULONG ReferenceCount; //0x114
	ULONG DependentLoadFlags; //0x118
	UCHAR SigningLevel; //0x11c
};

static_assert(sizeof(_LDR_DATA_TABLE_ENTRY) == 0x120);

//0x10 bytes (sizeof)
struct _LEAP_SECOND_DATA
{
	UCHAR Enabled; //0x0
	ULONG Count; //0x4
	_LARGE_INTEGER Data[1]; //0x8
};

static_assert(sizeof(_LEAP_SECOND_DATA) == 0x10);

//0x7c8 bytes (sizeof)
struct _PEB
{
	UCHAR InheritedAddressSpace; //0x0
	UCHAR ReadImageFileExecOptions; //0x1
	UCHAR BeingDebugged; //0x2
	UCHAR BitField; //0x3
	UCHAR Padding0[4]; //0x4
	VOID* Mutant; //0x8
	VOID* ImageBaseAddress; //0x10
	_PEB_LDR_DATA* Ldr; //0x18
	_RTL_USER_PROCESS_PARAMETERS* ProcessParameters; //0x20
	VOID* SubSystemData; //0x28
	VOID* ProcessHeap; //0x30
	_RTL_CRITICAL_SECTION* FastPebLock; //0x38
	_SLIST_HEADER* volatile AtlThunkSListPtr; //0x40
	VOID* IFEOKey; //0x48
	ULONG CrossProcessFlags; //0x50
	UCHAR Padding1[4]; //0x54
	VOID* KernelCallbackTable; //0x58
	ULONG SystemReserved; //0x60
	ULONG AtlThunkSListPtr32; //0x64
	VOID* ApiSetMap; //0x68
	ULONG TlsExpansionCounter; //0x70
	UCHAR Padding2[4]; //0x74
	VOID* TlsBitmap; //0x78
	ULONG TlsBitmapBits[2]; //0x80
	VOID* ReadOnlySharedMemoryBase; //0x88
	VOID* SharedData; //0x90
	VOID** ReadOnlyStaticServerData; //0x98
	VOID* AnsiCodePageData; //0xa0
	VOID* OemCodePageData; //0xa8
	VOID* UnicodeCaseTableData; //0xb0
	ULONG NumberOfProcessors; //0xb8
	ULONG NtGlobalFlag; //0xbc
	_LARGE_INTEGER CriticalSectionTimeout; //0xc0
	ULONGLONG HeapSegmentReserve; //0xc8
	ULONGLONG HeapSegmentCommit; //0xd0
	ULONGLONG HeapDeCommitTotalFreeThreshold; //0xd8
	ULONGLONG HeapDeCommitFreeBlockThreshold; //0xe0
	ULONG NumberOfHeaps; //0xe8
	ULONG MaximumNumberOfHeaps; //0xec
	VOID** ProcessHeaps; //0xf0
	VOID* GdiSharedHandleTable; //0xf8
	VOID* ProcessStarterHelper; //0x100
	ULONG GdiDCAttributeList; //0x108
	UCHAR Padding3[4]; //0x10c
	_RTL_CRITICAL_SECTION* LoaderLock; //0x110
	ULONG OSMajorVersion; //0x118
	ULONG OSMinorVersion; //0x11c
	USHORT OSBuildNumber; //0x120
	USHORT OSCSDVersion; //0x122
	ULONG OSPlatformId; //0x124
	ULONG ImageSubsystem; //0x128
	ULONG ImageSubsystemMajorVersion; //0x12c
	ULONG ImageSubsystemMinorVersion; //0x130
	UCHAR Padding4[4]; //0x134
	ULONGLONG ActiveProcessAffinityMask; //0x138
	ULONG GdiHandleBuffer[60]; //0x140
	VOID (*PostProcessInitRoutine)(); //0x230
	VOID* TlsExpansionBitmap; //0x238
	ULONG TlsExpansionBitmapBits[32]; //0x240
	ULONG SessionId; //0x2c0
	UCHAR Padding5[4]; //0x2c4
	_ULARGE_INTEGER AppCompatFlags; //0x2c8
	_ULARGE_INTEGER AppCompatFlagsUser; //0x2d0
	VOID* pShimData; //0x2d8
	VOID* AppCompatInfo; //0x2e0
	_UNICODE_STRING CSDVersion; //0x2e8
	struct _ACTIVATION_CONTEXT_DATA* ActivationContextData; //0x2f8
	struct _ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap; //0x300
	_ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData; //0x308
	_ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap; //0x310
	ULONGLONG MinimumStackCommit; //0x318
	VOID* SparePointers[4]; //0x320
	ULONG SpareUlongs[5]; //0x340
	VOID* WerRegistrationData; //0x358
	VOID* WerShipAssertPtr; //0x360
	VOID* pUnused; //0x368
	VOID* pImageHeaderHash; //0x370
	ULONG TracingFlags; //0x378
	UCHAR Padding6[4]; //0x37c
	ULONGLONG CsrServerReadOnlySharedMemoryBase; //0x380
	ULONGLONG TppWorkerpListLock; //0x388
	_LIST_ENTRY TppWorkerpList; //0x390
	VOID* WaitOnAddressHashTable[128]; //0x3a0
	VOID* TelemetryCoverageHeader; //0x7a0
	ULONG CloudFileFlags; //0x7a8
	ULONG CloudFileDiagFlags; //0x7ac
	CHAR PlaceholderCompatibilityMode; //0x7b0
	CHAR PlaceholderCompatibilityModeReserved[7]; //0x7b1
	_LEAP_SECOND_DATA* LeapSecondData; //0x7b8
	ULONG LeapSecondFlags; //0x7c0
	ULONG NtGlobalFlag2; //0x7c4
};

static_assert(sizeof(_PEB) == 0x7c8);

//0x10 bytes (sizeof)
struct _CLIENT_ID
{
	VOID* UniqueProcess; //0x0
	VOID* UniqueThread; //0x8
};

static_assert(sizeof(_CLIENT_ID) == 0x10);

//0x4e8 bytes (sizeof)
struct _GDI_TEB_BATCH
{
	ULONG Offset : 31; //0x0
	ULONG HasRenderingCommand : 1; //0x0
	ULONGLONG HDC; //0x8
	ULONG Buffer[310]; //0x10
};

static_assert(sizeof(_GDI_TEB_BATCH) == 0x4e8);

//0x28 bytes (sizeof)
struct _ACTIVATION_CONTEXT_STACK
{
	struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* ActiveFrame; //0x0
	_LIST_ENTRY FrameListCache; //0x8
	ULONG Flags; //0x18
	ULONG NextCookieSequenceNumber; //0x1c
	ULONG StackId; //0x20
};

static_assert(sizeof(_ACTIVATION_CONTEXT_STACK) == 0x28);

//0x1838 bytes (sizeof)
struct _TEB
{
	_NT_TIB NtTib; //0x0
	VOID* EnvironmentPointer; //0x38
	_CLIENT_ID ClientId; //0x40
	VOID* ActiveRpcHandle; //0x50
	VOID* ThreadLocalStoragePointer; //0x58
	_PEB* ProcessEnvironmentBlock; //0x60
	ULONG LastErrorValue; //0x68
	ULONG CountOfOwnedCriticalSections; //0x6c
	VOID* CsrClientThread; //0x70
	VOID* Win32ThreadInfo; //0x78
	ULONG User32Reserved[26]; //0x80
	ULONG UserReserved[5]; //0xe8
	VOID* WOW32Reserved; //0x100
	ULONG CurrentLocale; //0x108
	ULONG FpSoftwareStatusRegister; //0x10c
	VOID* ReservedForDebuggerInstrumentation[16]; //0x110
	VOID* SystemReserved1[30]; //0x190
	CHAR PlaceholderCompatibilityMode; //0x280
	UCHAR PlaceholderHydrationAlwaysExplicit; //0x281
	CHAR PlaceholderReserved[10]; //0x282
	ULONG ProxiedProcessId; //0x28c
	_ACTIVATION_CONTEXT_STACK _ActivationStack; //0x290
	UCHAR WorkingOnBehalfTicket[8]; //0x2b8
	LONG ExceptionCode; //0x2c0
	UCHAR Padding0[4]; //0x2c4
	_ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer; //0x2c8
	ULONGLONG InstrumentationCallbackSp; //0x2d0
	ULONGLONG InstrumentationCallbackPreviousPc; //0x2d8
	ULONGLONG InstrumentationCallbackPreviousSp; //0x2e0
	ULONG TxFsContext; //0x2e8
	UCHAR InstrumentationCallbackDisabled; //0x2ec
	UCHAR UnalignedLoadStoreExceptions; //0x2ed
	UCHAR Padding1[2]; //0x2ee
	_GDI_TEB_BATCH GdiTebBatch; //0x2f0
	_CLIENT_ID RealClientId; //0x7d8
	VOID* GdiCachedProcessHandle; //0x7e8
	ULONG GdiClientPID; //0x7f0
	ULONG GdiClientTID; //0x7f4
	VOID* GdiThreadLocalInfo; //0x7f8
	ULONGLONG Win32ClientInfo[62]; //0x800
	VOID* glDispatchTable[233]; //0x9f0
	ULONGLONG glReserved1[29]; //0x1138
	VOID* glReserved2; //0x1220
	VOID* glSectionInfo; //0x1228
	VOID* glSection; //0x1230
	VOID* glTable; //0x1238
	VOID* glCurrentRC; //0x1240
	VOID* glContext; //0x1248
	ULONG LastStatusValue; //0x1250
	UCHAR Padding2[4]; //0x1254
	_UNICODE_STRING StaticUnicodeString; //0x1258
	WCHAR StaticUnicodeBuffer[261]; //0x1268
	UCHAR Padding3[6]; //0x1472
	VOID* DeallocationStack; //0x1478
	VOID* TlsSlots[64]; //0x1480
	_LIST_ENTRY TlsLinks; //0x1680
	VOID* Vdm; //0x1690
	VOID* ReservedForNtRpc; //0x1698
	VOID* DbgSsReserved[2]; //0x16a0
	ULONG HardErrorMode; //0x16b0
	UCHAR Padding4[4]; //0x16b4
	VOID* Instrumentation[11]; //0x16b8
	_GUID ActivityId; //0x1710
	VOID* SubProcessTag; //0x1720
	VOID* PerflibData; //0x1728
	VOID* EtwTraceData; //0x1730
	VOID* WinSockData; //0x1738
	ULONG GdiBatchCount; //0x1740
	_PROCESSOR_NUMBER CurrentIdealProcessor; //0x1744
	ULONG GuaranteedStackBytes; //0x1748
	UCHAR Padding5[4]; //0x174c
	VOID* ReservedForPerf; //0x1750
	VOID* ReservedForOle; //0x1758
	ULONG WaitingOnLoaderLock; //0x1760
	UCHAR Padding6[4]; //0x1764
	VOID* SavedPriorityState; //0x1768
	ULONGLONG ReservedForCodeCoverage; //0x1770
	VOID* ThreadPoolData; //0x1778
	VOID** TlsExpansionSlots; //0x1780
	VOID* DeallocationBStore; //0x1788
	VOID* BStoreLimit; //0x1790
	ULONG MuiGeneration; //0x1798
	ULONG IsImpersonating; //0x179c
	VOID* NlsCache; //0x17a0
	VOID* pShimData; //0x17a8
	ULONG HeapData; //0x17b0
	UCHAR Padding7[4]; //0x17b4
	VOID* CurrentTransactionHandle; //0x17b8
	struct _TEB_ACTIVE_FRAME* ActiveFrame; //0x17c0
	VOID* FlsData; //0x17c8
	VOID* PreferredLanguages; //0x17d0
	VOID* UserPrefLanguages; //0x17d8
	VOID* MergedPrefLanguages; //0x17e0
	ULONG MuiImpersonation; //0x17e8
	volatile USHORT CrossTebFlags; //0x17ec
	USHORT SameTebFlags; //0x17ee
	VOID* TxnScopeEnterCallback; //0x17f0
	VOID* TxnScopeExitCallback; //0x17f8
	VOID* TxnScopeContext; //0x1800
	ULONG LockCount; //0x1808
	LONG WowTebOffset; //0x180c
	VOID* ResourceRetValue; //0x1810
	VOID* ReservedForWdf; //0x1818
	ULONGLONG ReservedForCrt; //0x1820
	_GUID EffectiveContainerId; //0x1828
};

static_assert(sizeof(_TEB) == 0x1838);

struct UNLINKED_MODULE
{
	HMODULE hModule;
	PLIST_ENTRY RealInLoadOrderLinks;
	PLIST_ENTRY RealInMemoryOrderLinks;
	PLIST_ENTRY RealInInitializationOrderLinks;
	PLIST_ENTRY RealHashLinks;
	_LDR_DATA_TABLE_ENTRY* Entry;
};

static_assert(sizeof(UNLINKED_MODULE) == 0x30);

#pragma pack(pop)
