#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <SDL2/SDL_mixer.h>
#include <windows.h>
#include <Mmsystem.h>
#pragma comment (lib, "Winmm.lib")
#include <cstdlib>

///donya jafari-zahra aghaeipoor-21

using namespace std;

int w=1280;
int h=800;
int id;
bool sound1;
bool music1;

Mix_Music *Music;
Mix_Chunk *Click;
Mix_Chunk *SwapColor;
Mix_Chunk *Win;
Mix_Chunk *Explosion;
Mix_Chunk *Applause;

int map1 (SDL_Renderer *m_renderer);
int map2 (SDL_Renderer *m_renderer);
int map3 (SDL_Renderer *m_renderer);
int startMenu(SDL_Renderer *m_renderer);
int leaderboard (SDL_Renderer *m_renderer);

void Sort(int a[], int n)
{
    for(int i=n-1 ;i>0; i--)
      for(int j=0; j<i; j++)
        if(a[j]>a[j+1])
          swap(a[j],a[j+1]);
}

struct playerType
{
    string username,password;
    int points=0;
};

playerType player[100];

struct ball
{
    double x,y,a,b,dx,xx;
    int color;
};

struct shoot
{
    double x,y,i,dx,dy;
    int color;
    bool way=0,checked=0;
};

struct map2Ball
{
    int i=0;
    double x,y,Vx,Vy;
    int color;
    double x1=60;
    double y1=-160;
    double x2=w/2+500;
    double y2=-1000;
    double x3=w+900;
    double y3=-10;
    double x4=w/2+500;
    double y4=h/2+200;
    double x5=w/2+500;
    double y5=h/2+200;
    double x6=-900;
    double y6=-h;
    double x7=-200;
    double y7=-4*h;
    double x8=0;
    double y8=-100;
    double x9=0;
    double y9=-1000;
    double x10=0;
    double y10=300000;
    bool exist=1;
};

struct map3Ball
{
    int i=0;
   double x,y,Vx,Vy;
    int color;
    double x1=60;
    double y1=-160;
    double x2=w/2+500;
    double y2=2000;
    double x3=w+900;
    double y3=1000;
    double x4=w/2+500;
    double y4=-h/2-200;
    double x5=w/2+500;
    double y5=-h/2-200;
    double x6=-9000;
    double y6=-10000;
    double x7=-2000;
    double y7=-4*h;
    double x8=-30000;
    double y8=1000;
    double x9=-30000;
    double y9=1000;
    double x10=-300000;
    double y10=3000;
    bool exist=1;
};

struct map1Ball
{
    int i=0;
   double x,y,Vx,Vy;
    int color;
    double x1=60;
    double y1=-160;
    double x2=w/2+500;
    double y2=-1000;
    double x3=w+900;
    double y3=-10;
    double x4=w/2+500;
    double y4=h/2+200;
    double x5=w/2+500;
    double y5=h/2+200;
    double x6=-900;
    double y6=-h;
    double x7=-200;
    double y7=-4*h;
    double x8=3000;
    double y8=-100;
    double x9=30000;
    double y9=-10000;
    double x10=30000;
    double y10=-30000;
    bool exist=1;
};

void texture(SDL_Renderer *m_renderer, int xp, int yp, string addressOfImage, int width, int height)
{
    int n=addressOfImage.length();
    char char_array[n+1];
    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture(m_renderer, char_array);
    SDL_Rect texr1;
    texr1.x=xp;
    texr1.y=yp;
    texr1.w=width;
    texr1.h=height;
    SDL_RenderCopy(m_renderer, myTexture, NULL, &texr1);
    SDL_DestroyTexture(myTexture);
}

void explosion(SDL_Renderer *m_renderer,int x,int y)
{
    for(int i=6 ; i<=6 ; i++)
    {
        string si;
        si+=to_string(i);
        si+=".png";
        texture(m_renderer,x-100,y-100,si,200,200);
        SDL_RenderPresent( m_renderer );
    }
}

void angledImage(SDL_Renderer *m_renderer,string addressOfImage , int x, int y, int width, int height, double angle)
{
    int n=addressOfImage.length();
    char char_array[n+1];
    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture(m_renderer, char_array);
    SDL_Rect rectangle{x,y,width,height};
    SDL_QueryTexture (myTexture,NULL,NULL,&width,&height);
    SDL_RenderCopyEx(m_renderer,myTexture,NULL,&rectangle,angle,NULL,SDL_FLIP_NONE);
    SDL_DestroyTexture(myTexture);
}

int startMenu(SDL_Renderer *m_renderer)
{
       SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
       SDL_RenderClear( m_renderer );
       texture(m_renderer, 0,0,"start10.jpg",w,h);
       filledCircleRGBA (m_renderer, w/2, h/2, 150, 157, 176, 180, 255);
       aacircleRGBA (m_renderer, w/2, h/2, 135, 0, 0, 0, 255);
       SDL_RenderPresent( m_renderer );
       SDL_Color text_color2={0, 0, 0};
       const char* text="start";
       textColor(m_renderer,w/2-70,h/2-35,text,1 ,60,text_color2);

    while(1)
    {
       SDL_Event e;
       if(SDL_PollEvent(&e))
       {
          if( e.type == SDL_MOUSEBUTTONDOWN )///press to start
          {
              if(sound1==1)
                Mix_PlayChannel(-1,Click,0);
            SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
            SDL_RenderClear( m_renderer );
            texture(m_renderer, 0,0,"start10.jpg",w,h);
            filledCircleRGBA (m_renderer, w/2, h/2, 150, 157, 176, 180, 255);
            aacircleRGBA (m_renderer, w/2, h/2, 135, 0, 0, 0, 255);
            SDL_RenderPresent( m_renderer );
            SDL_Color text_color2={0, 0, 0};
            const char* text="start";
            textColor(m_renderer,w/2-70,h/2-35,text,1 ,60,text_color2);
            int x, y;
            SDL_GetMouseState( &x, &y );
            if( ((x-(w/2))*(x-(w/2)))+((y-(h/2))*(y-(h/2))) < 150*150 )
            {
                break;
            }
          }
       }
    }
        SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
        SDL_RenderClear( m_renderer );
        texture(m_renderer, 0,0,"choose.jpg",w,h);

        SDL_Color text_color1={0, 0, 0};
        SDL_Color text_color3={255, 255, 255};
        const char* text1="milky way galaxy";
        const char* text2="interstellar";
        const char* text3="meteorite rain";
        const char* text4="leaderboard";
        const char* text5="exit";

        boxRGBA (m_renderer, 326, 60, 953, 740, 15, 31, 52, 255);
        boxRGBA (m_renderer, 426-50, 116, 735, 216, 150, 150, 150, 255);
        textColor(m_renderer,406, 146, text1, 2, 40, text_color1);
        boxRGBA (m_renderer, 526, 272, 835+50, 372, 150, 150, 150, 255);
        textColor(m_renderer,566, 302, text2, 2, 40, text_color1);
        boxRGBA (m_renderer, 426-50, 428, 735, 528, 150, 150, 150, 255);
        textColor(m_renderer,426, 458, text3, 2, 40, text_color1);
        boxRGBA (m_renderer, 426-50, 584, 835+50, 684, 150, 150, 150, 255);
        textColor(m_renderer,426, 614, text4, 2, 40, text_color1);
        boxRGBA (m_renderer, w-200, h-150, w-50, h-80, 0, 0, 0, 255);
        textColor(m_renderer,w-200+15, h-150+20, text5, 1, 40, text_color3);

        texture(m_renderer, 735,116,"111.png",150,100);
        texture(m_renderer, 426-50,272,"222.png",150,100);
        texture(m_renderer, 735,428,"333.png",150,100);

        rectangleRGBA(m_renderer, 735,116,735+150,116+100,150, 150, 150, 255);
        rectangleRGBA(m_renderer, 426-50,272,426-50+150,272+100,150, 150, 150, 255);
        rectangleRGBA(m_renderer, 735,428,735+150,428+100,150, 150, 150, 255);

        SDL_RenderPresent( m_renderer );

    while(1)
    {
       SDL_Event e;
       if(SDL_PollEvent(&e))
       {
          if( e.type == SDL_MOUSEBUTTONDOWN )///map selecting
          {
              if(sound1==1)
                Mix_PlayChannel(-1,Click,0);
            int x, y;
            SDL_GetMouseState( &x, &y );
            SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
            SDL_RenderClear( m_renderer );
            texture(m_renderer, 0,0,"choose.jpg",w,h);
            SDL_Color text_color1={0, 0, 0};
            SDL_Color text_color3={255, 255, 255};
            const char* text1="milky way galaxy";
            const char* text2="interstellar";
            const char* text3="meteorite rain";
            const char* text4="leaderboard";
            const char* text5="exit";

              boxRGBA (m_renderer, 326, 60, 953, 740, 15, 31, 52, 255);
              boxRGBA (m_renderer, 426-50, 116, 735, 216, 150, 150, 150, 255);
              textColor(m_renderer,406, 146, text1, 2, 40, text_color1);
              boxRGBA (m_renderer, 526, 272, 835+50, 372, 150, 150, 150, 255);
              textColor(m_renderer,566, 302, text2, 2, 40, text_color1);
              boxRGBA (m_renderer, 426-50, 428, 735, 528, 150, 150, 150, 255);
              textColor(m_renderer,426, 458, text3, 2, 40, text_color1);
              boxRGBA (m_renderer, 426-50, 584, 835+50, 684, 150, 150, 150, 255);
              textColor(m_renderer,426, 614, text4, 2, 40, text_color1);
              boxRGBA (m_renderer, w-200, h-150, w-50, h-80, 0, 0, 0, 255);
              textColor(m_renderer,w-200+15, h-150+20, text5, 1, 40, text_color3);

              texture(m_renderer, 735,116,"111.png",150,100);
              texture(m_renderer, 426-50,272,"222.png",150,100);
              texture(m_renderer, 735,428,"333.png",150,100);

              rectangleRGBA(m_renderer, 735,116,735+150,116+100,150, 150, 150, 255);
              rectangleRGBA(m_renderer, 426-50,272,426-50+150,272+100,150, 150, 150, 255);
              rectangleRGBA(m_renderer, 735,428,735+150,428+100,150, 150, 150, 255);

              SDL_RenderPresent( m_renderer );

            if( (x > 426-50 && x < 735 ) && ( y > 116 && y < 216 ) )///map1
            {
               map1(m_renderer);
            }
            if( (x > 526 && x < 835+50 ) && ( y > 272 && y < 372 ) )///map2
            {
               map2(m_renderer);
            }
            if( (x > 426-50 && x < 735 ) && ( y > 428 && y < 528 ) )///map3
            {
               map3(m_renderer);
            }
            if( (x > 426-50 && x < 835+50 ) && ( y > 584 && y < 684 ) )///leader board
            {
               leaderboard(m_renderer);
            }
            if( (x >w-200 && x < w-50 ) && ( y > h-150 && y <  h-80 ) )///exit and close the window
            {
                return 0;
            }
          }
       }
    }
}

