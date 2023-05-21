#include <algorithm>
#include "shared_ptr.hpp"

//storage
shared_ptr::Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_ ++;
}

void shared_ptr::Storage::decr() {
    ref_count_ --;
}


int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}


Matrix* shared_ptr::Storage::getObject() const{
    return data_;
}


//shared_ptr
shared_ptr::shared_ptr(Matrix *obj) {
    if (obj != nullptr)
        storage_ = new Storage(obj);
    else
        storage_ = nullptr;
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    if (storage_ != nullptr)
        this->storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    shared_ptr temp = shared_ptr(other);
    std::swap(storage_, other.storage_);
    return *this;
}

shared_ptr::~shared_ptr(){
    if (storage_ != nullptr) {
        storage_->decr();
        if (storage_->getCounter() == 0) {
            delete storage_;
        }
    }
}

Matrix *shared_ptr::ptr() const {
    if (storage_ != nullptr)
        return this->storage_->getObject();
    else
        return nullptr;
}

bool shared_ptr::isNull() const{
    if (storage_ != nullptr)
        return !(storage_->getObject());
    return true;
}

void shared_ptr::reset(Matrix* obj){
    if (storage_ != nullptr) {
        if (obj == storage_->getObject()) return;
        shared_ptr el = shared_ptr(obj);
        std::swap(storage_, el.storage_);
    }else{
        storage_ = new Storage(obj);
    }
}

Matrix* shared_ptr::operator->() const {
    if (storage_ != nullptr)
        return storage_->getObject();
    throw "the pointer to nullptr";
}

Matrix& shared_ptr::operator*() const {
    if (storage_ != nullptr)
        return *storage_->getObject();
    throw "the pointer to nullptr";
}
