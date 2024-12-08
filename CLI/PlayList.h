#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "MediaFile.cpp"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class PlayList {
private:
    std::string Name;
    std::vector<std::shared_ptr<MediaFile>> MediaTrackList;
public:
    PlayList(std::string _name);
    PlayList(const PlayList& other) = default;
    PlayList(PlayList&& other) noexcept = default;
    ~PlayList() = default;

    bool addMediaFile(const std::shared_ptr<MediaFile>& _mediafile);
    bool removeMediaFile(const std::string& _path);
    const std::shared_ptr<MediaFile> getMediaFilebyPath(const std::string& _path) const;
    const std::vector<std::shared_ptr<MediaFile>>& getPlayList() const;
    void setName(const std::string& _name);
    std::string getName() const;
    int size() const;
    void clear();
};



#endif //PLAYLIST_H