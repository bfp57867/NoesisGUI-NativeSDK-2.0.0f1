////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <type_traits>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret, class ...Args>
class Delegate<Ret (Args...)>
{
public:
    Delegate()
    {
        Init();
    }

    /// Constructor from free function
    Delegate(Ret (*f)(Args...))
    {
        FromFreeFunc(f);
    }

    /// Constructor from functor (lambdas)
    template<class F, class = typename std::enable_if<std::is_class<F>::value>::type>
    Delegate(const F& f)
    {
        FromFunctor(f, &F::operator());
    }

    /// Constructor from member function and object
    template<class C> Delegate(C* obj, Ret (C::*f)(Args...))
    {
        FromMemberFunc(obj, f);
    }

    /// Constructor from member function and object
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*f)(Args...))
    {
        FromMemberFunc(obj.GetPtr(), f);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*f)(Args...) const)
    {
        FromMemberFunc(obj.GetPtr(), f);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const C* obj, Ret (C::*f)(Args...) const)
    {
        FromMemberFunc(obj, f);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const Ptr<const C>& obj, Ret (C::*f)(Args...) const)
    {
        FromMemberFunc(obj.GetPtr(), f);
    }

    /// Copy constructor
    Delegate(const Delegate& d)
    {
        Copy(d);
    }

    /// Destructor
    ~Delegate()
    {
        Destroy();
    }

    /// Copy operator
    Delegate& operator=(const Delegate& d)
    {
        if (this != &d)
        {
            Destroy();
            Copy(d);
        }

        return *this;
    }

    /// Reset
    void Reset()
    {
        Destroy();
        Init();
    }

    /// Check if delegate is null
    NsBool Empty() const
    {
        return GetImpl()->Empty();
    }

    /// Boolean conversion
    operator NsBool() const
    {
        return !Empty();
    }

    /// Equality
    NsBool operator==(const Delegate& d) const
    {
        return GetImpl()->Equal(d.GetImpl());
    }

    /// Non-equality
    NsBool operator!=(const Delegate& d) const
    {
        return !(*this == d);
    }

    /// Add delegate
    void Add(const Delegate& d)
    {
        GetImpl()->Add(d);
    }

    /// Add delegate
    void operator+=(const Delegate& d)
    {
        Add(d);
    }

    /// Remove delegate
    void Remove(const Delegate& d)
    {
        GetImpl()->Remove(d);
    }

    /// Remove delegate
    void operator-=(const Delegate& d)
    {
        Remove(d);
    }

    /// Numbers of contained delegates
    NsSize Size() const
    {
        return GetImpl()->Size();
    }

    /// Delegate invocation. In multidelegates the returned value corresponds to the last invocation
    Ret Invoke(Args... args) const
    {
        return GetImpl()->Invoke(args...);
    }

    /// Delegate invocation
    Ret operator()(Args... args) const
    {
        return Invoke(args...);
    }

    /// Manual invocation of the ith delegate
    Ret Invoke(NsSize i, Args... args) const
    {
        return GetImpl()->Invoke(i, args...);
    }

