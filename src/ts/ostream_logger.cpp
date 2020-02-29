#include <PLODD/ts/ostream_logger.h>

#include <list>

#include <PLODD/ts/time.hpp>

namespace pld {
namespace ts {

std::list<shared_stream_mutex> ostream_logger::shared_mutex_list = {};
std::mutex ostream_logger::vector_mutex = {};

ostream_logger::ostream_logger(std::ostream * requested_stream_pointer) : base_logger("HEYHEY", logging_level::DEBUG){
    std::lock_guard<std::mutex> vector_lock(vector_mutex);
    bool found_shared_mutex = false;
    obj_stream_ptr = requested_stream_pointer;
    //Make sure the vector has something in it before we try to iterate over it:
    if(shared_mutex_list.begin() == shared_mutex_list.end()){
        std::mutex * heaped_mutex = new std::mutex();
        shared_mutex_list.push_back(shared_stream_mutex(obj_stream_ptr, heaped_mutex, 1));
        obj_shared_mutex = &shared_mutex_list.back();
        return;
    }
    //Try to find an existing shared mutex with the same stream pointer:
    for(auto& it : shared_mutex_list){
        if(it.stream_ptr == requested_stream_pointer){
            it.dependents++;
            obj_shared_mutex = &it;
            found_shared_mutex = true;
            break;
        } else {
            continue;
        }
    }
    //If there isn't one with a matching stream pointer, make a new one.
    if(!found_shared_mutex){
        std::mutex * heaped_mutex = new std::mutex();
        shared_mutex_list.push_back(shared_stream_mutex(obj_stream_ptr, heaped_mutex, 1));
        obj_shared_mutex = &shared_mutex_list.back();
    }
}

ostream_logger::~ostream_logger(){
    std::lock_guard<std::mutex> vec_lock(vector_mutex);
    //This object no longer requires the mutex, as it is being destoried.
    obj_shared_mutex->dependents--;
    //Garbage collection:
    for(auto it = shared_mutex_list.begin(); it != shared_mutex_list.end();){
        if(it->dependents < 1){
            delete it->mutex;
            it = shared_mutex_list.erase(it);
            continue;
        }
        it++;
    }
}

void ostream_logger::debug(std::string msg){
    std::lock_guard<std::mutex> stream_lock(*obj_shared_mutex->mutex);
    (*obj_stream_ptr) << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << "\n";
}

void ostream_logger::info(std::string msg){
    std::lock_guard<std::mutex> stream_lock(*obj_shared_mutex->mutex);
    (*obj_stream_ptr) << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << "\n";
}

void ostream_logger::warn(std::string msg){
    std::lock_guard<std::mutex> stream_lock(*obj_shared_mutex->mutex);
    (*obj_stream_ptr) << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << "\n";
}

void ostream_logger::error(std::string msg){
    std::lock_guard<std::mutex> stream_lock(*obj_shared_mutex->mutex);
    (*obj_stream_ptr) << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << "\n";
}

} //ts
} //pld