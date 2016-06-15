# 3DS Key Scrambler/Unscrambler

## Description

This tool allows you to obtain the Normal Key, that is calculated by the 3DS AES Key Scrambler, based on a KeyX and a KeyY.
You can also obtain the KeyX out of a Normal Key with the respective KeyY (or the KeyY from the Normal Key with the respective KeyX).

### Notes
- The value of the constant C is required to calculate the Normal Key, KeyX or KeyY. (This is a copyrighted value, Google is your friend)
- The tool can be built with the constant C in it, although, it shouldn't be shared since it contains the copyrighted value.

## Building

To build the tool just run `make`
But if you want the constant C to be included in the code, edit the `const_c` string in `src/main.c` to add the value and run `make INCLUDE_CONST_C=1`

## Usage

- For a Normal Key, do:
```bash
#if built without Constant C
3ds_keyscrambler N KeyX KeyY Constant_C

#if built with Constant C
3ds_keyscrambler N KeyX KeyY
```

- For a KeyX, do:
```bash
#if built without Constant C
3ds_keyscrambler X Normal_Key KeyY Constant_C

#if built with Constant C
3ds_keyscrambler X Normal_Key KeyY
```

- For a KeyY, do:
```bash
#if built without Constant C
3ds_keyscrambler Y Normal_Key KeyX Constant_C

#if built with Constant C
3ds_keyscrambler Y Normal_Key KeyX
```

## License

(If the LICENSE file wasn't enough, here, have a copy on Readme.)

MIT License

Copyright (c) 2016 luigoalma

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
