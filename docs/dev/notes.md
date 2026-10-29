# Notes

Things easily forgotten.

## Settings: adding a new option

1. `config`
    * [Config.hpp](/core/include/config/Config.hpp)
        * Add the new option to the `Config` struct. Order keys alphabetically to facilitate comparison with config file.
    * [Config.cpp](/core/src/config/Config.cpp)
        * `enforce_limits` - if the new option should have some limits in place, add the relevant checks.
        * `from_json` - retrieve the option from JSON object.
        * `get_default_config` - add the default value.
        * `to_json` - store the option in JSON object.
2. `lang`
    * [Settings.hpp](/core/include/lang/Settings.hpp)
        * Add the option field to the `Settings` struct, prefix it with `opt_`.
        * Include the new field in the JSON macro.
    * Add the new `opt_` field to every language file in the [lang](/assets/lang/) directory.
3. `app`
    * [Settings.hpp](/core/include/app/Settings.hpp)
        * Add a new raw pointer for `ui::Box` component related to the option.
    * [Settings.cpp](/core/src/app/Settings.cpp)
        * `Settings` - add a new component to `opt_box` and store the pointer to it in the newly created member of the `Settings` class. Adjust `toolbar_spacing.y`.
        * `game_reset_required` - add conditional statement for the option if modifying it requires starting a new game.
        * `get_config` - retrieve value stored in the new option.
        * `restart_required` - add conditional statement for the option if modifying it requires restart.
        * `set_config` - add pointer assertion and set the value to the new component.
4. [README.md](/README.md)
    * Document the new option.
