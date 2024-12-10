[![License][LicenseBadge]][LicenseURL]

# GTK Examples

> [!NOTE]
> _"It's been X days/weeks/months since last commit, is this project still maintained?"_
> __Yes__. I'm just busy working :)

A set of various GTK code examples in different programming languages.

![GTK Examples Banner](banner.png)

## Building and running

The main requirement to build and run the (C and Vala) examples is to have:

  - Development files for GTK (3 and 4)
  - Meson
  - C and Vala compilers

> [!NOTE]
> You might also need the GLEW development files (needed by the glarea example), try building and running first to see if everything it's ok

Then just run:

```
meson setup _BUILD .
ninja -C _BUILD
```

And that's it! You'll found compiled binaries under the following folders:

  - _BUILD/c/ for the C examples
  - _BUILD/vala/ for the Vala examples

### Lua

In the case of the Lua examples, they're supposed to run on any version of Lua, and the only requirement is to have [LGI](https://github.com/lgi-devs/lgi) installed, BUT: I highly recommend you to have the Git version. That's because the Git version supports GTK 4 and libadwaita, so you'll be sure every example will work.

> [!WARNING]
> To build [LGI](https://github.com/lgi-devs/lgi) you'll need `gobject-introspection`, check out the [LGI repo](https://github.com/lgi-devs/lgi) for more details if you're having trouble.

## About this repository

I decided to merge all my repos with GTK examples here because I feel that having different repos for the same purpose and with (basically) the same code is a mess, so I prefer to have all these examples in one place.

## About some examples

Note that GTK 3 and 4 are considerably different, which means that I'll try to have the same examples for both versions, but not all of them will be present in both versions. That said, here's a list of notes about some of the examples:

  - GtkDialog: GTK 3 only, this class was deprecated in GTK 4.10
  - GtkAssistant: in GTK 3 you can set a subtitle in the header bar, but not in GTK 4 because there's no subtitle property in GtkHeaderBar.
  - GtkCssProvider: in GTK 4 this class was deprecated in GTK 4.10, the example is still present, but it's slightly different

[LicenseBadge]: https://img.shields.io/badge/License-Zlib-brightgreen?style=for-the-badge
[LicenseURL]: https://opensource.org/licenses/Zlib