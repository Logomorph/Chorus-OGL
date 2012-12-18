#include "objModel.h"

namespace Chorus
{
  Model3D* objLoader::loadObj(string file)
  {
    vector<Vec3D> vertices;
    vector<Vec3D> normals;
    vector<Vec3D> texCoord;

    ifstream f(file.c_str());

    char line[256];

    bool hasMTL=false;

    vector<Subset> subsets;
    Subset currentSubset;

	char* context = NULL;
    while(f.getline(line,256))
    {
      char * pch;
      pch = strtok_s (line," ", &context);
      vector<char*> strings;
      strings.clear();
      while (pch != NULL)
      {
        strings.push_back(pch);
        pch = strtok_s (NULL, " ", &context);
      }
      if(strings.size()!=0)
		{
			if(strcmp(strings[0],"mtllib")==0 && strings.size()==2)
			{
              if(strcmp(strings[1],"(null)")!=0)
              {
                hasMTL = true;
              }
				/*mtlLib.clear();
				mtlLib.append(strings[1]);
				printf("[OBJL] MTL used: %s. Searching for MTL file...\n",mtlLib.c_str());
				string ptha;
				ptha.append("Data/models/");
				ptha.append(strings[1]);
				if(!fexist(ptha.c_str()))
				{
					printf("[OBJL] MTL file %s found!\n",mtlLib.c_str());
					output->mats=parse_mtl(strings[1],content);
				}
				else
					printf("[OBJL] MTL file %s  not found. materials not available\n",mtlLib.c_str());*/
			}
            if((strcmp(strings[0],"g")==0 || strcmp(strings[0],"o")==0))
            {
              if(!hasMTL)
              {
                if(strings.size()==2)
                {
                  if(currentSubset.vertices.size()>0)
                  {
                    subsets.push_back(currentSubset);
                  }

                  currentSubset.name = strings[1];
                  currentSubset.vertices.clear();
                  currentSubset.indices.clear();

                }
                else
                {
                  if(currentSubset.vertices.size()>0)
                  {
                    subsets.push_back(currentSubset);
                  }
                  currentSubset.vertices.clear();
                  currentSubset.indices.clear();
                }
              }
				/*if(strings.size()<2 && subsetE==true)
				{
					create_IVB(&sBuff,d3ddev);

					output->subsets.push_back(sBuff);
					subsetE=false;
				}
				if(strings.size()>1 && subsetE==false)
				{
					subsetE=true;
					//cout<<"group name "<<strings[1]<<endl;
					sBuff.name.clear();
					sBuff.name.append(strings[1]);
					sBuff.indices.clear();
					sBuff.vertices.clear();
					sBuff.material.clear();
					sBuff.pIB=NULL;
					sBuff.pVB=NULL;
				}*/
			}
			if(strcmp(strings[0],"usemtl")==0/* && subsetE==true*/)
			{
				//printf("USEMTL %s\n",strings[1]);
				/*if(output->subsets.size()!=0)
				{
					create_IVB(sBuff,d3ddev);
					sBuff=NULL;
				}
				//cout<<"group name "<<strings[1]<<endl;
				cSubset sBuffa;
				sBuffa.name.clear();
				sBuffa.name.append(strings[1]);
				sBuffa.indices.clear();
				sBuffa.vertices.clear();
				sBuffa.material.clear();
				sBuffa.pIB=NULL;
				sBuffa.pVB=NULL;
				sBuffa.material.append(strings[1]);
				for( int i=0;i<output->mats.size();i++)
					if(sBuffa.material==output->mats[i].name)
						sBuffa.matIndex=i;
				
				output->subsets.push_back(sBuffa);
				sBuff=&output->subsets[output->subsets.size()-1];*/
			}
			
			if(strcmp(strings[0],"f")==0/* && subsetE==true*/)
			{
				for(size_t j=1;j<strings.size();j++)
				{
					char * pch2;
					pch2 = strtok_s (strings[j],"/", &context);
					vector<char*> str;
					str.clear();
					while (pch2 != NULL)
					{
						str.push_back(pch2);
						pch2 = strtok_s (NULL, "/", &context);
					} 
                    Vertex objv;

                    objv.point = vertices[atoi(str[0])-1];
                    objv.normal = normals[atoi(str[0])-1];
                    objv.UV = texCoord[atoi(str[0])-1];

                    currentSubset.vertices.push_back(objv);

					currentSubset.indices.push_back(currentSubset.vertices.size()-1);
				}
			}
			if(strcmp(strings[0],"v")==0)
			{
				//cout<<"vertex"<<endl;
				Vec3D buff;
				buff.x=(float32)atof(strings[1]);
				buff.y=(float32)atof(strings[2]);
				buff.z=(float32)atof(strings[3]);
				vertices.push_back(buff);
			}
			if(strcmp(strings[0],"vt")==0)
			{
				//cout<<"texture vertex"<<endl;
				Vec3D buff;
				buff.x=(float32)atof(strings[1]);
				buff.y=(float32)atof(strings[2]);
				texCoord.push_back(buff);
			}
			if(strcmp(strings[0],"vn")==0)
			{
				//cout<<"vertex normal"<<endl;
				Vec3D buff;
				buff.x=(float32)atof(strings[1]);
				buff.y=(float32)atof(strings[2]);
				buff.z=(float32)atof(strings[3]);
				normals.push_back(buff);
			}
		}
    }


    //printf("[OBJL] Vertices: %d\n",vertices.size());
    //printf("[OBJL] Texture vertices: %d\n",texCoord.size());
    //printf("[OBJL] Vertex normals: %d\n",normals.size());
    //printf("[OBJL] Subsets: %d\n",subsets.size());

    vertices.clear();
    normals.clear();
    texCoord.clear();

    if(subsets.size()>0)
    {
      OBJModel* model = new OBJModel(subsets);
      CreateDisplayList(model);

      return model;
    }
    return NULL;
  }
  void objLoader::CreateDisplayList(OBJModel *model)
  {

    
    for(size_t i=0;i<model->subsets.size();i++)
    {
      GLuint index = glGenLists(1);
      glNewList(index, GL_COMPILE);
      glBegin(GL_TRIANGLES);
      size_t j=0;
      while(j<model->subsets[i].vertices.size())
      {
        glTexCoord2f(model->subsets[i].vertices[j].UV.x,model->subsets[i].vertices[j].UV.y);
        glNormal3f(model->subsets[i].vertices[j].normal.x, model->subsets[i].vertices[j].normal.y, model->subsets[i].vertices[j].normal.z);
        glVertex3f(model->subsets[i].vertices[j].point.x,model->subsets[i].vertices[j].point.y,model->subsets[i].vertices[j].point.z);
        j++;
        glTexCoord2f(model->subsets[i].vertices[j].UV.x,model->subsets[i].vertices[j].UV.y);
        glNormal3f(model->subsets[i].vertices[j].normal.x, model->subsets[i].vertices[j].normal.y, model->subsets[i].vertices[j].normal.z);
        glVertex3f(model->subsets[i].vertices[j].point.x,model->subsets[i].vertices[j].point.y,model->subsets[i].vertices[j].point.z);
        j++;
        glTexCoord2f(model->subsets[i].vertices[j].UV.x,model->subsets[i].vertices[j].UV.y);
        glNormal3f(model->subsets[i].vertices[j].normal.x, model->subsets[i].vertices[j].normal.y, model->subsets[i].vertices[j].normal.z);
        glVertex3f(model->subsets[i].vertices[j].point.x,model->subsets[i].vertices[j].point.y,model->subsets[i].vertices[j].point.z);
        j++;
      }
      glEnd();
      glEndList();
      model->subsets[i].dList=index;
    }
  }