int leaderboard (SDL_Renderer *m_renderer)
{
       SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
       SDL_RenderClear( m_renderer );
       texture(m_renderer, 0,0,"start7.jpg",w,h);
       boxRGBA(m_renderer, w/3,0,(2*w)/3,h,170,170,200,255);
       texture(m_renderer, (2*w)/3-50,0,"cross.png",50,50);
       SDL_RenderPresent(m_renderer);
       SDL_Event e;
       lineRGBA(m_renderer, w/3+147,0,w/3+147,h,0,0,0,255);
       lineRGBA(m_renderer, w/3+247,0,w/3+247,h,0,0,0,255);

       ifstream Username1("username.txt");///saving array of usernames
       string username[100];
       int i=0;
       string x="";
       while(x!="-1")
       {
          Username1>>x;
          username[i]=x;
          i++;
       }

       ifstream Score1("scores.txt");///saving array of scores
       string score[100];
       i=0;
       x="";
       while(x!="-1")
       {
          Score1>>x;
          score[i]=x;
          i++;
       }
       int a[100],b[100];
       int q;
       for(q=0; q<i-1; q++)
       {
           a[q]=atoi(score[q].c_str());
           b[q]=a[q];
       }
      Sort(a,q+1);
      int Rank=0;
      for(int m=i-1; m>=0; m--)
        for(int n=0; n<i-1; n++)
          if(a[m]!=a[m+1])
           if(a[m]==b[n])
           {
               Rank++;
               SDL_Color text_color={0, 0, 0};///showing rankings
               const char* text1;
               const char* text2;
               const char* text3;

               stringstream ss;
               ss<<Rank;
               string s;
               ss>>s;
               text1 =s.c_str();

               stringstream dd;
               dd<<username[n];
               string d;
               dd>>d;
               text2 =d.c_str();

               stringstream rr;
               rr<<b[n];
               string r;
               rr>>r;
               text3 =r.c_str();

               textColor(m_renderer,w/3+50,(Rank*50),text1,2 ,25,text_color);
               textColor(m_renderer,w/3+150,(Rank*50),text2,2 ,25,text_color);
               textColor(m_renderer,w/3+250,(Rank*50),text3,2 ,25,text_color);
               lineRGBA(m_renderer, w/3+3,(Rank*50)+25,(2*w)/3-3,(Rank*50)+25,0,0,0,255);
           }

       while(1)
       {
           if(SDL_PollEvent(&e))
           {
               if( e.type == SDL_MOUSEBUTTONDOWN )///returning to start menu
               {
                   if(sound1==1)
                     Mix_PlayChannel(-1,Click,0);
                   int x, y;
                   SDL_GetMouseState( &x, &y );
                   if( (x > (2*w)/3-50 && x < (2*w)/3 ) && ( y > 0 && y < 50 ))
                     if(startMenu(m_renderer)==0)
                        return 0;
               }
           }
       }
}

int timeUP(SDL_Renderer *m_renderer, int point, int id)
{
    Mix_PlayChannel(-1,Applause,0);
    SDL_Event e;
    SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
    SDL_RenderClear( m_renderer );
    texture(m_renderer, 0,0,"mode.jpg",w,h);
    boxRGBA(m_renderer,w/3,h/3,(2*w)/3,(2*h)/3,99,123,159,255);///showing score and powers
    SDL_Color text_color2={0, 0, 0};
    const char* text="times up...";
    const char* text1="your score: ";
    const char* text3;
    stringstream ss;
    ss<<point;
    string s;
    ss>>s;
    text3 =s.c_str() ;
    textColor(m_renderer,w/2-100,h/2-35-50,text,2 ,40,text_color2);
    textColor(m_renderer,w/2-100,h/2-35+100-50,text1,2 ,35,text_color2);
    textColor(m_renderer,w/2+100,h/2-35+100-50,text3,2 ,35,text_color2);
    const char* text4;
    int power;
    string p;
    power=rand()%3;
     if(power==0)
     {
        text4="you won the bomb power!";
        p="bomb";
     }
    else if(power==1)
    {
        text4="you won the fire power!";
        p="fire";
    }
    else if(power==2)
    {
        text4="you won the color power!";
        p="color";
    }
    textColor(m_renderer,w/2+100-310,h/2-35+100,text4,1 ,35,text_color2);
    texture(m_renderer,(2*w)/3-50,h/3,"cross.png",50,50);
    SDL_RenderPresent(m_renderer);

    ifstream Score1("scores.txt");///updating score
    string score[100];
    int i=0;
    string x="";
    while(x!="-1")
    {
        Score1>>x;
        score[i]=x;
        i++;
    }
    int newScore;
    newScore=atoi(score[id].c_str())+point;
    score[id]=to_string(newScore);
    ofstream Score2;
    Score2.open("scores.txt");
    for(int m=0; m<i; m++)
    {
        Score2<<score[m]<<endl;
    }
        Score2.close();

    ifstream Power1(p+".txt");///updating power
    string POWER[100];
    i=0;
    x="";
    while(x!="-1")
    {
        Power1>>x;
        POWER[i]=x;
        i++;
    }
    int newPower;
    newPower=atoi(POWER[id].c_str())+1;
    POWER[id]=to_string(newPower);
    ofstream Power2;
    Power2.open(p+".txt");
    for(int m=0; m<i; m++)
    {
        Power2<<POWER[m]<<endl;
    }
        Power2.close();

    while(1)
    {
       if(SDL_PollEvent(&e))
       {
            if( e.type == SDL_MOUSEBUTTONDOWN )///returning to start menu
            {
                if(sound1==1)
                   Mix_PlayChannel(-1,Click,0);
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( (x >(2*w)/3-50 && x < (2*w)/3) && (y > h/3 && y < h/3+50 ) )
                    if(startMenu(m_renderer)==0)
                        return 0;
            }
        }
    }
}

int ballUP(SDL_Renderer *m_renderer, int point, int id)
{
    Mix_PlayChannel(-1,Applause,0);
    SDL_Event e;
    SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
    SDL_RenderClear( m_renderer );
    texture(m_renderer, 0,0,"mode.jpg",w,h);
    boxRGBA(m_renderer,w/3,h/3,(2*w)/3,(2*h)/3,99,123,159,255);///showing score and power
    SDL_Color text_color2={0, 0, 0};
    const char* text="out of margin...";
    const char* text1="your score: ";
    const char* text3;
    stringstream ss;
    ss<<point;
    string s;
    ss>>s;
    text3 =s.c_str() ;
    textColor(m_renderer,w/2-130,h/2-35-50,text,2 ,40,text_color2);
    textColor(m_renderer,w/2-100,h/2-35+100-50,text1,2 ,35,text_color2);
    textColor(m_renderer,w/2+100,h/2-35+100-50,text3,2 ,35,text_color2);
    const char* text4;
    int power;
    string p;
    power=rand()%3;
     if(power==0)
     {
        text4="you won the bomb power!";
        p="bomb";
     }
    else if(power==1)
    {
        text4="you won the fire power!";
        p="fire";
    }
    else if(power==2)
    {
        text4="you won the color power!";
        p="color";
    }
    textColor(m_renderer,w/2+100-310,h/2-35+100,text4,1 ,35,text_color2);
    texture(m_renderer,(2*w)/3-50,h/3,"cross.png",50,50);
    SDL_RenderPresent(m_renderer);

    ifstream Score1("scores.txt");///updating score
    string score[100];
    int i=0;
    string x="";
    while(x!="-1")
    {
        Score1>>x;
        score[i]=x;
        i++;
    }
    int newScore;
    newScore=atoi(score[id].c_str())+point;
    score[id]=to_string(newScore);
    ofstream Score2;
    Score2.open("scores.txt");
    for(int m=0; m<i; m++)
    {
        Score2<<score[m]<<endl;
    }
        Score2.close();

    ifstream Power1(p+".txt");///updating power
    string POWER[100];
    i=0;
    x="";
    while(x!="-1")
    {
        Power1>>x;
        POWER[i]=x;
        i++;
    }
    int newPower;
    newPower=atoi(POWER[id].c_str())+1;
    POWER[id]=to_string(newPower);
    ofstream Power2;
    Power2.open(p+".txt");
    for(int m=0; m<i; m++)
    {
        Power2<<POWER[m]<<endl;
    }
        Power2.close();

    while(1)
    {
       if(SDL_PollEvent(&e))
       {
            if( e.type == SDL_MOUSEBUTTONDOWN )///returning to start menu
            {
                if(sound1==1)
                  Mix_PlayChannel(-1,Click,0);
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( (x >(2*w)/3-50 && x < (2*w)/3) && (y > h/3 && y < h/3+50 ) )
                    if(startMenu(m_renderer)==0)
                        return 0;
            }
        }
    }
}

