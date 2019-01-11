#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *Thread1(void *arg) {
  execlp("./build/Prototyp1", "./build/Prototype1", NULL);
  return (arg);
}

void *Thread2(void *arg) {
  execlp("./build/Prototyp1", "./build/Prototype1", NULL);
  return (arg);
}

void *Thread3(void *arg) {
  execlp("./build/Prototyp1", "./build/Prototype1", NULL);
  return (arg);
}

void *Thread4(void *arg) {
  execlp("./build/Prototyp1", "./build/Prototype1", NULL);
  return (arg);
}

int main() {
  pthread_t th1, th2, th3, th4;
  int       status;
  void *    result;

  status = pthread_create(&th1, NULL, Thread1, (void *)NULL);
  if (status != 0) {
    fprintf(stderr, "pthread_create : %s", strerror(status));
  }

  status = pthread_create(&th2, NULL, Thread2, (void *)NULL);
  if (status != 0) {
    fprintf(stderr, "pthread_create : %s", strerror(status));
  }

  status = pthread_create(&th3, NULL, Thread3, (void *)NULL);
  if (status != 0) {
    fprintf(stderr, "pthread_create : %s", strerror(status));
  }

  status = pthread_create(&th4, NULL, Thread4, (void *)NULL);
  if (status != 0) {
    fprintf(stderr, "pthread_create : %s", strerror(status));
  }

  pthread_join(th1, &result);
  pthread_join(th2, &result);
  pthread_join(th3, &result);
  pthread_join(th4, &result);

  return 0;
}