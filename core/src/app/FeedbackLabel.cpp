// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "app/FeedbackLabel.hpp"
#include "theme/FeedbackLabel.hpp"
#include "ui/Label.hpp"

namespace app {

theme::FeedbackLabel FeedbackLabel::styles_{};

std::once_flag FeedbackLabel::styles_set_{};

FeedbackLabel::FeedbackLabel(const sf::Font& font, sf::Vector2f size)
    : ui::Label{font, size, styles_.none, ""}, pin_{Pin::None} {}

FeedbackLabel::~FeedbackLabel() = default;

FeedbackLabel::Pin FeedbackLabel::get_pin() const noexcept {
    return pin_;
}

void FeedbackLabel::reset() {
    set_pin(Pin::None);
}

void FeedbackLabel::set_pin(Pin pin) {
    pin_ = pin;

    switch (pin) {
    case Pin::None:  set_style(styles_.none); break;
    case Pin::Red:   set_style(styles_.red); break;
    case Pin::White: set_style(styles_.white);
    }
}

void FeedbackLabel::set_theme(theme::FeedbackLabel theme) {
    std::call_once(styles_set_, [theme] {
        FeedbackLabel::styles_ = theme;
    });
}

} // namespace app
