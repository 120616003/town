#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <deque>  
#include <pthread.h>
#include <functional>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

namespace town {

class ThreadPool
{
public:
    typedef std::function<void()> Task;

public:
    explicit ThreadPool(size_t threadNum = 10, std::string threadName = "ThreadPool")
    {
        isRunning_ = true;
        threadsNum_ = threadNum;
        threadName_ = threadName;
        createThreads();
    }

    ~ThreadPool()
    {
        stop();
    }

public:
    size_t addTask(const Task& task)
    {
        pthread_mutex_lock(&mutex_);
        taskQueue_.push_back(task);
        size_t size = taskQueue_.size();
        pthread_mutex_unlock(&mutex_);
        pthread_cond_signal(&condition_);
        return size;
    }

    void stop()
    {
        if (!isRunning_) {
            return;
        }

        isRunning_ = false;
        pthread_cond_broadcast(&condition_);

        for (size_t i = 0; i < threadsNum_; i++) {
            pthread_join(threads_[i], nullptr);
        }

        free(threads_);
        threads_ = nullptr;

        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&condition_);
    }

    size_t size()
    {
        pthread_mutex_lock(&mutex_);
        size_t size = taskQueue_.size();
        pthread_mutex_unlock(&mutex_);
        return size;
    }

    Task take()
    {
        Task task = nullptr;
        pthread_mutex_lock(&mutex_);
        while (taskQueue_.empty() && isRunning_) {
            pthread_cond_wait(&condition_, &mutex_);
        }

        if (!isRunning_) {
            pthread_mutex_unlock(&mutex_);
            return task;
        }

        assert(!taskQueue_.empty());
        task = taskQueue_.front();
        taskQueue_.pop_front();
        pthread_mutex_unlock(&mutex_);
        return task;
    }

private:
    void createThreads()
    {
        pthread_mutex_init(&mutex_, nullptr);
        pthread_cond_init(&condition_, nullptr);
        threads_ = static_cast<pthread_t*>(malloc(sizeof(pthread_t) * threadsNum_));
        for (size_t i = 0; i < threadsNum_; i++) {
            pthread_create(&threads_[i], nullptr, threadFunc, this);
            std::string threadName = threadName_ + "_" + std::to_string(i);
            pthread_setname_np(threads_[i], threadName.c_str());
        }
    }

    static void* threadFunc(void* threadData)
    {
        pthread_t tid = pthread_self();
        ThreadPool* pool = static_cast<ThreadPool*>(threadData);
        while (pool->isRunning_) {
            ThreadPool::Task task = pool->take();
            if (!task) {
                printf("thread %lu will exit\n", tid);
                break;
            }
            assert(task);
            task();
        }
        return 0;
    }

private:
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;

private:
    volatile  bool   isRunning_;
    size_t           threadsNum_;
    pthread_t*       threads_;
    std::deque<Task> taskQueue_;
    pthread_mutex_t  mutex_;
    pthread_cond_t   condition_;
    std::string      threadName_;

}; /* ThreadPool */

} /* town */

#endif /* THREAD_POOL_H */