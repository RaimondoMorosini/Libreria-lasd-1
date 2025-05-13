
#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "mappable.hpp"
namespace lasd
{

    template <typename Data>
    class LinearContainer : virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data>
    {
    protected:
        using Container::size;

    public:
        virtual ~LinearContainer() = default; // Destructor

        LinearContainer &operator=(const LinearContainer &) = delete;     // Copy assignment
        LinearContainer &operator=(LinearContainer &&) noexcept = delete; // Move assignment

        // Comparison operators
        inline bool operator==(const LinearContainer &) const noexcept;
        inline bool operator!=(const LinearContainer &) const noexcept;

        // functions required by the class diagram
        virtual const Data &operator[](ulong) const = 0; // deve lanciare std::out_of_range
        inline virtual const Data &Front() const; // deve lanciare std::length_error
        inline virtual const Data &Back() const; // deve lanciare std::length_error

        /* ************************************************************************ */
        // Specific member function (inherited from TraversableContainer)

        using typename TraversableContainer<Data>::TraverseFun;

        inline void Traverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderTraversableContainer)

        inline void PreOrderTraverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderTraversableContainer)

        inline void PostOrderTraverse(TraverseFun) const override;

 
    };

    /* ************************************************************************** */
    template <typename Data>
    class MutableLinearContainer : virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
    {
    protected:
        using Container::size;
    public:
        virtual ~MutableLinearContainer() = default; // Destructor

        MutableLinearContainer &operator=(const MutableLinearContainer &) = delete;     // Copy assignment
        MutableLinearContainer &operator=(MutableLinearContainer &&) noexcept = delete; // Move assignment

        // Comparison operators
        inline bool operator==(const MutableLinearContainer &) const noexcept;
        inline bool operator!=(const MutableLinearContainer &) const noexcept;

        // functions required by the class diagram

        virtual Data &operator[](ulong) = 0; // deve lanciare std::out_of_range
        inline virtual Data &Front();// deve lanciare std::length_error
        inline virtual Data &Back();// deve lanciare std::length_error


               /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFun;

        inline void Map(MapFun) override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderMappableContainer)

        inline void PreOrderMap(MapFun) override;

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderMappableContainer)

        inline void PostOrderMap(MapFun) override;
    };

    /* ************************************************************************** */

    template <typename Data>
    class SortableLinearContainer : virtual public MutableLinearContainer<Data>
    {
    protected:
        using Container::size;
    public:
        virtual ~SortableLinearContainer() = default; // Destructor

        SortableLinearContainer &operator=(const SortableLinearContainer &) = delete;     // Copy assignment
        SortableLinearContainer &operator=(SortableLinearContainer &&) noexcept = delete; // Move assignment

        // Comparison operators
        inline bool operator==(const SortableLinearContainer &) const noexcept;
        inline bool operator!=(const SortableLinearContainer &) const noexcept;

        // functions required by the class diagram

        virtual void Sort() noexcept;

    protected:
        // Auxiliary member functions

        void QuickSort(ulong p, ulong r) noexcept;
        ulong Partition(ulong p, ulong r) noexcept;
    };

    /* ************************************************************************** */

}

#include "linear.cpp"

#endif
