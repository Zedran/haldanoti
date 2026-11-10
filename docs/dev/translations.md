# Translation guide

## Table of contents

* [Specification](#specification)
* [Key translation conventions](#key-translation-conventions)
* [Linux Desktop Entry](#linux-desktop-entry)
* [Crash log file location](#crash-log-file-location)
* [Validating and formatting JSON](#validating-and-formatting-json)
* [Notes](#notes)

## Specification

Each language has a dedicated JSON file in the [assets/lang/](../../assets/lang) directory.

**JSON format:**

* `LF` line endings
* 4-space indentation
* Non-ASCII characters unescaped (except `\n`)

File name contains an [ISO 639](https://en.wikipedia.org/wiki/List_of_ISO_639_language_codes) 2-letter language code, just like the language part of the [GNU locale names](https://www.gnu.org/software/gettext/manual/html_node/Locale-Names.html). It ends with the `.json` extension. Country/territory variants are not supported. If several dialects of your language exist, choose the standard form.

At present, the font supports languages using:

* Latin script
* Cyryllic script
* Greek alphabet

## Key translation conventions

Try to maintain similar length to the values in [en.json](../../assets/lang/en.json). Text for elements under the `toolbar` key may be split across multiple lines.

The following table clarifies translation guidelines for the few ambigous keys.

| Key                             | Guideline                                                    |
|:--------------------------------|:-------------------------------------------------------------|
| `board.game_row.fb_label.red`   | Initial uppercase letter of the word "red".                  |
| `board.game_row.fb_label.white` | Initial uppercase letter of the word "white".                |
| `board.secret_row.hint_unique`  | Initial uppercase letter of the word "unique".               |
| `settings.opt_code_chars`       | "Code characters", "code symbols" etc.                       |
| `settings.opt_fb_chars`         | Synonyms of "feedback", "response", "characters", "symbols". |
| `settings.opt_hints`            | May be imperative "show hints" or just the noun "hints".     |

## Linux Desktop Entry

In addition to the language file, a localized `Comment` key should be added to the [desktop entry template](../../platform/linux/haldanoti.desktop.in). Localized keys are postfixed with an ISO 639 language code in square brackets. They are separated from other keys with a blank line.

When adding your translation of the `Comment` key, preserve the blank line and alphabetical order among localized keys.

Example of a correct structure:

```ini
Categories=Game;

Comment[eo]=Esperanto translation
Comment[pl]=Polish translation
```

## Crash log file location

Unrecoverable errors are written to the crash log file, which is located at:

* Linux: `$HOME/.cache/haldanoti/haldanoti.log`
* Windows: `%LOCALAPPDATA%\haldanoti\haldanoti.log`

If the application crashes silently while you are tinkering with your language file, it is most likely a problem with JSON syntax (missing brackets or quotes, misplaced commas). Verify by checking error messages written in the log.

## Validating and formatting JSON

You may use Python's [json.tool](https://docs.python.org/3/library/json.html#module-json.tool) utility to detect errors and format JSON file:

```sh
python -m json.tool --indent 4 --no-ensure-ascii eo.json eo.json
```

## Notes

* If you are working from Git repository (therefore you keep your language file in `/assets/lang/`), you will need to reconfigure the project (by running `cmake ..` inside `/build/`) to see changes you made.
