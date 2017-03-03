/**
 * Chatroom Lab
 * CS 241 - Fall 2016
 */
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "utils.h"
#include "user_hooks.h"
static const size_t MESSAGE_SIZE_DIGITS = 4;

char *create_message(char *name, char *message) {
  int name_len = strlen(name);
  int msg_len = strlen(message);
  char *msg = calloc(1, msg_len + name_len + 4);
  sprintf(msg, "%s: %s", name, message);
  // printf("when created, message is: %s\n", msg);
  // printf("\nmaking message of size: %d\n", msg_len + name_len + 4);

  return msg;
}

ssize_t get_message_size(int socket) 
{
  // printf("\ngetting message size\n");

  int32_t size;
  ssize_t read_bytes =
      read_all_from_socket(socket, (char *)&size, MESSAGE_SIZE_DIGITS);
  if (read_bytes == 0 || read_bytes == -1)
  {
    // printf("problem in get_message_size, size is %zd\n", read_bytes);
    return read_bytes;
  }
  // printf("the message size was %u\n", ntohl(size));

  return (ssize_t)ntohl(size);
}

ssize_t write_message_size(size_t size, int socket) 
{

   // printf("\nin write_message_size\n");
  // printf("size is %lu\n", size);
  size_t network_sized = htonl(size);
  // printf("\nnetwork_sized is located at %p\n", (&network_sized));
  // printf("message-size is %zu\n", size);

  size_t count = sizeof(uint32_t);
  char* buffer = (char*)(&network_sized);

  // printf("\nwriting the message size\n");
  size_t total_bytes_written=0;

  // printf("socket is %d\n", socket);

  while(1)
  {
    // printf("in write_message_size while loop\n");
    usleep(200000);
    void* address = (void*)(buffer+total_bytes_written) ;
    // printf("\naddress is %p\n",address);

    int bytes_written = write(socket, address, count-total_bytes_written );
    // printf("write_message_size has wrote\n");
    if(bytes_written!=-1)
    total_bytes_written += (size_t)bytes_written;
    
    if( total_bytes_written == count )
    {
      // printf("printed everyting\n");
      return total_bytes_written;
    }

    else if( bytes_written == 0 )
      return 0;

    else if( bytes_written == -1 && errno != EINTR) {
      perror("write_all_to_socket()");
      return -1;
    }
  }

  return 9001;
 
}

// reads count number of bytes from socket and stores them in buffer
ssize_t read_all_from_socket(int socket, char *buffer, size_t count) 
{
  // printf("count is %lu\n", count);
  size_t total_bytes_read=0;

  while(1)
  {
    // printf("read_all_from_socket has read\n");
    //TODO: change to myread
    int bytes_read = read(socket, buffer+total_bytes_read, count-total_bytes_read);
    
    if(bytes_read != -1)
    total_bytes_read += bytes_read;

    if( ((size_t)total_bytes_read)==count )
      return count;


    else if( bytes_read == 0 )
      return 0;

    else if( bytes_read == -1 && errno != EINTR) 
    {
      // perror("read_all_from_socket()");
      return -1;
    }
    // if(bytes_read==-1)
    // printf("EINTR\n");
  }
  
}

ssize_t write_all_to_socket(int socket, const char *buffer, size_t count) 
{
  // printf("\nwriting the message size\n");
  size_t total_bytes_written=0;

  // printf("message is %s\n", buffer);
  // printf("count is %lu\n", count);

  // printf("socket is %d\n", socket);

  while(1)
  {
    // printf("in write_message_size while loop\n");
    usleep(200000);
    void* address = (void*)(buffer+total_bytes_written) ;
    // printf("\naddress is %p\n",address);

    int bytes_written = write(socket, address, count-total_bytes_written );
    // printf("write_message_size has wrote\n");
    if(bytes_written!=-1)
    total_bytes_written += (size_t)bytes_written;
    
    if( total_bytes_written == count )
    {
      // printf("printed everyting\n");
      return total_bytes_written;
    }

    else if( bytes_written == 0 )
      return 0;

    else if( bytes_written == -1 && errno != EINTR) {
      perror("write_all_to_socket()");
      return -1;
    }
  }

  // printf("I soulg never print\n");
  return 9001;
}
