
#include "Texture.h"


GLuint	texture;

//Texture texpiso[10];
Texture texpiso[3];
Texture texarbol[3];


bool texturatexpiso(){
	int i;
	if (LoadTGA(&texpiso[0], "modelos/escenario/piso/texturaPiso.tga"))
	{
		for (i = 0; i<3; i++){
			glGenTextures(1, &texpiso[i].texID);
			glBindTexture(GL_TEXTURE_2D, texpiso[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, texpiso[i].bpp / 8, texpiso[i].width, texpiso[i].height, 0, texpiso[i].type, GL_UNSIGNED_BYTE, texpiso[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (texpiso[i].imageData)
			{
				free(texpiso[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool texturaArbol(){
    int i;
	if (LoadTGA(&texarbol[0], "modelos/escenario/arbol/tronco/Color-material-tree.tga"))
	{
		for (i = 0; i<3; i++){
			glGenTextures(1, &texarbol[i].texID);
			glBindTexture(GL_TEXTURE_2D, texarbol[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, texarbol[i].bpp / 8, texarbol[i].width, texarbol[i].height, 0, texarbol[i].type, GL_UNSIGNED_BYTE, texarbol[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (texarbol[i].imageData)
			{
				free(texarbol[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	}


