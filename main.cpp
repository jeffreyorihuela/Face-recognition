#include "Knnsequential.cpp"

#include <chrono>

int main() {
    KnnSequential knn("coordinates.txt");
    Record record_("coordinates.txt");
    vector<string> target = record_.readLine(30);

    auto begin = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    KnnSequential knn1("coordinates.txt", 100);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "1 FIND SIMILAR TO " << target[0] << endl;
    knn1.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn2("coordinates.txt", 200);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "2 FIND SIMILAR TO " << target[0] << endl;
    knn2.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn3("coordinates.txt", 400);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "3 FIND SIMILAR TO " << target[0] << endl;
    knn3.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn4("coordinates.txt", 800);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "4 FIND SIMILAR TO " << target[0] << endl;
    knn4.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn5("coordinates.txt", 1600);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "5 FIND SIMILAR TO " << target[0] << endl;
    knn5.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn6("coordinates.txt", 3200);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "6 FIND SIMILAR TO " << target[0] << endl;
    knn6.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    KnnSequential knn7("coordinates.txt", 6400);
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "7 FIND SIMILAR TO " << target[0] << endl;
    knn7.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    
    KnnSequential knn8("coordinates.txt");
    begin = std::chrono::high_resolution_clock::now();
    // do something
    cout << "8 FIND SIMILAR TO " << target[0] << endl;
    knn8.nearest(8, target);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}