int main( int argc, char * argv[] )
{
    srand(time(NULL));
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO ;
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    Music=Mix_LoadMUS("music.mp3");
    Click=Mix_LoadWAV("click.wav");
    SwapColor=Mix_LoadWAV("swap.wav");
    Win=Mix_LoadWAV("win.wav");
    Explosion=Mix_LoadWAV("explosion.wav");
    Applause=Mix_LoadWAV("applause.wav");

    Uint32 WND_flags = SDL_WINDOW_SHOWN ;//SDL_WINDOW_BORDERLESS ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1280, 800, WND_flags, &m_window, &m_renderer );

    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// menu
 bool registerORlogin;

     texture(m_renderer, 0,0,"start3.jpg",w,h);
     boxRGBA (m_renderer, 426, 160, 853, 640, 13, 31, 52, 255);
     boxRGBA (m_renderer, 446, 256, 833, 352, 115, 117, 120, 255);
     boxRGBA (m_renderer, 446, 448, 833, 544, 115, 117, 120, 255);

     const char* text1="login";

     int x1_position=566;
     int y1_position=265;
     SDL_Color text_color={250, 250, 250};
     textColor(m_renderer,x1_position, y1_position, text1, 2, 65, text_color);

     const char* text2="register";

     int x2_position=536;
     int y2_position=457;
     textColor(m_renderer,x2_position, y2_position, text2, 2, 65, text_color);

     SDL_Event e;
      while(1)
      {
        SDL_PollEvent(&e);
        if( e.type == SDL_MOUSEBUTTONDOWN )///see if the user in logging in or registering
        {
            if(sound1==1)
                Mix_PlayChannel(-1,Click,0);
            int x, y;
            SDL_GetMouseState( &x, &y );

            if( (x > 446 && x < 833) && (y > 256 && y < 352) )
            {
               registerORlogin=1;  ///read info
            }

            if( (x > 446 && x < 833 ) && ( y > 448 && y < 544 ) )
            {
              registerORlogin=0;   ///write info
            }

            if( (x > 446 && x < 833 ) && ((y > 256 && y < 352) || (y > 448 && y < 544)))
            {
//////////////////////////////////////////////////////////////////////////////////////////////////register & login menu
                 boxRGBA (m_renderer, 426, 160, 853, 640, 13, 31, 52, 255);

                 boxRGBA (m_renderer, 446, 256, 833, 352, 115, 117, 120, 255);

                 boxRGBA (m_renderer, 446, 448, 833, 544, 115, 117, 120, 255);

                 const char* text3="Username:";

                 int x3_position=446;
                 int y3_position=190;
                 textColor(m_renderer,x3_position, y3_position, text3, 2, 40, text_color);

                 const char* text4="Password:";

                 int x4_position=446;
                 int y4_position=382;
                 textColor(m_renderer,x4_position, y4_position, text4, 2, 40, text_color);

                 SDL_RenderPresent( m_renderer );
                 break;
            }
        }
      }
///////////////////////////////////////////////////////////////////////////////////////////////////getting player info
int playerCounter=0;
string username,password;

while(1)
{
   if(SDL_PollEvent(&e))
   {
     if( e.type == SDL_MOUSEBUTTONDOWN )///user or pass
    {
        if(sound1==1)
                Mix_PlayChannel(-1,Click,0);
            int x, y;
            SDL_GetMouseState( &x, &y );
            const char* text1;

            while( (x > 446 && x < 833 ) && (y > 256 && y < 352) )///user
            {
                SDL_StartTextInput();
                SDL_Event e1;
                while( SDL_PollEvent( &e1 ) != 0 )
                {
                    if( e1.type == SDL_KEYDOWN )///key pressed
                    {
                        if( e1.key.keysym.sym == SDLK_BACKSPACE && username.length() > 0 )///delete char
                        {
                            SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
                            SDL_RenderClear( m_renderer );
                            texture(m_renderer, 0,0,"start3.jpg",w,h);
                            boxRGBA (m_renderer, 426, 160, 853, 640, 13, 31, 52, 255);
                            boxRGBA (m_renderer, 446, 256, 833, 352, 115, 117, 120, 255);
                            boxRGBA (m_renderer, 446, 448, 833, 544, 115, 117, 120, 255);
                            const char* text3="Username:";
                            int x3_position=446;
                            int y3_position=190;
                            textColor(m_renderer,x3_position, y3_position, text3, 2, 40, text_color);
                            const char* text4="Password:";
                            int x4_position=446;
                            int y4_position=382;
                            textColor(m_renderer,x4_position, y4_position, text4, 2, 40, text_color);

                            username.pop_back();
                            text1=username.c_str();
                            int x_position=456;
                            int y_position=262;
                            textColor(m_renderer,x_position,y_position,text1,2 ,24,text_color);
                            SDL_RenderPresent( m_renderer );
                        }
                       if(e1.key.keysym.sym == SDLK_RETURN)///next box & save data
                       {
                            x=450;
                            y=450;
                            SDL_StopTextInput();
                            if(registerORlogin==0)///register the user
                            {
                              ifstream Username1("username.txt");
                              string x;
                              while(x!="-1")
                              {
                                  Username1>>x;
                                  player[playerCounter].username=x;
                                  playerCounter++;
                              }
                              id=playerCounter-1;
                              ofstream Username2("username.txt");
                              for(int i=0; i<playerCounter-1 ; i++)
                              {
                                  Username2<<player[i].username+"\n";
                              }
                                Username2<<username+"\n";
                                Username2<<"-1\n";

                              ifstream Bomb1("bomb.txt");///initialize bomb in file
                              string bomb[100];
                              int i=0;
                              x="";
                              while(x!="-1")
                              {
                                  Bomb1>>x;
                                  bomb[i]=x;
                                  i++;
                              }

                              ofstream Bomb2("bomb.txt");
                              for(int i=0; i<playerCounter-1; i++)
                              {
                                 Bomb2<<bomb[i]+"\n";
                              }
                              Bomb2<<"0\n";
                              Bomb2<<"-1\n";

                              ifstream Color1("color.txt");///initialize color in file
                              string color[100];
                              i=0;
                              x="";
                              while(x!="-1")
                              {
                                  Color1>>x;
                                  color[i]=x;
                                  i++;
                              }

                              ofstream Color2("color.txt");
                              for(int i=0; i<playerCounter-1; i++)
                              {
                                 Color2<<color[i]+"\n";
                              }
                              Color2<<"0\n";
                              Color2<<"-1\n";

                              ifstream Fire1("fire.txt");///initialize fire in file
                              string fire[100];
                              i=0;
                              x="";
                              while(x!="-1")
                              {
                                  Fire1>>x;
                                  fire[i]=x;
                                  i++;
                              }

                              ofstream Fire2("fire.txt");
                              for(int i=0; i<playerCounter-1; i++)
                              {
                                 Fire2<<fire[i]+"\n";
                              }
                              Fire2<<"0\n";
                              Fire2<<"-1\n";

                              ifstream Score1("scores.txt");///initialize score in file
                              string score[100];
                              i=0;
                              x="";
                              while(x!="-1")
                              {
                                  Score1>>x;
                                  score[i]=x;
                                  i++;
                              }

                              ofstream Score2("scores.txt");
                              for(int i=0; i<playerCounter-1; i++)
                              {
                                 Score2<<score[i]+"\n";
                              }
                              Score2<<"0\n";
                              Score2<<"-1\n";

                                break;
                            }

                            else if(registerORlogin==1)///login the user
                            {
                               ifstream Username1("username.txt");
                               string x;
                               while(x!=username)
                               {
                                  Username1>>x;
                                  playerCounter++;
                               }
                               id=playerCounter-1;
                            }
                       }
                    }
                    if( e1.type == SDL_TEXTINPUT )///receive username
                    {
                        username += e1.text.text;

                        const char* text=username.c_str();
                        int x_position=456;
                        int y_position=262;
                        SDL_Color text_color = { 250, 250, 250};
                        textColor(m_renderer,x_position,y_position,text,2 ,24,text_color);

                    }
               }
           }
           while((x > 446 && x < 833 ) && (y > 448 && y < 544))///pass
           {
                SDL_StartTextInput();
                SDL_Event e1;
                while( SDL_PollEvent( &e1 ) != 0 )
                {
                    if( e1.type == SDL_KEYDOWN )
                    {
                       if( e1.key.keysym.sym == SDLK_BACKSPACE && password.length() > 0 )///delete char
                        {
                            SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
                            SDL_RenderClear( m_renderer );
                            texture(m_renderer, 0,0,"start3.jpg",w,h);
                            boxRGBA (m_renderer, 426, 160, 853, 640, 13, 31, 52, 255);
                            boxRGBA (m_renderer, 446, 256, 833, 352, 115, 117, 120, 255);
                            boxRGBA (m_renderer, 446, 448, 833, 544, 115, 117, 120, 255);
                            const char* text3="Username:";
                            int x3_position=446;
                            int y3_position=190;
                            textColor(m_renderer,x3_position, y3_position, text3, 2, 40, text_color);
                            const char* text4="Password:";
                            int x4_position=446;
                            int y4_position=382;
                            textColor(m_renderer,x4_position, y4_position, text4, 2, 40, text_color);

                            int x1_position=456;
                            int y1_position=262;
                            textColor(m_renderer,x1_position,y1_position,text1,2 ,24,text_color);

                            password.pop_back();
                            const char* text=password.c_str();
                            int x_position=456;
                            int y_position=454;
                            textColor(m_renderer,x_position,y_position,text,2 ,24,text_color);
                            SDL_RenderPresent( m_renderer );

                        }
                       if(e1.key.keysym.sym == SDLK_RETURN)///close box & save data
                       {
                            x=0;
                            y=0;
                            playerCounter=0;
                            SDL_StopTextInput();
                            if(registerORlogin==0)
                            {
                              ifstream Password1("password.txt");
                              string x;
                              while(x!="-1")
                              {
                                  Password1>>x;
                                  player[playerCounter].password=x;
                                  playerCounter++;
                              }
                              ofstream Password2("password.txt");
                              for(int i=0; i<playerCounter-1 ; i++)
                              {
                                  Password2<<player[i].password+"\n";
                              }
                                Password2<<password+"\n";
                                Password2<<"-1\n";
                                break;
                            }
                       }
                    }
                    if( e1.type == SDL_TEXTINPUT )///receive password
                    {
                        password += e1.text.text;

                        const char* text=password.c_str();
                        int x_position=456;
                        int y_position=454;
                        SDL_Color text_color = { 250, 250, 250};
                        textColor(m_renderer,x_position,y_position,text,2 ,24,text_color);
                    }
                }
           }
        break;
     }
   }
}
/////////////////////////////////////////////////////////////////////////////////setting menu
sound1=0;
music1=0;
const char* onORoff;

SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
SDL_RenderClear( m_renderer );
texture(m_renderer, 0,0,"start3.jpg",w,h);

    boxRGBA (m_renderer, 401, 110 , 878, 690, 13, 31, 52, 255);

    texture(m_renderer, 440, 165 , "music.png" , 70, 70);
     texture(m_renderer, 440, 305 , "sound.png" , 70, 70);
      texture(m_renderer, 430, 435, "help.png" , 90, 90);
       texture(m_renderer, 440, 585, "exit3.png" , 70, 70);

    boxRGBA (m_renderer, 525, 165 , 838, 235, 144, 168, 187, 255);
     boxRGBA (m_renderer, 525, 305 , 838, 375, 144, 168, 187, 255);
      boxRGBA (m_renderer, 525, 445 , 838, 515, 144, 168, 187, 255);
       boxRGBA (m_renderer, 525, 585 , 838, 655, 144, 168, 187, 255);
         texture(m_renderer, 828, 110, "cross.png" , 50, 50);

    rectangleRGBA (m_renderer,435 , 165 , 525, 235,144, 168, 187, 255);
     rectangleRGBA (m_renderer,435 , 305 , 525, 375,144, 168, 187, 255);
      rectangleRGBA (m_renderer,435 , 445 , 525, 515,144, 168, 187, 255);
       rectangleRGBA (m_renderer,435 , 585 , 525, 655,144, 168, 187, 255);

SDL_Color text_colorr = { 0, 0, 0};

const char* music="music";
 const char* sound="sound";
  const char* help="help";
   const char* exit="exit";

   textColor(m_renderer,535,175,music,2 ,30,text_colorr);
    textColor(m_renderer,535,315,sound,2 ,30,text_colorr);
     textColor(m_renderer,535,455,help,2 ,30,text_colorr);
      textColor(m_renderer,535,595,exit,2 ,30,text_colorr);

while(1)
{

 if(SDL_PollEvent(&e))
   {
     if( e.type == SDL_MOUSEBUTTONDOWN )///selecting a setting menu option
    {
        if(sound1==1)
                Mix_PlayChannel(-1,Click,0);
            int x, y;
            SDL_GetMouseState( &x, &y );

            if( (x>525) && (x<838)  && (y>165)  && (y<235))///music activation or deactivation
            {
                if(music1==0)
                {
                   music1=1;
                   Mix_PlayMusic(Music,0);
                }
                else if(music1==1)
                {
                   music1=0;
                   Mix_PauseMusic();
                }
            }
            if( (x>525) && (x<838)  && (y>305)  && (y<375))///sound activation or deactivation
            {
                if(sound1==0)
                {
                    sound1=1;
                    onORoff="sound on";
                }
                else if(sound1==1)
                {
                    sound1=0;
                    onORoff="sound off";
                }
                SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
                SDL_RenderClear( m_renderer );
                texture(m_renderer, 0,0,"start3.jpg",w,h);

                boxRGBA (m_renderer, 401, 110 , 878, 690, 13, 31, 52, 255);

                texture(m_renderer, 440, 165 , "music.png" , 70, 70);
                 texture(m_renderer, 440, 305 , "sound.png" , 70, 70);
                  texture(m_renderer, 430, 435, "help.png" , 90, 90);
                   texture(m_renderer, 440, 585, "exit3.png" , 70, 70);

                boxRGBA (m_renderer, 525, 165 , 838, 235, 144, 168, 187, 255);
                 boxRGBA (m_renderer, 525, 305 , 838, 375, 144, 168, 187, 255);
                  boxRGBA (m_renderer, 525, 445 , 838, 515, 144, 168, 187, 255);
                   boxRGBA (m_renderer, 525, 585 , 838, 655, 144, 168, 187, 255);
                    texture(m_renderer, 828, 110, "cross.png" , 50, 50);

                rectangleRGBA (m_renderer,435 , 165 , 525, 235,144, 168, 187, 255);
                 rectangleRGBA (m_renderer,435 , 305 , 525, 375,144, 168, 187, 255);
                  rectangleRGBA (m_renderer,435 , 445 , 525, 515,144, 168, 187, 255);
                   rectangleRGBA (m_renderer,435 , 585 , 525, 655,144, 168, 187, 255);

              const char* music="music";
               const char* sound="sound";
                const char* help="help";
                 const char* exit="exit";

                textColor(m_renderer,535,175,music,2 ,30,text_colorr);
                 textColor(m_renderer,535,315,sound,2 ,30,text_colorr);
                  textColor(m_renderer,535,455,help,2 ,30,text_colorr);
                   textColor(m_renderer,535,595,exit,2 ,30,text_colorr);

                textColor(m_renderer,535,20,onORoff,1 ,30,text_color);
                SDL_Delay(1000);
            }
            if( (x>525) && (x<838)  && (y>445)  && (y<515))///show help
            {
                texture(m_renderer, 0, 0, "help1.jpg", w, h);
                texture(m_renderer, w-100, h-100, "next.png", 50, 50);
                SDL_RenderPresent(m_renderer);
                while(1)
                {
                    if(SDL_PollEvent(&e))
                    {
                        if( e.type == SDL_MOUSEBUTTONDOWN )
                        {
                            if(sound1==1)
                              Mix_PlayChannel(-1,Click,0);
                            int x, y;
                            SDL_GetMouseState( &x, &y );

                           if( (x>w-100) && (x<w-100+50)  && (y>h-100)  && (y<h-100+50))
                               break;
                        }
                    }
               }
               texture(m_renderer, 0, 0, "help2.jpg", w, h);
               texture(m_renderer, w-100, h-100, "done.jpg", 50, 50);
               SDL_RenderPresent(m_renderer);
               while(1)
                {
                    if(SDL_PollEvent(&e))
                    {
                        if( e.type == SDL_MOUSEBUTTONDOWN )///return to setting menu
                        {
                            if(sound1==1)
                              Mix_PlayChannel(-1,Click,0);
                            int x, y;
                            SDL_GetMouseState( &x, &y );

                           if( (x>w-100) && (x<w-100+50)  && (y>h-100)  && (y<h-100+50))
                           {
                               SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
                               SDL_RenderClear( m_renderer );
                               texture(m_renderer, 0,0,"start3.jpg",w,h);

                              boxRGBA (m_renderer, 401, 110 , 878, 690, 13, 31, 52, 255);

                              texture(m_renderer, 440, 165 , "music.png" , 70, 70);
                              texture(m_renderer, 440, 305 , "sound.png" , 70, 70);
                              texture(m_renderer, 430, 435, "help.png" , 90, 90);
                              texture(m_renderer, 440, 585, "exit3.png" , 70, 70);

                             boxRGBA (m_renderer, 525, 165 , 838, 235, 144, 168, 187, 255);
                             boxRGBA (m_renderer, 525, 305 , 838, 375, 144, 168, 187, 255);
                             boxRGBA (m_renderer, 525, 445 , 838, 515, 144, 168, 187, 255);
                             boxRGBA (m_renderer, 525, 585 , 838, 655, 144, 168, 187, 255);
                             texture(m_renderer, 828, 110, "cross.png" , 50, 50);

                             rectangleRGBA (m_renderer,435 , 165 , 525, 235,144, 168, 187, 255);
                             rectangleRGBA (m_renderer,435 , 305 , 525, 375,144, 168, 187, 255);
                             rectangleRGBA (m_renderer,435 , 445 , 525, 515,144, 168, 187, 255);
                             rectangleRGBA (m_renderer,435 , 585 , 525, 655,144, 168, 187, 255);

                            textColor(m_renderer,535,175,music,2 ,30,text_colorr);
                            textColor(m_renderer,535,315,sound,2 ,30,text_colorr);
                            textColor(m_renderer,535,455,help,2 ,30,text_colorr);
                            textColor(m_renderer,535,595,exit,2 ,30,text_colorr);

                            break;

                           }
                        }
                    }
               }
            }
            if( (x>525) && (x<838)  && (y>585)  && (y<655))///exiting the game(closing the window)
            {
                return 0;
            }
            if( (x>828) && (x<878)  && (y>110)  && (y<160))///close setting and show start menu
            {
                break;
            }
    }
   }
}
/////////////////////////////////////////////////////////////////////////////////start menu
 if(startMenu(m_renderer)==0)///close the window if exit was pressed in start menu
 {
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;
 }
}

