//
// Created by Rahul Gupta on 01/06/26.
//

#ifndef CPP_UNDER_THE_HOOD_UNIQUE_PTR_H
#define CPP_UNDER_THE_HOOD_UNIQUE_PTR_H

namespace rdx
{
    template <typename Type, typename Deleter = std::default_delete<Type>>
    class unique_ptr
    {
private:
        Type* m_ptr;
        Deleter m_deleter = {};
public:
        /*
        NOTE: By default, that destruction would take place via delete, but, during construction,
        std::unique_ptr objects can be configured to use custom deleters: arbitrary functions
        (or function objects, including those arising from lambda expressions) to be
        invoked when it’s time for their resources to be destroyed.
        */
        explicit unique_ptr() = default;
        explicit unique_ptr(Type* ptr) : m_ptr(ptr) {}
        explicit unique_ptr(Type* ptr, Deleter deleter)
                 : m_ptr(ptr)
                 , m_deleter(std::move(deleter)) {}


        // ========================================================================
        // Delete copy assignment and copy operator
        // ========================================================================
        /*
        NOTE: Copying a std::unique_ptr isn’t allowed, because if you could copy a
        std::unique_ptr, you’d end up with two std::unique_ptrs to the same resource,
        each thinking it owned (and should therefore destroy) that resource.
        */

        unique_ptr(const unique_ptr<Type>& other) = delete;
        unique_ptr& operator=(const unique_ptr<Type>& other) = delete;


        // ========================================================================
        // Allow move assignment and move operator
        // ========================================================================
        /*
        NOTE: std::unique_ptr embodies exclusive ownership semantics. A non-null std::
        unique_ptr always owns what it points to. Moving a std::unique_ptr transfers
        ownership from the source pointer to the destination pointer. (The source pointer is
        set to null.)
        */
        unique_ptr(Type&& other) noexcept : m_ptr(other.m_ptr)
        {
            other.m_ptr = nullptr;
        }

        unique_ptr&& operator=(unique_ptr<Type>&& other) noexcept
        {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }

        // ========================================================================
        // get()
        // ========================================================================
        /*
        NOTE: get() operation returns the underlying ptr
        */
        inline Type* get() const noexcept
        {
            return m_ptr;
        }

        // ========================================================================
        // Destructors
        // ========================================================================
        /*
        NOTE: By default, that destruction would take place via delete, but, during construction,
        std::unique_ptr objects can be configured to use custom deleters: arbitrary func‐
        tions (or function objects, including those arising from lambda expressions) to be
        invoked when it’s time for their resources to be destroyed.
        */
        ~unique_ptr()
        {
            if (m_ptr)
                m_deleter(m_ptr);
        }

    };
} // rdx

#endif //CPP_UNDER_THE_HOOD_UNIQUE_PTR_H