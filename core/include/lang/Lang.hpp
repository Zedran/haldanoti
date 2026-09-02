// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "lang/Board.hpp"
#include "lang/Settings.hpp"
#include "lang/Toolbar.hpp"

namespace lang {

struct Lang {
    Board   board;
    Toolbar toolbar;
    Settings settings;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Lang, board, toolbar, settings);

} // namespace lang
