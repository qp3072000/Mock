#include "list.h"

shared_ptr<List> List::instance = nullptr;

shared_ptr<List> List::getInstanceList() {
  if (instance == nullptr) {
    instance = shared_ptr<List>(new List()); // make_shared call constructor List, but
                                      // contructor list is private => Error
  }
  return instance;
}


void List::addPlaylist(const Playlist &playlist) { list.push_back(playlist); }


void List::erasePlaylist(int index) {
  if (index >= 0 && index < list.size()) {
    cout << "Erase playlist " << list[index].getNameString() << " is success" << endl;
    list.erase(list.begin() + index);
  } else {
    cout << "Not find index. Erase Playlist is not success" << endl;
  }
}


void List::getInforPlaylist(int index) {
  if (index >= 0 && index < list.size()) {
    list[index].getInforPlaylist();
  } else {
    cout << "Not find index. Get Playlist is not success" << endl;
  }
}

void List::getInforList() {
  int count = 0;
  for (auto x : list) {
    cout << count << "       " << x.getNameString() << endl;
    ++count;
  }
}


void List::addMediaFile(int index, const MediaFile &media) {
  if (index >= 0 && index < list.size()) {
    list[index].addMediaFile(media);
    cout << "List " << list[index].getNameString() << " insert new media file is success" << endl;
  } else {
    cout << "Not find index. Insert new media file is not success ";
  }
}

void List::eraseMediaFile(int index, int indexMediaFile) {
  if (index >= 0 && index < list.size()) {
    list[index].eraseMediaFile(indexMediaFile);
    cout << "List " << list[index].getNameString() << " erase media file " << indexMediaFile
         << " is success" << endl;
  } else {
    cout << "Not find index. Erase media file is not success ";
  }
}


void List::changeTitleMediaFile(int index, int indexMediaFile, const string &title) {
  if (index >= 0 && index < list.size()) {
    list[index].changeTitleMediaFile(indexMediaFile, title);
    cout << "List " << list[index].getNameString() << " change title media file " << indexMediaFile
         << " is success" << endl;
  } else {
    cout << "Not find index. Change Title media file is not success ";
  }
}

void List::changeArtistMediaFile(int index, int indexMediaFile,
                                 const string &artist) {
  if (index >= 0 && index < list.size()) {
    list[index].changeArtistMediaFile(indexMediaFile, artist);
    cout << "List " << list[index].getNameString() << " change Artist media file " << indexMediaFile
         << " is success" << endl;
  } else {
    cout << "Not find index. Change artist media file is not success ";
  }
}


void List::changeYearMediaFile(int index, int indexMediaFile,
                               int year) {
  if (index >= 0 && index < list.size()) {
    list[index].changeYearMediaFile(indexMediaFile, year);
    cout << "List " << list[index].getNameString() << " change year media file " << indexMediaFile
         << " is success" << endl;
  } else {
    cout << "Not find index. Change year media file is not success ";
  }
}

void List::getInforMediaFile(int index, int indexMediaFile) {
  if (index >= 0 && index < list.size()) {
    list[index].getInforMediaFile(indexMediaFile);
    cout << "List " << list[index].getNameString() << " get infor media file " << indexMediaFile
         << " is success" << endl;
  } else {
    cout << "Not find index. Get infor media file is not success ";
  }
}

string List::getPathMediaFile(int index, int indexMediaFile) {
  if (index >= 0 && index < list.size()) {
    return list[index].getPathMediaFile(indexMediaFile);
  } else {
    return "";
    cout << "Not find indexPlaylist. Get infor media file is not success ";
  }
}
