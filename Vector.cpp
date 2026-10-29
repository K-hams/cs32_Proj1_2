// ============================================================================
// CS32 P01 Part 1: Vector implementation
//
// This is the ONLY file you edit and submit.
//
// Every function below is a stub that throws "not implemented". Replace each
// stub body with your implementation. See Vector.h for what each function
// must do.
//
// Note: this file is #included at the bottom of Vector.h rather than compiled
// on its own (templates must be visible wherever they are used). Do not add
// it to a g++ command line; `make` already does the right thing.
// You may add your own non-member helper functions here.
// ============================================================================

#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"
#include "Sequence.h"

// ---- Constructors and the Big 3 ----

// Default constructor. Creates an empty vector: size 0, capacity 0, no
// allocation.
template <typename T>
Vector<T>::Vector() {
    // TODO
    begin_ = nullptr;
    end_ = nullptr;
    end_cap_ = nullptr; 
}

// Creates a vector of n elements, each value-initialized (0 for int, "" for
// std::string). Size and capacity are both n. Note that new T[n] does NOT
// zero ints. If n is 0, allocates nothing.
//
// Hint: you don't need a special case for each type. Assigning T() works for
// every type: it gives 0 for int, 0.0 for double, nullptr for pointers, ""
// for std::string, and calls the default constructor for a class type.
template <typename T>
Vector<T>::Vector(std::size_t n) {
    // TODO
    if (n == 0){
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return;
    }

    begin_ = new T[n]; 

     for (std::size_t i = 0; i < n; i++) {
        begin_[i] = T();      
    }

    end_ = begin_ + n;
    end_cap_ = begin_ + n; 
    
}

// Creates a vector of n copies of value. Size and capacity are both n.
// If n is 0, allocates nothing.
template <typename T>
Vector<T>::Vector(std::size_t n, const T& value) {
    // TODO
     if (n == 0){
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return;
    }
    
    begin_ = new T[n]; 

     for (std::size_t i = 0; i < n; i++) {
        begin_[i] = value;      
    }

    end_ = begin_ + n;
    end_cap_ = begin_ + n; 
}

// Creates a vector holding the elements of il, in order: Vector<int> v{1, 2, 3}.
// Size and capacity are both il.size(). If il is empty, allocates nothing.
//
// Working with std::initializer_list<T>: when you write Vector<int> v{1, 2, 3},
// the compiler packs {1, 2, 3} into il. It is a read-only view of the values:
//   - il.size() is the number of values (3 here)
//   - you can loop over it:  for (const T& x : il) { ... }
//   - il.begin() and il.end() are pointers to const T, like your own begin()/end()
//   - it has NO operator[], so il[i] does not compile
// Reference: https://en.cppreference.com/w/cpp/utility/initializer_list
template <typename T>
Vector<T>::Vector(std::initializer_list<T> il) {
    // TODO
    //if il is empty
    if (il.size() == 0){
        begin_ = nullptr;
        end_ = nullptr;
        end_cap_ = nullptr; 
        return;
    }
    //il isn't a number its list can't do il[i] can do while loop
    begin_ = new T[il.size()]; 

    //elem based for loop
    int num = 0;
    for (const T& x : il){
        begin_[num] = x; 
        num++; 
    }

    end_ = begin_ + il.size();
    
    end_cap_ = begin_ + il.size();

}

// Copy constructor. Makes a deep copy of other. The new capacity is other.size() 
// (not other.capacity()).
// If other is empty, allocates nothing.
template <typename T>
Vector<T>::Vector(const Vector& other) {
    // TODO

    //if other is empty
    if (other.size() == 0){
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return;
    }


    begin_ = new T[other.size()];
    

    for (std::size_t i = 0; i < other.size(); i++){
        begin_[i] = other.begin_[i];
    }

    end_ = begin_ + other.size();
    
    end_cap_ = begin_ + other.size();
}

// Copy assignment operator. Replaces this vector's contents with a deep copy
// of other's elements and frees the old buffer. The new capacity is
// other.size() (if 0, no buffer). Self-assignment (v = v) must leave v
// unchanged. Returns *this so that a = b = c works.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    // TODO

    //if already equals
    if (this == &other) {
        return *this;
    }

    //have to free old mem
    delete[] begin_; 

     //if other is empty
    if (other.size() == 0){
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return *this;
    }

    

    begin_ = new T[other.size()];
    
    for (std::size_t i = 0; i < other.size(); i++){
        begin_[i] = other.begin_[i];
    }

    end_ = begin_ + other.size();
    end_cap_ = begin_ + other.size();

    return *this; 

}

// Destructor. 
template <typename T>
Vector<T>::~Vector() {
    // TODO
    delete[] begin_; 

}
// ---- Private helper ----

