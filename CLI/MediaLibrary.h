#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

//#include "MediaFile.h"
#include "PlayList.cpp"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

class MediaLibrary {
private:
    std::map<std::string, std::shared_ptr<MediaFile>> MediaFileList;
    std::map<std::string, std::shared_ptr<PlayList>> PlayListList;

    std::shared_ptr<PlayList> CurrentPlayList; // manage the currently playlist
    std::shared_ptr<MediaFile> CurrentMediaFile; //manage the current song

    void saveFile(std::string _path);
    void getData();

public:
    MediaLibrary();
    MediaLibrary(const MediaLibrary& other) = delete;
    MediaLibrary(MediaLibrary&& other) = delete;
    ~MediaLibrary();

    bool addNewMediaFile(const std::string& _path);
    bool removeMediaFilebyPath(const std::string& _path);
    std::shared_ptr<MediaFile> getMediaFilebyPath(const std::string& _path);
    const std::map<std::string, std::shared_ptr<MediaFile>>& getAllMediaFiles() const;
    bool addNewPlayList(const std::string& _name);
    bool removePlayList(const std::string& _name);
    const std::map<std::string, std::shared_ptr<PlayList>>& getAllPlayList() const;
    
    bool addMediaFiletoPlayList(const std::string& _playlistname, const std::string& _filepath);
    bool removeMediaFilefromPlayList(const std::string& _playlistname, const std::string& _filepath);
    std::shared_ptr<PlayList> getPlayListbyName(const std::string& _name);
    // manage the current play media
    void setCurrentMediaFile(const std::string& _path);
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    bool settoNextMediaFileinLibrary(); // not yet
    bool settoPrevMediaFileinLibrary(); // not yet
    void setCurrentPlayList(const std::string& _name);
    std::shared_ptr<PlayList> getCurrentPlayList() const;
    bool settoNextMediaFileinPlayList(); // not yet
    bool settoPrevMediaFileinPlayList(); // not yet
    
};

#endif //MEDIALIBRARY_H
