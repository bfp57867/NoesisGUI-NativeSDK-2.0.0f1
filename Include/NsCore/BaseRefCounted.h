////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #696]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASEREFCOUNTED_H__
#define __CORE_BASEREFCOUNTED_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseObject.h>
#include <NsCore/Atomic.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for types that control its lifetime with a reference counter. Instances of this class 
/// are usually stored inside a Ptr smart pointer. See Ptr class for more information.
///
/// The reference counter is initialized to 1. This means that the initial creation of the instance
/// counts as a reference. 
///
/// The management of the references is transparent if you use the kernel factory + Ptr, but if you
/// use a BaseRefCounted outside a Ptr, you need to manually release the pointer with Release().
/// Do not delete BaseRefCounted object with the operator delete because additional references 
/// to the instance may still be alive.
///
/// Example:
///
///     Mesh* mesh = new StaticMesh();
///     // ...
///     mesh->Release();
///     // delete mesh;     // Don't do this!
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BaseRefCounted: public BaseObject
{
public:
    NS_DISABLE_COPY(BaseRefCounted)

    inline BaseRefCounted();
    inline virtual ~BaseRefCounted() = 0;

    /// Increments reference count and returns the new value
    inline NsInt32 AddReference() const;

    /// Decrements reference count and returns the new value
    /// When the reference count on an object reaches zero, it is deleted
    inline NsInt32 Release() const;

    /// Gets current reference count for the object
    inline NsInt32 GetNumReferences() const;

protected:
    /// Invoked when the reference counter reaches 0. By default the instance is deleted
    /// Can be reimplemented by child classes to avoid the default destruction
    /// Return the reference counter (0 if the object was destroyed)
    inline virtual NsInt32 OnDestroy() const;

    /// Increments reference count. Can be reimplemented by child classes
    inline virtual NsInt32 InternalAddReference() const;

    /// Decrements reference count. Can be reimplemented by child classes
    inline virtual NsInt32 InternalRelease() const;

private:
    mutable Atomic<NsInt32> mRefCount;

    NS_DECLARE_REFLECTION(BaseRefCounted, BaseObject)
};

NS_WARNING_POP

}
}

/// Inline include
#include <NsCore/BaseRefCounted.inl>


#endif
