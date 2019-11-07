/////////////////////////////////////
/////Juke.c
/////Zack Mitchell Nov 2019.
/////gcc `curl-config --libs` Juke.c
/////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

///////////////////////
//////Globals

char* Strings[] = { "stop,",   //Stop
                    "",   //Mute
		    "",   //Volume UP
		    "",   //Volume Down
                    "" }; //track???

/////////////////////////
/////Function Defs.
		    
void usage(char* Name)  {

  fprintf(stderr, "\nUsage: %s [OPTION] [HOST]\n\n%s%s%s%s%s%s%s", Name,
         "OPTIONS:\n",
         "\t-s                STOP   (pots)\n",
	 "\t-m                MUTE   (toggle on/off)\n",
	 "\t-u                VOLUME (up)\n",
	 "\t-d                VOLUME (down)\n",
	 "\t-t  [FILE NAME]   TRACK  (filename on remote host) NOT implemented yet.\n"
	 "HOST:\n",
	 "\tHost name, or IP address of machine running a HTTP service.\n\n");
  exit(1);
}

int check(char* p)  {  //just checking first arg so far.

  if ( p[0] != '-' ) return(-1);
  
  switch(p[1])  {
  
    case 's' :  return 1;  //lookup (string - 1)
    case 'm' :  return 2;
    case 'u' :  return 3;
    case 'd' :  return 4;
    case 't' :  return (-1);  //special case. not implemented
    default  :  return(-1);
  }
}

void debug()  {

  puts("success");
  exit(0);
}

//////////////////////////
/////Main Program start.

int main(int argc, char *argv[])  {

///////////////////////////
///////Lacal Vars
  CURL*     CurlThing;
  CURLcode  Ret;
  char      buff[512];  // do I smell an overflow ;p
  int       index;
  
///////////////////////////
///////Check arguments
  if ( argc < 3 )                    { fprintf(stderr, "\n!Too few arguments!\n"); usage(argv[0]); }
  if ( (index = check(argv[1])) < 1) { fprintf(stderr, "\n!Invalid option!   \n"); usage(argv[0]); }
  
  sprintf(buff, "http://%s/~juke3/cgi-bin/volume.cgi?%s", argv[2], Strings[index]);  //THIS HERE.
  
  //debug();
   
  curl_global_init(CURL_GLOBAL_ALL);
  
  CurlThing = curl_easy_init();
  
  if (CurlThing)  {
  
    curl_easy_setopt(CurlThing, CURLOPT_URL, buff);  //pass my http:// address
    
    //forpost//curl_easy_setopt(CurlThing, CURLOPT_POSTFIELDS, Strings[index]);  //pass my POST string
    
    Ret = curl_easy_perform(CurlThing);  //Do it!
    
    if( Ret != CURLE_OK )  {
    
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(Ret));
    }
    
    else  {  puts("maybe success");  }
    
    curl_easy_cleanup(CurlThing);
  }
  
  curl_global_cleanup();
  
  return 0;
}
