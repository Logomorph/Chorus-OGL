#include "Content.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{

  Content::Content(void)
  {
    textures.clear();
  }

  Content::~Content(void)
  {
  }
  RenderTarget Content::createRenderTarget(uint Width, uint Height)
  {
    LOG("[CONTENT] Creating render target...");
    RenderTarget tgt;

    tgt.FramebufferName = 0;
    glGenFramebuffers(1, &tgt.FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, tgt.FramebufferName);

    tgt.tex.loaded=true;
    tgt.tex.renderAttempted=false;
    tgt.tex.w=Width;
    tgt.tex.h=Height;
    // The texture we're going to render to
    glGenTextures(1, &tgt.tex.texID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, tgt.tex.texID);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, Width, Height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    glGenRenderbuffers(1, &tgt.depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, tgt.depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, tgt.depthrenderbuffer);

    // Set "renderedTexture" as our color attachment #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tgt.tex.texID, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT};
    glDrawBuffers(2, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our frame buffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      ERR("[CONTENT] Failed to create render target!");

    LOG("[CONTENT] Done!");

    return tgt;
  }
  Texture Content::loadTex(std::string file)
  {
    LOG("[CONTENT] Loading texture "+file+"...");
    if(textures.find(file) == textures.end())
    {

      SDL_Surface* ImageData = NULL; 
      ImageData = IMG_Load(file.c_str());
      //couldn't load the texture
      if (ImageData == NULL)
      {
        ERR("[CONTENT] Error loading texture!: " + std::string( SDL_GetError() ) );

        //return an empty texture
        Texture buff;
        buff.texID = 0;
        buff.w=buff.h=0;
        buff.loaded=false;
        buff.renderAttempted=false;

        return buff;
      }
      else
      {
        //post the texture to openGL
        Texture buff = postToOGL(ImageData);

        //add it to the texture map
        textures.insert(std::pair<string,Texture>(file,buff));

        //free the original surface and return the Texture object
        SDL_FreeSurface( ImageData ); 
        LOG("[CONTENT] Done!");
        return buff;
      }
    }
    //the texture is alredy loaded
    else
    {
      LOG("[CONTENT] Texture already in memory!");
      LOG("[CONTENT] Done!");

      //return the existing texture
      return textures[file];
    }
  }

  Texture Content::createTex(string name,int width, int height,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
  {

    LOG("[CONTENT] Creating texture "+name+"...");
    if(textures.find(name) == textures.end())
    {
      Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      rmask = 0xff000000;
      gmask = 0x00ff0000;
      bmask = 0x0000ff00;
      amask = 0x000000ff;
#else
      rmask = 0x000000ff;
      gmask = 0x0000ff00;
      bmask = 0x00ff0000;
      amask = 0xff000000;
#endif

      SDL_Surface* ImageData = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
        rmask,gmask,bmask,amask);
      //couldn't create the texture
      if (ImageData == NULL)
      {
        ERR("[CONTENT] CreateRGBSurface failed: " + std::string( SDL_GetError() ) );

        //return an empty texture
        Texture buff;
        buff.texID = 0;
        buff.w=buff.h=0;
        buff.loaded=false;
        buff.renderAttempted=false;

        return buff;
      }
      else
      {
        //fill the image with pixels of the colors specified in r,g,b,a
        //locking might not be needed on some machines
        if( SDL_MUSTLOCK( ImageData ) ) 
        { 
          //Lock the surface 
          SDL_LockSurface( ImageData );
        }

        Uint32 pixel = SDL_MapRGBA(ImageData->format, r, g, b,a);
        Uint32 *pixels = (Uint32 *)ImageData->pixels;
        for(int i=0;i<width*height;i++)
        {
          pixels[i] = pixel;

        }
        if( SDL_MUSTLOCK( ImageData ) ) 
        { 
          //Unlock surface
          SDL_UnlockSurface( ImageData ); 
        }
        //done

        //post the texture to openGL
        Texture buff = postToOGL(ImageData);

        //add it to the texture map
        textures.insert(std::pair<string,Texture>(name,buff));

        //free the original surface and return the Texture object
        SDL_FreeSurface( ImageData ); 
        LOG("[CONTENT] Done!");
        return buff;
      }
    }
    //the texture is alredy loaded
    else
    {
      LOG("[CONTENT] Texture already in memory!");
      LOG("[CONTENT] Done!");

      //return the existing texture
      return textures[name];
    }
  }

  //Create an opengl texture from a SDL_Surface
  Texture Content::postToOGL(SDL_Surface* ImageData)
  {
    //create a new OGL texture and bind it
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //build 2D mipmaps for it
    if (ImageData->format->Amask)
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, ImageData->w, ImageData->h, GL_RGBA, GL_UNSIGNED_BYTE, ImageData->pixels);
    else
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ImageData->w, ImageData->h, GL_RGB, GL_UNSIGNED_BYTE, ImageData->pixels);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    //create a new Texture object and set the properties
    Texture buff;
    buff.texID = texture;
    buff.w=ImageData->w;
    buff.h=ImageData->h;
    buff.loaded=true;
    buff.renderAttempted=false;

    return buff;
  }

  Font Content::loadFnt(std::string file)
  {
    LOG("[CONTENT] Loading font "+ file +"...");

    Font buff;

    TiXmlDocument     *xmlDoc = new TiXmlDocument(file.c_str());
    if (!xmlDoc->LoadFile())
    {
      // Fatal error, cannot load
      ERR("[CONTENT] Failed to load "+file);
      buff.loaded=false;
      return buff;
      SafeDelete<TiXmlDocument> (xmlDoc);
    }
    else
    {
      TiXmlElement *xMap = 0;

      xMap = xmlDoc->FirstChildElement("font");

      //read basic info

      TiXmlElement *xComm = xMap->FirstChildElement("common");

      buff.lineH = atoi(xComm->Attribute("lineHeight"));

      int sizeW = atoi(xComm->Attribute("scaleW"));
      int sizeH = atoi(xComm->Attribute("scaleH"));

      //load font atlas
      TiXmlElement *xPages = xMap->FirstChildElement("pages");
      TiXmlElement *xPage = xPages->FirstChildElement("page");

      buff.tex = this->loadTex(xPage->Attribute("file"));


      //read character info
      TiXmlElement *xChars = xMap->FirstChildElement("chars");


      TiXmlElement *xChar = xChars->FirstChildElement("char");
      while(xChar)
      {
        charDescript bfx;
        bfx.id = atoi(xChar->Attribute("id"));

        int X = atoi(xChar->Attribute("x"));
        int Y = atoi(xChar->Attribute("y"));
        int W = atoi(xChar->Attribute("width"));
        int H = atoi(xChar->Attribute("height"));

        bfx.W=W;
        bfx.H=H;

        bfx.xOff = (float)atoi(xChar->Attribute("xoffset"));
        bfx.yOff = (float)atoi(xChar->Attribute("yoffset"));
        bfx.xAdv = (float)atoi(xChar->Attribute("xadvance"));

        //translate the position information to texture coordinates
        bfx.rX = float(X)/float(sizeW);
        bfx.rY = float(Y)/float(sizeH);
        bfx.rR = ((float(X)+float(W)))/float(sizeW);
        bfx.rB = ((float(Y)+float(H)))/float(sizeH);

        buff.chars.push_back(bfx);

        xChar=xChar->NextSiblingElement("char");
      }

      xmlDoc->Clear();
      SafeDelete<TiXmlDocument> (xmlDoc);

      LOG("[CONTENT] Font loaded!");

      buff.loaded=true;
      return buff;
    }
  }

  Model3D* Content::loadObj(string file)
  {
    LOG("[CONTENT] Loading OBJ file "+ file +"...");
    Model3D* model = objLoader::loadObj(file);
    if(model==NULL)
    {
      ERR("[CONTENT] Failed to load "+file);
      return NULL;
    }
    LOG("[CONTENT] Model loaded!");
    return model;
  }

  Shader Content::loadShader(string vertex,string fragment)
  {
    LOG("[CONTENT] Loading shader "+ vertex +" & " + fragment+"...");
    Shader sh;
    sh.f=sh.p=sh.v=0;
    sh.loaded=false;

    std::ifstream vert;
    size_t lenghtV;
    vert.open(vertex.c_str(), std::ios::binary);      // open input file

    std::ifstream frag;
    int lenghtF;
    frag.open(fragment.c_str(), std::ios::binary);      // open input file

    if(vert.fail() || frag.fail())
    {
      ERR("[CONTENT] Failed to load "+ vertex +" & " + fragment);
    }
    else
    {
      vert.seekg(0, std::ios::end);    // go to the end
      lenghtV = (size_t)vert.tellg();           // report location (this is the lenght)
      vert.seekg(0, std::ios::beg);    // go back to the beginning
      char* vs = new char[lenghtV+1];    // allocate memory for a buffer of appropriate dimension
      vs[lenghtV]='\0';
      vert.read(vs, lenghtV);       // read the whole file into the buffer
      vert.close();                    // close file handle


      frag.seekg(0, std::ios::end);    // go to the end
      lenghtF = (size_t)frag.tellg();           // report location (this is the lenght)
      frag.seekg(0, std::ios::beg);    // go back to the beginning
      char* fs = new char[lenghtF+1];    // allocate memory for a buffer of appropriate dimension
      fs[lenghtF]='\0';
      frag.read(fs, lenghtF);       // read the whole file into the buffer
      frag.close();                    // close file handle

      //create the shaders
      sh.v = glCreateShader(GL_VERTEX_SHADER);
      sh.f = glCreateShader(GL_FRAGMENT_SHADER);	

      const char * vv = vs;
      const char * ff = fs;

      glShaderSource(sh.v, 1, &vv,NULL);
      glShaderSource(sh.f, 1, &ff,NULL);


      delete vs;
      delete fs;

      glCompileShader(sh.v);
      glCompileShader(sh.f);

      sh.p = glCreateProgram();

      glAttachShader(sh.p,sh.v);
      glAttachShader(sh.p,sh.f);

      glLinkProgram(sh.p);

      /*printShaderInfoLog(sh.v);
      printShaderInfoLog(sh.f);*/
      printProgramInfoLog(sh.p);

      LOG("[CONTENT] Shader loaded!");

      sh.loaded=true;
    }
    return sh;
  }

  void Content::printShaderInfoLog(GLuint obj)
  {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 1)
    {
      LOG("Shader InfoLog:");
      infoLog = (char *)malloc(infologLength);
      glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
      LOG(infoLog);
      free(infoLog);
    }
  }

  void Content::printProgramInfoLog(GLuint obj)
  {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 1)
    {
      ERR("[CONTENT] Program InfoLog:");
      infoLog = (char *)malloc(infologLength);
      glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
      LOG(infoLog);
      free(infoLog);
      ERR("[CONTENT] Shader might not work!");
    }
  }

}