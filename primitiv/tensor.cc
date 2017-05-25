#include <config.h>

#include <sstream>
#include <stdexcept>
#include <utility>
#include <primitiv/device.h>
#include <primitiv/tensor.h>

using std::move;

namespace primitiv {

Tensor::Tensor(Tensor &&src)
: shape_(move(src.shape_))
, device_(src.device_)
, data_(src.data_) {
  src.device_ = nullptr;
  src.data_ = nullptr;
}

Tensor::~Tensor() {
  if (valid()) {
    device_->delete_tensor(*this);
  }
}

Tensor &Tensor::operator=(Tensor &&src) {
  if (this != &src) {
    if (valid()) {
      device_->delete_tensor(*this);
    }
    shape_ = move(src.shape_);
    device_ = src.device_;
    data_ = src.data_;
    src.device_ = nullptr;
    src.data_ = nullptr;
  }
  return *this;
}

std::vector<float> Tensor::to_vector() const {
  return device_->tensor_to_vector(*this);
}

void Tensor::reset(const float k) {
  device_->reset_tensor(*this, k);
}

void Tensor::reset(const std::vector<float> &values) {
  device_->reset_tensor(*this, values);
}

void Tensor::add_gradient(const Tensor &x) {
  device_->add_gradient(*this, x);
}

}  // namepsace primitiv
