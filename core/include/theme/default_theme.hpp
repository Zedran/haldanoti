// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <vector>

#include <SFML/Graphics/Color.hpp>

#include "theme/CodeButton.hpp"
#include "theme/RowBoxStyle.hpp"
#include "theme/Theme.hpp"
#include "ui/Button.hpp"
#include "ui/Label.hpp"

namespace theme {

// Transparent color.
constexpr sf::Color a0 = sf::Color::Transparent;

// Outline color.
constexpr sf::Color ol{0x8b7659ff};

// Disabled button style.
constexpr ui::Label::Style dbs{.bg{0xf2dec6ff}, .fg{0x000000ff}, .ol{ol}};

// Transparent RowBoxStyle.
constexpr RowBoxStyle rbs_a0{.active{.bg{a0}, .ol{a0}}, .inactive{.bg{a0}, .ol{a0}}};

// A vector of styles for code elements.
const std::vector<ui::Button::Style> code_elements{{
    {
        .disabled{dbs},
        .normal{.bg{0x4484c4ff}, .fg{0xffffffff}, .ol{ol}},
        .hover{.bg{0x4484c4ff}, .fg{0xffffffff}, .ol{ol}},
        .active{.bg{0x4484c4ff}, .fg{0xffffffff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0x07efccff}, .fg{0x000000ff}, .ol{ol}},
        .hover{.bg{0x07efccff}, .fg{0x000000ff}, .ol{ol}},
        .active{.bg{0x07efccff}, .fg{0x000000ff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0x249635ff}, .fg{0xffffffff}, .ol{ol}},
        .hover{.bg{0x249635ff}, .fg{0xffffffff}, .ol{ol}},
        .active{.bg{0x249635ff}, .fg{0xffffffff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0xff8800ff}, .fg{0x000000ff}, .ol{ol}},
        .hover{.bg{0xff8800ff}, .fg{0x000000ff}, .ol{ol}},
        .active{.bg{0xff8800ff}, .fg{0x000000ff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0xc90e0eff}, .fg{0xffffffff}, .ol{ol}},
        .hover{.bg{0xc90e0eff}, .fg{0xffffffff}, .ol{ol}},
        .active{.bg{0xc90e0eff}, .fg{0xffffffff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0x5f17d3ff}, .fg{0xffffffff}, .ol{ol}},
        .hover{.bg{0x5f17d3ff}, .fg{0xffffffff}, .ol{ol}},
        .active{.bg{0x5f17d3ff}, .fg{0xffffffff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0x000000ff}, .fg{0xffffffff}, .ol{ol}},
        .hover{.bg{0x000000ff}, .fg{0xffffffff}, .ol{ol}},
        .active{.bg{0x000000ff}, .fg{0xffffffff}, .ol{ol}},
    },
    {
        .disabled{dbs},
        .normal{.bg{0xffea0aff}, .fg{0x000000ff}, .ol{ol}},
        .hover{.bg{0xffea0aff}, .fg{0x000000ff}, .ol{ol}},
        .active{.bg{0xffea0aff}, .fg{0x000000ff}, .ol{ol}},
    },
}};

// CodeButton style.
const CodeButton cb{
    .empty{
        .disabled{.bg{dbs.bg}, .fg{a0}, .ol{ol}},
        .normal{.bg{dbs.bg}, .fg{0x000000ff}, .ol{ol}},
        .hover{.bg{dbs.bg}, .fg{0x000000ff}, .ol{ol}},
        .active{.bg{dbs.bg}, .fg{0x000000ff}, .ol{ol}},
    },
    .elements{code_elements},
};

// Default theme of the application.
const Theme DEFAULT_THEME{
    .bg{0x8b7659ff},
    .board{
        .box{
            .bg{a0},
            .ol{a0},
        },
        .game_row{
            .box{
                .active{
                    .bg{0xffffffff},
                    .ol{a0},
                },
                .inactive{
                    .bg{0xfff8f2ff},
                    .ol{a0},
                },
            },
            .code_box{rbs_a0},
            .fb_box{rbs_a0},
            .ok_box{rbs_a0},
            .code_button{cb},
            .fb_label{
                .show_text = false,
                .none{dbs},
                .red{.bg{0xc90e0eff}, .fg{0xffffffff}, .ol{ol}},
                .white{.bg{0xffffffff}, .fg{0x000000ff}, .ol{ol}},
            },
            .ok_button{
                .disabled{.bg{0xfff8f2ff}, .fg{0x000000ff}, .ol{a0}},
                .normal{.bg{0x009b00ff}, .fg{0xffffffff}, .ol{ol}},
                .hover{.bg{0x00b400ff}, .fg{0xffffffff}, .ol{ol}},
                .active{.bg{0x00ce00ff}, .fg{0x000000ff}, .ol{ol}},

            },
        },
        .secret_row{
            .box{
                .bg{a0},
                .ol{a0},
            },
            .code_box{
                .bg{0xf2dec6ff},
                .ol{a0},
            },
            .info_running{
                .bg{a0},
                .fg{a0},
                .ol{a0},
            },
            .info_lost{
                .bg{0xf2dec6ff},
                .fg{0x000000ff},
                .ol{a0},
            },
            .info_won{
                .bg{0x249635ff},
                .fg{0xffffffff},
                .ol{a0},
            },
        }
    },
    .message{
        .bg{0x000000aa},
        .fg{0xffffffff},
        .ol{a0},
    },
    .toolbar{
        .box{
            .bg{0xf2dec6ff},
            .ol{a0},
        },
        .new_game{
            .disabled{dbs},
            .normal{
                .bg{0x3774b0ff},
                .fg{0xffffffff},
                .ol{ol}
            },
            .hover{
                .bg{0x4484c4ff},
                .fg{0xffffffff},
                .ol{ol}
            },
            .active{
                .bg{0x6d9fd1ff},
                .fg{0x000000ff},
                .ol{ol}
            },
        },
        .settings{
            .disabled{dbs},
            .normal{
                .bg{0xff9900ff},
                .fg{0x000000ff},
                .ol{ol}
            },
            .hover{
                .bg{0xffad33ff},
                .fg{0x000000ff},
                .ol{ol}
            },
            .active{
                .bg{0xffcc80ff},
                .fg{0x000000ff},
                .ol{ol}
            },
        },
        .exit{
            .disabled{dbs},
            .normal{
                .bg{0xC80000ff},
                .fg{0xffffffff},
                .ol{ol}
            },
            .hover{
                .bg{0xe80000ff},
                .fg{0xffffffff},
                .ol{ol}
            },
            .active{
                .bg{0xff4040ff},
                .fg{0x000000ff},
                .ol{ol}
            },
        },
    },
    .settings{
        .bg{
            .bg{0x73737373},
            .ol{a0}
        },
        .box{
            .bg{0xf2dec6ff},
            .ol{ol}
        },
        .label{
            .bg{a0},
            .fg{0x000000ff},
            .ol{a0}
        },
        .checkbox{
            .box{
                .bg{0xf2dec6ff},
                .ol{a0},
            },
            .button_off{
                .disabled{dbs},
                .normal{dbs},
                .hover{.bg{0xfff8f2ff}, .fg{dbs.fg}, .ol{ol}},
                .active{.bg{0xffffffff}, .fg{dbs.fg}, .ol{ol}},
            },
            .button_on{
                .disabled{dbs},
                .normal{.bg{dbs.bg}, .fg{0x000000ff}, .ol{ol}},
                .hover{.bg{0xfff8f2ff}, .fg{0x000000ff}, .ol{ol}},
                .active{.bg{0xffffffff}, .fg{0x000000ff}, .ol{ol}},
            },
            .label{
                .bg{a0},
                .fg{0x000000ff},
                .ol{a0},
            },
        },
        .selector{
            .box{
                .bg{0xf2dec6ff},
                .ol{a0},
            },
            .label{
                .bg{a0},
                .fg{0x000000ff},
                .ol{a0},
            },
            .button{
                .disabled{.bg{dbs.bg}, .fg{0x000000ff}, .ol{a0}},
                .normal{.bg{dbs.bg}, .fg{0x000000ff}, .ol{a0}},
                .hover{.bg{0xfff8f2ff}, .fg{0x000000ff}, .ol{ol}},
                .active{.bg{0xffffffff}, .fg{0x000000ff}, .ol{ol}},
            },
        },
        .save{
            .disabled{.bg{0xfff8f2ff}, .fg{0x000000ff}, .ol{a0}},
            .normal{.bg{0x009b00ff}, .fg{0xffffffff}, .ol{ol}},
            .hover{.bg{0x00b400ff}, .fg{0xffffffff}, .ol{ol}},
            .active{.bg{0x00ce00ff}, .fg{0x000000ff}, .ol{ol}},

        },
        .cancel{
            .disabled{dbs},
            .normal{.bg{0xC80000ff}, .fg{0xffffffff}, .ol{ol}},
            .hover{.bg{0xe80000ff}, .fg{0xffffffff}, .ol{ol}},
            .active{.bg{0xff4040ff}, .fg{0x000000ff}, .ol{ol}},
        },
    },

};

} // namespace theme
