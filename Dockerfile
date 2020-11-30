ARG CONF=emu

FROM i386/debian:buster-slim AS build
ARG CONF
RUN apt-get -y update
RUN apt-get install -y libx11-dev \
	libxext-dev \
	linux-libc-dev \
	gcc

ENV INFERNO=/usr/inferno
COPY . $INFERNO
WORKDIR $INFERNO

# setup a custom mkconfig
RUN echo > mkconfig ROOT=$INFERNO; \
echo >>mkconfig TKSTYLE=std; \
echo >>mkconfig CONF=${CONF}; \
echo >>mkconfig SYSHOST=Linux; \
echo >>mkconfig SYSTARG=Linux; \
echo >>mkconfig OBJTYPE=386; \
echo >>mkconfig 'OBJDIR=$SYSTARG/$OBJTYPE'; \
echo >>mkconfig '<$ROOT/mkfiles/mkhost-$SYSHOST'; \
echo >>mkconfig '<$ROOT/mkfiles/mkfile-$SYSTARG-$OBJTYPE'

# build code
RUN ./makemk.sh
ENV PATH="$INFERNO/Linux/386/bin:${PATH}"
RUN mk mkdirs
RUN mk nuke
RUN mk install


FROM i386/busybox:glibc AS inferno
ARG CONF

RUN mkdir -p /usr/lib/i386-linux-gnu/
COPY --from=build \
	/usr/lib/i386-linux-gnu/libX11.so.6 \
	/usr/lib/i386-linux-gnu/libxcb.so.1 \
	/usr/lib/i386-linux-gnu/libXau.so.6 \
	/usr/lib/i386-linux-gnu/libXdmcp.so.6 \
	/usr/lib/i386-linux-gnu/libXext.so.6 \
	/usr/lib/i386-linux-gnu/libbsd.so.0   /usr/lib/i386-linux-gnu/
RUN mkdir -p /lib/i386-linux-gnu/
COPY --from=build \
	/lib/i386-linux-gnu/libgcc_s.so.1 \
	/lib/i386-linux-gnu/libdl.so.2 \
	/lib/i386-linux-gnu/librt.so.1	 /lib/i386-linux-gnu/

#RUN apt-get -y install libx11-6 libxext6

WORKDIR /usr/inferno
COPY --from=build /usr/inferno/ .
RUN cp ./Linux/386/bin/$CONF ./inferno
CMD ["./inferno", "-c1",  "echo", "Hello from Purgatory!" ]
