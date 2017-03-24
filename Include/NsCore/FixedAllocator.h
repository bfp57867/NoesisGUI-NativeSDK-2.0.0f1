////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FIXEDALLOCATOR_H__
#define __CORE_FIXEDALLOCATOR_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/NSTLMemoryAllocator.h>
#include <NsCore/Vector.h>
#include <EASTL/fixed_vector.h>


class Noesis_FixedAllocatorTest;


namespace Noesis
{
namespace Core
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A Fixed-Size allocator. Based on "Modern C++ Design" implementation by Andrei Alexandrescu
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API FixedAllocator
{
public:
    NS_DISABLE_COPY(FixedAllocator)

    FixedAllocator();
    ~FixedAllocator();

    /// Initialization
    void Initialize(MemoryAllocator* allocator, NsSize blockSize, NsSize pageSize);
    void Initialize(NsSize blockSize, NsSize pageSize);

    /// Allocates memory
    void* Allocate();

    /// Frees memory
    void Deallocate(void* p);

    /// Return the size in byes of each object
    NsSize GetBlockSize() const;

    /// Whenever a chunk is empty, FixedAllocator doesn't free it. It is mantained internally
    /// expecting new allocations in the future. Only one empty chunk is stored each time.
    /// This function free the empty chunk. Call the function to save a few bytes whenever you
    /// know, there won't be more allocations
    /// \return A boolean indicating if a trim was performed
    NsBool TrimEmptyChunk();

    /// This function optimize the memory usage of the internal containers. Basically is the
    /// swap trick for the internal vector of chunks
    /// \return A boolean indicating if the trim was performed
    NsBool TrimChunkList();

    /// Check for corruption
    /// \return A boolean indicating if the current state of the FixedAllocator is corrupted
    NsBool IsCorrupt() const;
    
    /// \return the kernel memory allocator being used by this FixedAllocator
    MemoryAllocator* GetMemoryAllocator() const;

private:
    friend class ::Noesis_FixedAllocatorTest;

    struct Chunk
    {
        void Init(NsSize blockSize, NsUInt8 blocks, MemoryAllocator* allocator);
        void* Allocate(NsSize blockSize);
        void Deallocate(void* p, NsSize blockSize);
        void Reset(NsSize blockSize, NsUInt8 blocks);
        void Release(MemoryAllocator* allocator);
        NsBool IsCorrupt(NsUInt8 numBlocks, NsSize blockSize, NsBool checkIndexes) const;
        NsBool IsBlockAvailable(void* p, NsUInt8 numBlocks, NsSize blockSize) const;
        NsBool HasBlock(void* p, NsSize chunkLength) const;
        NsBool HasAvailable(NsUInt8 numBlocks) const;
        NsBool IsFilled() const;

        NsUInt8* data;
        NsUInt8 nextFree;
        NsUInt8 freeBlocks;
    };

    const Chunk* HasBlock(void* p) const;
    void DoDeallocate(void* p);
    void MakeNewChunk();
    Chunk* VicinityFind(void* p) const;

private:
    typedef nstl::fixed_vector<Chunk, 4, true, nstl::MemoryAllocator> Chunks;
    
    static const NsUInt8 MinObjectsPerChunk = 8;
    static const NsUInt8 MaxObjectsPerChunk = 0xff;

    NsSize mBlockSize;
    NsUInt8 mNumBlocks;

    Chunks mChunks;
    Chunk* mAllocChunk;
    Chunk* mDeallocChunk;
    Chunk* mEmptyChunk;
    
    MemoryAllocator* mAllocator;
};

NS_WARNING_POP

}
}

#endif
