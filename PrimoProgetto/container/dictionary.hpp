
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "traversable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    class DictionaryContainer : virtual public TestableContainer<Data>
    {
    public:
        virtual ~DictionaryContainer() = default; // Destructor

        DictionaryContainer &operator=(const DictionaryContainer &) = delete;     // Copy assignment
        DictionaryContainer &operator=(DictionaryContainer &&) noexcept = delete; // Move assignment

        // Comparison operators
        bool operator==(const DictionaryContainer &) const noexcept = delete;
        bool operator!=(const DictionaryContainer &) const noexcept = delete;

        /* ************************************************************************ */

        // functions required by the class diagram

        // Ho due insert perchè gestisco la copia e la move
        virtual bool Insert(const Data &) = 0;
        virtual bool Insert(Data &&) = 0;
        virtual bool Remove(const Data &) = 0;

        inline virtual bool InsertAll(const TraversableContainer<Data> &);
        inline virtual bool InsertAll(MappableContainer<Data> &&);
        inline virtual bool RemoveAll(const TraversableContainer<Data> &);

        inline virtual bool InsertSome(const TraversableContainer<Data> &);
        inline virtual bool InsertSome(MappableContainer<Data> &&);
        inline virtual bool RemoveSome(const TraversableContainer<Data> &);
    };

    template <typename Data>
    class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>
    {
    public:
        // Destructor
        ~OrderedDictionaryContainer() = default;                                                // Destructor
        OrderedDictionaryContainer &operator=(const OrderedDictionaryContainer &) = delete;     // Copy assignment
        OrderedDictionaryContainer &operator=(OrderedDictionaryContainer &&) noexcept = delete; // Move assignment

        // Comparison operators
        bool operator==(const OrderedDictionaryContainer &) const noexcept = delete;
        bool operator!=(const OrderedDictionaryContainer &) const noexcept = delete;

        // Specific member functions
        virtual const Data &Min() const  = 0;;                     // (concrete function must throw std::length_error when empty)
        virtual const Data &Max() const = 0;;                     // (concrete function must throw std::length_error when empty)
        virtual const Data &Predecessor(const Data &) const= 0;; // (concrete function must throw std::length_error when not found)
        virtual const Data &Successor(const Data &) const= 0;;   // (concrete function must throw std::length_error when not found)

        virtual Data MinNRemove(); // (concrete function must throw std::length_error when empty)
        virtual void RemoveMin();  // (concrete function must throw std::length_error when empty)

        virtual Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
        virtual void RemoveMax();  // (concrete function must throw std::length_error when empty)

        virtual Data PredecessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
        virtual void RemovePredecessor(const Data &);  // (concrete function must throw std::length_error when not found)

        virtual Data SuccessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
        virtual void RemoveSuccessor(const Data &);  // (concrete function must throw std::length_error when not found)
    };

} // Close namespace lasd

#include "dictionary.tpp"

#endif
