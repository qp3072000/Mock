#ifndef H_VIEW_H
#define H_VIEW_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class View {
private:
  static shared_ptr<View> instance;
  View() {}

public:
  static shared_ptr<View> getInstanceView();

  void showOptionsMainMenu();
  void showOptionsUpdatePlaylist();
  void showOptionsUpdateMediaFile();
  void showOptionsPlayMusic();

  void showList();
  void showPlaylist();
  void showMediaFile();

  void cinIndex(int indexPlaylist, int indexMediaFile);
  void cinIndex(int indexPlaylist);
  void cinOption(int& key);
  void cinString(string &text);
};
#endif
