#ifndef PRIMITIV_CPU_DEVICE_H_
#define PRIMITIV_CPU_DEVICE_H_

#include <map>
#include <random>
#include <primitiv/device.h>

namespace primitiv {

/**
 * Device class for the usual CPU.
 */
class CPUDevice : public Device {
  CPUDevice(const CPUDevice &) = delete;
  CPUDevice(CPUDevice &&) = delete;
  CPUDevice &operator=(const CPUDevice &) = delete;
  CPUDevice &operator=(CPUDevice &&) = delete;

public:
  /**
   * Creates a CPUDevice object.
   * @remarks The internal random number generator is initialized by
   *          `std::random_device`.
   */
  CPUDevice();

  /**
   * Creates a CPUDevice object.
   * @param rng_seed The seed value of internal random number generator.
   */
  explicit CPUDevice(const unsigned rng_seed);

  ~CPUDevice() override;

  using Device::new_tensor;
  Tensor new_tensor(const Shape &shape) override;
  Tensor new_tensor(const Shape &shape, const float k) override;
  Tensor new_tensor(
      const Shape &shape, const std::vector<float> &values) override;
  void delete_tensor(Tensor &x) override;
  std::vector<float> tensor_to_vector(const Tensor &x) override;
  void reset_tensor(Tensor &x, const float k) override;
  void reset_tensor(Tensor &x, const std::vector<float> &values) override;

  Tensor random_bernoulli(const Shape &shape, const float p) override;
  Tensor random_uniform(
      const Shape &shape, const float lower, const float upper) override;
  Tensor random_normal(
      const Shape &shape, const float mean, const float sd) override;

  Tensor slice(
      const Tensor &x, const unsigned dim,
      const unsigned lower, const unsigned upper) override;

  Tensor duplicate(const Tensor &x) override;
  Tensor negate(const Tensor &x) override;

  Tensor add(const Tensor &x, const float k) override;
  Tensor add(const Tensor &a, const Tensor &b) override;
  Tensor subtract(const Tensor &x, const float k) override;
  Tensor subtract(const float k, const Tensor &x) override;
  Tensor subtract(const Tensor &a, const Tensor &b) override;
  Tensor multiply(const Tensor &x, const float k) override;
  Tensor multiply(const Tensor &a, const Tensor &b) override;
  Tensor divide(const Tensor &x, const float k) override;
  Tensor divide(const float k, const Tensor &x) override;
  Tensor divide(const Tensor &a, const Tensor &b) override;

  Tensor transpose(const Tensor &x) override;
  Tensor dot(const Tensor &a, const Tensor &b) override;

  Tensor exp(const Tensor &x) override;
  Tensor tanh(const Tensor &x) override;
  Tensor sigmoid(const Tensor &x) override;
  Tensor step(const Tensor &x) override;
  Tensor relu(const Tensor &x) override;

  Tensor batch_sum(const Tensor &x) override;

  void add_gradient(Tensor &a, const Tensor &b) override;

private:
  std::map<void *, unsigned> blocks_;
  std::mt19937 rng_;
};

}  // namespace primitiv

#endif  // PRIMITIV_CPU_DEVICE_H_