private:
    void FromFreeFunc(Ret (*f)(Args...))
    {
        typedef Ret (*F)(Args...);
        static_assert(sizeof(FreeFuncStub<F>) <= sizeof(data), "Insufficient buffer size");
        new(data) FreeFuncStub<F>(f);
    }

    template<class F>
    void FromFunctor(const F& f, Ret(F::*)(Args...))
    {
        static_assert(sizeof(FunctorStub<F>) <= sizeof(data), "Insufficient buffer size");
        new(data) FunctorStub<F>(f);
    }

    template<class F>
    void FromFunctor(const F& f, Ret(F::*)(Args...) const)
    {
        static_assert(sizeof(FunctorStub<F>) <= sizeof(data), "Insufficient buffer size");
        new(data) FunctorStub<F>(f);
    }

    template<class C>
    void FromMemberFunc(C* obj, Ret (C::*f)(Args...))
    {
        typedef Ret (C::*F)(Args...);
        static_assert(sizeof(MemberFuncStub<C, F>) <= sizeof(data), "Insufficient buffer size");
        new(data) MemberFuncStub<C, F>(obj, f);
    }

    template<class C>
    void FromMemberFunc(const C* obj, Ret (C::*f)(Args...) const)
    {
        typedef Ret (C::*F)(Args...) const;
        static_assert(sizeof(MemberFuncStub<C, F>) <= sizeof(data), "Insufficient buffer size");
        new(data) MemberFuncStub<C, F>(const_cast<C*>(obj), f);
    }

    void Init()
    {
        static_assert(sizeof(NullStub) <= sizeof(data), "Insufficient buffer size");
        new(data) NullStub();
    }

    class Impl;

    Impl* GetImpl()
    {
        return reinterpret_cast<Impl*>(data);
    }

    const Impl* GetImpl() const
    {
        return reinterpret_cast<const Impl*>(data);
    }

    void Destroy()
    {
        GetImpl()->Destroy();
    }

    void Copy(const Delegate& d)
    {
        d.GetImpl()->Copy(GetImpl());
    }

    typedef Int2Type<0> _0;

    Delegate(const Impl* impl, _0)
    {
        impl->Copy(GetImpl());
    }

    enum Type
    {
        Type_Null,
        Type_FreeFunc,
        Type_Functor,
        Type_MemberFunc,
        Type_MultiDelegate
    };

    class Impl
    {
    public:
        virtual ~Impl() {};
        virtual Type GetType() const = 0;
        virtual NsBool Empty() const = 0;
        virtual NsSize Size() const = 0;
        virtual NsBool Equal(const Impl* impl) const = 0;
        virtual Ret Invoke(Args... args) const = 0;
        virtual Ret Invoke(NsSize i, Args... args) const = 0;
        virtual void Copy(Impl* dest) const = 0;
        virtual void Add(const Delegate& d) = 0;
        virtual void Remove(const Delegate& d) = 0;

        void Destroy()
        {
            this->~Impl();
        }
    };

    /// Implementation for null delegates
    class NullStub: public Impl
    {
    public:
        Type GetType() const
        {
            return Type_Null;
        }

        NsBool Empty() const
        {
            return true;
        }

        NsSize Size() const
        {
            return 0;
        }

        NsBool Equal(const Impl* impl) const
        {
            return GetType() == impl->GetType();
        }

        Ret Invoke(Args...) const
        {
            return Ret();
        }

        Ret Invoke(NsSize, Args...) const
        {
            return Ret();
        }

        void Copy(Impl* dest) const
        {
            new(dest) NullStub(*this);
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                this->Destroy();
                d.GetImpl()->Copy(this);
            }
        }

        void Remove(const Delegate& d)
        {
            NS_ASSERT(d.Empty());
        }
    };

    /// Base class implementation for single delegates
    class SingleDelegate: public Impl
    {
    protected:
        NsBool Empty() const
        {
            return false;
        }

        NsSize Size() const
        {
            return 1;
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                NS_ASSERT(!this->Equal(d.GetImpl()));

                Delegate self(this, _0());

                this->Destroy();

                MultiDelegate* multiDelegate = new(this) MultiDelegate();
                multiDelegate->Add(self);
                multiDelegate->Add(d);
            }
        }

        void Remove(const Delegate& d)
        {
            if (!d.Empty())
            {
                NS_ASSERT(this->Equal(d.GetImpl()));
                this->Destroy();
                new(this) NullStub();
            }
        }
    };

    /// Implementation for free functions
    template<class Func> class FreeFuncStub: public SingleDelegate
    {
    public:
        FreeFuncStub(Func f): mFunc(f) {}

        Type GetType() const
        {
            return Type_FreeFunc;
        }

        NsBool Equal(const Impl* impl) const
        {
            const FreeFuncStub* funcStub = static_cast<const FreeFuncStub*>(impl);
            return GetType() == impl->GetType() && mFunc == funcStub->mFunc;
        }

        Ret Invoke(Args... args) const
        {
            return mFunc(args...);
        }

        Ret Invoke(NsSize i, Args... args) const
        {
            NS_ASSERT(i == 0);
            return mFunc(args...);
        }

        void Copy(Impl* dest) const
        {
            new(dest) FreeFuncStub(*this);
        }

    private:
        Func mFunc;
    };

    /// Implementation for functors
    template<class F> class FunctorStub: public SingleDelegate
    {
    public:
        FunctorStub(const F& f): mFunctor(f) {}

        Type GetType() const
        {
            return Type_Functor;
        }

        NsBool Equal(const Impl*) const
        {
            return false;
        }

        Ret Invoke(Args... args) const
        {
            return const_cast<F*>(&mFunctor)->operator()(args...);
        }

        Ret Invoke(NsSize i, Args... args) const
        {
            NS_ASSERT(i == 0);
            return const_cast<F*>(&mFunctor)->operator()(args...);
        }

        void Copy(Impl* dest) const
        {
            new(dest) FunctorStub(*this);
        }

    private:
        F mFunctor;
    };

    /// Implementation for member functions
    template<class C, class Func> class MemberFuncStub: public SingleDelegate
    {
    public:
        MemberFuncStub(C* obj, Func f): mObj(obj), mFunc(f) {}

        Type GetType() const
        {
            return Type_MemberFunc;
        }

        NsBool Equal(const Impl* impl) const
        {
            const MemberFuncStub* memberStub = static_cast<const MemberFuncStub*>(impl);
            return GetType() == impl->GetType() && mObj == memberStub->mObj &&
                mFunc == memberStub->mFunc;
        }

        Ret Invoke(Args... args) const
        {
            return (mObj->*mFunc)(args...);
        }

        Ret Invoke(NsSize i, Args... args) const
        {
            NS_ASSERT(i == 0);
            return (mObj->*mFunc)(args...);
        }

        void Copy(Impl* dest) const
        {
            new(dest) MemberFuncStub(*this);
        }

    protected:
        C* mObj;
        Func mFunc;
    };

    /// Implementation for MultiDelegates
    class MultiDelegate: public Impl
    {
    public:
        MultiDelegate(): mVector(*new DelegateVector()) {}
        MultiDelegate(const MultiDelegate& d): mVector(*new DelegateVector(*d.mVector.GetPtr())) {}

        Type GetType() const
        {
            return Type_MultiDelegate;
        }

        NsBool Empty() const
        {
            return mVector->v.empty();
        }

        NsSize Size() const
        {
            return mVector->v.size();
        }

        typedef eastl::fixed_vector<Delegate, 2> Delegates;

        NsBool Equal(const Impl* impl) const
        {
            if (GetType() == impl->GetType())
            {
                const MultiDelegate* multiDelegate = static_cast<const MultiDelegate*>(impl);
                return mVector->v == multiDelegate->mVector->v;
            }

            return false;
        }

        class DelegateVector: public BaseComponent
        {
        public:
            DelegateVector(): nestingCount(0), compactPending(0) {}
            DelegateVector(const DelegateVector& o): nestingCount(0), compactPending(0), v(o.v) {}

            struct IsNull
            {
                inline NsBool operator()(const Delegate& d) const
                {
                    return d.Empty();
                }
            };

            // Remove null delegates
            void Compact()
            {
                NS_ASSERT(compactPending == 1);
                NS_ASSERT(nestingCount == 0);
                v.erase(nstl::remove_if(v.begin(), v.end(), IsNull()), v.end());
                compactPending = 0;
            }

            NsUInt16 nestingCount;
            NsUInt16 compactPending;
            Delegates v;
        };

        struct InvokerGuard
        {
            InvokerGuard(const Ptr<DelegateVector>& v): _v(v)
            {
                _v->nestingCount++;
            }

            ~InvokerGuard()
            {
                if (--_v->nestingCount == 0 && _v->compactPending == 1)
                {
                    _v->Compact();
                }
            }

            Ptr<DelegateVector> _v;
        };

        Ret Invoke(Args... args) const
        {
            // Hold reference to the vector to avoid it being destructed in the iteration loop
            InvokerGuard guard(mVector);

            const Delegates& v = mVector->v;

            if (v.empty())
            {
                return Ret();
            }
            else
            {
                NsSize numDelegates = v.size();
                for (NsSize i = 0; i < numDelegates - 1; ++i)
                {
                    (v[i])(args...);
                }

                // last delegate is used to return a value
                return (v[numDelegates - 1])(args...);
            }
        }

        Ret Invoke(NsSize i, Args... args) const
        {
            NS_ASSERT(i < mVector->v.size());
            return mVector->v[i](args...);
        }

        void Copy(Impl* dest) const
        {
            new(dest) MultiDelegate(*this);
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                Delegates& v = mVector->v;
                NS_ASSERT(nstl::find(v.begin(), v.end(), d) == v.end());
                v.push_back(d);
            }
        }

        void Remove(const Delegate& d)
        {
            if (!d.Empty())
            {
                Delegates& v = mVector->v;
                typename Delegates::iterator it = nstl::find(v.begin(), v.end(), d);
                NS_ASSERT(it != v.end());
                it->Reset();
                mVector->compactPending = 1;
            }
        }

    private:
        Ptr<DelegateVector> mVector;

    private:
        MultiDelegate& operator=(const MultiDelegate&);
    };

