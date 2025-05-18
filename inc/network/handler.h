#ifndef HANDLER_H
#define HANDLER_H

#include <enet/enet.h>

typedef enum
{
  PACKET_NONE,
  PACKET_NEWUSER,
  PACKET_VELOCITY
} PacketType;

typedef struct
{
  PacketType type;

  union
  {
    struct
    {
      int id;
    } newuser;

    struct
    {
      float x;
      float y;
    } velocity;
  };
} PacketResult;

PacketResult handle_packet(ENetEvent* event);

#endif // HANDLER_H
