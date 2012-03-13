/*********************************************************
 * Copyright (C) 2007 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation version 2.1 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *********************************************************/

/*
 * This header file is given out as part of the open source
 * tools. Things in this file are public, but they may not have 
 * been tested or documented, and that may change in future releases.
 * The public Vix API is defined in vix.h
 *
 * These definitions are used by the implementation of the vix
 * client, the VMX process, and the tols.
 *
 */

#ifndef _VIXOpenSource_h_
#define _VIXOpenSource_h_

#ifdef __cplusplus
extern "C"{
#endif 

/*
 * VIX_HIDE_BORA_DEPENDENCIES:
 *
 * This flag allows some mini-applications to use parts of Vix that will
 * someday make it into the public API, without including all of the include
 * directories in bora. Specifically, some VMware apps will want to use a
 * separate, more public, build tree, but still make use API that have not been
 * publicly released yet.
 */

/*
 * VIX_HIDE_FROM_JAVA
 *
 * Setting this flag minizes the functions exposed here.  The java
 * binding is generated by processing this header, resulting in a
 * large number of currently unused functions.  To keep the number
 * of functions that need to be exposed via vixWrapper, we hide all
 * but the needed functions to java.
 */

/*
 * If we're hiding functions from java, also hide the bora dependencies.
 */
#ifdef VIX_HIDE_FROM_JAVA
#define VIX_HIDE_BORA_DEPENDENCIES
#endif

#include "vm_basic_types.h"

#ifndef VIX_HIDE_BORA_DEPENDENCIES
#include "cryptoError.h"
#endif // VIX_HIDE_BORA_DEPENDENCIES

#include "vix.h"    // Vix Public API



/*
 *-----------------------------------------------------------------------------
 *
 * Vix Errors --
 *
 *-----------------------------------------------------------------------------
 */


#ifndef VIX_HIDE_BORA_DEPENDENCIES
VixError Vix_TranslateSystemError(int systemError);
VixError Vix_TranslateCryptoError(CryptoError cryptoError);
VixError Vix_TranslateErrno(int systemError);

#ifdef _WIN32
VixError Vix_TranslateCOMError(HRESULT comError);
VixError Vix_TranslateGuestRegistryError(int systemError);
#endif

#endif // VIX_HIDE_BORA_DEPENDENCIES

/*
 * This defines additional error codes.
 * The public error codes are defined in vix.h
 * These error codes are in addition to those.
 */
enum {
   VIX_E_OP_NOT_SUPPORTED_ON_NON_VMWARE_VM         = 3038,

   VIX_E_VI_OP_NOT_SUPPORTED_ON_GUEST              = 3048,
   VIX_E_INVALID_LOGIN_CREDENTIALS                 = 3050,

   /* File Errors */
   VIX_E_DIRECTORY_NOT_EMPTY                       = 20006,

   VIX_E_GUEST_AUTH_MULIPLE_MAPPINGS               = 20007,

   /* Guest Reg Errors */
   VIX_E_REG_KEY_INVALID                           = 20008,
   VIX_E_REG_KEY_HAS_SUBKEYS                       = 20009,
   VIX_E_REG_VALUE_NOT_FOUND                       = 20010,

   /* Reg Errors*/
   VIX_E_REG_INCORRECT_VALUE_TYPE                  = 25000
   /* WARNING. Do not exceed 2**16 */
};

/*
 *-----------------------------------------------------------------------------
 *
 * VIX Handles --
 *
 * These are common functions that apply to handles of several types. 
 *-----------------------------------------------------------------------------
 */

/*
 * VIX Property ID's
 *
 * These are used in the tools, but they are not (yet) part of the public
 * API. They may be promoted, but for now they are not tested or documented.
 */

enum {
   VIX_PROPERTY_VM_GUEST_TEMP_DIR_PROPERTY            = 203,

   /* VMX properties. */
   VIX_PROPERTY_VMX_VERSION                           = 4400,
   VIX_PROPERTY_VMX_PRODUCT_NAME                      = 4401,
   /* DEPRECTATED VIX_PROPERTY_VMX_VIX_FEATURES                      = 4402, */

   /* GuestOS and Tools properties. */
   VIX_PROPERTY_GUEST_TOOLS_VERSION                   = 4500,
   VIX_PROPERTY_GUEST_TOOLS_API_OPTIONS               = 4501,
   VIX_PROPERTY_GUEST_OS_FAMILY                       = 4502,
   VIX_PROPERTY_GUEST_OS_VERSION                      = 4503,
   VIX_PROPERTY_GUEST_OS_PACKAGE_LIST                 = 4504,
   VIX_PROPERTY_GUEST_NAME                            = 4505,
   VIX_PROPERTY_GUEST_POWER_OFF_SCRIPT                = 4506,
   VIX_PROPERTY_GUEST_POWER_ON_SCRIPT                 = 4507,
   VIX_PROPERTY_GUEST_RESUME_SCRIPT                   = 4508,
   VIX_PROPERTY_GUEST_SUSPEND_SCRIPT                  = 4509,
   VIX_PROPERTY_GUEST_TOOLS_PRODUCT_NAM               = 4511,
   VIX_PROPERTY_FOREIGN_VM_TOOLS_VERSION              = 4512,
   VIX_PROPERTY_VM_DHCP_ENABLED                       = 4513,
   VIX_PROPERTY_VM_IP_ADDRESS                         = 4514,
   VIX_PROPERTY_VM_SUBNET_MASK                        = 4515,
   VIX_PROPERTY_VM_DEFAULT_GATEWAY                    = 4516,
   VIX_PROPERTY_VM_DNS_SERVER_DHCP_ENABLED            = 4517,
   VIX_PROPERTY_VM_DNS_SERVER                         = 4518,
   VIX_PROPERTY_GUEST_TOOLS_WORD_SIZE                 = 4519,
   VIX_PROPERTY_GUEST_OS_VERSION_SHORT                = 4520,

   VIX_PROPERTY_GUEST_AUTH_SSPI_TOKEN                 = 4531,
   VIX_PROPERTY_GUEST_AUTH_SSPI_SESSION_ID            = 4532,
   VIX_PROPERTY_GUEST_AUTH_SESSION_TICKET             = 4533,

   /* VI guest operation status */
   VIX_PROPERTY_GUEST_START_PROGRAM_ENABLED           = 4540,
   VIX_PROPERTY_GUEST_LIST_PROCESSES_ENABLED          = 4541,
   VIX_PROPERTY_GUEST_TERMINATE_PROCESS_ENABLED       = 4542,
   VIX_PROPERTY_GUEST_READ_ENVIRONMENT_VARIABLE_ENABLED      = 4543,

   VIX_PROPERTY_GUEST_VALIDATE_CREDENTIALS_ENABLED     = 4544,
   VIX_PROPERTY_GUEST_ACQUIRE_CREDENTIALS_ENABLED      = 4545,
   VIX_PROPERTY_GUEST_RELEASE_CREDENTIALS_ENABLED      = 4546,

   VIX_PROPERTY_GUEST_MAKE_DIRECTORY_ENABLED           = 4547,
   VIX_PROPERTY_GUEST_DELETE_FILE_ENABLED              = 4548,
   VIX_PROPERTY_GUEST_DELETE_DIRECTORY_ENABLED         = 4549,
   VIX_PROPERTY_GUEST_MOVE_DIRECTORY_ENABLED           = 4550,
   VIX_PROPERTY_GUEST_MOVE_FILE_ENABLED                = 4551,
   VIX_PROPERTY_GUEST_CREATE_TEMP_FILE_ENABLED         = 4552,
   VIX_PROPERTY_GUEST_CREATE_TEMP_DIRECTORY_ENABLED    = 4553,
   VIX_PROPERTY_GUEST_LIST_FILES_ENABLED               = 4554,
   VIX_PROPERTY_GUEST_CHANGE_FILE_ATTRIBUTES_ENABLED   = 4555,
   VIX_PROPERTY_GUEST_INITIATE_FILE_TRANSFER_FROM_GUEST_ENABLED   = 4556,
   VIX_PROPERTY_GUEST_INITIATE_FILE_TRANSFER_TO_GUEST_ENABLED   = 4557,
   VIX_PROPERTY_GUEST_ADD_AUTH_PRINICPAL_ENABLED         = 4558,
   VIX_PROPERTY_GUEST_REMOVE_AUTH_PRINICPAL_ENABLED      = 4559,
   VIX_PROPERTY_GUEST_LIST_AUTH_PRINICPALS_ENABLED       = 4560,
   VIX_PROPERTY_GUEST_LIST_MAPPED_PRINICPALS_ENABLED     = 4561,
   VIX_PROPERTY_GUEST_CREATE_REGISTRY_KEY_ENABLED      = 4562,
   VIX_PROPERTY_GUEST_LIST_REGISTRY_KEYS_ENABLED       = 4563,
   VIX_PROPERTY_GUEST_DELETE_REGISTRY_KEY_ENABLED      = 4564,
   VIX_PROPERTY_GUEST_SET_REGISTRY_VALUE_ENABLED       = 4565,
   VIX_PROPERTY_GUEST_LIST_REGISTRY_VALUES_ENABLED     = 4566,
   VIX_PROPERTY_GUEST_DELETE_REGISTRY_VALUE_ENABLED    = 4567,
};



/*
 *-----------------------------------------------------------------------------
 *
 * PropertyList --
 *
 *-----------------------------------------------------------------------------
 */

/* 
 * VIX Property Type
 */

enum {
   //VIX_PROPERTYTYPE_ANY             = 0,
   //VIX_PROPERTYTYPE_INTEGER         = 1,
   //VIX_PROPERTYTYPE_STRING          = 2,
   //VIX_PROPERTYTYPE_BOOL            = 3,
   //VIX_PROPERTYTYPE_HANDLE          = 4,
   //VIX_PROPERTYTYPE_INT64           = 5,
   //VIX_PROPERTYTYPE_BLOB            = 6,
   VIX_PROPERTYTYPE_POINTER           = 7
};


#ifndef VIX_HIDE_FROM_JAVA
/*
 * This is a single name/value pair.
 */
typedef struct VixPropertyValue
{
   int                        propertyID;
   VixPropertyType            type;

   union {
      Bool                    boolValue;
      char                    *strValue;
      int                     intValue;
      int64                   int64Value;
      VixHandle               handleValue;
      struct {
         unsigned char        *blobContents;
         int                  blobSize;
      } blobValue;
      void                    *ptrValue;
   } value;

   Bool                       isDirty;
   Bool                       isSensitive;
   struct VixPropertyValue    *next;
} VixPropertyValue;


/*
 * This is the entire list.
 */
typedef struct VixPropertyListImpl
{
   VixPropertyValue    *properties;
} VixPropertyListImpl;


/*
 * This defines what action Deserialize should take when it encounters
 * a string that is not UTF-8.
 */
typedef enum VixPropertyListBadEncodingAction {
   /*
    * Abort the deserialization and return an error. This is the recommended
    * value since it is the strictest; you don't have to think about how
    * any clients or library code will handle escaped values.
    * This should always be used when parsing property lists passing arguments
    * to RPCs since we should be very strict in terms of actions we take
    * based on arguments.
    */
   VIX_PROPERTY_LIST_BAD_ENCODING_ERROR,

   /*
    * Escape any non-UTF-8 characters in the string, add the result to the
    * property list, and continue deserializing. This should only be used
    * when there are likely to be applications generated non-ASCII values
    * for the property list in question (e.g., the Tools properties sent by
    * pre-i18n Tools) and the properties are more informative then
    * actionable (something like the hostname of a guest, maybe).
    */
   VIX_PROPERTY_LIST_BAD_ENCODING_ESCAPE,
} VixPropertyListBadEncodingAction;


void VixPropertyList_Initialize(VixPropertyListImpl *propList);

void VixPropertyList_RemoveAllWithoutHandles(VixPropertyListImpl *propList);

VixError VixPropertyList_Serialize(VixPropertyListImpl *propListImpl,
                                   Bool dirtyOnly,
                                   size_t *resultSize,
                                   char **resultBuffer);

VixError VixPropertyList_Deserialize(VixPropertyListImpl *propListImpl,
                                     const char *buffer,
                                     size_t bufferSize,
                                     VixPropertyListBadEncodingAction action);
 
VixError
VixPropertyList_DeserializeNoClobber(VixPropertyListImpl *propListImpl,
                                     const char *buffer,
                                     size_t bufferSize,
                                     VixPropertyListBadEncodingAction action);

VixError VixPropertyList_GetString(struct VixPropertyListImpl *propList,
                                   int propertyID,
                                   int index,
                                   char **resultValue);
                                                 
VixError VixPropertyList_SetString(struct VixPropertyListImpl *propList,
                                   int propertyID,
                                   const char *value);

VixError VixPropertyList_GetInteger(struct VixPropertyListImpl *propList,
                                    int propertyID,
                                    int index,
                                    int *resultValue);

VixError VixPropertyList_SetInteger(struct VixPropertyListImpl *propList,
                                    int propertyID,
                                    int value);

VixError VixPropertyList_GetBool(struct VixPropertyListImpl *propList,
                                 int propertyID,
                                 int index,
                                 Bool *resultValue);

VixError VixPropertyList_SetBool(struct VixPropertyListImpl *propList,
                                 int propertyID,
                                 Bool value);

VixError VixPropertyList_GetHandle(struct VixPropertyListImpl *propList,
                                   int propertyID,
                                   int index,
                                   VixHandle *resultValue);

VixError VixPropertyList_SetHandle(struct VixPropertyListImpl *propList,
                                   int propertyID,
                                   VixHandle value);

VixError VixPropertyList_GetInt64(struct VixPropertyListImpl *propList,
                                  int propertyID,
                                  int index,
                                  int64 *resultValue);

VixError VixPropertyList_SetInt64(struct VixPropertyListImpl *propList,
                                  int propertyID,
                                  int64 value);

VixError VixPropertyList_GetBlob(struct VixPropertyListImpl *propList,
                                 int propertyID,
                                 int index,
                                 int *resultSize,
                                 unsigned char **resultValue);

VixError VixPropertyList_SetBlob(struct VixPropertyListImpl *propList,
                                 int propertyID,
                                 int blobSize,
                                 const unsigned char *value);

VixError VixPropertyList_RemoveAll(VixHandle propertyListHandle);

VixError VixPropertyList_Remove(VixHandle propertyListHandle,
                                int propertyID);

VixError VixPropertyList_RemoveFromImpl(VixPropertyListImpl *propList,
                                        int propertyID);

VixError VixPropertyList_AppendProperties(VixHandle handle, 
                                          int firstPropertyID,
                                          ...);

VixError VixPropertyList_FindProperty(VixPropertyListImpl *propList,
                                      int propertyID,
                                      VixPropertyType type,
                                      int index,
                                      Bool createIfMissing,
                                      VixPropertyValue **resultEntry);

Bool VixPropertyList_PropertyExists(VixPropertyListImpl *propList,
                                    int propertyID,
                                    VixPropertyType type);

VixError VixPropertyListAppendProperty(VixPropertyListImpl *propList,
                                       int propertyID,
                                       VixPropertyType type,
                                       VixPropertyValue **resultEntry);

int VixPropertyList_GetNumProperties(VixHandle propertyListHandle,
                                     int propertyID);

VixError VixPropertyList_GetOptionalProperties(VixHandle propertyListHandle, 
                                               int firstPropertyID,
                                               ...);

VixError VixPropertyList_GetIndexedProperties(VixHandle propertyListHandle, 
                                              Bool ignoreMissingProperties,
                                              int firstPropertyID,
                                              int firstPropertyIndex,
                                              ...);

VixError VixPropertyList_GetPtr(VixPropertyListImpl *propList,
                                int propertyID,
                                int index,
                                void **resultValue);

VixError VixPropertyList_SetPtr(VixPropertyListImpl *propList,
                                int propertyID,
                                void *value);

int VixPropertyList_NumItems(VixPropertyListImpl *propList);

Bool VixPropertyList_Empty(VixPropertyListImpl *propList);


#endif   // VIX_HIDE_FROM_JAVA


/*
 *-----------------------------------------------------------------------------
 *
 * VixVM --
 *
 * This describes the persistent configuration state of a single VM. The 
 * VM may or may not be running.
 *
 *-----------------------------------------------------------------------------
 */

#define VIX_FOREIGN_VM_TOOLS_VMX_VERSION_STRING    "Foreign VM Tools"

/*
 * These are the types of variable strings we can read in the VM.
 */
enum {
   //VIX_VM_GUEST_VARIABLE            = 1,
   //VIX_VM_CONFIG_RUNTIME_ONLY       = 2,
   //VIX_GUEST_ENVIRONMENT_VARIABLE   = 3,
   VIX_GUEST_CONFIG                 = 4,
   VIX_VMDB_VARIABLE                = 5,
};

/*
 * Options for RunProgramInGuest().
 */
enum {
   //VIX_RUNPROGRAM_RETURN_IMMEDIATELY       = 0x0001,
   //VIX_RUNPROGRAM_ACTIVATE_WINDOW          = 0x0002,
   /* DEPRECATED VIX_RUNPROGRAM_USE_INTERACTIVE_SESSION  = 0x0004, */
   VIX_RUNPROGRAM_RUN_AS_LOCAL_SYSTEM      = 0x0008,
};


/*
 * Options for VixVM_ListFileSystemsInGuest()
 */
enum {
   VIX_FILESYSTEMS_SHOW_ALL     = 0x000,
};


/*
 * These are the property flags for each file.  This is a superset
 * of the values defined in the public header.
 */

enum {
   //VIX_FILE_ATTRIBUTES_DIRECTORY     = 0x0001,
   //VIX_FILE_ATTRIBUTES_SYMLINK       = 0x0002,
   VIX_FILE_ATTRIBUTES_HIDDEN          = 0x0004,
   VIX_FILE_ATTRIBUTES_READONLY        = 0x0008,
};

/*
 * These are the propery flags for SetGuestFileAttributes request.
 */

enum {
   VIX_FILE_ATTRIBUTE_SET_ACCESS_DATE        = 0x0001,
   VIX_FILE_ATTRIBUTE_SET_MODIFY_DATE        = 0x0002,
   VIX_FILE_ATTRIBUTE_SET_READONLY           = 0x0004,
   VIX_FILE_ATTRIBUTE_SET_HIDDEN             = 0x0008,
   VIX_FILE_ATTRIBUTE_SET_UNIX_OWNERID       = 0x0010,
   VIX_FILE_ATTRIBUTE_SET_UNIX_GROUPID       = 0x0020,
   VIX_FILE_ATTRIBUTE_SET_UNIX_PERMISSIONS   = 0x0040,
};

/*
 * Principal types for IdProvider management.
 */
typedef enum VixGuestAuthPrincipalType {
   VIX_GUEST_AUTH_PRINCIPAL_TYPE_NONE              = 0,
   VIX_GUEST_AUTH_PRINCIPAL_TYPE_NAMED             = 1,
   VIX_GUEST_AUTH_PRINCIPAL_TYPE_ANY               = 2,
} VixGuestAuthPrincipalType;

/*
 * Types for Windows Registry Management.
 */

/*
 * In a 64 bit Windows OS, the registry has two views: 32 bit and 64 bit.
 * Normally using "registry redirection", 32 bit applications automatically
 * access the 32 bit view, while 64 bit applications access 64 bit view.
 * However, applications can pass a flag to specifically access either 32
 * or 64 bit registry view, irrespective of their own bitness.
 *
 * NOTE: 32 bit windows will ignore these flags if passed.
 *
 * Based on the above, and on the fact that in our case 32 bit tools run only
 * on 32 bit windows and 64 bit tools run only on 64 bit windows, we get the
 * following registry view access matrix:
 * Application      wowNative            wow32             wow64
 * -----------      --------             -----             -----
 * 32 bit tools     32 bit view          32 bit view       32 bit view
 * 64 bit tools     64 bit view          32 bit view       64 bit view
 * So in essence, we always access 32 bit view UNLESS its 64 bit tools and user
 * has specified either wowNative or wow64 as the registry access flag.
 */

typedef enum VixRegKeyWowBitness {
   VIX_REGISTRY_KEY_WOW_NATIVE        = 0,
   VIX_REGISTRY_KEY_WOW_32            = 1,
   VIX_REGISTRY_KEY_WOW_64            = 2,
} VixRegKeyWowBitness;

typedef enum VixRegValueDataType {
   VIX_REGISTRY_VALUE_DWORD           = 0,
   VIX_REGISTRY_VALUE_QWORD           = 1,
   VIX_REGISTRY_VALUE_STRING          = 2,
   VIX_REGISTRY_VALUE_EXPAND_STRING   = 3,
   VIX_REGISTRY_VALUE_MULTI_STRING    = 4,
   VIX_REGISTRY_VALUE_BINARY          = 5,
} VixRegValueDataType;

/*
 *-----------------------------------------------------------------------------
 *
 * VixDebug --
 *
 *      Vix debug macros, to allow conditional printf debugging with file/line
 *      information.
 *
 *      Use as:
 *
 *      VIX_DEBUG(("test debug message: %s %d\n", stringArg, intArg));
 *       
 *       Output will go to logfile if VIX_DEBUG_PREFERENCE_NAME is non-zero
 *
 *      VIX_DEBUG_LEVEL(3, ("test debug message: %s %d\n", stringArg, intArg));
 *
 *       Output will go to logfile if VIX_DEBUG_PREFERENCE_NAME is >=
 *       the first argument to the macro.
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef VIX_HIDE_FROM_JAVA

extern int vixDebugGlobalSpewLevel;
extern int vixApiTraceGlobalSpewLevel;
extern char *VixAllocDebugString(char *fmt, ...) PRINTF_DECL(1,2);
extern void VixDebugInit(int debugLevel, int apiTraceLevel,
                         Bool panicOnVixAssert);
extern const char *VixDebug_GetFileBaseName(const char *path);
extern void VixAssert(const char *cond, const char *file, int lineNum);

extern VixError VixLogError(VixError err, const char *function, int line,
                const char *fileName, unsigned long threadId, const char *fmt, ...)
                PRINTF_DECL(6, 7);


/*
 * preference name for client and vmx
 */
#define VIX_DEBUG_PREFERENCE_NAME  "vix.debugLevel"
#define VIX_ASSERT_PREFERENCE_NAME "vix.doAssert"
#define VIX_API_TRACE_PREFERENCE_NAME "vix.apiTraceLevel"

/*
 * Assertions.  Normally we'd just use ASSERT(), but we've hit many cases
 * where ASSERT() is desired by foundry developers, but not by foundry users.
 * So we have our own VIX_ASSERT(), which is configured via a preference,
 * vix.doAssert, off by default.
 */
#ifdef VMX86_DEBUG
# ifdef __cplusplus
# define  VIX_ASSERT(cond) (UNLIKELY(!(cond)) ? VixAssert(#cond, __FILE__, __LINE__) : (void) 0)
# else
# define  VIX_ASSERT(cond) (UNLIKELY(!(cond)) ? VixAssert(#cond, __FILE__, __LINE__) : 0)
# endif
#else
#define  VIX_ASSERT(cond)
#endif

#define DEFAULT_VIX_LOG_LEVEL    0
#define DEFAULT_VIX_API_TRACE_LEVEL 0

#define VIX_DEBUG_LEVEL(logLevel, s) if (logLevel <= vixDebugGlobalSpewLevel) \
    {  char *debugString = VixAllocDebugString s; \
       Log("Vix: [%lu %s:%d]: %s", (unsigned long)Util_GetCurrentThreadId(),    \
           VixDebug_GetFileBaseName(__FILE__), __LINE__, debugString); \
       free(debugString); }

#define VIX_DEBUG(s) if (0 != vixDebugGlobalSpewLevel) \
    {  char *debugString = VixAllocDebugString s; \
       Log("Vix: [%lu %s:%d]: %s", (unsigned long)Util_GetCurrentThreadId(),    \
           VixDebug_GetFileBaseName(__FILE__), __LINE__, debugString); \
       free(debugString); }

#define VIX_DEBUG_ALWAYS(s) {  char *debugString = VixAllocDebugString s; \
       Log("Vix: [%lu %s:%d]: %s", (unsigned long) Util_GetCurrentThreadId(),         \
           VixDebug_GetFileBaseName(__FILE__), __LINE__, debugString); \
       free(debugString); }

#define VIX_API_TRACE_ON() (vixApiTraceGlobalSpewLevel > 0)

#define VIX_API_LOG(s) if (VIX_API_TRACE_ON())                       \
    {  char *debugString = VixAllocDebugString s;                    \
       Log("VixApiLog: %lu %s %s\n", (unsigned long) Util_GetCurrentThreadId(),\
           __FUNCTION__, debugString);                               \
       free(debugString); }

// If no MSG is given, a description of err is suplemented.
#define VIX_ERROR(err) (VIX_ERROR_MSG(err, NULL))
#define VIX_ERROR_MSG(err, ...) (VixLogError(err, __FUNCTION__, __LINE__, \
      VixDebug_GetFileBaseName(__FILE__), \
      (unsigned long)Util_GetCurrentThreadId(), __VA_ARGS__))

#endif   // VIX_HIDE_FROM_JAVA

#ifdef __cplusplus
} // extern "C" {
#endif 


#endif // _VIXOpenSource_h_