int map1 (SDL_Renderer *m_renderer)
{

      player[id].points=0;
      SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
      SDL_RenderClear( m_renderer );
      texture(m_renderer, 0,0,"mode.jpg",w,h);
      boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
      boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
      boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
      const char* resume="ball removal";
      const char* exit="time mode";
      SDL_Color text_color={255, 255, 255};
      textColor(m_renderer,w/3+100+20, h/3+55, resume, 2, 32, text_color);
      textColor(m_renderer,w/3+100+30, (2*h)/3-150+40, exit, 2, 32, text_color);
      SDL_RenderPresent( m_renderer );
      SDL_Event e;
      bool mode;

  while(1)///choose the mode
  {
     if(SDL_PollEvent(&e))
     {
            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                if(sound1==1)
                  Mix_PlayChannel(-1,Click,0);
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )
                {
                  mode=1;///limited balls
                  break;
                }
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )
                {
                   mode=0;///time mode
                   break;
                }
            }
     }
  }

    ifstream Bomb1("bomb.txt");///getting player power info
    string BOMB[100];
    int X=0;
    string x="";
    while(x!="-1")
    {
        Bomb1>>x;
        BOMB[X]=x;
        X++;
    }
    int bomb;
    bomb=atoi(BOMB[id].c_str());

    ifstream Fire1("fire.txt");
    string FIRE[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Fire1>>x;
        FIRE[X]=x;
        X++;
    }
    int fire;
    fire=atoi(FIRE[id].c_str());

    ifstream Color1("color.txt");
    string COLOR[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Color1>>x;
        COLOR[X]=x;
        X++;
    }
    int color;
    color=atoi(COLOR[id].c_str());
    bool cUSE=0;
    bool fUSE=0;
    bool bUSE=0;
    int fTIMES;

    ///special balls
    int count0=0;
    int count1=0;
    int count2=0;
    int count3=0;

    map1Ball ball[100];
    shoot shoot[100];
    ball[0].x=60;
    ball[0].y=160;
    ball[0].i=0;
    ball[0].color=rand()%4;
    int counter=0;
    int counter1=0;
    shoot[counter1].color=rand()%4;
    int counter2=0;
    const char* points, *POINTS="SCORE:";
    Uint32 Start = SDL_GetTicks();
    float secondsElapsed;

    int XX=0,YY=0;///read the curve
    ifstream x_curve("x1.txt");
    ifstream y_curve("y1.txt");
    double input=0,xx[1000],yy[1000];
    while(input!=-1)
    {
       x_curve>>input;
       xx[XX]=input;
       XX++;
    }
    input=0;
    while(input!=-1)
    {
       y_curve>>input;
       yy[YY]=input;
       YY++;
    }

