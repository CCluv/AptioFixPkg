/** @file
  Clean several important nvram variables to recover from issues.

Copyright (c) 2018, vit9696. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Guid/LiluVariables.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>

STATIC
EFI_GUID
mLiluNormalVariableGuid     = LILU_NORMAL_VARIABLE_GUID;

STATIC
EFI_GUID
mLiluReadOnlyVariableGuid   = LILU_READ_ONLY_VARIABLE_GUID;

STATIC
EFI_GUID
mLiluWriteOnlyVariableGuid  = LILU_WRITE_ONLY_VARIABLE_GUID;

STATIC
EFI_GUID
mOzmosisProprietary1Guid    = { 0x4D1FDA02, 0x38C7, 0x4A6A, { 0x9C, 0xC6, 0x4B, 0xCC, 0xA8, 0xB3, 0x01, 0x02 } };

STATIC
EFI_GUID
mOzmosisProprietary2Guid    = { 0x1F8E0C02, 0x58A9, 0x4E34, { 0xAE, 0x22, 0x2B, 0x63, 0x74, 0x5F, 0xA1, 0x01 } };

STATIC
EFI_GUID
mOzmosisProprietary3Guid    = { 0x9480E8A1, 0x1793, 0x46C9, { 0x91, 0xD8, 0x11, 0x08, 0xDB, 0xA4, 0x73, 0x1C } };

STATIC
BOOLEAN
IsDeletableVariable (
  IN CHAR16    *Name,
  IN EFI_GUID  *Guid
  )
{
  //
  // Apple GUIDs
  //
  if (CompareGuid (Guid, &gAppleVendorVariableGuid)
    || CompareGuid (Guid, &gAppleBootVariableGuid)
    || CompareGuid (Guid, &gAppleTrbSecureVariableGuid)) {
    return TRUE;
  //
  // Global variable boot options
  //
  } else if (CompareGuid (Guid, &gEfiGlobalVariableGuid)) {
    //
    // Only erase boot and driver entries for BDS
    // I.e. BootOrder, Boot####, DriverOrder, Driver####
    //
    if (!StrnCmp (Name, L"Boot", StrLen(L"Boot"))
      || !StrnCmp (Name, L"Driver", StrLen(L"Driver"))) {
      return TRUE;
    }
  //
  // Lilu extensions if present
  //
  } else if (CompareGuid (Guid, &mLiluNormalVariableGuid)
    || CompareGuid (Guid, &mLiluReadOnlyVariableGuid)
    || CompareGuid (Guid, &mLiluWriteOnlyVariableGuid)) {
    return TRUE;
  //
  // Ozmozis extensions if present
  //
  } else if (CompareGuid (Guid, &mOzmosisProprietary1Guid)
    || CompareGuid (Guid, &mOzmosisProprietary2Guid)
    || CompareGuid (Guid, &mOzmosisProprietary3Guid)) {
    return TRUE;
  }

  return FALSE;
}

STATIC
VOID
DeleteVariables (
  VOID
  )
{
  EFI_GUID     CurrentGuid;
  EFI_STATUS   Status;
  CHAR16       *Buffer = NULL;
  CHAR16       *TmpBuffer;
  UINTN        BufferSize = 0;
  UINTN        RequestedSize = 1024;
  BOOLEAN      Restart = TRUE;
  BOOLEAN      CriticalFailure = FALSE;

  do {
    if (RequestedSize > BufferSize) {
      TmpBuffer = AllocateZeroPool (RequestedSize);
      if (TmpBuffer) {
        if (Buffer) {
          CopyMem (TmpBuffer, Buffer, BufferSize);
          FreePool (Buffer);
        }
        Buffer = TmpBuffer;
        BufferSize = RequestedSize;
      } else {
        Print (L"Failed to allocate variable name buffer of %u bytes\n", (UINT32)RequestedSize);
        break;
      }
    }

    if (Restart) {
      ZeroMem (&CurrentGuid, sizeof(CurrentGuid));
      ZeroMem (Buffer, BufferSize);
      Restart = FALSE;
    }

    Status = gRT->GetNextVariableName (&RequestedSize, Buffer, &CurrentGuid);

    if (!EFI_ERROR (Status)) {
      if (IsDeletableVariable (Buffer, &CurrentGuid)) {
        Print (L"Deleting %g:%s... ", &CurrentGuid, Buffer);
        Status = gRT->SetVariable (Buffer, &CurrentGuid, 0, 0, NULL);
        if (!EFI_ERROR (Status)) {
          Print (L"OK\n");
          Restart = TRUE;
        } else {
          Print (L"FAIL (%r)\n", Status);
          break;
        }
      }
    } else if (Status != EFI_BUFFER_TOO_SMALL && Status != EFI_NOT_FOUND) {
      if (!CriticalFailure) {
        Print (L"Unexpected error (%r), trying to rescan\n", Status);
        CriticalFailure = TRUE;
      } else {
        Print (L"Unexpected error (%r), aborting\n", Status);
        break;
      }
    }

  } while (Status != EFI_NOT_FOUND);

  if (Buffer) {
    FreePool (Buffer);
  }
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"Performing quick NVRAM cleanup...\n");

  DeleteVariables ();

  Print (L"Done quick NVRAM cleanup, please reboot!\n");

  return EFI_SUCCESS;
}
