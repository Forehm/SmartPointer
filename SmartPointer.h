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

        explicit SmartPointer(Type* raw_ptr) noexcept
            : ptr_(raw_ptr) 
        {
        }


        SmartPointer(const SmartPointer&) = delete;

        ~SmartPointer() 
        {
            delete ptr_;
        }

        Type* GetRawPtr() const noexcept 
        {
            return ptr_;
        }

        T* Release() noexcept 
        {
            T* p = ptr_;
            ptr_ = nullptr;
            return p;
        }

        explicit operator bool() const 
        {
            return ptr_ != nullptr;
        }

        T* operator->() const 
        {
            using namespace std::literals;
            if (!ptr_) 
            {
                throw std::logic_error("Scoped ptr is null"s);
            }
            return ptr_;
        }

        T& operator*() const 
        {
            using namespace std::literals;
            if (!ptr_) 
            {
                throw std::logic_error("Scoped ptr is null"s);
            }
            return *ptr_;
        }

    private:
        T* ptr_ = nullptr;
    };
}

