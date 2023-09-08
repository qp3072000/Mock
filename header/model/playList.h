#ifndef H_PLAYLIST_H
#define H_PLAYLIST_H

#include "mediaFile.h"
#include <vector>

class Playlist {
private:
  vector<MediaFile> playlist;
  string namePlaylist;

public:
  Playlist(const string &name);

  void addMediaFile(const MediaFile &media);
  void eraseMediaFile(int index);
  void getInforMediaFile(int index);
  void changeTitleMediaFile(int index, const string &title);
  void changeArtistMediaFile(int index, const string &artist);
  void changeYearMediaFile(int index, int year);

  void getInforPlaylist();
  string getPathMediaFile(int index);

  void setNameString(const string &name);
  string getNameString();
};
#endif
