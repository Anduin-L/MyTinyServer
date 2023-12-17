//
// Created by Anduin L on 17/12/2023.
//

#ifndef MYTINYSERVER_LOCKER_H
#define MYTINYSERVER_LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>
#include <string>

class sem {
public:
    sem() : m_sem(nullptr), m_sem_name("/my_semaphore") {
      if ((m_sem = sem_open(m_sem_name, O_CREAT, 0)) == SEM_FAILED) {
        throw std::runtime_error("Failed to open semaphore");
      }
    }

    sem(const char *name, int num) : m_sem_name(name) {
      if ((m_sem = sem_open(m_sem_name, O_CREAT, num)) == SEM_FAILED) {
        throw std::runtime_error("Failed to open semaphore");
      }
    }

    ~sem() {
      if (m_sem != nullptr) {
        sem_close(m_sem);
      }
    }

    bool wait() {
      return sem_wait(m_sem) == 0;
    }

    bool post() {
      return sem_post(m_sem) == 0;
    }

    bool unlink() {
      if (sem_unlink(m_sem_name) != 0) {
        throw std::runtime_error("Failed to unlink semaphore");
      }
      return true;
    }

private:
    sem_t *m_sem;
    const char *m_sem_name;
};

class locker {
public:
    locker() {
      if (pthread_mutex_init(&m_mutex, NULL) != 0) {
        throw std::exception();
      }
    }

    ~locker() {
      pthread_mutex_destroy(&m_mutex);
    }

    bool lock() {
      return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock() {
      return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t *get() {
      return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};

class cond {
public:
    cond() {
      if (pthread_cond_init(&m_cond, NULL) != 0) {
        //pthread_mutex_destroy(&m_mutex);
        throw std::exception();
      }
    }

    ~cond() {
      pthread_cond_destroy(&m_cond);
    }

    bool wait(pthread_mutex_t *m_mutex) {
      int ret = 0;
      //pthread_mutex_lock(&m_mutex);
      ret = pthread_cond_wait(&m_cond, m_mutex);
      //pthread_mutex_unlock(&m_mutex);
      return ret == 0;
    }

    bool timewait(pthread_mutex_t *m_mutex, struct timespec t) {
      int ret = 0;
      //pthread_mutex_lock(&m_mutex);
      ret = pthread_cond_timedwait(&m_cond, m_mutex, &t);
      //pthread_mutex_unlock(&m_mutex);
      return ret == 0;
    }

    bool signal() {
      return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast() {
      return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    //static pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif //MYTINYSERVER_LOCKER_H