while(1)
{
  double angle;
  SDL_RenderClear( m_renderer );
  texture(m_renderer, 0, 0, "map1.png", w, h);
  texture(m_renderer, 0, 500, "power.png", 100, 300);
  texture(m_renderer, w-600,-110,"blackHOLE1.png",200,200);
  circleRGBA (m_renderer, (2*w)/3-100+75,(2*h)/3-200+75, 100, 255, 255, 255, 255);

   if(bomb!=0)///show user what powers they own
        filledCircleRGBA (m_renderer, 50 , 550 , 40, 255, 255 ,255, 150);
   if(color!=0)
        filledCircleRGBA (m_renderer, 50 , 750 , 40, 255, 255 ,255, 150);
   if(fire!=0)
        filledCircleRGBA (m_renderer, 50 , 650 , 40, 255, 255 ,255, 150);

  int r,g,b;///determine the probable shooted ball color
          if(shoot[counter1].color==0)
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[counter1].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[counter1].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[counter1].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
          if(bUSE==1 || cUSE==1 || fUSE==1)
            filledCircleRGBA (m_renderer,(2*w)/3-100+75,(2*h)/3-200+75, 70, 0, 0, 0, 255);///ball power predictor
          else
            filledCircleRGBA (m_renderer,(2*w)/3-100+75,(2*h)/3-200+75, 70, r, g, b, 255);///ball color predictor

  if(SDL_PollEvent(&e))
  {
      if( e.type == SDL_MOUSEBUTTONDOWN )///shoot a ball if clicked
      {
            int x, y;
            SDL_GetMouseState( &x, &y );
            if( (x>w-50) && (x<w)  && (y>50)  && (y<100))///music activation or deactivation
            {
                if(music1==0)
                {
                   music1=1;
                   Mix_PlayMusic(Music,0);
                }
                else if(music1==1)
                {
                   music1=0;
                   Mix_PauseMusic();
                }
            }
            else if( (x>w-50) && (x<w)  && (y>0)  && (y<50))///sound activation or deactivation
            {
                if(sound1==0)
                    sound1=1;
                else if(sound1==1)
                    sound1=0;
            }
            else if( ((x-(50))*(x-(50)))+((y-(550))*(y-(550))) < 40*40 && bomb!=0 )///check if user is using powers
            {
                bUSE=1;
                bomb--;
            }
            else if( ((x-(50))*(x-(50)))+((y-(650))*(y-(650))) < 40*40 && fire!=0 )
            {
                fUSE=1;
                fire--;
                fTIMES=0;
            }
            else if( ((x-(50))*(x-(50)))+((y-(750))*(y-(750))) < 40*40 && color!=0 )
            {
                cUSE=1;
                color--;
            }
            else
            {
                if(cUSE==1)///shoot the powered ball
                {
                    cUSE=0;
                    shoot[counter1].x=(2*w)/3-100+75;
                    shoot[counter1].y=(2*h)/3-200+75;
                    shoot[counter1].color=4;
                    shoot[counter1].dx=double (x-((2*w)/3-100+75))/30;
                    shoot[counter1].dy=double (y-((2*h)/3-200+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(bUSE==1)
                {
                      bUSE=0;
                    shoot[counter1].x=(2*w)/3-100+75;
                    shoot[counter1].y=(2*h)/3-200+75;
                    shoot[counter1].color=5;
                    shoot[counter1].dx=double (x-((2*w)/3-100+75))/30;
                    shoot[counter1].dy=double (y-((2*h)/3-200+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(fUSE==1)
                {
                    fTIMES++;
                    if(fTIMES==3)
                     fUSE=0;
                    shoot[counter1].x=(2*w)/3-100+75;
                    shoot[counter1].y=(2*h)/3-200+75;
                    shoot[counter1].color=6;
                    shoot[counter1].dx=double (x-((2*w)/3-100+75))/30;
                    shoot[counter1].dy=double (y-((2*h)/3-200+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else///shoot the normal ball if not
                {
                    shoot[counter1].x=(2*w)/3-100+75;
                    shoot[counter1].y=(2*h)/3-200+75;
                    shoot[counter1+1].color=rand()%4;
                    shoot[counter1].dx=double (x-((2*w)/3-100+75))/30;
                    shoot[counter1].dy=double (y-((2*h)/3-200+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
            }
      }
     if( e.type == SDL_KEYDOWN )
     {
         if(e.key.keysym.sym == SDLK_ESCAPE)///pause menu
         {
            boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
            boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
            boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
            const char* resume="resume";
            const char* exit="exit";
            SDL_Color text_color={255, 255, 255};
            textColor(m_renderer,w/3+100+40, h/3+50, resume, 2, 40, text_color);
            textColor(m_renderer,w/3+100+80, (2*h)/3-150+35, exit, 2, 40, text_color);
            SDL_RenderPresent( m_renderer );

             while(1)
             {
                if(SDL_PollEvent(&e))
                {
                    if( e.type == SDL_MOUSEBUTTONDOWN )///exit or resume
                    {
                       int x, y;
                       SDL_GetMouseState( &x, &y );
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )///continue the game
                          break;
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )///exit and go to start menu
                          if(startMenu(m_renderer)==0)
                            return 0;
                   }
                }
             }
         }
         if(e.key.keysym.sym == SDLK_SPACE)///change the coming ball color
         {
            int previous;
            bool found;
            found=0;
            previous=shoot[counter1].color;
            while(shoot[counter1].color==previous || found==0)
            {
                found=0;
                shoot[counter1].color=rand()%4;
                for(int i=0; i<=counter; i++)
                    if(shoot[counter1].color==ball[i].color && ball[i].exist==1)
                    {
                        found=1;
                        break;
                    }
            }
            if(sound1==1)
               Mix_PlayChannel(-1,SwapColor,0);
         }
     }
     if( e.type == SDL_MOUSEMOTION )///change the shooter angle
     {
            int x, y;
            SDL_GetMouseState( &x, &y );
            angle=atan2(-(y-(h/2-100)),(x-(w/2-100)));
            lineRGBA (m_renderer, (2*w)/3-100+75,(2*h)/3-200+75, x, y, 255, 0, 0, 100);
            angledImage(m_renderer,"cannon.png" , (2*w)/3-100, (2*h)/3-200 , 150, 150,-(angle*180)/M_PI+90);
    }
   }
   angledImage(m_renderer,"cannon.png" ,(2*w)/3-100, (2*h)/3-200, 150, 150,-(angle*180)/M_PI+90);
   if( (((ball[counter].x-60)*(ball[counter].x-60))+((ball[counter].y-160)*(ball[counter].y-160))) > 3600)///check if its the time to send the new ball
    {
       counter++;
       ball[counter].x=60;
       ball[counter].y=160;
       ball[counter].i=0;
       if(count0%28==rand()%28)///decide if a ball is special or not
           ball[counter].color=11;
        else if(count1%28==rand()%28)
           ball[counter].color=12;
        else if(count0%14==rand()%14)
           ball[counter].color=7;
        else if(count1%14==rand()%14)
           ball[counter].color=8;
        else if(count2%14==rand()%14)
           ball[counter].color=9;
        else if(count3%14==rand()%14)
           ball[counter].color=10;
        else
           ball[counter].color=rand()%4;
    }

    for(int i=0; i<=counter; i++)///draw all sent balls on the curve
    {
        if((ball[i].x>w || ball[i].x<0 || ball[i].y<0 || ball[i].y>h)&&(ball[i].exist==1)&&mode==1)///check lose (ball mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();
            if (ballUP(m_renderer,player[id].points,id)==0)/// show win menu then go to start and if exit was pressed close the window
                return 0;
        }
        if(ball[i].y<0)
            ball[i].exist=0;

        for(int i=0; i<counter1; i++)///move the shooted ball
        {
         if(shoot[i].way==0)
         {
           shoot[i].x+=shoot[i].dx;
           shoot[i].y+=shoot[i].dy;

          int r,g,b;
          if(shoot[i].color==0)///determine the shooted ball color
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[i].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[i].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[i].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
          if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==4 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"cball1.png",60,60);///draw the shooted ball(color)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==5 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"bball1.png",60,60);///draw the shooted ball(bomb)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==6 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"fball1.png",60,60);///draw the shooted ball(fire)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) )
            filledCircleRGBA (m_renderer, shoot[i].x, shoot[i].y, 30, r, g, b, 255);///draw the shooted ball
         }
        }

//        ball[i].i+=0.001;
//        double t = ball[i].i;

        if(secondsElapsed>60 && mode==0)///check lose (time mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();
            if (timeUP(m_renderer,player[id].points,id)==0)///show win menu
                return 0;
        }
        int PEBI;///previous existing ball index

//         ball[i].Vx= ( (10*ball[i].x2) - (9*ball[i].x1) ) * pow( (1-t) , 8 ) +///x element of the curve
//                     ( (90*ball[i].x3) - (80*ball[i].x2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].x4) - (315*ball[i].x3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].x5) - (720*ball[i].x4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].x6) - (1050*ball[i].x5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].x7) - (840*ball[i].x6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].x8) - (360*ball[i].x7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].x9) - (90*ball[i].x8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].x10) - (10*ball[i].x9) ) * pow ( t , 8);
//
//         ball[i].Vy= ( (10*ball[i].y2) - (9*ball[i].y1) ) * pow( (1-t) , 8 ) +///y element of the curve
//                     ( (90*ball[i].y3) - (80*ball[i].y2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].y4) - (315*ball[i].y3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].y5) - (720*ball[i].y4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].y6) - (1050*ball[i].y5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].y7) - (840*ball[i].y6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].y8) - (360*ball[i].y7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].y9) - (90*ball[i].y8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].y10) - (10*ball[i].y9) ) * pow ( t , 8);

          for(int m=i+1; m<=counter; m++)///control balls waiting for other balls
          {
              if(ball[m].exist==0)
              {
                while(ball[m].exist==0)
                    m++;
                PEBI=m;
              }
            break;
          }
          if(ball[i+1].exist==1 && i!=counter)
            PEBI=i+1;
          if(counter==0)
            PEBI=0;

//             ball[i].x += ball[i].Vx/2500;
//             ball[i].y += ball[i].Vy/2500;
           if ( ((ball[i].x-ball[PEBI].x)*(ball[i].x-ball[PEBI].x))+((ball[i].y-ball[PEBI].y)*(ball[i].y-ball[PEBI].y))< 3630)///move the ball on the curve if its close to previous
           {
             ball[i].x=xx[ball[i].i];
             ball[i].y=yy[ball[i].i];
             ball[i].i++;
           }


        for (int i=counter ; i>=0 ; i--)///check if the balls are colliding
        {
//          if( ((ball[i].x-ball[i-1].x)*(ball[i].x-ball[i-1].x))+((ball[i].y-ball[i-1].y)*(ball[i].y-ball[i-1].y))< 3600)
//          {
//              double dx,dy,distance1,distance2;
//              distance1=sqrt(((ball[i-1].x-ball[i].x)*(ball[i-1].x-ball[i].x))+((ball[i-1].y-ball[i].y)*(ball[i-1].y-ball[i].y)));
//              distance2=60-distance1;
//              dx=distance2*cos(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              dy=distance2*sin(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              ball[i-1].x+=dx;
//              ball[i-1].y+=dy;

              for(int j=counter1-1; j>-1; j--)///check if the shooted ball collided with a ball on the curve and move it on the curve too
              {
                    int color;
                    bool simpleExplosion=0;
                    if( fabs (shoot[j].x-ball[i].x) < 30 && fabs (shoot[j].y-ball[i].y) < 30 && i!=counter && shoot[j].checked==0 && ball[i].exist==1)
                    {
                        if(ball[i].color==7 || ball[i].color==8 || ball[i].color==9 || ball[i].color==10)
                          ball[i].color-=7;
                        else if(ball[i].color==11)
                        {
                           ball[i].exist=0;
                           player[id].points++;
                           explosion (m_renderer,ball[i].x,ball[i].y);
                           if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                        }

                        else
                        {
                          for(int m=0; m<i; m++)
                          {
                            int n=m;
                            while(ball[m+1].exist==0)
                                m++;
                            ball[n].color=ball[m+1].color;
                          }
                          color=ball[i].color;
                          ball[i].color=shoot[j].color;
                          simpleExplosion=1;
                        }

                        shoot[j].checked=1;
                        shoot[j].way=1;

                      if(shoot[j].color==4)///if color power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                        for(int m=counter; m>=0; m--)
                          if(ball[m].color==color && ball[m].exist==1)
                            {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                            }
                      }

                      else if(shoot[j].color==6)///if fire power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                      }

                      else if(shoot[j].color==5)///if bomb power is being used
                      {
                          for(int m=i-3; m<=i+3; m++)
                            if(ball[m].exist==1 && m>=0 && m<=counter)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                      }

                     else///if no specific power is being used
                     {
                       int right,left,Rcounter=0,Lcounter=0;///check if they are more then or equal to three
                      right=i;
                      left=i;
                      Lcounter=0;
                      Rcounter=0;
                      while(1)
                      {
                          if( ( ball[right+1].color==ball[right].color ||  ball[right+1].color==12 )  && (right+1)!=counter && ball[right+1].exist==1)
                          {
                            Rcounter++;
                            right++;
                          }
                          else
                            break;
                      }
                      while(1)
                      {
                          if( ( ball[left-1].color==ball[left].color || ball[left-1].color==12 ) && (left-1)!=counter && ball[left-1].exist==1)
                          {
                            Lcounter++;
                            left--;
                          }
                          else
                            break;
                      }

                      if(Lcounter+Rcounter+1>=3 && simpleExplosion==1)///remove them if they were more then three
                      {
                          for(int m=i; m<=i+Rcounter; m++)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                          for(int m=i-1; m>=i-Lcounter; m--)
                          {
                             ball[m].exist=0;
                             player[id].points++;
                             explosion (m_renderer,ball[m].x,ball[m].y);
                             if(sound1==1)
                               Mix_PlayChannel(-1,Explosion,0);
                          }
                      }
                     }
                    }
                  //}
              }
          }
         int r,g,b;
         if(ball[i].color==0)///determine the ball on the way color
        {
            r=180;
            g=86;
            b=227;
            count0++;
        }
        if(ball[i].color==1)
        {
            r=86;
            g=213;
            b=227;
            count1++;

        }
        if(ball[i].color==2)
        {
            r=212;
            g=68;
            b=68;
            count2++;
        }
        if(ball[i].color==3)
        {
            r=232;
            g=132;
            b=26;
            count3++;
        }
        if(mode==1)///40=ball limit
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 && i<40 )
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }
        else
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 )///no ball limit if time mode is chosen
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }
      }

      Uint32 End = SDL_GetTicks();///timer
      secondsElapsed = (End - Start) / 1000;
      stringstream tt;
      tt<<secondsElapsed;
      string t;
      tt>>t;
      const char *time;
      const char *TIME="/60";
      time =t.c_str();
      SDL_Color text_color = { 250, 250, 250};
      if(mode==0)
      {
        textColor(m_renderer,150,700,time,1 ,24,text_color);
        textColor(m_renderer,200,700,TIME,1 ,24,text_color);
      }

  stringstream ss;///show player score
  ss<<player[id].points;
  string s;
  ss>>s;
  points =s.c_str();
  textColor(m_renderer,150,750,POINTS,1 ,24,text_color);
  textColor(m_renderer,250,750,points,1 ,24,text_color);

  if(sound1==1)
    texture(m_renderer,w-50,0,"soundON.png",50,50);
  else
    texture(m_renderer,w-50,0,"soundOFF.png",50,50);
  if(music1==1)
    texture(m_renderer,w-50,50,"musicON.png",50,50);
  else
    texture(m_renderer,w-50,50,"musicOFF.png",50,50);

 SDL_RenderPresent( m_renderer );

 }
}

int map3 (SDL_Renderer *m_renderer)
{
      player[id].points=0;
      SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
      SDL_RenderClear( m_renderer );
      texture(m_renderer, 0,0,"mode.jpg",w,h);
      boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
      boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
      boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
      const char* resume="ball removal";
      const char* exit="time mode";
      SDL_Color text_color={255, 255, 255};
      textColor(m_renderer,w/3+100+20, h/3+55, resume, 2, 32, text_color);
      textColor(m_renderer,w/3+100+30, (2*h)/3-150+40, exit, 2, 32, text_color);
      SDL_RenderPresent( m_renderer );
      SDL_Event e;
      bool mode;

  while(1)///choose the mode
  {
     if(SDL_PollEvent(&e))
     {
            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                if(sound1==1)
                   Mix_PlayChannel(-1,Click,0);
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )
                {
                  mode=1;///limited balls
                  break;
                }
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )
                {
                   mode=0;///time mode
                   break;
                }
            }
     }
  }

    ifstream Bomb1("bomb.txt");///getting player power info
    string BOMB[100];
    int X=0;
    string x="";
    while(x!="-1")
    {
        Bomb1>>x;
        BOMB[X]=x;
        X++;
    }
    int bomb;
    bomb=atoi(BOMB[id].c_str());

    ifstream Fire1("fire.txt");
    string FIRE[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Fire1>>x;
        FIRE[X]=x;
        X++;
    }
    int fire;
    fire=atoi(FIRE[id].c_str());

    ifstream Color1("color.txt");
    string COLOR[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Color1>>x;
        COLOR[X]=x;
        X++;
    }

    int color;
    color=atoi(COLOR[id].c_str());

    bool cUSE=0;
    bool fUSE=0;
    bool bUSE=0;
    int fTIMES;

    ///special balls
    int count0=0;
    int count1=0;
    int count2=0;
    int count3=0;

    map3Ball ball[100];
    shoot shoot[100];
    ball[0].x=60;
    ball[0].y=160;
    ball[0].i=0;
    ball[0].color=rand()%4;
    int counter=0;
    int counter1=0;
    shoot[counter1].color=rand()%4;
    int counter2=0;
    const char* points, *POINTS="SCORE:";
    Uint32 Start = SDL_GetTicks();
    float secondsElapsed;

    int XX=0,YY=0;///read the curve
    ifstream x_curve("x3.txt");
    ifstream y_curve("y3.txt");
    double input=0,xx[1000],yy[1000];
    while(input!=-1)
    {
       x_curve>>input;
       xx[XX]=input;
       XX++;
    }
    input=0;
    while(input!=-1)
    {
       y_curve>>input;
       yy[YY]=input;
       YY++;
    }


