
# matrix-nx-sdk

This is a [Matrix](https://matrix.org/) client SDK for the Nintendo Switch. This code is forked from the [Matrix 3DS Client SDK](https://github.com/Sorunome/matrix-3ds-sdk).

## Prerequisites

- [devkitPro](https://devkitpro.org/wiki/Getting_Started)

After installing devkitPro, you will need to download the following using [devkitPro pacman](https://devkitpro.org/wiki/devkitPro_pacman) or the devkitPro updater:

- switch-curl
- switch-jansson
- switch-dev

In other words, you'll need to run the following command in a Terminal/command prompt (with administrator/root privileges):

```
dkp-pacman -S switch-curl switch-jansson switch-dev
```

## Compilation

This project ships with a [Makefile](Makefile), which is meant to simplify the compilation process. If you're unfamiliar with them, you can find out more about GNU Make [here](https://www.gnu.org/software/make/).

```bash
make
make install
```

## Usage

As mentioned above, this library depends on jansson and libcurl. Make sure to add them to your project's compilation options and make sure that they have been included in your project's Makefile:

```
-lmatrix-nx-sdk -ljansson `curl-config --libs`
```

### Support

[![3DS spec support room on Matrix](https://img.shields.io/matrix/matrix-3ds-sdk:sorunome.de.svg?label=%23matrix-3ds-sdk:sorunome.de&logo=matrix&server_fqdn=sorunome.de)](https://matrix.to/#/#matrix-3ds-sdk:sorunome.de)

### Funding

Donate to the original creator ([Sorunome](https://github.com/Sorunome/matrix-3ds-sdk)):
[![donate](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/Sorunome/donate)
