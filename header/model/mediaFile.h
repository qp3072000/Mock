#ifndef H_MEDIAFILE_H
#define H_MEDIAFILE_H

#include <memory>
#include <string>
#include <taglib/fileref.h>
#include <taglib/taglib.h>
#include <taglib/tag.h>

using namespace std;

class MediaFile {
private:
  string pathMediaFile;
  TagLib::FileRef file;

public:
  MediaFile(const string &path);

  void setPath(const string &path);
  void setTitleMedia(const string &title);
  void setArtistMedia(const string &artist);
  void setYearPublish(int year);

  string getPath();
  string getTitle();
  string getArtist();
  int getYearPublish();

  bool checkFile();
  bool saveMediaFile();
};

#endif
