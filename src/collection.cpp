//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/collection.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/collection.h>

#include <vector>
//-----------------------------LOGGER_COLLECTION------------------------------//
namespace logging {

template<typename T>
using vec_iter = typename std::vector<T>::iterator;

//operator[]
template<typename T>
inline T* collection<T>::operator[](size_t n){
    return logger_vector[n];
}
template<typename T>
inline const T* collection<T>::operator[](size_t n) const {
    return logger_vector[n];
}

//at()
template<typename T>
inline T* collection<T>::at(size_t n){
    return logger_vector.at(n);
}
template<typename T>
inline const T* collection<T>::at(size_t n) const {
    return logger_vector.at(n);
}

//begin()
template<typename T>
inline vec_iter<T*> collection<T>::begin(){
    return logger_vector.begin();
}
template<typename T>
inline const vec_iter<T*> collection<T>::begin() const {
    return logger_vector.begin();
}

//end()
template<typename T>
inline vec_iter<T*> collection<T>::end(){
    return logger_vector.end();
}
template<typename T>
inline const vec_iter<T*> collection<T>::end() const {
    return logger_vector.end();
}

} //logging