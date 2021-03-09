#ifndef SECURE_QUEUE_H
#define SECURE_QUEUE_H

#include <queue>
#include <atomic>

template <class T>
class SecureQueue
{
public:
	void push(T& value)
	{ __push(value); }

	T pop()
	{ return __pop(); }

	void pop(T& value)
	{ __pop(value); }

	uint64_t size()
	{ return __size(); }

	bool empty()
	{ return __empty(); }

public:
	SecureQueue()
	{
		m_atomic_record.store(0);
	}

	void __push(T& value)
	{
		while (m_atomic_lock.test_and_set(std::memory_order_acquire));
		m_queue.push(std::move(value));
		m_atomic_record.fetch_add(1, std::memory_order_seq_cst);
		m_atomic_lock.clear(std::memory_order_release);
	}

	T __pop()
	{
		while (m_atomic_lock.test_and_set(std::memory_order_acquire));
		T value = std::move(m_queue.front());
		m_queue.pop();
		m_atomic_record.fetch_sub(1, std::memory_order_seq_cst);
		m_atomic_lock.clear(std::memory_order_release);
		return value;
	}

	void __pop(T& value)
	{
		while (m_atomic_lock.test_and_set(std::memory_order_acquire));
		value = std::move(m_queue.front());
		m_queue.pop();
		m_atomic_record.fetch_sub(1, std::memory_order_seq_cst);
		m_atomic_lock.clear(std::memory_order_release);
	}

	uint64_t __size()
	{
		return m_atomic_record.load();
	}

	bool __empty()
	{
		return __size() == 0;
	}

private:
	std::queue<T> m_queue;
	std::atomic<uint64_t> m_atomic_record;
	std::atomic_flag m_atomic_lock = ATOMIC_FLAG_INIT;
};

#endif /* SECURE_QUEUE_H */