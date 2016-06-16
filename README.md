# flip

Flip is a data model library, designed as a framework, real-time collaboration-oriented, transactional, portable and compact.

## Requirements

`flip` requires :
- either Windows Microsoft Visual Studio C++ 2013 Update 4 or later
- or Apple XCode 6 or later

The supported C++ dialect are C++11 or later.

## Testing

`flip` can be built to run regression tests.

To do so it is adviced to have a [`python`](https://www.python.org/downloads/) installation with minimum version `2.7`.
[`gyp`](https://code.google.com/p/gyp/source/checkout) is then required to generate projects file for IDEs.

When this is set up, run `configure.py`. This will create a `projects` at the root of your `flip` repository with the native project type for your platform (a Visual Studio Solution or an Xcode Project).

## Integrating

The following distribution of `flip` comes as headers in the `include` directory as well as
precompiled platform specific binaries in the `lib` directory.

The directory `include` must be part of your header paths.
See [`regress_public.gypi`](/test/regress/regress_public.gypi) gyp file as an example for your IDE configuration.

The directory `lib` contains different libraries depending on your platform/compiler :

```
lib/
   macos/
      libflip.a      Universal binary i386/x86_64 using XCode 6 clang compiler
   windows/
      Visual Studio 2013/
         Win32/
            flip.lib
         x64/
            flip.lib
      Visual Studio 2015/
         Win32/
            flip.lib
         x64/
            flip.lib
```

This distribution comes with the default configuration of precompiler flags except for `flip_FATAL_MODE` which is set to `flip_FATAL_MODE_THROW` to allow the regression tests to run.
See [Flip Configuration Guide](/documentation/markdown/config/README.md) for more details.

## Documentation

An extensive number of guides and references are available in different documentation formats :

0. In GitHub Flavored Markdown Format directly browsable from the GitHub website [here](/documentation/markdown/README.md)
1. In Docset Format for [Dash](https://kapeli.com/dash) on MacOS X and [Zeal](http://zealdocs.org) on Linux and Windows [here](/documentation/docset)
2. In HTML Format [here](/documentation/html)
