#ifndef INCLUDE_PROTOTYPE_HPP
#define INCLUDE_PROTOTYPE_HPP

namespace sp
{
class ICloneable
{
  public:
    virtual ICloneable* clone() const = 0;
};
} // namespace sp

#endif