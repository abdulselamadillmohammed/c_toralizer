# c_toralizer

**Toralize** is a minimal LD_PRELOAD / DYLD shim that transparently routes TCP connections through a SOCKS4 proxy (e.g., Tor at `127.0.0.1:9150`).  
It works by intercepting `connect()` calls and relaying them via the proxy.

## Features

- Transparent TCP tunneling through Tor
- Simple and lightweight (~100 LOC)
- Works with many CLI tools (`curl`, etc.) if library injection is allowed

## Limitations

- SOCKS4 only → requires an **IP address** (no hostname DNS resolution via Tor)
- No UDP support
- On macOS, `DYLD_INSERT_LIBRARIES` is ignored for Apple-signed binaries (use Homebrew builds)

## Build

**macOS**:

```bash
clang -dynamiclib -o toralize.dylib toralize.c
```

**Linux**:

```bash
gcc -fPIC -shared -o toralize.so toralize.c -ldl -D_GNU_SOURCE
```

## Usage

Wrapper script example (macOS):

```bash
#!/bin/bash
export DYLD_INSERT_LIBRARIES="/absolute/path/to/toralize.dylib"
export DYLD_FORCE_FLAT_NAMESPACE=1
"$@"
unset DYLD_INSERT_LIBRARIES
unset DYLD_FORCE_FLAT_NAMESPACE
```

Run any command through Tor:

```bash
./toralize curl https://ifconfig.me
```

## Example

./toralize curl -X POST http://127.0.0.1:8000/api/token/ \
 -d "username=yourusername&password=yourpassword"

## Disclaimer

This project is for **educational use**. For real anonymity, use [torsocks](https://gitweb.torproject.org/torsocks.git/) or applications configured with SOCKS5.