private:
    class Dummy0 {};
    class Dummy1 {};
    class SingleInheritance: public Dummy0 {};
    class MultipleInheritance: public Dummy0, public Dummy1 {};

    // http://www.gotw.ca/gotw/028.htm
    union MaxAlign 
    {
        Ret (*_1)(Args...);
        struct { void* obj; Ret (SingleInheritance::*f)(Args...); } _2;
        struct { void* obj; Ret (MultipleInheritance::*f)(Args...); } _3;
    };

    union
    {
        MaxAlign maxAlign;
        NsByte data[4 * sizeof(void*)];
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper functions to deduce automatically the type when creating a delegate
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class Ret , class ...Args>
Delegate<Ret (Args...)> MakeDelegate(C* obj, Ret (C::*f)(Args...))
{
    return Delegate<Ret (Args...)>(obj, f);
}

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*f)(Args...))
{
    return Delegate<Ret (Args...)>(obj, f);
}

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const C* obj, Ret (C::*f)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, f);
}

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<C>& obj, Ret (C::*f)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, f);
}

template<class C, class Ret, class ...Args>
Delegate<Ret (Args...)> MakeDelegate(const Ptr<const C>& obj, Ret (C::*f)(Args...) const)
{
    return Delegate<Ret (Args...)>(obj, f);
}

}
}
