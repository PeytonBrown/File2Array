# File2Array

Converts any file to an array or bytes. Useful for embedding resources directly into an application.

# Usage

Simply drag and drop any file on to the File2Array.exe

![Example usage](https://i.imgur.com/lERmD1R.gif)

# Example output

```
#pragma once

int Hello_World_size = 11;

unsigned char Hello_World[] = {
	0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64
};
```