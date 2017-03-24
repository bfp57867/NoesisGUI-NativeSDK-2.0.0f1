////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #629]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_PTR_H__
#define __CORE_PTR_H__


#include <cstddef>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Automatically handles lifetime of BaseRefCounted objects by doing AddReference() and Release().
/// BaseRefCounted objects start with reference counter set to 1. When they are stored inside a
/// Ptr<> the counter is increased by 1 again. To avoid having to do a manual Release(), Ptr<>
/// supports being constructed from a reference. In this case the reference counter is not
/// incremented.
///
///     Ptr<Cube> cube = *new Cube();
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Ptr
{
public:
    typedef T Type;

    /// Constructs a null smart pointer
    inline Ptr();
    inline Ptr(std::nullptr_t);

    /// Constructor from pointer. Reference counter is incremented
    inline explicit Ptr(T* ptr);

    /// Constructor from reference. Reference counter is not incremented
    /// Very useful for assigning from new operator: Ptr<Cube> cube = *new Cube();
    inline Ptr(T& ptr);

    /// Copy constructors
    inline Ptr(const Ptr& ptr);
    template<class S> inline Ptr(const Ptr<S>& ptr);

    /// Move constructors
    inline Ptr(Ptr&& ptr);
    template<class S> inline Ptr(Ptr<S>&& ptr);

    /// Destructor
    inline ~Ptr();

    /// Copy operators
    inline Ptr& operator=(const Ptr& ptr);
    template<class S> inline Ptr& operator=(const Ptr<S>& ptr);

    /// Move operators
    inline Ptr& operator=(Ptr&& ptr);
    template<class S> inline Ptr& operator=(Ptr<S>&& ptr);

    /// Copy from reference. Reference counter is not incremented
    /// Very useful for assinging from new operator: cube = *new Cube();
    inline Ptr& operator=(T& ptr);

    /// Resets to null pointer
    inline void Reset();

    /// Resets to pointer. Reference counter is incremented
    inline void Reset(T* ptr);

    /// Clears the stored pointer without decrementing the reference counter
    inline T* GiveOwnership();

    /// Dereferences the stored pointer
    inline T* operator->() const;

    /// Returns the stored pointer 
    inline T* GetPtr() const;

    /// True if holds a valid (non null) pointer
    inline operator bool() const;

    /// Comparison operators
    //@{
    template<class S> inline bool operator==(const Ptr<S>& ptr) const;
    template<class S> inline bool operator!=(const Ptr<S>& ptr) const;
    template<class S> inline bool operator<(const Ptr<S>& ptr) const;

    template<class S> inline bool operator==(S* ptr) const;
    template<class S> inline bool operator!=(S* ptr) const;
    template<class S> inline bool operator<(S* ptr) const;
    //@}

private:
    T* mPtr;
};

}

/// Ptr is used frequently, so we don't want to write Core::Ptr every time
using Core::Ptr;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hash function
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{

template<class T> struct hash;
template<class T> struct hash<Noesis::Core::Ptr<T>>
{
    size_t operator()(const Noesis::Core::Ptr<T>& s) const
    {
        return size_t(NsUIntPtr(s.GetPtr()));
    }
};

}


#include <NsCore/Ptr.inl>


#endif
