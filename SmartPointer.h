#pragma once
#include <stdexcept> 
#include <string>


namespace forehm
{
    template <typename Type>
    class SmartPointer 
    {
    public:
        SmartPointer() = default;

        SmartPointer(const SmartPointer&) = delete;

        explicit SmartPointer(Type* raw_ptr) noexcept
            : ptr_(raw_ptr) 
        {
        }

        Type* GetRawPtr() const noexcept 
        {
            return ptr_;
        }

        Type* Release() noexcept 
        {
            Type* p = ptr_;
            ptr_ = nullptr;
            return p;
        }

        explicit operator bool() const 
        {
            return ptr_ != nullptr;
        }

        Type* operator->() const 
        {
            using namespace std::literals;
            if (!ptr_) 
            {
                throw std::logic_error("Scoped ptr is null"s);
            }
            return ptr_;
        }

        Type& operator*() const 
        {
            using namespace std::literals;
            if (!ptr_) 
            {
                throw std::logic_error("Scoped ptr is null"s);
            }
            return *ptr_;
        }

        ~SmartPointer() 
        {
            delete ptr_;
        }

    private:

        Type* ptr_ = nullptr;
    };
}

