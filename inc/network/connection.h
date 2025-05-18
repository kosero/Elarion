#ifndef CONNECTION_H
#define CONNECTION_H

#include <enet/enet.h>

typedef enum
{
  CONNECTION_SERVER,
  CONNECTION_CLIENT
} ConnectionType;

typedef struct
{
  ENetHost* host;
  ENetPeer* peer;
  ConnectionType type;
} Connection;

Connection* connection_create(ConnectionType type, const char* address,
                              enet_uint16 port, size_t max_peers);
int connection_service(Connection* conn, ENetEvent* event,
                       enet_uint32 timeout_ms);
int connection_send(Connection* conn, ENetPeer* peer, const void* data,
                    size_t size, enet_uint8 channel, enet_uint32 flags);
void connection_disconnect(Connection* conn, ENetPeer* peer, enet_uint32 data);
void connection_destroy(Connection* conn);

#endif // CONNECTION_H
