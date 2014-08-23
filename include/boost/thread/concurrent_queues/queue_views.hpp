#ifndef BOOST_THREAD_QUEUE_VIEWS_HPP
#define BOOST_THREAD_QUEUE_VIEWS_HPP

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/thread for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/thread/detail/config.hpp>
#include <boost/thread/detail/move.hpp>
#include <boost/thread/concurrent_queues/queue_op_status.hpp>
#include <boost/thread/concurrent_queues/queue_base.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost
{
namespace concurrent
{

  template <typename Queue>
  class queue_back_view
  {
   Queue& queue;
  public:
    typedef typename Queue::value_type value_type;
    typedef typename Queue::size_type size_type;

    // Constructors/Assignment/Destructors
    queue_back_view(Queue& q) BOOST_NOEXCEPT : queue(q) {}

    // Observers
    bool empty() const  { return queue.empty(); }
    bool full() const { return queue.full(); }
    size_type size() const { return queue.size(); }
    bool closed() const { return queue.closed(); }

    // Modifiers
    void close() { queue.close(); }

    void push(const value_type& x) { queue.push_back(x); }
    void push(BOOST_THREAD_RV_REF(value_type) x) { queue.push_back(forward<value_type>(x)); }

    void pull(value_type& x) { queue.pull_back(x); }
    // enable_if is_nothrow_copy_movable<value_type>
    value_type pull()  { return queue.pull_back(); }

    queue_op_status try_push(const value_type& x) { return queue.try_push_back(x); }
    queue_op_status try_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.try_push_back(forward<value_type>(x)); }

    queue_op_status try_pull(value_type& x) { return queue.try_pull_back(x); }

    queue_op_status nonblocking_push(const value_type& x) { return queue.nonblocking_push_back(x); }
    queue_op_status nonblocking_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.nonblocking_push_back(forward<value_type>(x)); }

    queue_op_status nonblocking_pull(value_type& x) { return queue.nonblocking_pull_back(x); }

    queue_op_status wait_push(const value_type& x) { return queue.wait_push_back(x); }
    queue_op_status wait_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.wait_push_back(forward<value_type>(x)); }
    queue_op_status wait_pull_front(value_type& x) { return queue.wait_pull_back(x); }

  };

  template <typename Queue>
  class queue_front_view
  {
   Queue& queue;
  public:
    typedef typename Queue::value_type value_type;
    typedef typename Queue::size_type size_type;

    // Constructors/Assignment/Destructors
    queue_front_view(Queue& q) BOOST_NOEXCEPT : queue(q) {}

    // Observers
    bool empty() const  { return queue.empty(); }
    bool full() const { return queue.full(); }
    size_type size() const { return queue.size(); }
    bool closed() const { return queue.closed(); }

    // Modifiers
    void close() { queue.close(); }

    void push(const value_type& x) { queue.push_front(x); }
    void push(BOOST_THREAD_RV_REF(value_type) x) { queue.push_front(forward<value_type>(x)); }

    void pull(value_type& x) { queue.pull_front(x); };
    // enable_if is_nothrow_copy_movable<value_type>
    value_type pull()  { return queue.pull_front(); }

    queue_op_status try_push(const value_type& x) { return queue.try_push_front(x); }
    queue_op_status try_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.try_push_front(forward<value_type>(x)); }

    queue_op_status try_pull(value_type& x) { return queue.try_pull_front(x); }

    queue_op_status nonblocking_push(const value_type& x) { return queue.nonblocking_push_front(x); }
    queue_op_status nonblocking_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.nonblocking_push_front(forward<value_type>(x)); }

    queue_op_status nonblocking_pull(value_type& x) { return queue.nonblocking_pull_front(x); }

    queue_op_status wait_push(const value_type& x) { return queue.wait_push_front(x); }
    queue_op_status wait_push(BOOST_THREAD_RV_REF(value_type) x) { return queue.wait_push_front(forward<value_type>(x)); }
    queue_op_status wait_pull(value_type& x) { return queue.wait_pull_front(x); }

  };

#if 0
  template <class T>
  using queue_back = queue_back_view<queue_base<T> > ;
  template <class T>
  using queue_front = queue_front_view<queue_base<T> > ;
#else
  template <class T>
  struct queue_back {
    typedef queue_back_view<queue_base<T> > type;
  };
  template <class T>
  struct queue_front {
    typedef queue_front_view<queue_base<T> > type;
  };

#endif

//  template <class Queue>
//  queue_back_view<Queue> back(Queue & q) { return queue_back_view<Queue>(q); }
//  template <class Queue>
//  queue_front_view<Queue> front(Queue & q) { return queue_front_view<Queue>(q); }
//#if 0
//  template <class T>
//  queue_back<T> back(queue_base<T> & q) { return queue_back<T>(q); }
//  template <class T>
//  queue_front<T> front(queue_base<T> & q) { return queue_front<T>(q); }
//#else
//  template <class T>
//  typename queue_back<T>::type back(queue_base<T> & q) { return typename queue_back<T>::type(q); }
//  template <class T>
//  typename queue_front<T>::type front(queue_base<T> & q) { return typename queue_front<T>::type(q); }
//#endif
}

using concurrent::queue_back_view;
using concurrent::queue_front_view;
using concurrent::queue_back;
using concurrent::queue_front;
//using concurrent::back;
//using concurrent::front;

}

#include <boost/config/abi_suffix.hpp>

#endif
