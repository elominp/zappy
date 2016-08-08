#include "zappy_communicator.h"
#include "zappy_recv.c"
#include "zappy_send.c"
#include "zappy_connect_to_server2.c"
#include "zappy_connect_to_server.c"
#include "zappy_disconnect_from_server.c"
#include "zappy_return_value_to_string.c"
#include "zappy_getnextline.c"

static void                 zappy_destructor(void *ptr)
{
  t_zappy_communicator      *communicator;

  if ((communicator = ptr) == NULL)
      return;
  if (communicator->communicator != NULL &&
      communicator->communicator->status)
  {
      communicator->disconnect(communicator);
      free(communicator->communicator);
  }
}

t_zappy_communicator        *create_zappy_communicator(void)
{
  t_zappy_communicator      *communicator;

  if ((communicator = malloc(sizeof(*communicator))) == NULL)
    return (NULL);
  communicator->connect = connect_to_server;
  communicator->disconnect = disconnect_from_server;
  communicator->return_value_to_string = return_value_to_string;
  communicator->send = zappy_send;
  communicator->recv = zappy_recv;
  communicator->last_return_value = 0;
  communicator->communicator = NULL;
  communicator->destructor = zappy_destructor;
  communicator->getnextline = zappy_getnextline;
  communicator->buffer = NULL;
  return (communicator);
}

#ifndef __cplusplus
void                        delete(void *ptr)
{
    void                    (*fct)(void *);

    if (ptr != NULL)
    {
        if ((fct = *(void **) ptr) != NULL)
            fct(ptr);
        free(ptr);
    }
}
#endif
