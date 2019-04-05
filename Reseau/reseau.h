#include "../definitions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#define PORT 15000 // Port du serveur

SOCKET serveur(SOCKET sock);
SOCKET client(SOCKET sock);
void deconnextion(SOCKET sock);
