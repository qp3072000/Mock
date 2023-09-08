#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

#include "controller.h"

void Controller::run() {
    int key = 0;
    bool running = true;

    while (running) {
        viewPtr->showOptionsMainMenu();
        viewPtr->cinOption(key);

        switch (key) {
        case SHOW_MUSIC:
            showMusicInFolder();
            break;
        case CREATE_PLAYLIST:
            createPlaylist();
            break;
        case ERASE_PLAYLIST:
            erasePlaylist();
            break;
        case SHOW_PLAYLIST:
            showPlaylist();
            break;
        case UPDATE_PLAYLIST:
            updatePlaylist();
            break;
        case SHOW_MEDIAFILE:
            showMediaFile();
            break;
        case PLAY:
            optionMusic();
            break;
        case EXIT_MENU:
            running = false;
            break;
        }
    }
}

void Controller::createPlaylist() {
  string name = "";

  cout << "Input name new playlist: ";
  viewPtr->cinString(name);

  Playlist newPlaylist(name);
  listPtr->addPlaylist(newPlaylist);

  cout << "Create new playlist is success!" << endl;
}

void Controller::erasePlaylist() {

  int indexPlaylist = 0;

  viewPtr->showList();     // view list
  listPtr->getInforList(); // model get data list

  viewPtr->cinIndex(indexPlaylist);

  listPtr->erasePlaylist(indexPlaylist);
}

void Controller::showPlaylist() { 
  int indexPlaylist = 0;

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist);

  viewPtr->showPlaylist();
  listPtr->getInforPlaylist(indexPlaylist);
}

void Controller::updatePlaylist() {
  int key = 0;

  viewPtr->showOptionsUpdatePlaylist();

  viewPtr->cinOption(key);

  switch (key) {
  case INSERT_MEDIAFILE:
    insertMediaFile();
    break;
  case ERASE_MEDIAFILE:
    eraseMediaFile();
    break;
  case UPDATE_MEDIAFILE:
    viewPtr->showOptionsUpdateMediaFile();
    viewPtr->cinOption(key);

    switch (key) {
    case TITLE:
      changeTitleMediaFile();
      break;
    case ARTIST:
      changeArtistMediaFile();
      break;
    case YEAR:
      changeYearMediaFile();
      break;
    case EXIT_UPDATEMEDIA:
      break;
    }
    break;
  case EXIT_UPDATEPLAYLIST:
    break;
  }
}

void Controller::insertMediaFile() { 
  int indexPlaylist = 0;
  string path = "";

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist);

  cout << "Input path for new media file: ";
  viewPtr->cinString(path);

  MediaFile newMediaFile(path);
  listPtr->addMediaFile(indexPlaylist, newMediaFile);
}

void Controller::eraseMediaFile() {

  int indexPlaylist = 0;
  int indexMediaFile = 0;

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist, indexMediaFile);

  listPtr->eraseMediaFile(indexPlaylist, indexMediaFile);
}

void Controller::changeTitleMediaFile() {
  int indexPlaylist = 0;
  int indexMediaFile = 0;
  string title = "";

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist, indexMediaFile);

  cout << "Input new Title: ";
  viewPtr->cinString(title);

  listPtr->changeTitleMediaFile(indexPlaylist, indexMediaFile, title);
}

void Controller::changeArtistMediaFile() {

  int indexPlaylist = 0;
  int indexMediaFile = 0;
  string artist = "";

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist, indexMediaFile);

  cout << "Input new artist: ";
  viewPtr->cinString(artist);

  listPtr->changeArtistMediaFile(indexPlaylist, indexMediaFile, artist);
}

void Controller::changeYearMediaFile() {

  int indexPlaylist = 0;
  int indexMediaFile = 0;
  int year = 0;

  viewPtr->showList();
  listPtr->getInforList();

  viewPtr->cinIndex(indexPlaylist, indexMediaFile);

  cout << "Input new year: ";
  cin >> year;

  listPtr->changeYearMediaFile(indexPlaylist, indexMediaFile, year);
}

void Controller::showMediaFile() {
  int indexPlaylist = 0;
  int indexMediaFile = 0;

  viewPtr->showList();     // view list
  listPtr->getInforList(); // model get data list

  viewPtr->cinIndex(indexPlaylist, indexMediaFile);

  viewPtr->showMediaFile();
  listPtr->getInforMediaFile(indexPlaylist, indexMediaFile);
}

void Controller::showMusicInFolder() {
  string path;

  cout << "Input path: ";
  viewPtr->cinString(path);

  fs::path folderPath(path);

  if (!fs::exists(folderPath)) {
    cerr << "Path does not exist" << endl;
    return;
  }

  try {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
      if (fs::is_regular_file(entry) && entry.path().extension() == ".mp3") {
        cout << entry.path().filename() << endl;
      }
    }
  }
  catch (const exception& ex) {
    cerr << "Error while listing files: " << ex.what() << endl;
    return;
  }
}

