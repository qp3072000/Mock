#pragma one

#include "list.h"
#include "view.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <thread>
#include <mutex>
#include"common.h"

using namespace std;

class Controller {
private:
  shared_ptr<View> viewPtr; 
  shared_ptr<List> listPtr;

  int currentPlayMusic;
  int currentPlayPlaylist; 

  //Playlist
  void createPlaylist();
  void erasePlaylist();
  void showPlaylist();
  void updatePlaylist();

  //MediaFile
  void insertMediaFile();
  void showMediaFile();
  void eraseMediaFile();
  void changeTitleMediaFile();
  void changeArtistMediaFile();
  void changeYearMediaFile();
  
  //Play Music
  void showMusicInFolder();
  void optionMusic();
  void playMusic();
  void nextMusic();
  void previousMusic(); 

  bool checkThread;//Check Thread created

  bool isPause; //Flat Pause current Music
  bool loadMusic; //Flat load Music to Play
  string musicPath;
  mutex changedMusic;

public:
  void run();
  Controller()
      : viewPtr(View::getInstanceView()), listPtr(List::getInstanceList()),
        currentPlayMusic(0), currentPlayPlaylist(0), checkThread(true), isPause(false), loadMusic(false), musicPath("") {}
};
