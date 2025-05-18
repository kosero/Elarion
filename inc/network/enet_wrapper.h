#ifndef ENET_WRAPPER_H
#define ENET_WRAPPER_H

#include <enet/enet.h>

typedef struct
{
  ENetHost* host;
} ENetWrapperServer;

typedef struct
{
  ENetHost* host;
  ENetPeer* peer;
} ENetWrapperClient;

int init_enet(void);      // enet_initialize()
void shutdown_enet(void); // enet_deinitialize()

ENetWrapperServer* create_server(enet_uint16 port, size_t max_clients);
void destroy_server(ENetWrapperServer* server);

ENetWrapperClient* create_client(void);
int connect_client(ENetWrapperClient* client, const char* address,
                   enet_uint16 port);
void destroy_client(ENetWrapperClient* client);

#endif // ENET_WRAPPER_H
