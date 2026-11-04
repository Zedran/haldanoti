# <img src="assets/haldanoti.svg" alt="haldanoti.svg" width="24"> Haldanóti

Haldanóti (Quenya: hidden numbers) is a digital adaptation of the classic [Bulls and Cows](https://en.wikipedia.org/wiki/Bulls_and_cows) game.

## Table of contents

* [Installation](#installation)
* [Rules](#rules)
* [Settings](#settings)
* [License](#license)

## Installation

Refer to the [installation instructions](docs/manual/installation.md).

## Rules

At the start of the game, a secret code is set. Over the course of 12 turns (each represented by a single row on the board), the player attempts to guess the correct code. Each guess is evaluated and the player receives feedback in the form of colored pins. Every pin represents a single code element. There are 3 types of pins:

* **Red** - a correct element is in the correct position.
* **White** - a correct element is in an incorrect position.
* **None** - an incorrect element is present.

A feedback field does not correspond to any particular code field. Pins are placed from left to right, with red pins taking precedence over the white pins.

To win the game, player must deduce the correct sequence within at most 12 attempts.

## Settings

The following table presents configuration options that are available. Some changes require restarting the game to take effect.

| Option                  | Restart | Description                                                                 |
|:------------------------|:-------:|:----------------------------------------------------------------------------|
| **Code characters**     | yes     | Display numbers in addition to colors in the code fields.                   |
| **Code length**         |         | Change the number of elements in the secret code.                           |
| **Feedback characters** | yes     | Display small signs in the feedback fields in addition to colors.           |
| **Language**            | yes     | Game's display language.                                                    |
| **Show hints**          |         | Show a number of distinct elements in the secret code.                      |
| **Theme**               | yes     | Game's color theme.                                                         |
| **Unique elements**\*   |         | Do not repeat code elements and do not allow duplicates in guesses.         |
| **VSync**               |         | Run at native framerate instead of limiting it to 60 FPS.                   |

\* Modifying **Code length** or **Unique elements** options immediately starts a new game.

## License

This software is available under AGPL-3.0-only license.

For information on third-party source code and assets, refer to [NOTICE.md](NOTICE.md).
