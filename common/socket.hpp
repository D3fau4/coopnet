#pragma once

#define SOCKET_DEFAULT_INFO 7919

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdint.h>
#define in_addr_t ULONG
#define MSG_DONTWAIT 0

#define SOCKET_RESET_ERROR() WSASetLastError(0)
#define SOCKET_LAST_ERROR WSAGetLastError()
#define SOCKET_EAGAIN EAGAIN
#define SOCKET_EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKET_ECONNRESET WSAECONNRESET

#elif defined(__SWITCH__)

// Nintendo Switch (libnx) - BSD sockets are provided through switch.h
#include <switch.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <sys/ioctl.h>

// in_addr_t is not provided by libnx netinet/in.h
typedef uint32_t in_addr_t;

#define SOCKET_RESET_ERROR() errno = 0
#define SOCKET_LAST_ERROR errno
#define SOCKET_EAGAIN EAGAIN
#define SOCKET_EWOULDBLOCK EWOULDBLOCK
#define SOCKET_ECONNRESET ECONNRESET

#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>

#define SOCKET_RESET_ERROR() errno = 0
#define SOCKET_LAST_ERROR errno
#define SOCKET_EAGAIN EAGAIN
#define SOCKET_EWOULDBLOCK EWOULDBLOCK
#define SOCKET_ECONNRESET ECONNRESET

#endif

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif

uint64_t SocketAddHash(uint64_t info);
int SocketInitialize(int aAf, int aType, int aProtocol);
int SocketClose(int aSocket);
void SocketSetOptions(int aSocket);
void SocketLimitBuffer(int aSocket, int64_t* amount);
uint64_t SocketGetInfoBits(int aSocket);

