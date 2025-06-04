#include <utility> // per std::move

// Test costruttore per copia
template <template <typename> class C, typename T, typename Traversable, typename TestFunc>
void TestConstructionCopy(const Traversable& source, TestFunc testFn) {
    C<T> container(source);
    testFn(container);
}

// Test costruttore per move
template <template <typename> class C, typename T, typename Mappable, typename TestFunc>
void TestConstructionMove(Mappable&& source, TestFunc testFn) {
    C<T> container(std::move(source));
    testFn(container);
}


// ===== Funzione unica che testa entrambi i costruttori =====
template <template <typename> class C, typename T>
void RunConstructorTestsForContainer()
{
    // Creo un Vector<T> di esempio
    Vector<T> vec;
    vec.Resize(3);
    vec[0] = MakeValue<T>(1);
    vec[1] = MakeValue<T>(2);
    vec[2] = MakeValue<T>(3);

    // Lambda con test comuni su un container costruito
    auto baseTests = [](const C<T>& container) {
        ASSERT_EQ(container.Size(), 3);
        ASSERT_TRUE(container.Exists(MakeValue<T>(1)));
        ASSERT_TRUE(container.Exists(MakeValue<T>(2)));
        ASSERT_TRUE(container.Exists(MakeValue<T>(3)));


    };

    // Test costruttore COPY
    TestConstructionCopy<C, T>(vec, baseTests);

    // Ricreo vec per la move 
    Vector<T> vecMove;
    vecMove.Resize(3);
    vecMove[0] = MakeValue<T>(1);
    vecMove[1] = MakeValue<T>(2);
    vecMove[2] = MakeValue<T>(3);

    // Test costruttore MOVE
    TestConstructionMove<C, T>(std::move(vecMove), baseTests);
    
}
