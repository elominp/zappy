#ifndef ZAPPY_COMMUNICATOR_H
# define ZAPPY_COMMUNICATOR_H

# ifdef __WIN32__
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <winsock.h>
# else
#  include <sys/socket.h>
#  include <netdb.h>
#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <unistd.h>
# endif
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define CAPSULE_NAME "ZappyCommunicator Capsule"

# define NOSUCHHOSTNAME -1
# define CANTOPENSOCKET -2
# define CANTCONNECTTOHOST -3
# define CANTCONVERTSOCKETTOFILE -4
# define NOCOMMUNICATOR -5
# define CANTWRITEONSOCKET -6
# define NOTCONNECTED -7
# define MEMFAILED -8
# define READERROR -9

# define READSUCCESS 1
# define NOTHINGTOREAD 2
# define LINEEXTRACTED 3
# define NOLINETOEXTRACT 4

typedef struct hostent hostent;
typedef struct sockaddr_in sockaddr_in;

typedef struct  s_communicator
{
  int           socket;
  FILE          *fsocket;
  char          *host;
  uint16_t      port;
  hostent       *hostent_ptr;
  char          ip[16];
  sockaddr_in   socket_conf;
  int           status;
}               t_communicator;

typedef struct      s_zappy_communicator
{
  void              (*destructor)(void *);
  t_communicator    *communicator;
  int               last_return_value;
  char              *buffer;
  size_t            buffer_len;
  t_communicator    *(*connect)(struct s_zappy_communicator *, const char *, uint16_t);
  void              (*disconnect)(struct s_zappy_communicator *, ...);
  const char        *(*return_value_to_string)(struct s_zappy_communicator *, ...);
  size_t            (*send)(struct s_zappy_communicator *, const char *, ...);
  char              *(*recv)(struct s_zappy_communicator *);
  char              *(*getnextline)(struct s_zappy_communicator *);
}                   t_zappy_communicator;

# ifdef __cplusplus
extern "C" {
# endif

t_zappy_communicator        *create_zappy_communicator(void);

# ifdef __cplusplus
}
# endif

# ifndef __cplusplus
void                        delete(void *ptr);
# endif

#endif /* ZAPPY_COMMUNICATOR_H */