while(1)
{
  double angle;
  SDL_RenderClear( m_renderer );
  texture(m_renderer, 0, 0, "map3.png", w, h);
  texture(m_renderer, 0, h-300, "power.png", 100, 300);
  texture(m_renderer, w-340,-90,"blackHOLE1.png",200,200);
  circleRGBA (m_renderer, w/2-100+75, h/2-100+75, 100, 255, 255, 255, 255);

   if(bomb!=0)///show user what powers they own
        filledCircleRGBA (m_renderer, 50 , 550 , 40, 255, 255 ,255, 150);
   if(color!=0)
        filledCircleRGBA (m_renderer, 50 , 750 , 40, 255, 255 ,255, 150);
   if(fire!=0)
        filledCircleRGBA (m_renderer, 50 , 650 , 40, 255, 255 ,255, 150);

  int r,g,b;///determine the probable shooted ball color
          if(shoot[counter1].color==0)
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[counter1].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[counter1].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[counter1].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
          if(bUSE==1 || cUSE==1 || fUSE==1)
            filledCircleRGBA (m_renderer,w/2-100+75, h/2-100+75, 70, 0, 0, 0, 255);///ball power predictor
          else
            filledCircleRGBA (m_renderer,w/2-100+75, h/2-100+75, 70, r, g, b, 255);///ball color predictor

  if(SDL_PollEvent(&e))
  {
      if( e.type == SDL_MOUSEBUTTONDOWN )///shoot a ball if clicked
      {
            int x, y;
            SDL_GetMouseState( &x, &y );
            if( (x>w-50) && (x<w)  && (y>350)  && (y<400))///music activation or deactivation
            {
                if(music1==0)
                {
                   music1=1;
                   Mix_PlayMusic(Music,0);
                }
                else if(music1==1)
                {
                   music1=0;
                   Mix_PauseMusic();
                }
            }
            else if( (x>w-50) && (x<w)  && (y>300)  && (y<350))///sound activation or deactivation
            {
                if(sound1==0)
                    sound1=1;
                else if(sound1==1)
                    sound1=0;
            }
            else if( ((x-(50))*(x-(50)))+((y-(550))*(y-(550))) < 40*40 && bomb!=0 )///check if user is using powers
            {
                bUSE=1;
                bomb--;
            }
            else if( ((x-(50))*(x-(50)))+((y-(650))*(y-(650))) < 40*40 && fire!=0 )
            {
                fUSE=1;
                fire--;
                fTIMES=0;
            }
            else if( ((x-(50))*(x-(50)))+((y-(750))*(y-(750))) < 40*40 && color!=0 )
            {
                cUSE=1;
                color--;
            }
            else
            {
                if(cUSE==1)///shoot the powered ball
                {
                    cUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=4;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(bUSE==1)
                {
                      bUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=5;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(fUSE==1)
                {
                    fTIMES++;
                    if(fTIMES==3)
                     fUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=6;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else///shoot the normal ball if not
                {
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1+1].color=rand()%4;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
            }
      }
     if( e.type == SDL_KEYDOWN )
     {
         if(e.key.keysym.sym == SDLK_ESCAPE)///pause menu
         {
            boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
            boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
            boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
            const char* resume="resume";
            const char* exit="exit";
            SDL_Color text_color={255, 255, 255};
            textColor(m_renderer,w/3+100+40, h/3+50, resume, 2, 40, text_color);
            textColor(m_renderer,w/3+100+80, (2*h)/3-150+35, exit, 2, 40, text_color);
            SDL_RenderPresent( m_renderer );

             while(1)
             {
                if(SDL_PollEvent(&e))
                {
                    if( e.type == SDL_MOUSEBUTTONDOWN )///exit or resume
                    {
                       int x, y;
                       SDL_GetMouseState( &x, &y );
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )
                          break;
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )
                          if(startMenu(m_renderer)==0)
                            return 0;
                   }
                }
             }
         }
         if(e.key.keysym.sym == SDLK_SPACE)///change the coming ball color
         {
            int previous;
            bool found;
            found=0;
            previous=shoot[counter1].color;
            while(shoot[counter1].color==previous || found==0)
            {
                found=0;
                shoot[counter1].color=rand()%4;
                for(int i=0; i<=counter; i++)
                    if(shoot[counter1].color==ball[i].color && ball[i].exist==1)
                    {
                        found=1;
                        break;
                    }
            }
            if(sound1==1)
               Mix_PlayChannel(-1,SwapColor,0);
         }
     }
     if( e.type == SDL_MOUSEMOTION )///change the shooter angle
     {
            int x, y;
            SDL_GetMouseState( &x, &y );
            angle=atan2(-(y-(h/2-100)),(x-(w/2-100)));
            lineRGBA (m_renderer, w/2-100+75,h/2-100+75, x, y, 255, 0, 0, 100);
            angledImage(m_renderer,"cannon.png" , w/2-100, h/2-100, 150, 150,-(angle*180)/M_PI+90);
    }
   }
   angledImage(m_renderer,"cannon.png" , w/2-100, h/2-100, 150, 150,-(angle*180)/M_PI+90);
   if( (((ball[counter].x-60)*(ball[counter].x-60))+((ball[counter].y-160)*(ball[counter].y-160))) > 3600)///check if its the time to send the new ball
    {
       counter++;
       ball[counter].x=60;
       ball[counter].y=160;
       ball[counter].i=0;
       if(count0%28==rand()%28)///decide if a ball is special or not
           ball[counter].color=11;
        else if(count1%28==rand()%28)
           ball[counter].color=12;
        else if(count0%14==rand()%14)
           ball[counter].color=7;
        else if(count1%14==rand()%14)
           ball[counter].color=8;
        else if(count2%14==rand()%14)
           ball[counter].color=9;
        else if(count3%14==rand()%14)
           ball[counter].color=10;
        else
           ball[counter].color=rand()%4;
    }

    for(int i=0; i<=counter; i++)///draw all sent balls on the curve
    {
        if((ball[i].x>w || ball[i].x<0 || ball[i].y<0 || ball[i].y>h)&&(ball[i].exist==1)&&mode==1)///check lose (ball mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();

           if (ballUP(m_renderer,player[id].points,id)==0)
                return 0;
        }
        if(ball[i].y<0)
            ball[i].exist=0;

        for(int i=0; i<counter1; i++)///move the shooted ball
        {
         if(shoot[i].way==0)
         {
           shoot[i].x+=shoot[i].dx;
           shoot[i].y+=shoot[i].dy;

          int r,g,b;
          if(shoot[i].color==0)///determine the shooted ball color
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[i].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[i].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[i].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
         if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==4 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"cball1.png",60,60);///draw the shooted ball(color)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==5 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"bball1.png",60,60);///draw the shooted ball(bomb)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==6 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"fball1.png",60,60);///draw the shooted ball(fire)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) )
            filledCircleRGBA (m_renderer, shoot[i].x, shoot[i].y, 30, r, g, b, 255);///draw the shooted ball
         }
        }

//        ball[i].i+=0.001;
//        double t = ball[i].i;

        if(secondsElapsed>60 && mode==0)///check lose (time mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();

            if (timeUP(m_renderer,player[id].points,id)==0)
                return 0;
        }
        int PEBI;///previous existing ball index

//         ball[i].Vx= ( (10*ball[i].x2) - (9*ball[i].x1) ) * pow( (1-t) , 8 ) +///x element of the curve
//                     ( (90*ball[i].x3) - (80*ball[i].x2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].x4) - (315*ball[i].x3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].x5) - (720*ball[i].x4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].x6) - (1050*ball[i].x5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].x7) - (840*ball[i].x6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].x8) - (360*ball[i].x7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].x9) - (90*ball[i].x8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].x10) - (10*ball[i].x9) ) * pow ( t , 8);
//
//         ball[i].Vy= ( (10*ball[i].y2) - (9*ball[i].y1) ) * pow( (1-t) , 8 ) +///y element of the curve
//                     ( (90*ball[i].y3) - (80*ball[i].y2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].y4) - (315*ball[i].y3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].y5) - (720*ball[i].y4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].y6) - (1050*ball[i].y5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].y7) - (840*ball[i].y6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].y8) - (360*ball[i].y7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].y9) - (90*ball[i].y8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].y10) - (10*ball[i].y9) ) * pow ( t , 8);

          for(int m=i+1; m<=counter; m++)///control balls waiting for other balls
          {
              if(ball[m].exist==0)
              {
                while(ball[m].exist==0)
                    m++;
                PEBI=m;
              }
            break;
          }
          if(ball[i+1].exist==1 && i!=counter)
            PEBI=i+1;
          if(counter==0)
            PEBI=0;

//             ball[i].x += ball[i].Vx/2500;
//             ball[i].y += ball[i].Vy/2500;
           if ( ((ball[i].x-ball[PEBI].x)*(ball[i].x-ball[PEBI].x))+((ball[i].y-ball[PEBI].y)*(ball[i].y-ball[PEBI].y))< 3630)///move the ball on the curve if its close to previous
           {
             ball[i].x=xx[ball[i].i];
             ball[i].y=yy[ball[i].i];
             ball[i].i++;
           }

        for (int i=counter ; i>=0 ; i--)///check if the balls are colliding
        {
//          if( ((ball[i].x-ball[i-1].x)*(ball[i].x-ball[i-1].x))+((ball[i].y-ball[i-1].y)*(ball[i].y-ball[i-1].y))< 3600)
//          {
//              double dx,dy,distance1,distance2;
//              distance1=sqrt(((ball[i-1].x-ball[i].x)*(ball[i-1].x-ball[i].x))+((ball[i-1].y-ball[i].y)*(ball[i-1].y-ball[i].y)));
//              distance2=60-distance1;
//              dx=distance2*cos(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              dy=distance2*sin(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              ball[i-1].x+=dx;
//              ball[i-1].y+=dy;

              for(int j=counter1-1; j>-1; j--)///check if the shooted ball collided with a ball on the curve and move it on the curve too
              {
                    int color;
                    bool simpleExplosion=0;
                    if( fabs (shoot[j].x-ball[i].x) < 30 && fabs (shoot[j].y-ball[i].y) < 30 && i!=counter && shoot[j].checked==0 && ball[i].exist==1)
                    {
                        if(ball[i].color==7 || ball[i].color==8 || ball[i].color==9 || ball[i].color==10)
                         ball[i].color-=7;
                        else if(ball[i].color==11)
                        {
                           ball[i].exist=0;
                           player[id].points++;
                           explosion (m_renderer,ball[i].x,ball[i].y);
                           if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                        }

                       else
                       {
                          for(int m=0; m<i; m++)
                          {
                            int n=m;
                            while(ball[m+1].exist==0)
                                m++;
                            ball[n].color=ball[m+1].color;
                          }
                          color=ball[i].color;
                          ball[i].color=shoot[j].color;
                          simpleExplosion=1;
                       }

                        shoot[j].checked=1;
                        shoot[j].way=1;

                      if(shoot[j].color==4)///if color power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                         for(int m=counter; m>=0; m--)
                         if(ball[m].color==color && ball[m].exist==1)
                         {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                        }
                      }

                      else if(shoot[j].color==6)///if fire power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                      }

                      else if(shoot[j].color==5)///if bomb power is being used
                      {
                          for(int m=i-3; m<=i+3; m++)
                            if(ball[m].exist==1 && m>=0 && m<=counter)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                      }

                    else///if no specific power is being used
                    {
                      int right,left,Rcounter=0,Lcounter=0;///check if they are more then or equal to three
                      right=i;
                      left=i;
                      Lcounter=0;
                      Rcounter=0;
                      while(1)
                      {
                          if( ( ball[right+1].color==ball[right].color || ball[right+1].color==12 ) && (right+1)!=counter && ball[right+1].exist==1)
                          {
                            Rcounter++;
                            right++;
                          }
                          else
                            break;
                      }
                      while(1)
                      {
                          if( ( ball[left-1].color==ball[left].color || ball[left-1].color==12 ) && (left-1)!=counter && ball[left-1].exist==1)
                          {
                            Lcounter++;
                            left--;
                          }
                          else
                            break;
                      }

                      if(Lcounter+Rcounter+1>=3 && simpleExplosion==1)///remove them if they were more then three
                      {
                          for(int m=i; m<=i+Rcounter; m++)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                          for(int m=i-1; m>=i-Lcounter; m--)
                          {
                             ball[m].exist=0;
                             player[id].points++;
                             explosion (m_renderer,ball[m].x,ball[m].y);
                             if(sound1==1)
                               Mix_PlayChannel(-1,Explosion,0);
                          }
                       }
                      }
                    }
                  //}
              }
          }
         int r,g,b;
         if(ball[i].color==0)///determine the ball on the way color
        {
            r=180;
            g=86;
            b=227;
            count0++;
        }
        if(ball[i].color==1)
        {
            r=86;
            g=213;
            b=227;
            count1++;

        }
        if(ball[i].color==2)
        {
            r=212;
            g=68;
            b=68;
            count2++;
        }
        if(ball[i].color==3)
        {
            r=232;
            g=132;
            b=26;
            count3++;
        }
        if(mode==1)///40=ball limit
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 && i<40 )
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }
        else
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 )///no ball limit if time mode is chosen
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }

      }

      Uint32 End = SDL_GetTicks();///timer
      secondsElapsed = (End - Start) / 1000;
      stringstream tt;
      tt<<secondsElapsed;
      string t;
      tt>>t;
      const char *time;
      const char *TIME="/60";
      time =t.c_str();
      SDL_Color text_color = { 250, 250, 250};
      if(mode==0)
      {
        textColor(m_renderer,150,700,time,1 ,24,text_color);
        textColor(m_renderer,200,700,TIME,1 ,24,text_color);
      }

  stringstream ss;///show player score
  ss<<player[id].points;
  string s;
  ss>>s;
  points =s.c_str();
  textColor(m_renderer,w-200+50,100-50,POINTS,1 ,24,text_color);
  textColor(m_renderer,w-100+50,100-50,points,1 ,24,text_color);

  if(sound1==1)
    texture(m_renderer,w-50,300,"soundON.png",50,50);
  else
    texture(m_renderer,w-50,300,"soundOFF.png",50,50);
  if(music1==1)
    texture(m_renderer,w-50,350,"musicON.png",50,50);
  else
    texture(m_renderer,w-50,350,"musicOFF.png",50,50);

 SDL_RenderPresent( m_renderer );

 }
}

