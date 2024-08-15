FROM alpine:latest AS builder

RUN apk add --no-cache gcc musl-dev make cmake linux-headers git
WORKDIR /src/odbc-ini-gen
COPY . .
RUN cmake -S . -B build_alpine && \
    cmake --build build_alpine && \
    cmake --install build_alpine --prefix /opt/odbc-ini-gen && \
    printf 'Installed %s' "$(/opt/odbc-ini-gen/bin/odbc_ini_gen --version)"

FROM alpine AS runner
# FROM busybox:musl AS runner
# FROM scratch AS runner
# FROM gcr.io/distroless/static-debian12 AS runner

COPY --from=builder /opt/odbc-ini-gen /opt/odbc-ini-gen
ENTRYPOINT ["/opt/odbc-ini-gen/bin/odbc_ini_gen"]