void Controller::playMusic() {
  Mix_Music *song = nullptr;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
    return;
  }

  // Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    cerr << "SDL_mixer could not initialize! SDL_mixer Error: "
         << Mix_GetError() << endl;
    return;
  }

  bool quit = false;
  while (!quit) {
    // Check for SDL events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Load Music
    if (loadMusic) {
      if (song) {
        Mix_FreeMusic(song);
      }
      song = Mix_LoadMUS(musicPath.c_str());
      if (!song) {
        cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError()
             << endl;
        break; // Exit the loop on load failure
      }
      {
        lock_guard<mutex> lock(changedMusic);
        loadMusic = false;
      }
    }

    // Play Music
    Mix_PlayMusic(song, 0);

    // Wait while playing music
    while (Mix_PlayingMusic()) {
      // Check event Pause-Resume
      if (isPause) {
        Mix_PauseMusic();
      } else {
        Mix_ResumeMusic();
      }

      // Check event play new music
      if (loadMusic) {
        break;
      }

      SDL_Delay(100);
    }

    // Auto next music
    while (!Mix_PlayingMusic()) {
      {
        lock_guard<mutex> lock(changedMusic);
        ++currentPlayMusic; // Increase index
        musicPath = listPtr->getPathMediaFile(currentPlayPlaylist, currentPlayMusic);
      }

      // Check Path is available ?
      if (!musicPath.empty()) {
        {
          lock_guard<mutex> lock(changedMusic);
          loadMusic = true;
        }
      }
      else {
        cout << "Next music is empty. Playing the first song again!" << endl;
        {
          lock_guard<mutex> lock(changedMusic);
          currentPlayMusic = 0;
          musicPath = listPtr->getPathMediaFile(currentPlayPlaylist, currentPlayMusic);
          loadMusic = true;
        }
      }
      break;
    }
  }

  // Free resources and clean up
  if (song) {
    Mix_FreeMusic(song);
  }

  Mix_CloseAudio();
  SDL_Quit();
}

void Controller::nextMusic() {
    int nextMusicIndex;
    string nextMusicPath;

    {
        lock_guard<mutex> lock(changedMusic);
        nextMusicIndex = currentPlayMusic + 1;
        nextMusicPath = listPtr->getPathMediaFile(currentPlayPlaylist, nextMusicIndex);

        if (nextMusicPath.empty()) {
            cout << "Next music is empty. Playing the first song again!" << endl;
            currentPlayMusic = 0;
            musicPath = listPtr->getPathMediaFile(currentPlayPlaylist, currentPlayMusic);
        } else {
            currentPlayMusic = nextMusicIndex;
            musicPath = nextMusicPath;
        }

        loadMusic = true;
    }
}

void Controller::previousMusic() {
    int previousMusicIndex;
    string previousMusicPath;

    {
        lock_guard<mutex> lock(changedMusic);
        previousMusicIndex = currentPlayMusic - 1;
        previousMusicPath = listPtr->getPathMediaFile(currentPlayPlaylist, previousMusicIndex);

        if (previousMusicPath.empty()) {
            cout << "Previous music is empty. Playing the first song again!" << endl;
            currentPlayMusic = 0;
        } else {
            currentPlayMusic = previousMusicIndex;
        }

        musicPath = listPtr->getPathMediaFile(currentPlayPlaylist, currentPlayMusic);
        loadMusic = true;
    }
}



void Controller::optionMusic() {
  int key = 0;

  while (true) {
    viewPtr->showOptionsPlayMusic();
    viewPtr->cinOption(key);

    switch (key) {
      case PLAY_MUSIC: {
        lock_guard<mutex> lock(changedMusic);
        viewPtr->cinIndex(currentPlayPlaylist, currentPlayMusic);
        musicPath = listPtr->getPathMediaFile(currentPlayPlaylist, currentPlayMusic);
        loadMusic = true;
        isPause = false;
        break;
      }
      case PAUSE: {
        lock_guard<mutex> lock(changedMusic);
        isPause = true;
        break;
      }
      case RESUME: {
        lock_guard<mutex> lock(changedMusic);
        isPause = false;
        break;
      }
      case NEXT:
        nextMusic();
        break;
      case PREVIOUS:
        previousMusic();
        break;
      case EXIT_PLAY:
        return;
    }

    // Create Thread one time
    if (checkThread) {
      thread t1(&Controller::playMusic, this); //Passing arguments to threads
      t1.detach();
      checkThread = false;
    }
  }
}

