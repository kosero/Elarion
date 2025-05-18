#include "network/handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PacketResult handle_packet(ENetEvent* event)
{
  PacketResult result = {.type = PACKET_NONE};

  if (!event || !event->packet)
    return result;

  char* raw = (char*)malloc(event->packet->dataLength + 1);
  memcpy(raw, event->packet->data, event->packet->dataLength);
  raw[event->packet->dataLength] = '\0';

  char* sep = strchr(raw, ':');
  if (!sep)
  {
    fprintf(stderr, "Invalid packet format: %s\n", raw);
    free(raw);
    return result;
  }

  *sep = '\0';
  char* command = raw;
  char* data = sep + 1;

  if (strcmp(command, "newuser") == 0)
  {
    result.type = PACKET_NEWUSER;
    result.newuser.id = atoi(data);
  }
  else if (strcmp(command, "vel") == 0)
  {
    result.type = PACKET_VELOCITY;
    sscanf(data, "%f,%f", &result.velocity.x, &result.velocity.y);
  }

  free(raw);
  return result;
}
