#include "ChorusCore.h"
#include "Model3D.h"
#include "fstream"
#include "iostream"
#include "vector"
#include <GL/glew.h>

using namespace std;

namespace Chorus
{
  struct Vertex
  {
    Vec3D point;
    Vec3D normal;
    Vec3D UV;
  };
  struct Subset
  {
    string name;
    vector<Vertex> vertices;
    vector<short> indices;
    GLuint dList;
  };

  class OBJModel : public Model3D
  {
  private:
  public:
    vector<Subset> subsets;
    OBJModel(vector<Subset> subs) { subsets = subs; }
    ~OBJModel() { }

    virtual void Draw();
  };

  class objLoader
  {
  private:
    static void CreateDisplayList(OBJModel *model);
  public:
    static Model3D* loadObj(string file);
  };
}