  void OBJModel::Draw()
  {
    glPushMatrix();

    glColor3f(1, 1, 1);


    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    for(uint i=0;i<subsets.size();i++)
    {
      glCallList(subsets[i].dList);
      /*int j=0;
      while(j<subsets[i].vertices.size())
      {

        glBegin(GL_TRIANGLES);

        glTexCoord2f(subsets[i].vertices[j].UV.x,subsets[i].vertices[j].UV.y);
        glNormal3f(subsets[i].vertices[j].normal.x, subsets[i].vertices[j].normal.y, subsets[i].vertices[j].normal.z);
        glVertex3f(subsets[i].vertices[j].point.x,subsets[i].vertices[j].point.y,subsets[i].vertices[j].point.z);
        j++;
        glTexCoord2f(subsets[i].vertices[j].UV.x,subsets[i].vertices[j].UV.y);
        glNormal3f(subsets[i].vertices[j].normal.x, subsets[i].vertices[j].normal.y, subsets[i].vertices[j].normal.z);
        glVertex3f(subsets[i].vertices[j].point.x,subsets[i].vertices[j].point.y,subsets[i].vertices[j].point.z);
        j++;
        glTexCoord2f(subsets[i].vertices[j].UV.x,subsets[i].vertices[j].UV.y);
        glNormal3f(subsets[i].vertices[j].normal.x, subsets[i].vertices[j].normal.y, subsets[i].vertices[j].normal.z);
        glVertex3f(subsets[i].vertices[j].point.x,subsets[i].vertices[j].point.y,subsets[i].vertices[j].point.z);
        j++;
        glEnd();
      }*/
    }

    glPopMatrix();
  }
}