# Theming guide

Theme determines the appearance of the game. It is a set of colors defined in a JSON file.

This document describes how the game's theming system works. It is assumed that you:

* are familiar with [JSON](https://en.wikipedia.org/wiki/JSON)
* understand HTML color codes (color information encoded as hexadecimal values)
* have basic knowledge of C++ (in particular: [namespaces](https://en.cppreference.com/cpp/language/namespace), [structs](https://en.cppreference.com/cpp/keyword/struct), [classes](https://en.cppreference.com/cpp/language/class) and [inheritance](https://en.cppreference.com/cpp/language/derived_class))

## Table of contents

* [sf::Color](#sfcolor)
* [Theming system](#theming-system)
    * [Widget level](#widget-level)
    * [Application level](#application-level)
* [Theme files location](#theme-files-location)
    * [System theme directory](#system-theme-directory)
    * [User theme directory](#user-theme-directory)
* [Crash log file location](#crash-log-file-location)
* [Tips](#tips)

## sf::Color

`sf::Color` class represents a color in SFML (main dependency of the game). It is the most basic component of the application's theme. The class contains 4 integer values, one for each color component (red, green, blue, alpha). In a theme file, these colors are stored as HTML color codes (`"#rrggbbaa"`).

The table below presents supported HTML color code formats.

| Value      | Description                                                                    |
|:-----------|:-------------------------------------------------------------------------------|
| `#ff0000`  | Color red, with redundant\* `#` and implicit\*\* alpha value of 100% (`0xff`). |
| `000000`   | Color black with implicit alpha value of 100% (`0xff`).                        |
| `00ff0080` | Color green with explicitly set alpha value of 50% (`0x80`).                   |
| `0000ff00` | Fully transparent color blue.                                                  |

\* `#` prefix is tolerated, but redundant.<br>
\*\* if alpha value is omitted, 100% alpha is assumed.

## Theming system

Theming system is comprised of two levels:

* **Widget level** - style of Widget classes found in the [ui](../../core/include/ui/) directory.
* **Application level** - style of the specialized classes that are defined in the [app](../../core/include/app/) directory.

### Widget level

Basic Widget classes defined in the ui namespace are the building blocks of user interface. We will call them "primitives". Every primitive has an internal structure called `Style`. For example, `Style` of the [Label](../../core/include/ui/Label.hpp) class is defined as follows:

```cpp
struct Style {
    sf::Color bg; // background
    sf::Color fg; // foreground (text)
    sf::Color ol; // background's outline
};
```

It is translated to JSON as:

```json
{
    "bg": "00000000",
    "fg": "000000ff",
    "ol": "ffffffff"
}
```

This field naming convention is consistent for all Style structures.

As Widgets become more complex, they can include the whole Style structs of the Widgets they contain or are derived from. [Button](../../core/include/ui/Button.hpp)'s Style struct is a good example here. It is derived from Label and needs to store multiple Style structures of its base class in order to react visually to user's input:

```cpp
struct Style {
    ui::Label::Style disabled; // non-interactive
    ui::Label::Style normal;   // not interacted with
    ui::Label::Style hover;    // mouse over the Button
    ui::Label::Style active;   // pressed down
};
```

Button's Style looks as follows in JSON:

```json
{
    "active":   {"bg": "6d9fd1ff", "fg": "000000ff", "ol": "8b7659ff"},
    "disabled": {"bg": "f2dec6ff", "fg": "000000ff", "ol": "8b7659ff"},
    "hover":    {"bg": "4484c4ff", "fg": "ffffffff", "ol": "8b7659ff"},
    "normal":   {"bg": "3774b0ff", "fg": "ffffffff", "ol": "8b7659ff"}
}
```

### Application level

Application-level classes (namespace `app`) are specialized classes derived from primitive Widgets. Unlike the primitives, their styling structs are disconnected from their class declarations and can be found in the [theme](../../core/include/theme/) directory (namespace `theme`).

The outermost structure of the theming system is called [Theme](../../core/include/theme/Theme.hpp):

```cpp
struct Theme {
    sf::Color        bg;       // game window's background
    theme::Board     board;    // app::Board class
    ui::Label::Style message;  // notification label
    theme::Toolbar   toolbar;  // app::Toolbar class
    theme::Settings  settings; // app::Settings class
};
```

All application-level theme structures are composed similarly. They are a mix of colors, primitive styles and application-level theme structures that are lower in the hierarchy. `Theme` translates to JSON as follows (omitting values for brevity):

```json
{
    "bg": "",
    "board": {},
    "message": {},
    "toolbar": {},
    "settings": {}
}
```

When in doubt about the meaning of a field, check the comments in the [theme](../../core/include/theme/) struct definitions.

## Theme files location

There are two theme directories: system directory (where the application data is installed) and user directory.

Theme files are expected to have the `.json` extension.

### System theme directory

System theme directory location depends on the platform and installation method. If you installed the game with CMake, check the `install_manifest.txt` file in your `CMAKE_BINARY_DIR`. If you used Windows installer, you probably know your chosen install location. Linux packages can be examined with utilities provided by package managers:

```sh
# Debian
dpkg -L haldanoti

# RPM-based systems
rpm -ql haldanoti
```

### User theme directory

Usually, you will want to work with the user directory, which is located at:

* Linux: `$HOME/.config/haldanoti/theme/`
* Windows: `%APPDATA%\haldanoti\theme\`

You will have to create the `theme` directory by yourself.

User-defined themes take precedence over themes in the system directory. This allows you to tweak themes shipped with the application to your liking without cluttering theme selector on the settings page and without modifying system files. This rule, however, does not apply to the default theme (`default.json`). Theme with this name will always be loaded from the system directory. This behavior is required to provide a fallback mechanism - if you define your theme incorrectly, the game will launch using the default theme. Without this mechanism, the game would try to load an invalid theme and crash every time, forcing you to manually edit the config file to revert changes.

## Crash log file location

Unrecoverable errors are written to the crash log, which is located at:

* Linux: `$HOME/.cache/haldanoti/haldanoti.log`
* Windows: `%LOCALAPPDATA%\haldanoti\haldanoti.log`

If the application crashes silently while you are tinkering with your theme file, check error messages written in the log. Typical problems are:

* Invalid HTML color code structure.
* Incorrect number of styles for the CodeButton (read the [tips](#tips) section).

In the release build, if your theme is incorrectly structured or the file cannot be opened for some reason, the default theme will be loaded and no error will be written anywhere. It is recommended to work on a custom theme using debug build, so that you see more verbose error messages.

## Tips

* Do not define the whole theme yourself as it is a very laborious process. Copy the [default theme file](../../assets/theme/default.json) and modify colors to your liking. This gives you certainty that the complex JSON structure is correct.
* Take special care when working with the [CodeButton](../../core/include/theme/CodeButton.hpp) structure. It must contain the correct number of Button styles for CodeButton - one color for each code value (8 possible currently). If you define an incorrect number of styles, the application will crash.
* Theme selector provides quite a bit of space for theme name, but it cannot display very long strings well. Picking a name on the shorter side is recommended.
* If you are working from Git repository (therefore you keep your theme file in `/assets/theme/`), you will need to reconfigure the project (by running `cmake ..` inside `/build/`) to see changes you made to your theme.
