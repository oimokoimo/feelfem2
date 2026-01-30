# bamg-0.62 (Dec 1997) build container for podman
FROM ubuntu:18.04 AS build

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        build-essential \
        make \
        tar \
        gzip \
        gcc-4.8 \
        g++-4.8 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY bamg-v0.62.tar.gz /src/
RUN tar -xzf bamg-v0.62.tar.gz && test -d /src/bamg

WORKDIR /src/bamg

# ---- legacy pre-standard C++ header compatibility shims ----
RUN mkdir -p /usr/local/include && \
    printf '%s\n' \
'#ifndef IOSTREAM_H_COMPAT' \
'#define IOSTREAM_H_COMPAT' \
'#include <iostream>' \
'#include <ios>' \
'#include <ostream>' \
'#include <istream>' \
'' \
'// Old iostream.h compatibility (pre-ISO): provide global names' \
'typedef std::ios     ios;' \
'typedef std::istream istream;' \
'typedef std::ostream ostream;' \
'' \
'using std::cin;' \
'using std::cout;' \
'using std::cerr;' \
'using std::clog;' \
'using std::endl;' \
'using std::flush;' \
'#endif' \
    > /usr/local/include/iostream.h && \
    printf '%s\n' \
'#ifndef FSTREAM_H_COMPAT' \
'#define FSTREAM_H_COMPAT' \
'#include <fstream>' \
'#include <ios>' \
'' \
'// Old fstream.h compatibility (pre-ISO)' \
'typedef std::ios ios;' \
'' \
'using std::ifstream;' \
'using std::ofstream;' \
'using std::fstream;' \
'#endif' \
    > /usr/local/include/fstream.h && \
    printf '%s\n' \
'#ifndef IOMANIP_H_COMPAT' \
'#define IOMANIP_H_COMPAT' \
'#include <iomanip>' \
'' \
'// Old iomanip.h compatibility (pre-ISO)' \
'using std::setw;' \
'using std::setprecision;' \
'using std::setfill;' \
'using std::fixed;' \
'using std::scientific;' \
'#endif' \
    > /usr/local/include/iomanip.h && \
    printf '%s\n' \
'#ifndef NEW_H_COMPAT' \
'#define NEW_H_COMPAT' \
'#include <new>' \
'' \
'// Old new.h compatibility (pre-ISO): provide global symbols' \
'typedef std::new_handler new_handler;' \
'' \
'// Provide global set_new_handler (old code calls it without std::)' \
'inline new_handler set_new_handler(new_handler h) { return std::set_new_handler(h); }' \
'#endif' \
    > /usr/local/include/new.h

# ---- build ----
RUN make HOSTTYPE=linux clean || true && \
    make -j"$(nproc)" \
        HOSTTYPE=linux \
        CXX=g++-4.8 \
        CC=gcc-4.8 \
        CXXFLAGS="-O2 -std=gnu++98 -Wno-write-strings -fpermissive -I/usr/local/include" \
        CPPFLAGS="-I/usr/local/include"

# collect outputs
RUN mkdir -p /out && \
    cp -a /src/bamg /out/src && \
    (find /src/bamg -maxdepth 2 -type f -executable -print -exec cp -a {} /out/ \; ) || true

FROM ubuntu:18.04 AS runtime
WORKDIR /work
COPY --from=build /out /out
CMD ["/bin/bash"]

