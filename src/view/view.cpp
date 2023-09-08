#include "view.h"

shared_ptr<View> View::instance = nullptr;

shared_ptr<View> View::getInstanceView() {
    if (!instance) {
        instance = shared_ptr<View>(new View());
    }
    return instance;
}

void View::showOptionsMainMenu() {
  cout << "----------Main Menu Options----------" << endl;
  cout << "1 - Show mediafile in folder" << endl;
  cout << "2 - Create playlist" << endl;
  cout << "3 - Erase playlist" << endl;
  cout << "4 - Show playlist" << endl;
  cout << "5 - Update playlist" << endl;
  cout << "6 - Show media file" << endl;
  cout << "7 - Play music" << endl;
  cout << "0 - Exit" << endl;
}

void View::showOptionsUpdatePlaylist() {
  cout << "----------Playlist Options----------" << endl;
  cout << "1 - Insert media file" << endl;
  cout << "2 - Erase media file" << endl;
  cout << "3 - Update media file" << endl;
  cout << "0 - Exit" << endl;
}

void View::showOptionsUpdateMediaFile() {
  cout << "----------Media File Options----------" << endl;
  cout << "1 - Set Title" << endl;
  cout << "2 - Set Artist" << endl;
  cout << "3 - Set Year" << endl;
  cout << "0 - Exit" << endl;
}

void View::showOptionsPlayMusic() {
    cout << "----------Music Player Options----------" << endl;
    cout << "1 - Play" << endl;
    cout << "2 - Pause" << endl;
    cout << "3 - Resume" << endl;
    cout << "4 - Next" << endl;
    cout << "5 - Previous" << endl;
    cout << "0 - Exit" << endl;
}
void View::showList() {
  cout << "----------List----------" << endl;
  cout << "ID    | Name Playlist " << endl;
}

void View::showPlaylist() {
  cout << "----------Playlist----------" << endl;
  cout << "ID    | Title                  | Artist                  | Year" << endl;
}

void View::showMediaFile() {
  cout << "----------Media File----------" << endl;
  cout << " Title                  | Artist                  | Year" << endl;
}

void View::cinIndex(int indexPlaylist, int indexMediaFile) {
  cout << "Input index playlist: " ;
  cin >> indexPlaylist;

  cout << "Input index media file: " ;
  cin >> indexMediaFile;
}

void View::cinIndex(int indexPlaylist) {
  cout << "Input index playlist: " ;
  cin >> indexPlaylist;
}

void View::cinOption(int &key) {
  cout << "Input key: ";
  cin >> key;
}

void View::cinString(string &text) {
  cin.ignore();
  getline(cin,text);
}
