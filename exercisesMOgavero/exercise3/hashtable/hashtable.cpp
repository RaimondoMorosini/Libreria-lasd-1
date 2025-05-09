
namespace lasd {

/* ************************************************************************** */

#include <string>

/* ************************************************************************** */

template <>
class Hashable<int> {

public:

  ulong operator()(const int & dat) const noexcept {
    return (dat * dat);
  }

};

template <>
class Hashable<double> {

public:

  ulong operator()(const double & dat) const noexcept {
    long intgpart = floor(dat);
    long fracpart = pow(2, 24) * (dat - intgpart);
    return (intgpart * fracpart);
  }

};

template <>
class Hashable<std::string> {

public:

  ulong operator()(const std::string & dat) const noexcept {
    ulong hash = 5381;
    for (ulong i = 0; i < dat.length(); ++i) {
      hash = (hash << 5) + dat[i];
    }
    return hash;
  }

};

/* ************************************************************************** */

}
