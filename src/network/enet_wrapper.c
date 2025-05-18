#include "network/enet_wrapper.h"
#include <stdio.h>

int init_enet(void)
{
  if (enet_initialize() != 0)
  {
    fprintf(stderr, "ENet initialization failed.\n");
    return 0;
  }
  atexit(enet_deinitialize);
  return 1;
}

void shutdown_enet(void) { enet_deinitialize(); }

ENetWrapperServer* create_server(enet_uint16 port, size_t max_clients)
{
  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = port;

  ENetHost* server = enet_host_create(&address, max_clients, 2, 0, 0);
  if (!server)
  {
    fprintf(stderr, "Failed to create ENet server.\n");
    return NULL;
  }

  ENetWrapperServer* wrapper = malloc(sizeof(ENetWrapperServer));
  wrapper->host = server;
  return wrapper;
}

void destroy_server(ENetWrapperServer* server)
{
  if (server)
  {
    if (server->host)
    {
      enet_host_destroy(server->host);
    }
    free(server);
  }
}

ENetWrapperClient* create_client(void)
{
  ENetHost* client = enet_host_create(NULL, 1, 2, 0, 0);
  if (!client)
  {
    fprintf(stderr, "Failed to create ENet client.\n");
    return NULL;
  }

  ENetWrapperClient* wrapper = malloc(sizeof(ENetWrapperClient));
  wrapper->host = client;
  wrapper->peer = NULL;
  return wrapper;
}

int connect_client(ENetWrapperClient* client, const char* address_str,
                   enet_uint16 port)
{
  if (!client)
    return 0;

  ENetAddress address;
  enet_address_set_host(&address, address_str);
  address.port = port;

  client->peer = enet_host_connect(client->host, &address, 2, 0);
  if (!client->peer)
  {
    fprintf(stderr, "Failed to initiate ENet connection.\n");
    return 0;
  }

  ENetEvent event;
  if (enet_host_service(client->host, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT)
  {
    return 1;
  }

  enet_peer_reset(client->peer);
  client->peer = NULL;
  return 0;
}

void destroy_client(ENetWrapperClient* client)
{
  if (client)
  {
    if (client->peer)
    {
      enet_peer_disconnect(client->peer, 0);
    }
    if (client->host)
    {
      enet_host_destroy(client->host);
    }
    free(client);
  }
}
