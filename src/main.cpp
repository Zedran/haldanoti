// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <iostream>
#include <utility>

#include <SFML/Main.hpp>
#include <SFML/System/Exception.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "app/App.hpp"
#include "app/Window.hpp"
#include "config/Config.hpp"
#include "lang/Lang.hpp"
#include "theme/default_theme.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

#include "config.hpp"

int main() {
    dbg("{} {} {}", APP_NAME, VERSION, BRANCH);

    try {
        config::Config conf = config::read_config();
        lang::Lang     lang = utils::load_language(conf.lang);

        app::App app{
            app::Window::default_size(),
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
