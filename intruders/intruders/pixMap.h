#include <malloc.h>
#include <math.h>

class RGB
{
public:
	unsigned char r,g,b;
} ;//RGB;

//typedef struct RGBpixmap
class RGBpixmap
{
public:
	int nRows, nCols;
  RGB *pixel;
  void readBMPFile(char *file); //make pixmap from image
  void setTexture(GLuint textureID);  // specify image data as texture



}; //RGBpixmap;

/**************************************************************************
 *  fskip                                                                 *
 *     Skips bytes in a file.                                             *
 **************************************************************************/

void fskip(FILE *fp, int num_bytes)
{
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(fp);
}


/**************************************************************************
 *                                                                        *
 *    Loads a bitmap file into memory.                                    *
 **************************************************************************/

unsigned short getShort(FILE *fp) //helper function
{ //BMP format uses little-endian integer types
  // get a 2-byte integer stored in little-endian form
		char ic;
		unsigned short ip;
		ic = fgetc(fp); ip = ic;  //first byte is little one 
		ic = fgetc(fp);  ip |= ((unsigned short)ic << 8); // or in high order byte
		return ip;
}
//<<<<<<<<<<<<<<<<<<<< getLong >>>>>>>>>>>>>>>>>>>
unsigned long getLong(FILE *fp) //helper function
{  //BMP format uses little-endian integer types
   // get a 4-byte integer stored in little-endian form
		unsigned long ip = 0;
		char ic = 0;
		unsigned char uc = ic;
		ic = fgetc(fp); uc = ic; ip = uc;
		ic = fgetc(fp); uc = ic; ip |=((unsigned long)uc << 8);
		ic = fgetc(fp); uc = ic; ip |=((unsigned long)uc << 16);
		ic = fgetc(fp); uc = ic; ip |=((unsigned long)uc << 24);
		return ip;
	}
/* Compute the nearest power of 2 number that is 
 * less than or equal to the value passed in. 
 */
static GLuint 
nearestPower( GLuint value )
{
    int i = 1;

    if (value == 0) return -1;      /* Error! */
    for (;;) {
         if (value == 1) return i;
         else if (value == 3) return i*4;
         value >>= 1; i *= 2;
    }
}

RGBpixmap scaled; 
void RGBpixmap:: readBMPFile(char *file)
{
  FILE *fp;
  long index;
  int k,row,col,numPadBytes, nBytesInRow;
  char ch1,ch2;
  unsigned long fileSize;
  unsigned short reserved1;    // always 0
  unsigned short reserved2;     // always 0 
  unsigned long offBits; // offset to image - unreliable
  unsigned long headerSize;     // always 40
  unsigned long numCols; // number of columns in image
  unsigned long numRows; // number of rows in image
  unsigned short planes;      // always 1 
  unsigned short bitsPerPixel;    //8 or 24; allow 24 here
  unsigned long compression;      // must be 0 for uncompressed 
  unsigned long imageSize;       // total bytes in image 
  unsigned long xPels;    // always 0 
  unsigned long yPels;    // always 0 
  unsigned long numLUTentries;    // 256 for 8 bit, otherwise 0 
  unsigned long impColors;       // always 0 
  long count;
  char dum;

  GLsizei sWidth, sHeight;
  
  /* open the file */
  if ((fp = fopen(file,"rb")) == NULL)
  {
    printf("Error opening file %s.\n",file);
    exit(1);
  }

  /* check to see if it is a valid bitmap file */
  if (fgetc(fp)!='B' || fgetc(fp)!='M')
  {
    fclose(fp);
    printf("%s is not a bitmap file.\n",file);
    exit(1);
  }

  fileSize =      getLong(fp);
  reserved1 =    getShort(fp);    // always 0
  reserved2= 	getShort(fp);     // always 0 
  offBits =		getLong(fp); // offset to image - unreliable
  headerSize =     getLong(fp);     // always 40
  numCols =		getLong(fp); // number of columns in image
  numRows = 		getLong(fp); // number of rows in image
  planes=    	getShort(fp);      // always 1 
  bitsPerPixel=   getShort(fp);    //8 or 24; allow 24 here
  compression =    getLong(fp);      // must be 0 for uncompressed 
  imageSize = 	getLong(fp);       // total bytes in image 
  xPels =    	getLong(fp);    // always 0 
  yPels =    	getLong(fp);    // always 0 
  numLUTentries = getLong(fp);    // 256 for 8 bit, otherwise 0 
  impColors = 	getLong(fp);       // always 0 
  
  if(bitsPerPixel != 24) 
  { // error - must be a 24 bit uncompressed image
    printf("Error bitsperpixel not 24\n");
    exit(1);
  } 
   
  //add bytes at end of each row so total # is a multiple of 4
  // round up 3*numCols to next mult. of 4
  nBytesInRow = ((3 * numCols + 3)/4) * 4;
  numPadBytes = nBytesInRow - 3 * numCols; // need this many
  
  
   
  this->nRows = numRows; // set class's data members
  this->nCols = numCols;
  this->pixel = (RGB *) malloc(3 * numRows * numCols);//make space for array
  if(!this->pixel) return; // out of memory!
  count = 0;
  dum;
  for(row = 0; row < numRows; row++) // read pixel values
  {
  	for(col = 0; col < numCols; col++)
	{
	  int r,g,b;
	  b = fgetc(fp); g = fgetc(fp); r = fgetc(fp); //read bytes
	  this->pixel[count].r = r; //place them in colors
	  this->pixel[count].g = g;
	  this->pixel[count++].b = b;
	}
	fskip(fp,numPadBytes);
  }
   fclose(fp); 

     
   	 
}

void RGBpixmap::setTexture(GLuint textureID)
{
  glBindTexture(GL_TEXTURE_2D, textureID);
  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  // specify the image as texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->nCols, this->nRows, 0, GL_RGB,
	           GL_UNSIGNED_BYTE, this->pixel);
}
