// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <utility>

#include <SFML/Window/Mouse.hpp>

#include "app/Settings.hpp"
#include "ui/Blank.hpp"
#include "ui/Box.hpp"
#include "ui/Label.hpp"
#include "ui/Layout.hpp"

namespace app {

Settings::Settings(
    const sf::Font&         font,
    sf::Vector2f            size,
    lang::Settings          lang,
    theme::Settings         theme,
    std::vector<sf::String> lang_fnames,
    std::vector<sf::String> theme_fnames,
    sf::String              version
) : ui::Box{size, theme.bg, ui::Layout::Type::ColumnLayout}, state_{} {
    constexpr Box::Style INNER_BOX_STYLE{.bg{0}, .ol{0}};

    ui::Box& opt_box = add_component<ui::Box>(
        size.componentWiseMul(OPT_BOX_REL_SIZE),
        theme.opt_box,
        ui::Layout::Type::ColumnLayout
    );

    const sf::Vector2f opt_line_size = size.componentWiseMul(OPT_LINE_REL_SIZE);

    opt_box.add_component<ui::Label>(
        font,
        opt_line_size,
        theme.label,
        std::move(lang.title)
    );

    sel_lang_ = &opt_box.add_component<ui::Selector>(
        font,
        opt_line_size,
        theme.selector,
        std::move(lang.opt_lang),
        std::move(lang_fnames)
    );

    cb_code_chars_ = &opt_box.add_component<ui::Checkbox>(
        font,
        opt_line_size,
        theme.checkbox,
        std::move(lang.opt_code_chars)
    );

    cb_fb_chars_ = &opt_box.add_component<ui::Checkbox>(
        font,
        opt_line_size,
        theme.checkbox,
        std::move(lang.opt_fb_chars)
    );

    cb_hints_ = &opt_box.add_component<ui::Checkbox>(
        font,
        opt_line_size,
        theme.checkbox,
        std::move(lang.opt_hints)
    );

    cb_unique_elems_ = &opt_box.add_component<ui::Checkbox>(
        font,
        opt_line_size,
        theme.checkbox,
        std::move(lang.opt_unique_elems)
    );

    cb_vsync_ = &opt_box.add_component<ui::Checkbox>(
        font,
        opt_line_size,
        theme.checkbox,
        std::move(lang.opt_vsync)
    );

    sel_theme_ = &opt_box.add_component<ui::Selector>(
        font,
        opt_line_size.componentWiseMul({1.0f, 1.5f}),
        theme.selector,
        std::move(lang.opt_theme),
        std::move(theme_fnames),
        ui::Layout::Type::ColumnLayout
    );

    constexpr sf::Vector2f toolbar_spacing{0.0f, 4.0f};

    opt_box.add_component<ui::Blank>(opt_line_size.componentWiseMul(toolbar_spacing));

    opt_box.add_component<ui::Label>(
        font,
        size.componentWiseMul(VERSION_RELSIZE),
        theme.label,
        std::move(version)
    );

    const sf::Vector2f toolbar_size = size.componentWiseMul(TOOLBAR_REL_SIZE);

    ui::Box& toolbar = opt_box.add_component<ui::Box>(
        toolbar_size,
        INNER_BOX_STYLE,
        ui::Layout::Type::RowLayout
    );

    const unsigned int font_size = static_cast<unsigned int>(toolbar_size.y * FONT_REL_SIZE);
    const sf::Vector2f tb_button_size{toolbar_size.y * BUTTON_RELSIZE.x, toolbar_size.y * BUTTON_RELSIZE.y};

    ui::Button& save = toolbar.add_component<ui::Button>(
        font,
        tb_button_size,
        theme.save,
        std::move(lang.save),
        font_size
    );
    save.bind(sf::Mouse::Button::Left, [this] { this->set_state(State::SaveAndClose); });

    ui::Button& cancel = toolbar.add_component<ui::Button>(
        font,
        tb_button_size,
        theme.cancel,
        std::move(lang.cancel),
        font_size
    );
    cancel.bind(sf::Mouse::Button::Left, [this] { this->set_state(State::Close); });
}

bool Settings::config_differs(const config::Config& c) const noexcept {
    return ref_config_ != c;
}

config::Config Settings::get_config() const noexcept {
    return config::Config{
        .code_chars   = cb_code_chars_->get_state(),
        .fb_chars     = cb_fb_chars_->get_state(),
        .hints        = cb_hints_->get_state(),
        .lang         = sel_lang_->get_value().toAnsiString(),
        .theme        = sel_theme_->get_value().toAnsiString(),
        .unique_elems = cb_unique_elems_->get_state(),
        .vsync        = cb_vsync_->get_state(),
    };
}

const config::Config& Settings::get_ref_config() const noexcept {
    return ref_config_;
}

Settings::State Settings::get_state() const noexcept {
    return state_;
}

void Settings::set_config(const config::Config& c) {
    assert(cb_unique_elems_);
    cb_unique_elems_->set_state(c.unique_elems);

    assert(cb_hints_);
    cb_hints_->set_state(c.hints);

    assert(sel_lang_);
    sel_lang_->set_value(c.lang);

    assert(sel_theme_);
    sel_theme_->set_value(c.theme);

    assert(cb_code_chars_);
    cb_code_chars_->set_state(c.code_chars);

    assert(cb_fb_chars_);
    cb_fb_chars_->set_state(c.fb_chars);

    assert(cb_vsync_);
    cb_vsync_->set_state(c.vsync);

    set_ref_config(c);
}

bool Settings::restart_required(const config::Config& c) const noexcept {
    return ref_config_.lang != c.lang ||
           ref_config_.theme != c.theme ||
           ref_config_.code_chars != c.code_chars ||
           ref_config_.fb_chars != c.fb_chars;
}

void Settings::set_ref_config(const config::Config& c) noexcept {
    ref_config_ = c;
}

void Settings::set_state(State s) noexcept {
    state_ = s;
}

} // namespace app
