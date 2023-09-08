#ifndef H_LIST_H
#define H_LIST_H

#include "playList.h"

class List {
private:
  static shared_ptr<List> instance;
  vector<Playlist> list;
  List() {}

public:
  static shared_ptr<List> getInstanceList(); // Get singleton Object

  void addPlaylist(const Playlist &playlist);
  void erasePlaylist(int index);
  void getInforPlaylist(int index);

  void addMediaFile(int index, const MediaFile &media);
  void eraseMediaFile(int index, int indexMediaFile);
  void changeTitleMediaFile(int index, int indexMediaFile,
                            const string &title);
  void changeArtistMediaFile(int index, int indexMediaFile,
                             const string &artist);
  void changeYearMediaFile(int index, int indexMediaFile,
                           int year);
  void getInforMediaFile(int index, int indexMediaFile);

  void getInforList();

  string getPathMediaFile(int index, int indexMediaFile);
};
#endif
