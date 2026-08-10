// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "app/FeedbackLabel.hpp"
#include "lang/FeedbackLabel.hpp"
#include "theme/FeedbackLabel.hpp"
#include "ui/Label.hpp"

namespace app {

lang::FeedbackLabel FeedbackLabel::lang_{};

std::once_flag FeedbackLabel::lang_set_{};

theme::FeedbackLabel FeedbackLabel::styles_{};

std::once_flag FeedbackLabel::styles_set_{};

FeedbackLabel::FeedbackLabel(const sf::Font& font, sf::Vector2f size)
    : ui::Label{font, size, styles_.none, lang_.none, static_cast<unsigned int>(FONT_REL_SIZE * size.y)}, pin_{Pin::None} {}

FeedbackLabel::~FeedbackLabel() = default;

FeedbackLabel::Pin FeedbackLabel::get_pin() const noexcept {
    return pin_;
}

void FeedbackLabel::reset() {
    set_pin(Pin::None);
}

void FeedbackLabel::set_lang(lang::FeedbackLabel lang) {
    std::call_once(lang_set_, [lang] {
        FeedbackLabel::lang_ = lang;
    });
}

void FeedbackLabel::set_pin(Pin pin) {
    pin_ = pin;

    switch (pin) {
    case Pin::None:  set_style(styles_.none); break;
    case Pin::Red:   set_style(styles_.red); break;
    case Pin::White: set_style(styles_.white);
    }

    update_text();
}

void FeedbackLabel::set_theme(theme::FeedbackLabel theme) {
    std::call_once(styles_set_, [theme] {
        FeedbackLabel::styles_ = theme;
    });
}

void FeedbackLabel::update_text() {
    if (!styles_.show_text) {
        return;
    }

    switch (pin_) {
    case Pin::None:  set_text(lang_.none); break;
    case Pin::Red:   set_text(lang_.red); break;
    case Pin::White: set_text(lang_.white);
    }
}

} // namespace app
