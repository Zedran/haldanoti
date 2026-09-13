// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>

#include "lang/Lang.hpp"

namespace lang {

const Lang DEFAULT_LANG{
    .board{
        .game_row{
            .fb_label{
                L"",
                L"+",
                L"-"
            },
            .ok{L"Ok"}
        },
        .secret_row{
            .info_running{},
            .info_won{L"Code correct"},
            .info_lost{L"Game over"},
        },
    },
    .message{
        .restart_required{L"Restart required"},
    },
    .toolbar{
        .new_game{L"New\ngame"},
        .settings{L"Settings"},
        .exit{L"Exit"},
    },
    .settings{
        .check_mark{L"x"},
        .title{L"Settings"},
        .opt_unique_elems{L"Unique elements"},
        .opt_lang{L"Language"},
        .opt_fb_chars{L"Feedback characters"},
        .opt_hints{L"Show hints"},
        .opt_vsync{L"VSync"},
        .save{L"Save"},
        .cancel{L"Cancel"},
    }
};

} // namespace lang
