// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <iostream>

#include <SFML/Main.hpp>
#include <SFML/System/Exception.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "app/App.hpp"
#include "config/Config.hpp"
#include "lang/Lang.hpp"
#include "theme/default_theme.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"
#include "utils/utils.hpp"

#include "config.hpp"

int main() {
    constexpr float relh_to_winh{0.80f};
    constexpr float relw_to_h{0.5625f};

    const auto desktop = sf::VideoMode::getDesktopMode();

    const sf::Vector2f window_size = utils::round({
        static_cast<float>(desktop.size.y) * relh_to_winh * relw_to_h,
        static_cast<float>(desktop.size.y) * relh_to_winh,
    });

    dbg("{} {} {}", APP_NAME, VERSION, BRANCH);

    try {
        config::Config conf = config::read_config();
        lang::Lang     lang = utils::load_language(conf.lang);

        app::App app{
            window_size,
            std::move(conf),
            std::move(lang),
            theme::DEFAULT_THEME,
            VERSION
        };
        app.run();
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (const sf::Exception& e) {
        std::cerr << "SFML: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
