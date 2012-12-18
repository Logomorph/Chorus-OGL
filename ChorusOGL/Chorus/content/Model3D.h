#include "../core/ChorusCore.h"

namespace Chorus
{
  class Model3D
  {
  public:
    virtual ~Model3D() {}

    virtual void Draw() = 0;
  };
}