# Plugin providing additional Octet functions for Kirikiri

This plugin adds additional Octet functions in Kirikiri2 / 吉里吉里2 / KirikiriZ / 吉里吉里Z

## Building

After cloning submodules and placing `ncbind` and `tp_stub` in the parent directory, a simple `make` will generate `octetEx.dll`.

## How to use

After `Plugins.link("octetEx.dll");` is used, the additional functions will be exposed under the `Octet` class.

## License

This project is licensed under the MIT license. Please read the `LICENSE` file for more information.
