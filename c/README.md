[![License][LicenseBadge]][LicenseURL]

# GTK Examples

A set of GTK (3/4) examples in C

## Building

You'll need GTK 3/4 and Meson, then just go to the version of GTK you have and build the examples with:

```
meson . _BUILD
ninja -C _BUILD
```

The above commands will compile all the examples, after that, you can run the examples like:

```
_BUILD/<ExampleName>
```

[LicenseBadge]: https://img.shields.io/badge/License-Zlib-brightgreen?style=for-the-badge
[LicenseURL]: https://opensource.org/licenses/Zlib