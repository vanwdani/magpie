#ifndef MAGPIEUTILS_H
#define MAGPIEUTILS_H

#include "Moose.h"
#include "MooseEnum.h"
#include "MultiMooseEnum.h"
#include "libmesh/libmesh.h"
#include "libmesh/elem.h"

namespace MagpieUtils
{

/**
 * Returns a point inside element el distributed with uniform
 * probability. For higher order elements the non-linearity of the
 * mapping from the reference element coordinates to the physical element
 * could introduce a non-uniform distribution.
 * @param el The target element to locate the random point in
 * @param rnd A set of random numbers in [0:1) to use for generating the projected point
 */
Point randomElementPoint(const Elem & el, const Point & rnd);

///@{ ZAID (ZZAAA) conversion helper
unsigned int getZFromZAID(unsigned int zaid);
unsigned int getAFromZAID(unsigned int  zaid);
///@}

/// enum of different neutron energy groups (thermal, epithermal, fast, high)
enum NeutronEnergyType {Thermal = 0, Epithermal, Fast, High, NET_MAX};

/// vector of strings for each neutron energy type
const std::string & neutronEnergyName(unsigned int i);

/// Determines neutron energy type given its energy
NeutronEnergyType determineNeutronType(Real energy);

/**
 * Proxy object to emulate a reference to a T object that can be stored in
 * a container and is copy constructible. It uses a pointer to T internally
 * and overloads the assignement operator to make it behave like a reference.
 * This allows us to construct iterators that dereference to pairs and have
 * assignable 'second' members.
 */
template <typename T>
class reference_wrapper
{
public:
  reference_wrapper() = delete;
  reference_wrapper(T & obj) : ptr(&obj) {}
  reference_wrapper(const reference_wrapper<T> & ref) : ptr(ref.ptr) {}

  /// implicit cast to a value type for read access
  operator T() { return *ptr; }

  /// explicit cast to a value reference
  T & get() { return *ptr; }

  /// resets the pointer
  void set(T & rhs) { ptr = &rhs; }

  /// write access to the wrapped value
  T & operator= (const T & value) { *ptr = value; return *ptr; }

  ///@{ compound assignment operators for modification of the value
  T & operator+= (const T & rhs) { return *ptr += rhs; }
  T & operator-= (const T & rhs) { return *ptr -= rhs; }
  T & operator*= (const T & rhs) { return *ptr *= rhs; }
  T & operator/= (const T & rhs) { return *ptr /= rhs; }
  T & operator%= (const T & rhs) { return *ptr %= rhs; }
  T & operator<<= (const T & rhs) { return *ptr <<= rhs; }
  T & operator>>= (const T & rhs) { return *ptr >>= rhs; }
  T & operator^= (const T & rhs) { return *ptr ^= rhs; }
  T & operator&= (const T & rhs) { return *ptr &= rhs; }
  T & operator|= (const T & rhs) { return *ptr |= rhs; }
  ///@}

private:
  T * ptr;
};

} // namespace MagpieUtils

#endif //MAGPIEUTILS_H
