[![License][LicenseBadge]][LicenseURL]

# GTK 3 Examples

A set of GTK 3 examples in C

## Building

You'll need (obviouslly) GTK 3 and Meson, then just:

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