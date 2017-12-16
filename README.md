# c.js

JavaScript -> C transpiler.

## Build

Build the `c.js` transpiler with `make`:

```
$ make
```

#### Requirements

The build process requires `flex`, `bison`, and `gcc`.
Your *nix distro probably has these bundled.

## Test

Tests are written in JavaScript and run with with `ava`. Use `npm` to install `ava`.

```
$ npm install
$ npm test
```