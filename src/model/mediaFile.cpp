#include "mediaFile.h"

MediaFile::MediaFile(const string &path) : file(path.c_str()) {
  pathMediaFile = path;
}

bool MediaFile::checkFile() { return !file.isNull() && file.tag(); }

void MediaFile::setPath(const string &path) {
  if (checkFile()) {
    file = TagLib::FileRef(path.c_str());
    pathMediaFile = path;
  }
}

void MediaFile::setTitleMedia(const string &title) {
  if (checkFile()) {
    file.tag()->setTitle(title);
  } else {
    cout << "Enter file is not found. Please try again." << endl;
  }
}

void MediaFile::setArtistMedia(const string &artist) {
  if (checkFile()) {
    file.tag()->setArtist(artist);
  } else {
    cout << "Enter file is not found. Please try again." << endl;
  }
}

void MediaFile::setYearPublish(int year) {
  if (checkFile()) {
    file.tag()->setYear(year);
  } else {
    cout << "Enter file is not found. Please try again." << endl;
  }
}

string MediaFile::getTitle() {
  return checkFile() ? file.tag()->title().toCString(true) : "";
}

string MediaFile::getArtist() {
  return checkFile() ? file.tag()->artist().toCString(true) : "";
}

string MediaFile::getPath() { return checkFile() ? pathMediaFile : ""; }

int MediaFile::getYearPublish() { return checkFile() ? file.tag()->year() : 0; }

bool MediaFile::saveMediaFile() {
  if (checkFile()) {
    return file.save();
  }
  return false;
}
