// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "lang/Board.hpp"
#include "lang/Toolbar.hpp"

namespace lang {

struct Lang {
    Board   board;
    Toolbar toolbar;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Lang, board, toolbar);

} // namespace lang
