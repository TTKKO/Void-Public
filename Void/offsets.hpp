/*
 *		offsets.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		VRChat's function's memory locations
 */
// ReSharper disable CppInconsistentNaming
#pragma once

/* - UnityPlayer Patches  - */
constexpr auto ACCESSOR_READHEADER = 0x83ae50; // @xref: ArchiveStorageHeader::ReadHeaderSignature
constexpr auto TRANSFORM_COUNTNODESDEEP = 0xdf29f0; // @xref: CountNodesDeep
constexpr auto DEBUGPOSTPROCESSEDSTACKTRACE = 0xddbdc0; // @xref: DebugStringToFilePostprocessedStacktrace
constexpr auto REALLOCATESTRING = 0xc69f0; // @xref: core::StringStorageDefault<char>::reallocate
constexpr auto FLOATTRANSFER = 0xc8230; // @xref: SafeBinaryRead::Transfer<float>
constexpr auto AUDIOMIXERPRODUCE = 0xa86270; // @xref: ProduceHelper<AudioMixer,0>::Produce
constexpr auto READEROOB = 0x7b9eb0; // @xref: CachedReader::OutOfBoundsError
constexpr auto READOBJECT = 0x90bec0; // @xref: SerializedFile::ReadObject
constexpr auto DOWNLOADHANDLER_ASSETBUNDLE_GETASSETBUNDLE = 0x33EF80; // @xref: DownloadHandlerAssetBundle::GetAssetBundle
constexpr auto ASSETBUNDLE_LOADFROMASYNCOP_PERFORM = 0x2E34E0; // @xref: AssetBundleLoadFromAsyncOperation::Perform
constexpr auto PERSISTENTMANAGER_READOBJECTTHREADED = 0x903B80; // @xref: PersistentManager::ReadObjectThreaded
constexpr auto PERSISTENTMANAGER_READANDACTIVEOBJECTTHREADED = 0x9036B0; // @xref: PersistentManager::ReadAndActivateObjectThreaded
constexpr auto PERSISTENTMANAGER_REGISTERPARTIALLYLOADEDOBJECTINTERNAL = 0x903D70; // @xref: PersistentManager::RegisterPartiallyLoadedObjectInternal
constexpr auto ASSETBUNDLE_LOADASSETOP_GETLOADEDASSET = 0x2D5E10; // @xref: AssetBundleLoadAssetOperation::GetLoadedAsset
constexpr auto GAMEOBJECT_TRANSFER_STREAMEDBINARYREAD = 0x5A4A50; // @xref: GameObject::Transfer<StreamedBinaryRead>
constexpr auto AWAKEFROMLOADQUEUE_ADD = 0x90EEB0; // @xref: AwakeFromLoadQueue::Add
constexpr auto CACHEDREADERREAD = 0x7ba380; // @xref: CachedReader::Read
constexpr auto CACHEDREADERUPDATEREACHCACHE = 0x7BA6A0; // @xref: CachedReader::UpdateReadCache
constexpr auto CACHEDREADERSETPOSITION = 0x7BA5E0; // @xref: CachedReader::SetPosition
constexpr auto CACHEDREADEREND = 0x7B9C70; // @xref: CachedReader::End
constexpr auto NAMEDOBJECT_VIRTUALREDIRECTTRANSFER = 0x59a720; // @xref: NamedObject::VirtualRedirectTransfer
constexpr auto SERIALIZETRAITS_FORSTRINGTYPES = 0xDB490; // @xref: SerializeTraitsForStringTypes
constexpr auto SERIALIZETRAITS_RESIZE_KEYFRAME = 0x1720F0; // @xref: SerializeTraits<dynamic_array<KeyframeTpl<float>,0>>::ResizeSTLStyleArray
constexpr auto STREAMEDBINARYREAD_READDIRECT = 0x916380; // @xref: StreamedBinaryRead::ReadDirect
constexpr auto TRANSFERFIELD_ARRAY_STREAMEDBINARYREAD_CONVERTERSTRING = 0x8E3CC0; // @xref: TransferField_Array<StreamedBinaryRead,Converter_String>
constexpr auto STREAMEDBINARYREAD_TRANSFERSTLSTYLEARRAY_ARRAYOFMANAGEDOBJECTS = 0x8E8EA0; // @xref: StreamedBinaryRead::TransferSTLStyleArray<ArrayOfManagedObjectsTransferer>
constexpr auto DHA_ALLOCATE = 0x597070; // @xref: DynamicHeapAllocator::Allocate
constexpr auto RESIZESTLSTYLEARRAY = 0x172180; // @xref: SerializeTraits<dynamic_array<PPtr<Object>,0>>::ResizeSTLStyleArray
/* - UnityPlayer Methods - */
constexpr auto PERSISTENTMANAGER_UNLOCK = 0x904550; // @xref: PersistentManager::Unlock
constexpr auto DESTROYOBJECT_HIGHLEVEL = 0x78E410; // @xref: DestroyObjectHighLevel


//ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ
/* - GameAssembly - */
// constexpr auto DECOMPRESS_BYTES = 0x275E5D0; // @todo: sig 3-21-22
// constexpr auto COMPRESS_BYTES = 0x275C970; // @todo: sig 3-21-22

constexpr auto SETONSLIDE = 0x75CA30; // @todo: sig
constexpr auto SETONCLICK = 0x66C2F0; // @todo: sig
constexpr auto GETONCLICK = 0x670540; // @todo: sig
constexpr auto VRCPLAYER_LOADALLAVATARS = 0x639330;
constexpr auto VRCPLAYER_LOADAVATAR = 0x6394E0;
constexpr auto VRCUIMANAGER_PLACE = 0x1896dd0;
constexpr auto CREATEEXTERNALTEXTURE = 0x35a0c80;
constexpr auto ONAVATARLOAD = 0x63b4a0;
constexpr auto ONLEFTROOM = 0x992960;
constexpr auto PHOTONPLAYERJOIN = 0x994fa0;
constexpr auto PHOTONPLAYERLEFT = 0x9943E0;
constexpr auto SCENELOADEDINTERNAL = 0x35992e0;
constexpr auto SCENEUNLOADEDINTERNAL = 0x3599390;
constexpr auto SLIDERSLIDEEVENTCTOR = 0x51c3950;
constexpr auto ONAVATARDOWNLOAD = 0x3def420;
constexpr auto ASSETBUNDLELOAD = 0x1be04a0;
constexpr auto ASSETBUNDLELOADWORLD = 0x3def380;
constexpr auto CUSTOMSCENESCTOR = 0x10ec3b0;
constexpr auto APIWORLDCTOR = 0x1e34660;
constexpr auto UDONSYNCRUNPROGRAMASRPC = 0x82f9c0;
constexpr auto UDONRUNPROGRAMSTR = 0x511db30;
constexpr auto FROMBASE64STRING = 0x25aa0b0;
constexpr auto TOBASE64STRING = 0x25aae30;
constexpr auto GETBYTES = 0x32e3f80;
constexpr auto BLOCKCOPY = 0x2ee4c60;
constexpr auto OFFLINE_MODE = 0x1976560;
constexpr auto FAKE_PING = 0x2c01d70;
constexpr auto ANTI_PORTAL = 0x653EA0;
constexpr auto RECEIVEAUDIO = 0x14cf000;
constexpr auto SPAWNEMOJIRPC = 0x632150;
constexpr auto PLAYEMOTERPC = 0x631fc0;
constexpr auto APIUSERCTOR = 0x1972a20;
constexpr auto SENDFRIENDREQUEST = 0x145ec30;
constexpr auto ISFRIENDSWITH = 0x196fc40;
constexpr auto HASTAG = 0x196f9b0;
constexpr auto VRCPLAYERCUSTOMPLATES = 0x635a40;
constexpr auto GETCUSTOMDATA = 0x2bf6b60;
constexpr auto GETITEM = 0x2bf6be0;
constexpr auto USERINTERACTMENU = 0xeafe10;
constexpr auto PLAYERCURRENTUSER = 0x190ba30;
constexpr auto PLAYERTOSTRING = 0x777390;
constexpr auto GOTOROOM = 0x26bd7b0;
constexpr auto SETNAMEPLATECOLOR = 0x1495c40;
constexpr auto SETMUTESTATUS = 0x26cb890;
constexpr auto SETINTERACTABLE = 0x30db3f0;
constexpr auto SETCOLOR = 0x2e39c10;
constexpr auto VRCUIPOPUPMANAGER = 0x1492C80;
constexpr auto SETISOVERLAY = 0xb8bc10;
constexpr auto SHOWALERT = 0x1495c40;
constexpr auto TOGGLECLICKEDEVENTCTOR = 0x51c65c0;
constexpr auto VRCHANDGRASPER = 0x20b3990;
constexpr auto TMPSETFONTSIZE = 0xb8b930;
constexpr auto TOGGLESET = 0x51c74e0;
constexpr auto TOINT32 = 0x29cc110;
constexpr auto VRCUIMANAGER = 0x18984D0;
constexpr auto HUDMSG = 0x1896480;
constexpr auto VRCUIPAGEONCHANGE = 0x20a5dc0;
constexpr auto UIMANAGERIMPL = 0x9af3b0;
constexpr auto UIMANAGERIMPL_ONMENUCLOSE = 0x9abf50;
constexpr auto UIMANAGERIMPL_ONMENUOPEN = 0x9b01b0;
constexpr auto VRCUIPAGE_ONFLOWPAGE = 0xa18d10;
constexpr auto GETPLAYERPOSITION = 0x26bfcd0;
constexpr auto GETPLAYERROTATION = 0x26bfd70;
constexpr auto GETTYPE = 0x3c65d80;
constexpr auto GETTYPES = 0x2ce8f30;
constexpr auto TYPETOSTRING = 0x38e6dc0;
constexpr auto UNITYACTIONCTOR = 0x662880;
constexpr auto ARRAYLIST_CTOR = 0x25a35e0;
constexpr auto BUTTONCLICKCTOR = 0xEFD920;
constexpr auto PLAYERJOINED = 0x992c90;
constexpr auto PLAYERLEFT = 0x9932F0;
constexpr auto PLAYERGETPLAYER = 0x1af58a0;
constexpr auto GETALLPLAYERS = 0x1af5120;
constexpr auto GETPLAYERBYPHOTON = 0x1af5790;
constexpr auto GETROOMID = 0x10f16b0;
constexpr auto GETVRCUIPAGE = 0x18997c0;
constexpr auto MOVEMENT_SERIALIZE = 0xbc4060;
constexpr auto GETTYPE_TYPE_BOOL_BOOL = 0x38e5540;
constexpr auto ADDLISTENER = 0x36da420;
constexpr auto SET_FONTSIZE = 0x51c6080;
constexpr auto GET_FORWARD = 0x38c9a10;
constexpr auto GET_RIGHT = 0x38ca080;
constexpr auto GET_UP = 0x38ca270;
constexpr auto SENDREQUEST = 0x1976a40;
constexpr auto UISHADOWPLATECOLOR = 0xcde2b0;
constexpr auto VIDEOPLAYERURL = 0x50491a0;
constexpr auto ONOPRAISEEVENT = 0x96e1d0;
constexpr auto ONEVENTPATCH = 0x968e10;
constexpr auto APIAVATARCTOR = 0x213ea70;
constexpr auto PAGEAVATARCCTOR = 0x1163f80;
constexpr auto FORCECHANGEAVATAR = 0x8bb0e0;
constexpr auto GETSPRITEIMAGE = 0x8c7420;
constexpr auto SETSPRITEIMAGE = 0x2e43950;
constexpr auto GETMATERIALIMAGE = 0x2e42fb0;
constexpr auto SETMATERIALIMAGE = 0x2e39c60;
constexpr auto GRAPHICGETCOLOR = 0xf123a0;
constexpr auto HLFXTOGGLERENDERER = 0x309ea60;
constexpr auto HLFXGETINSTANCE = 0x309E9C0;
constexpr auto SWITCHAVATARRPC = 0x690e30;
constexpr auto ANTIEVENT = 0x143a060;
constexpr auto MODERATIONMANAGER_INSTANCE = 0xAA2E20;
constexpr auto MODERATIONMANAGER_CHECKMODERATION = 0xaa2960;
constexpr auto DESERIALIZEARRAY = 0x126bdb0;
constexpr auto SERIALIZEPARAMETERS = 0x113e9c0;
constexpr auto SET_TEXT = 0x51c6470;
constexpr auto TYPE_GETMETHODS = 0x38e4c00;
constexpr auto TYPE_GETTYPE = 0x1f2f940;
constexpr auto TYPE_GETTYPE_WITHNAME = 0x38e5880;
constexpr auto OBJECT_GETTYPE = 0x35c0fa0;
constexpr auto OBJECT_TOSTRING = 0x35c0fc0;
constexpr auto TYPE_GETMETHOD = 0x38e4b50;
constexpr auto GETCONSTRUCTORINFO = 0x38e3570;
constexpr auto METHODBASE_INVOKE = 0x35bb730;
constexpr auto PARAMAETERINFO_GETNAME = 0x679e90;
constexpr auto CONSTRUCTORINFO_INVOKE = 0x35b4730;
constexpr auto RAYCTOR = 0x399a460;
constexpr auto RICHTEXT = 0x51c6410;
constexpr auto SENDPOSTREQUEST = 0x19764a0;
