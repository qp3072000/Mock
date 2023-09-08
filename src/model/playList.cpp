#include "playList.h"

Playlist::Playlist(const string &name) : namePlaylist(name) {}

void Playlist::addMediaFile(const MediaFile &media) {
  playlist.push_back(media);
}


void Playlist::eraseMediaFile(int index) {
  // Check index is avaiable ?
  if (index >= 0 && index < playlist.size()) {
    playlist.erase(playlist.begin() + index);
  } else {
    cout << "Not find index. Erase Media File is not success" << endl;
  }
}

void Playlist::changeTitleMediaFile(int index, const string &title) {
  if (index >= 0 && index < playlist.size()) {
    playlist[index].setTitleMedia(title);
  } else {
    cout << "Not find index. Change Name Media File is not success" << endl;
  }
}

void Playlist::changeArtistMediaFile(int index, const string &artist) {
  if (index >= 0 && index < playlist.size()) {
    playlist[index].setArtistMedia(artist);
  } else {
    cout << "Not find index. Change Artist Media File is not success" << endl;
  }
}

void Playlist::changeYearMediaFile(int index, int year) {
  if (index >= 0 && index < playlist.size()) {
    playlist[index].setYearPublish(year);
  } else {
    cout << "Not find index. Change Year Media File is not success" << endl;
  }
}

void Playlist::getInforMediaFile(int index) {
  if (index >= 0 && index < playlist.size()) {
    cout << index << "       " << playlist[index].getTitle();
    cout << "                        " << playlist[index].getArtist();
    cout << "                        " << playlist[index].getYearPublish() << endl;
  }
  else {
    cout << "Not find index. Get Infor Media File is not success" << endl;
  }
}

void Playlist::getInforPlaylist() {
  for (int i = 0; i < playlist.size(); i++) {
    getInforMediaFile(i);
    cout << "----------------------------------------------------" << endl;
  }
}

void Playlist::setNameString(const string &name) { namePlaylist = name; }

string Playlist::getNameString() { return namePlaylist; }

string Playlist::getPathMediaFile(int index) {
  if (index >= 0 && index < playlist.size()) {
    return playlist[index].getPath();
  }
  else {
    return "";
    cout << "Not find indexMedia. Get Path Media File is not success" << endl;
  }
}
