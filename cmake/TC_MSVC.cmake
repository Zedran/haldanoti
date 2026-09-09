# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

set(WARN   "/W4 /WX- /permissive-")
set(HARDEN "/GS /guard:cf /DYNAMICBASE")

set(CMAKE_C_FLAGS_DEBUG            "/Od /Zi /Zc:preprocessor"          )
set(CMAKE_C_FLAGS_RELEASE          "/O2 /DNDEBUG ${HARDEN}"            )
set(CMAKE_C_FLAGS_RELWITHDEBINFO   "/Ox /Zi /DNDEBUG ${HARDEN}"        )
set(CMAKE_C_FLAGS_MINSIZEREL       "/O1 /DNDEBUG ${HARDEN}"            )

set(CMAKE_CXX_FLAGS_DEBUG          "/Od /Zi /Zc:preprocessor ${WARN}"  )
set(CMAKE_CXX_FLAGS_RELEASE        "/O2 /DNDEBUG ${WARN} ${HARDEN}"    )
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ox /Zi /DNDEBUG ${WARN} ${HARDEN}")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "/O1 /DNDEBUG ${WARN} ${HARDEN}"    )
