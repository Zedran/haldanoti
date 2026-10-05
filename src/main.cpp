// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <utility>

#include <SFML/Main.hpp>
#include <SFML/System/Exception.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "app/App.hpp"
#include "app/Window.hpp"
#include "config/Config.hpp"
#include "lang/Lang.hpp"
#include "utils/Logger.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

#include "config.hpp"

int main() {
    dbg("{} {} {}", APP_NAME, VERSION, BRANCH);

    try {
        config::Config conf = config::read_config();
        lang::Lang     lang = utils::load_language(conf.lang);
        theme::Theme   theme = utils::load_theme(conf.theme);

        app::App app{
            app::Window::default_size(),
            std::move(conf),
            std::move(lang),
            std::move(theme),
            VERSION
        };
        app.run();
    } catch (const nlohmann::json::exception& e) {
        utils::Logger::println(VERSION, "JSON", e);
        return EXIT_FAILURE;
    } catch (const sf::Exception& e) {
        utils::Logger::println(VERSION, "SFML", e);
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        utils::Logger::println(VERSION, "Exception", e);
        return EXIT_FAILURE;
    } catch (...) {
        utils::Logger::println(VERSION, "Unknown");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