int map2 (SDL_Renderer *m_renderer)
{
      player[id].points=0;
      SDL_SetRenderDrawColor( m_renderer, 11, 62, 121, 255 );
      SDL_RenderClear( m_renderer );
      texture(m_renderer, 0,0,"mode.jpg",w,h);
      boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
      boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
      boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
      const char* resume="ball removal";
      const char* exit="time mode";
      SDL_Color text_color={255, 255, 255};
      textColor(m_renderer,w/3+100+20, h/3+55, resume, 2, 32, text_color);
      textColor(m_renderer,w/3+100+30, (2*h)/3-150+40, exit, 2, 32, text_color);
      SDL_RenderPresent( m_renderer );
      SDL_Event e;
      bool mode;

  while(1)///choose the mode
  {
     if(SDL_PollEvent(&e))
     {
            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                if(sound1==1)
                   Mix_PlayChannel(-1,Click,0);
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )
                {
                  mode=1;///limited balls
                  break;
                }
                if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )
                {
                   mode=0;///time mode
                   break;
                }
            }
    }
  }

  ifstream Bomb1("bomb.txt");///getting player power info
    string BOMB[100];
    int X=0;
    string x="";
    while(x!="-1")
    {
        Bomb1>>x;
        BOMB[X]=x;
        X++;
    }
    int bomb;
    bomb=atoi(BOMB[id].c_str());

    ifstream Fire1("fire.txt");
    string FIRE[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Fire1>>x;
        FIRE[X]=x;
        X++;
    }
    int fire;
    fire=atoi(FIRE[id].c_str());

    ifstream Color1("color.txt");
    string COLOR[100];
    X=0;
    x="";
    while(x!="-1")
    {
        Color1>>x;
        COLOR[X]=x;
        X++;
    }
    int color;
    color=atoi(COLOR[id].c_str());

    bool cUSE=0;
    bool fUSE=0;
    bool bUSE=0;
    int fTIMES;

    ///special balls
    int count0=0;
    int count1=0;
    int count2=0;
    int count3=0;

    map2Ball ball[100];
    shoot shoot[100];
    ball[0].x=60;
    ball[0].y=160;
    ball[0].i=0;
    ball[0].color=rand()%4;
    int counter=0;
    int counter1=0;
    shoot[counter1].color=rand()%4;
    int counter2=0;
    const char* points, *POINTS="SCORE:";
    Uint32 Start = SDL_GetTicks();
    float secondsElapsed;

    int XX=0,YY=0;///read the curve
    ifstream x_curve("x2.txt");
    ifstream y_curve("y2.txt");
    double input=0,xx[1000],yy[1000];
    while(input!=-1)
    {
       x_curve>>input;
       xx[XX]=input;
       XX++;
    }
    input=0;
    while(input!=-1)
    {
       y_curve>>input;
       yy[YY]=input;
       YY++;
    }


while(1)
{
  double angle;
  SDL_RenderClear( m_renderer );
  texture(m_renderer, 0, 0, "map2.png", w, h);
  texture(m_renderer, w-100, h-400, "power.png", 100, 300);
  texture(m_renderer, -50,h-270,"blackHOLE1.png",200,200);
  circleRGBA (m_renderer, w/2-100+75, h/2-100+75, 100, 255, 255, 255, 255);

   if(bomb!=0)///show user what powers they own
        filledCircleRGBA (m_renderer, w-50 , h-400+50 , 40, 255, 255 ,255, 150);
   if(color!=0)
        filledCircleRGBA (m_renderer, w-50 , h-400+250 , 40, 255, 255 ,255, 150);
   if(fire!=0)
        filledCircleRGBA (m_renderer, w-50 , h-400+150 , 40, 255, 255 ,255, 150);

  int r,g,b;///determine the probable shooted ball color
          if(shoot[counter1].color==0)
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[counter1].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[counter1].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[counter1].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
          if(bUSE==1 || cUSE==1 || fUSE==1)
            filledCircleRGBA (m_renderer,w/2-100+75, h/2-100+75, 70, 0, 0, 0, 255);///ball power predictor
          else
            filledCircleRGBA (m_renderer,w/2-100+75, h/2-100+75, 70, r, g, b, 255);///ball color predictor

  if(SDL_PollEvent(&e))
  {
      if( e.type == SDL_MOUSEBUTTONDOWN )///shoot a ball if clicked
      {
            int x, y;
            SDL_GetMouseState( &x, &y );
            if( (x>w-50) && (x<w)  && (y>250)  && (y<300))///music activation or deactivation
            {
                if(music1==0)
                {
                   music1=1;
                   Mix_PlayMusic(Music,0);
                }
                else if(music1==1)
                {
                   music1=0;
                   Mix_PauseMusic();
                }
            }
            else if( (x>w-50) && (x<w)  && (y>200)  && (y<250))///sound activation or deactivation
            {
                if(sound1==0)
                    sound1=1;
                else if(sound1==1)
                    sound1=0;
            }
            else if( ((x-(w-50))*(x-(w-50)))+((y-(h-400+50))*(y-(h-400+50))) < 40*40 && bomb!=0 )///check if user is using powers
            {
                bUSE=1;
                bomb--;
            }
            else if( ((x-(w-50))*(x-(w-50)))+((y-(h-400+150))*(y-(h-400+150))) < 40*40 && fire!=0 )
            {
                fUSE=1;
                fire--;
                fTIMES=0;
            }
            else if( ((x-(w-50))*(x-(w-50)))+((y-(h-400+250))*(y-(h-400+250))) < 40*40 && color!=0 )
            {
                cUSE=1;
                color--;
            }
            else
            {
                if(cUSE==1)///shoot the powered ball
                {
                    cUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=4;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(bUSE==1)
                {
                      bUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=5;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else if(fUSE==1)
                {
                    fTIMES++;
                    if(fTIMES==3)
                     fUSE=0;
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1].color=6;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
                else///shoot the normal ball if not
                {
                    shoot[counter1].x=w/2-100+75;
                    shoot[counter1].y=h/2-100+75;
                    shoot[counter1+1].color=rand()%4;
                    shoot[counter1].dx=double (x-(w/2-100+75))/30;
                    shoot[counter1].dy=double (y-(h/2-100+75))/30;
                    counter1++;
                    if(sound1==1)
                      Mix_PlayChannel(-1,Click,0);
                }
            }
     }
     if( e.type == SDL_KEYDOWN )
     {
         if(e.key.keysym.sym == SDLK_ESCAPE)///pause menu
         {
            boxRGBA(m_renderer, w/3, h/3, (2*w)/3, (2*h)/3, 150, 150, 150, 255);
            boxRGBA(m_renderer, w/3+100, h/3+50, (2*w)/3-100, (2*h)/3-150, 50, 50, 50, 255);
            boxRGBA(m_renderer, w/3+100, (2*h)/3-150+35, (2*w)/3-100, (2*h)/3-50, 50, 50, 50, 255);
            const char* resume="resume";
            const char* exit="exit";
            SDL_Color text_color={255, 255, 255};
            textColor(m_renderer,w/3+100+40, h/3+50, resume, 2, 40, text_color);
            textColor(m_renderer,w/3+100+80, (2*h)/3-150+35, exit, 2, 40, text_color);
            SDL_RenderPresent( m_renderer );

             while(1)
             {
                if(SDL_PollEvent(&e))
                {
                    if( e.type == SDL_MOUSEBUTTONDOWN )///exit or resume
                    {
                       int x, y;
                       SDL_GetMouseState( &x, &y );
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > h/3+50 && y < (2*h)/3-150) )
                          break;
                       if( (x > w/3+100 && x < (2*w)/3-100) && (y > (2*h)/3-150+35 && y < (2*h)/3-50 ) )
                          if(startMenu(m_renderer)==0)
                            return 0;
                   }
                }
             }
         }
         if(e.key.keysym.sym == SDLK_SPACE)///change the coming ball color
         {
            int previous;
            bool found;
            found=0;
            previous=shoot[counter1].color;
            while(shoot[counter1].color==previous || found==0)
            {
                found=0;
                shoot[counter1].color=rand()%4;
                for(int i=0; i<=counter; i++)
                    if(shoot[counter1].color==ball[i].color && ball[i].exist==1)
                    {
                        found=1;
                        break;
                    }
            }
            if(sound1==1)
               Mix_PlayChannel(-1,SwapColor,0);
         }
     }
     if( e.type == SDL_MOUSEMOTION )///change the shooter angle
     {
            int x, y;
            SDL_GetMouseState( &x, &y );
            angle=atan2(-(y-(h/2-100)),(x-(w/2-100)));
            lineRGBA (m_renderer, w/2-100+75,h/2-100+75, x, y, 255, 0, 0, 100);
            angledImage(m_renderer,"cannon.png" , w/2-100, h/2-100, 150, 150,-(angle*180)/M_PI+90);
    }
   }
   angledImage(m_renderer,"cannon.png" , w/2-100, h/2-100, 150, 150,-(angle*180)/M_PI+90);
   if( (((ball[counter].x-60)*(ball[counter].x-60))+((ball[counter].y-160)*(ball[counter].y-160))) > 3600)///check if its the time to send the new ball
    {
       counter++;
       ball[counter].x=60;
       ball[counter].y=160;
       ball[counter].i=0;
       if(count0%28==rand()%28)///decide if a ball is special or not
           ball[counter].color=11;
        else if(count1%28==rand()%28)
           ball[counter].color=12;
        else if(count0%14==rand()%14)
           ball[counter].color=7;
        else if(count1%14==rand()%14)
           ball[counter].color=8;
        else if(count2%14==rand()%14)
           ball[counter].color=9;
        else if(count3%14==rand()%14)
           ball[counter].color=10;
        else
           ball[counter].color=rand()%4;
    }

    for(int i=0; i<=counter; i++)///draw all sent balls on the curve
    {
        if((ball[i].x>w || ball[i].x<50 || ball[i].y<0 || ball[i].y>h)&&(ball[i].exist==1) && mode==1)///check lose (ball mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();

            if (ballUP(m_renderer,player[id].points,id)==0)
                return 0;
        }
        if(ball[i].x<50)
            ball[i].exist=0;

        for(int i=0; i<counter1; i++)///move the shooted ball
        {
         if(shoot[i].way==0)
         {
           shoot[i].x+=shoot[i].dx;
           shoot[i].y+=shoot[i].dy;

          int r,g,b;
          if(shoot[i].color==0)///determine the shooted ball color
          {
            r=180;
            g=86;
            b=227;
          }
          if(shoot[i].color==1)
          {
            r=86;
            g=213;
            b=227;

          }
          if(shoot[i].color==2)
          {
            r=212;
            g=68;
            b=68;
          }
          if(shoot[i].color==3)
          {
            r=232;
            g=132;
            b=26;
          }
         if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==4 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"cball1.png",60,60);///draw the shooted ball(color)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==5 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"bball1.png",60,60);///draw the shooted ball(bomb)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) && shoot[i].color==6 )
            texture (m_renderer, shoot[i].x-30, shoot[i].y-30,"fball1.png",60,60);///draw the shooted ball(fire)
          else if( (shoot[i].x>0 && shoot[i].x<w) && (shoot[i].y>0 && shoot[i].y<h) )
            filledCircleRGBA (m_renderer, shoot[i].x, shoot[i].y, 30, r, g, b, 255);///draw the shooted ball
         }
        }