// Private helper: changes the capacity to exactly new_cap. Afterwards,
// capacity() == new_cap, size() and the elements are unchanged, and no memory
// is leaked. Any function that changes the capacity can be built on this one.
// Precondition: new_cap >= size(). If new_cap is 0, the vector ends up with no
// buffer at all.
template <typename T>
void Vector<T>::reallocate(std::size_t new_cap) {
    // TODO
    //Precondition:
    if (new_cap == 0 || new_cap < size()){
        delete[] begin_;
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return; 
    }
    //make new T to hold the vector and copy over the old stuff over and make 
    //T the size of new_cap? 

    std::size_t old_size = size();

    T* temp = new T[new_cap];

    for (std::size_t i = 0; i < size(); i++ ){
        temp[i] = begin_[i];
    }

    delete[] begin_;  // freeing 

    begin_ = temp; // new temp cap size

    end_ = begin_ + old_size; // increasing end to point to new end

    end_cap_ = begin_ + new_cap; //cap increasing 
}

// ---- Element access ----

// Returns a reference to element i. Do NOT check bounds: making sure
// i < size() is the caller's job, and an out-of-range i is undefined behavior
// (just like std::vector). at() is the version that checks.
template <typename T>
T& Vector<T>::operator[](std::size_t i) {
    return begin_[i];
}

// Same as above, for const vectors. operator== needs this: its parameters are
// const Vector&, so it can only read elements through a const member function.
template <typename T>
const T& Vector<T>::operator[](std::size_t i) const {
    // TODO
    return begin_[i];
    
}

// Returns a reference to element i.
// Throws std::out_of_range if i >= size().
template <typename T>
T& Vector<T>::at(std::size_t i) {
    // TODO
    if (i >= size()){
        throw std::out_of_range("out of range");
    }
    return begin_[i];
}

//new at addition
template <typename T>
const T& Vector<T>::at(std::size_t i) const {
    if (i >= size()) {
        throw std::out_of_range("Vector::at: index out of range");
    }
    return begin_[i];
}

// Returns a reference to the first element.
// Throws std::out_of_range if the vector is empty.

//deleting stuff
/*
template <typename T>
T& Vector<T>::front() {
    //vector empty
    if (empty()){
        throw std::out_of_range("out of range");
    }

    return begin_[0];
}

// Returns a reference to the last element.
// Throws std::out_of_range if the vector is empty.
template <typename T>
T& Vector<T>::back() {
    // TODO
    if (empty()){
        throw std::out_of_range("out of range");
    }

    return end_[-1];
}
*/
// Returns a pointer to the first element of the buffer, or nullptr if there
// is no buffer.
template <typename T>
T* Vector<T>::data() {
    // TODO
    return begin_;
}

// ---- Iterators ----

// Returns a pointer to the first element. Together with end(), this lets
// range-for loops and std::sort work on your Vector.
template <typename T>
T* Vector<T>::begin() {
    // TODO
    T* pointFirst = begin_;
    return pointFirst; 
}

// Same as above, for const vectors. Together with end() const, this lets a
// range-for loop run over a const Vector&.
template <typename T>
const T* Vector<T>::begin() const {
    // TODO
    T* pointFirst = begin_;
    return pointFirst; 
}

// Returns a pointer one past the last element (not past the end of the
// buffer). For an empty vector, end() == begin().
template <typename T>
T* Vector<T>::end() {
    // TODO
    return end_;
    
}

// Same as above, for const vectors.
template <typename T>
const T* Vector<T>::end() const {
    // TODO
    return end_;
}

// ---- Capacity ----

// Returns the number of elements currently stored.
template <typename T>
std::size_t Vector<T>::size() const {
    // TODO
    //have to find num of elements begin_ points to start 
    int size = end_ - begin_;
    return size; 
    
}

// Returns how many elements the buffer can hold before it must grow.
template <typename T>
std::size_t Vector<T>::capacity() const {
    // TODO
    //subtracting end_cap_ and begin to see difference between 
    std::size_t cap = end_cap_ - begin_;
    return cap; 
}

// Returns true if the vector has no elements (size() == 0).
/*
template <typename T>
bool Vector<T>::empty() const {
    // TODO
    if ((end_ - begin_) == 0){
        return true; 
    }

    return begin_ == end_;
}
    */

// Makes room for n elements up front, so that the vector can later grow to
// n elements without reallocating. Afterwards, capacity() is at least n (and
// exactly n if the buffer had to grow). The elements and size() are unchanged,
// and capacity never goes down.
template <typename T>
void Vector<T>::reserve(std::size_t n) {
    // Todo
    //extend capacity to be size n so end_cap_ goes till size n
    //already did this in reallocatin func?

    //preCondition: n > cap already
    if (n > capacity()){
        reallocate(n); 
    }
    
}

