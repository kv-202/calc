#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <QQueue>
#include <QMutex>

template <class T>
class ThreadSafeQueue
{
public:
    void enqueue(const T &value)
    {
        QMutexLocker l(&_mutex);
        _queue.enqueue(value);
    }

    bool dequeue(T &value)
    {
        QMutexLocker l(&_mutex);
        if (_queue.isEmpty())
            return false;

        value = _queue.dequeue();
        return true;
    }

    int size()
    {
        QMutexLocker l(&_mutex);
        return _queue.size();
    }

private:
    QQueue<T> _queue;
    QMutex _mutex;
};

#endif // THREADSAFEQUEUE_H