//        ball[i].i+=0.001;
//        double t = ball[i].i;

        if(secondsElapsed>60 && mode==0)///check lose (time mode)
        {
            BOMB[id]=to_string(bomb);///update bomb status
            ofstream Bomb2;
            Bomb2.open("bomb.txt");
            for(int m=0; m<X; m++)
            {
              Bomb2<<BOMB[m]<<endl;
            }
            Bomb2.close();

            COLOR[id]=to_string(color);///update color status
            ofstream Color2;
            Color2.open("color.txt");
            for(int m=0; m<X; m++)
            {
               Color2<<COLOR[m]<<endl;
            }
            Color2.close();

            FIRE[id]=to_string(fire);///update fire status
            ofstream Fire2;
            Fire2.open("fire.txt");
            for(int m=0; m<X; m++)
            {
              Fire2<<FIRE[m]<<endl;
            }
            Fire2.close();

            if (timeUP(m_renderer,player[id].points,id)==0)
                return 0;
        }
        int PEBI;///previous existing ball index

//         ball[i].Vx= ( (10*ball[i].x2) - (9*ball[i].x1) ) * pow( (1-t) , 8 ) +///x element of the curve
//                     ( (90*ball[i].x3) - (80*ball[i].x2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].x4) - (315*ball[i].x3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].x5) - (720*ball[i].x4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].x6) - (1050*ball[i].x5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].x7) - (840*ball[i].x6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].x8) - (360*ball[i].x7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].x9) - (90*ball[i].x8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].x10) - (10*ball[i].x9) ) * pow ( t , 8);
//
//         ball[i].Vy= ( (10*ball[i].y2) - (9*ball[i].y1) ) * pow( (1-t) , 8 ) +///y element of the curve
//                     ( (90*ball[i].y3) - (80*ball[i].y2) ) * pow( (1-t) , 7 ) * pow ( t , 1) +
//                     ( (360*ball[i].y4) - (315*ball[i].y3) ) * pow( (1-t) , 6 ) * pow ( t , 2) +
//                     ( (840*ball[i].y5) - (720*ball[i].y4) ) * pow( (1-t) , 5 ) * pow ( t , 3 ) +
//                     ( (1050*ball[i].y6) - (1050*ball[i].y5) ) * pow( (1-t) , 4 ) * pow ( t , 4) +
//                     ( (720*ball[i].y7) - (840*ball[i].y6) ) * pow( (1-t) , 3 ) * pow ( t , 5 ) +
//                     ( (315*ball[i].y8) - (360*ball[i].y7) ) * pow( (1-t) , 2 ) * pow ( t , 6) +
//                     ( (80*ball[i].y9) - (90*ball[i].y8) ) * pow( (1-t) , 1 ) * pow ( t , 7) +
//                     ( (9*ball[i].y10) - (10*ball[i].y9) ) * pow ( t , 8);

          for(int m=i+1; m<=counter; m++)///control balls waiting for other balls
          {
              if(ball[m].exist==0)
              {
                while(ball[m].exist==0)
                    m++;
                PEBI=m;
              }
            break;
          }
          if(ball[i+1].exist==1 && i!=counter)
            PEBI=i+1;
          if(counter==0)
            PEBI=0;

//             ball[i].x += ball[i].Vx/2500;
//             ball[i].y += ball[i].Vy/2500;
           if ( ((ball[i].x-ball[PEBI].x)*(ball[i].x-ball[PEBI].x))+((ball[i].y-ball[PEBI].y)*(ball[i].y-ball[PEBI].y))< 3630)///move the ball if its close to previous
           {
             ball[i].x=xx[ball[i].i];
             ball[i].y=yy[ball[i].i];
             ball[i].i++;
           }

        for (int i=counter ; i>=0 ; i--)///check if the balls are colliding
        {
//          if( ((ball[i].x-ball[i-1].x)*(ball[i].x-ball[i-1].x))+((ball[i].y-ball[i-1].y)*(ball[i].y-ball[i-1].y))< 3600)
//          {
//              double dx,dy,distance1,distance2;
//              distance1=sqrt(((ball[i-1].x-ball[i].x)*(ball[i-1].x-ball[i].x))+((ball[i-1].y-ball[i].y)*(ball[i-1].y-ball[i].y)));
//              distance2=60-distance1;
//              dx=distance2*cos(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              dy=distance2*sin(atan2((ball[i-1].y-ball[i].y),(ball[i-1].x-ball[i].x)));
//              ball[i-1].x+=dx;
//              ball[i-1].y+=dy;

              for(int j=counter1-1; j>-1; j--)///check if the shooted ball collided with a ball on the curve and move it on the curve too
              {
                    int color;
                    bool simpleExplosion=0;
                    if( fabs (shoot[j].x-ball[i].x) < 30 && fabs (shoot[j].y-ball[i].y) < 30 && i!=counter && shoot[j].checked==0 && ball[i].exist==1)
                    {
                        if(ball[i].color==7 || ball[i].color==8 || ball[i].color==9 || ball[i].color==10)
                         ball[i].color-=7;
                        else if(ball[i].color==11)
                        {
                           ball[i].exist=0;
                           player[id].points++;
                           explosion (m_renderer,ball[i].x,ball[i].y);
                           if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                        }

                       else
                       {
                           for(int m=0; m<i; m++)
                           {
                             int n=m;
                             while(ball[m+1].exist==0)
                                m++;
                             ball[n].color=ball[m+1].color;
                           }
                           color=ball[i].color;
                           ball[i].color=shoot[j].color;
                           simpleExplosion=1;
                       }

                        shoot[j].checked=1;
                        shoot[j].way=1;

                      if(shoot[j].color==4)///if color power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                        for(int m=counter; m>=0; m--)
                          if(ball[m].color==color && ball[m].exist==1)
                            {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                            }
                      }

                      else if(shoot[j].color==6)///if fire power is being used
                      {
                          ball[i].exist=0;
                          player[id].points++;
                          explosion (m_renderer,ball[i].x,ball[i].y);
                          if(sound1==1)
                            Mix_PlayChannel(-1,Explosion,0);
                      }

                      else if(shoot[j].color==5)///if bomb power is being used
                      {
                          for(int m=i-3; m<=i+3; m++)
                            if(ball[m].exist==1 && m>=0 && m<=counter)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                      }

                     else///if no specific power is being used
                     {
                       int right,left,Rcounter=0,Lcounter=0;///check if they are more then or equal to three
                      right=i;
                      left=i;
                      Lcounter=0;
                      Rcounter=0;
                      while(1)
                      {
                          if( ( ball[right+1].color==ball[right].color || ball[right+1].color==12 ) && (right+1)!=counter && ball[right+1].exist==1)
                          {
                            Rcounter++;
                            right++;
                          }
                          else
                            break;
                      }
                      while(1)
                      {
                          if( ( ball[left-1].color==ball[left].color || ball[left-1].color==12 ) && (left-1)!=counter && ball[left-1].exist==1)
                          {
                            Lcounter++;
                            left--;
                          }
                          else
                            break;
                      }

                      if(Lcounter+Rcounter+1>=3  && simpleExplosion==1)///remove them if they were more then three
                      {
                          for(int m=i; m<=i+Rcounter; m++)
                          {
                              ball[m].exist=0;
                              player[id].points++;
                              explosion (m_renderer,ball[m].x,ball[m].y);
                              if(sound1==1)
                                Mix_PlayChannel(-1,Explosion,0);
                          }
                          for(int m=i-1; m>=i-Lcounter; m--)
                          {
                             ball[m].exist=0;
                             player[id].points++;
                             explosion (m_renderer,ball[m].x,ball[m].y);
                             if(sound1==1)
                               Mix_PlayChannel(-1,Explosion,0);
                          }
                      }
                     }
                    }
                //}
              }
          }
        int r,g,b;
         if(ball[i].color==0)///determine the ball on the way color
        {
            r=180;
            g=86;
            b=227;
            count0++;
        }
        if(ball[i].color==1)
        {
            r=86;
            g=213;
            b=227;
            count1++;

        }
        if(ball[i].color==2)
        {
            r=212;
            g=68;
            b=68;
            count2++;
        }
        if(ball[i].color==3)
        {
            r=232;
            g=132;
            b=26;
            count3++;
        }
        if(mode==1)///40=ball limit
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 && i<40 )
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }
        else
        {
            if( (ball[i].x>0 && ball[i].x<w) && (ball[i].y>0 && ball[i].y<h) && ball[i].exist==1 )///no ball limit if time mode is chosen
            {
              if(ball[i].color==11)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"anoyying.png",60,60);
                else if(ball[i].color==12)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"question.png",60,60);
                else if(ball[i].color==7)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"purple.png",60,60);
                else if(ball[i].color==8)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"blue.png",60,60);
                else if(ball[i].color==9)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"red.png",60,60);
                else if(ball[i].color==10)
                    texture(m_renderer,ball[i].x-30,ball[i].y-30,"orange.png",60,60);
                else
                    filledCircleRGBA (m_renderer, ball[i].x, ball[i].y, 30, r, g, b, 255);
            }
        }
      }

      Uint32 End = SDL_GetTicks();///timer
      secondsElapsed = (End - Start) / 1000;
      stringstream tt;
      tt<<secondsElapsed;
      string t;
      tt>>t;
      const char *time;
      const char *TIME="/60";
      time =t.c_str();
      SDL_Color text_color = { 250, 250, 250};
      if(mode==0)
      {
        textColor(m_renderer,150,700,time,1 ,24,text_color);
        textColor(m_renderer,200,700,TIME,1 ,24,text_color);
      }

  stringstream ss;///show player score
  ss<<player[id].points;
  string s;
  ss>>s;
  points =s.c_str();
  textColor(m_renderer,w-200,100,POINTS,1 ,24,text_color);
  textColor(m_renderer,w-100,100,points,1 ,24,text_color);

  if(sound1==1)
    texture(m_renderer,w-50,200,"soundON.png",50,50);
  else
    texture(m_renderer,w-50,200,"soundOFF.png",50,50);
  if(music1==1)
    texture(m_renderer,w-50,250,"musicON.png",50,50);
  else
    texture(m_renderer,w-50,250,"musicOFF.png",50,50);

 SDL_RenderPresent( m_renderer );

 }
}

