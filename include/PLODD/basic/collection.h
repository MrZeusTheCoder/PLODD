//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  Collections! An std::vector for loggers! What a newfound principal!
//  (sarcasm kills us on the inside, yet humans find this masochistically...
//  funny?)
// 
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_COLLECTION_H_
#define PLODD_COLLECTION_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <type_traits>
#include <vector>
//-----------------------------LOGGER_COLLECTION------------------------------//
namespace pld {

//So basically because for this to be fully extendable and useable regardless
//of wether a specialization for a logger is defined or not then all the
//functions for the general specialization must be defined in the class (inline?)
//That is why we have this... ick.
//That is also why I made the names of things short/abbreviated. Sorry
//if it is hard to read, but I have included the full length versions as comments

template<typename T = base_logger>
class collection : public base_logger {
    //Type away, whatever your name is!
    typedef T* T_ptr;
    typedef const T* const_T_ptr;
    typedef T& T_ref;
    typedef const T& const_T_ref;
    typedef typename std::vector<T *>::iterator vec_iter;
    typedef const typename std::vector<T *>::iterator const_vec_iter;

    private:
        std::vector<T_ptr> l_vec; //l_vec stands for Logger VECtor.

    public:
        collection() : base_logger("PLODD_C", logging_level::ERROR){
            static_assert(std::is_base_of<base_logger, T>::value, "T value must inherit from base class logging::base_logger.");
            l_vec.clear();
        }

        collection(std::initializer_list<T_ptr> loggers) : base_logger("PLODD_C", logging_level::ERROR){
            static_assert(std::is_base_of<base_logger, T>::value, "T value must inherit from base class logging::base_logger.");
            l_vec = loggers;
        }

        collection(std::vector<T_ptr> logger_vector) : base_logger("PLODD_C", logging_level::ERROR){
            static_assert(std::is_base_of<base_logger, T>::value, "T value must inherit from base class logging::base_logger.");
            l_vec = logger_vector;
        }

        void debug(std::string msg){ for(T* x : l_vec){ x->debug(msg); } };
        void info(std::string msg){ for(T* x : l_vec){ x->info(msg); } };
        void warn(std::string msg){ for(T* x : l_vec){ x->warn(msg); } };
        void error(std::string msg){ for(T* x : l_vec){ x->error(msg); } };

        std::vector<T_ptr>* get_internal_vec(){ return &l_vec; }

        operator collection<base_logger>(){
            std::vector<base_logger *> base_lgr_vec;
            for(auto x : l_vec){
                base_lgr_vec.push_back(static_cast<base_logger *>(x));
            }
            return collection<base_logger>(base_lgr_vec); 
        }
        //Vector-like, fancy. Ignore the rest if you are just looking for logging stuff.
        //Acessors:
        T_ref           operator[](size_t pos){ return l_vec[pos]; }
        const_T_ref     operator[](size_t pos) const { return l_vec[pos]; }

        T_ref           at(size_t pos){ return l_vec.at(pos); }
        const_T_ref     at(size_t pos) const { return l_vec.at(pos); }

        T_ref           front(){ return l_vec.front(); }
        const_T_ref     front() const { return l_vec.front(); }

        T_ref           back(){ return l_vec.back(); }
        const_T_ref     back() const { return l_vec.back(); }

        T_ref           data() noexcept { return l_vec.data(); }
        const_T_ref     data() const noexcept { return l_vec.data(); }
        
        //Iterators: (ugh, the overloads)
        vec_iter        begin() noexcept { return l_vec.begin(); }
        const_vec_iter  begin() const noexcept { return l_vec.begin(); }
        vec_iter        rbegin() noexcept { return l_vec.rbegin(); }
        const_vec_iter  cbegin() const noexcept { return l_vec.cbegin(); }
        const_vec_iter  crbegin() const noexcept { return l_vec.crbegin(); }

        vec_iter        end() noexcept { return l_vec.end(); }
        const_vec_iter  end() const noexcept { return l_vec.end(); }
        const_vec_iter  cend() const noexcept { return l_vec.cend(); }

        //Capacity:
        size_t          capacity() const noexcept { return l_vec.capacity(); }
        bool            empty() const noexcept { return l_vec.empty(); }
        size_t          max_size() const noexcept { return l_vec.max_size(); }
        void            reserve(size_t new_cap){ l_vec.reserve(new_cap); }
        size_t          size() noexcept { return l_vec.size(); }
        void            shrink_to_fit(){ l_vec.shrink_to_fit(); }

        //Modifiers:
        void            clear() noexcept { return l_vec.clear(); }

        vec_iter        insert(const_vec_iter pos, const T& value){ return l_vec.insert(pos, value); }
        vec_iter        insert(const_vec_iter pos, T&& value){ return l_vec.insert(pos, value); }
        vec_iter        insert(const_vec_iter pos, size_t count, const T& value){ return l_vec.insert(pos, count, value); }
        template<typename input_iter>
        vec_iter        insert(const_vec_iter pos, input_iter first, input_iter last){ return l_vec.insert(pos, first, last); }
        vec_iter        insert(const_vec_iter pos, std::initializer_list<T> init_list){ return l_vec.insert(pos, init_list); }

        template<typename... Args>
        vec_iter        emplace(const_vec_iter pos, Args&&... args){ l_vec.emplace(pos, args...); }
        vec_iter        erase(const_vec_iter pos){ l_vec.erase(pos); }
        vec_iter        erase(const_vec_iter first, const_vec_iter last){ l_vec.erase(first, last); }
        void            push_back(T_ptr value){ l_vec.push_back(value); }
        template<typename... Args>
        void            emplace_back(Args&&... args){ l_vec.emplace_back(args...); }
        void            pop_back(){ l_vec.pop_back(); }
        void            resize(size_t count){ l_vec.resize(count); }
        void            resize(size_t count, const T& value_type){ l_vec.resize(count, value_type); }

        void swap(collection<T>* other){
            std::vector<T *> temp_local = l_vec; //Copy local vec
            l_vec = (*other->get_internal_vec());
            (*other->get_internal_vec()) = temp_local;
            
        }


};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_COLLECTION_H_