// Shrinks the buffer so capacity() == size(), keeping the elements.
// Does nothing if they are already equal. If size() is 0, frees the buffer
// and all three pointers become nullptr.
template <typename T>
void Vector<T>::shrink_to_fit() {
    // TODO
    //if cap == size already
    if (capacity() == size()){
        return; 
    }

    //if size = 0
    if (size() == 0){
        delete[] begin_;
        begin_ = nullptr; 
        end_ = nullptr;
        end_cap_ = nullptr;
        return; 
    }

    //shrinking
    reallocate(size());


}

// ---- Modifiers ----

// Appends a copy of value to the end. If the buffer is full, first grows it to
//     max(capacity() + 1, (size_t)(capacity() * growth_factor))
// Read growth_factor each time (the tests change it); do not hard-code 2.
// Careful: value may refer to an element of this vector (v.push_back(v[0])),
// which lives in the old buffer you are about to free.
template <typename T>
void Vector<T>::push_back(const T& value) {
    T holder = value; 

    //this is if the vector is full so we need to expand it
     if (size() == capacity()) {           // only when full
        std::size_t grown = static_cast<std::size_t>(capacity() * growth_factor);
        reallocate(std::max(capacity() + 1, grown));
    }

    *end_ = holder; 
     ++end_;      

}

// Removes the last element. Capacity is unchanged and nothing is freed.
// Throws std::out_of_range if the vector is empty.
/*
template <typename T>
void Vector<T>::pop_back() {
    // TODO
    if (empty()){
        throw std::out_of_range("vector is empty"); 
    }

    end_ = end_ - 1; 
}
    */

// Removes all elements: size becomes 0. Capacity is unchanged and nothing is
// freed.
template <typename T>
void Vector<T>::clear() {
    // TODO 

    //nothing freed so no delete[]
    end_ = begin_; 


}

// Changes the size to n.
//   - n < size(): removes elements from the end. Capacity is unchanged.
//   - n > size(): appends T() elements (0 for int). If n > capacity(), first
//     grows the buffer to exactly n. Slots reused from earlier elements must be
//     overwritten with T(), not left holding old values.
template <typename T>
void Vector<T>::resize(std::size_t n) {
    // TODO
    
    //just moving
    if (n < size()) {
        end_ = begin_ + n;              
    } 
    
    // checkin if n is less than size
    else if (n > size()) {

        //also less than capacity 
        if (n > capacity()) {
            reallocate(n);                   
        }

        //going thru the vector and flling the empty spots
        for (std::size_t i = size(); i < n; i++) {
            begin_[i] = T();                  
        }

        //moving end pointer
        end_ = begin_ + n;               
    }

    
}

// Inserts a copy of value at position index, so that afterwards v[index] is
// the new value. The elements that were at index and after each move one
// position right. index == size() appends. If the buffer
// is full, first grows it with the same formula as push_back.
// Throws std::out_of_range if index > size() (and changes nothing).
// Like push_back, value may refer to an element of this vector.
template <typename T>
void Vector<T>::insert(std::size_t index, const T& value) {
    // TODO

    //have to do this cuz value is a reference 
    T copy = value;


    if (index > size()){
        throw std::out_of_range("out of range"); 
    }
    //if buffer is full, grow with same formula as push_back
    if (size() == capacity()) {           // only when full
        std::size_t grown = static_cast<std::size_t>(capacity() * growth_factor);
        reallocate(std::max(capacity() + 1, grown));
    }

   

    for (std::size_t i = size(); i > index; i--) {
        begin_[i] = begin_[i - 1];
    }

    begin_[index] = copy;          
    ++end_;
}

// Removes the element at index, shifting the elements after it one position
// left. Capacity is unchanged.
// Throws std::out_of_range if index >= size() (and changes nothing).
template <typename T>
void Vector<T>::erase(std::size_t index) {
    // TODO
    if (index >=size()){
        throw std::out_of_range("out of range");
    }

    //moving all the elements left
    for (std::size_t i = index; i + 1 < size(); i++) {
        begin_[i] = begin_[i + 1];     
    }

    //removing without doing delete[]
    --end_;


}

// ---- Non-member operators ----

// Returns true if a and b have the same size and every pair of elements
// compares equal with ==. Capacity does not matter.
/*
template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    // TODO
    //capacity() does not matter

    //size
    if (a.size() != b.size()) {
        return false;
    }


    for (std::size_t i = 0; i < a.size(); i++) {
        if (!(a[i] == b[i])) {
            return false;
        }
    }

    return true;
}

// Returns true if a and b are not equal (hint: use operator==).
template <typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) {
    // TODO
    if (!(a == b)){
        return true;
    }
    return false;
}
*/

#endif
