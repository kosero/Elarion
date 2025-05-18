#include "network/connection.h"
#include "network/enet_wrapper.h"
#include <stdio.h>
#include <stdlib.h>

Connection* connection_create(ConnectionType type, const char* address,
                              enet_uint16 port, size_t max_peers)
{
  Connection* conn = malloc(sizeof(Connection));
  if (!conn)
    return NULL;

  conn->type = type;
  conn->peer = NULL;

  if (type == CONNECTION_SERVER)
  {
    ENetWrapperServer* server = create_server(port, max_peers);
    if (!server)
    {
      free(conn);
      return NULL;
    }
    conn->host = server->host;
    free(server);
  }
  else if (type == CONNECTION_CLIENT)
  {
    ENetWrapperClient* client = create_client();
    if (!client)
    {
      free(conn);
      return NULL;
    }

    if (!connect_client(client, address, port))
    {
      destroy_client(client);
      free(conn);
      return NULL;
    }

    conn->host = client->host;
    conn->peer = client->peer;
    free(client);
  }

  return conn;
}

int connection_service(Connection* conn, ENetEvent* event,
                       enet_uint32 timeout_ms)
{
  if (!conn || !conn->host || !event)
    return 0;
  return enet_host_service(conn->host, event, timeout_ms);
}

int connection_send(Connection* conn, ENetPeer* peer, const void* data,
                    size_t size, enet_uint8 channel, enet_uint32 flags)
{
  if (!conn || !peer || !data)
    return 0;

  ENetPacket* packet = enet_packet_create(data, size, flags);
  if (!packet)
    return 0;

  return enet_peer_send(peer, channel, packet) == 0;
}

void connection_disconnect(Connection* conn, ENetPeer* peer, enet_uint32 data)
{
  if (!conn || !peer)
    return;

  enet_peer_disconnect(peer, data);

  ENetEvent event;
  while (enet_host_service(conn->host, &event, 3000) > 0)
  {
    if (event.type == ENET_EVENT_TYPE_DISCONNECT)
    {
      break;
    }
  }

  enet_peer_reset(peer);
}

void connection_destroy(Connection* conn)
{
  if (!conn)
    return;

  if (conn->peer && conn->type == CONNECTION_CLIENT)
  {
    connection_disconnect(conn, conn->peer, 0);
  }

  if (conn->host)
  {
    enet_host_destroy(conn->host);
  }

  free(conn);
}
