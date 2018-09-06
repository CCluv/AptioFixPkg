/** @file
  EfiKey to name mapping.

Copyright (c) 2016, CupertinoNet. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "AmiShimEfiMap.h"

CONST CHAR8   *gEfiKeyToNameMap[] = {    
  "EfiKeyLCtrl",
  "EfiKeyA0",
  "EfiKeyLAlt",
  "EfiKeySpaceBar",
  "EfiKeyA2",
  "EfiKeyA3",
  "EfiKeyA4",
  "EfiKeyRCtrl",
  "EfiKeyLeftArrow",
  "EfiKeyDownArrow",
  "EfiKeyRightArrow",
  "EfiKeyZero",
  "EfiKeyPeriod",
  "EfiKeyEnter",
  "EfiKeyLShift",
  "EfiKeyB0",
  "EfiKeyB1",
  "EfiKeyB2",
  "EfiKeyB3",
  "EfiKeyB4",
  "EfiKeyB5",
  "EfiKeyB6",
  "EfiKeyB7",
  "EfiKeyB8",
  "EfiKeyB9",
  "EfiKeyB10",
  "EfiKeyRshift",
  "EfiKeyUpArrow",
  "EfiKeyOne",
  "EfiKeyTwo",
  "EfiKeyThree",
  "EfiKeyCapsLock",
  "EfiKeyC1",
  "EfiKeyC2",
  "EfiKeyC3",
  "EfiKeyC4",
  "EfiKeyC5",
  "EfiKeyC6",
  "EfiKeyC7",
  "EfiKeyC8",
  "EfiKeyC9",
  "EfiKeyC10",
  "EfiKeyC11",
  "EfiKeyC12",
  "EfiKeyFour",
  "EfiKeyFive",
  "EfiKeySix",
  "EfiKeyPlus",
  "EfiKeyTab",
  "EfiKeyD1",
  "EfiKeyD2",
  "EfiKeyD3",
  "EfiKeyD4",
  "EfiKeyD5",
  "EfiKeyD6",
  "EfiKeyD7",
  "EfiKeyD8",
  "EfiKeyD9",
  "EfiKeyD10",
  "EfiKeyD11",
  "EfiKeyD12",
  "EfiKeyD13",
  "EfiKeyDel",
  "EfiKeyEnd",
  "EfiKeyPgDn",
  "EfiKeySeven",
  "EfiKeyEight",
  "EfiKeyNine",
  "EfiKeyE0",
  "EfiKeyE1",
  "EfiKeyE2",
  "EfiKeyE3",
  "EfiKeyE4",
  "EfiKeyE5",
  "EfiKeyE6",
  "EfiKeyE7",
  "EfiKeyE8",
  "EfiKeyE9",
  "EfiKeyE10",
  "EfiKeyE11",
  "EfiKeyE12",
  "EfiKeyBackSpace",
  "EfiKeyIns",
  "EfiKeyHome",
  "EfiKeyPgUp",
  "EfiKeyNLck",
  "EfiKeySlash",
  "EfiKeyAsterisk",
  "EfiKeyMinus",
  "EfiKeyEsc",
  "EfiKeyF1",
  "EfiKeyF2",
  "EfiKeyF3",
  "EfiKeyF4",
  "EfiKeyF5",
  "EfiKeyF6",
  "EfiKeyF7",
  "EfiKeyF8",
  "EfiKeyF9",
  "EfiKeyF10",
  "EfiKeyF11",
  "EfiKeyF12",
  "EfiKeyPrint",
  "EfiKeySLck",
  "EfiKeyPause"
};

CONST UINTN   gEfiKeyToNameMapNum = sizeof(gEfiKeyToNameMap) / sizeof(gEfiKeyToNameMap[0]);
