#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <string>
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

#define MAX_VOLUME 100
#define MIN_VOLUME 0
#define AMOUNT_OF_CHANGE_VOLUME 10

class MediaFile {
private:
    Mix_Music* MusicFile;
    bool is_playing;
    bool is_paused;
    int volume;
    bool muted;
    int lastVolume;

    std::string Path;
    std::string title;         // Tên bài hát
    std::string artist;        // Nghệ sĩ
    std::string album;         // Album
    std::string genre;         // Thể loại
    unsigned int year;         // Năm phát hành
    unsigned int trackNumber;  // Số thứ tự bài hát trong album

    unsigned long fileSize;    // Kích thước file tính bằng byte
    int duration;              // Thời lượng tính bằng giây
    int bitrate;               // Bitrate tính bằng kbps
    int channels;              // Số kênh âm thanh
    int sampleRate;            // Tần số lấy mẫu tính bằng Hz
    std::string writingLibrary; // Thư viện viết (nếu có)

public:
    explicit MediaFile(const std::string& _path);
    MediaFile(const MediaFile& other) = default;
    MediaFile(MediaFile&& other) = default;
    ~MediaFile();

    void setPath(const std::string& _path);
    std::string getPath() const;

    void loadMetadata();
    void init();
    void loadMusic();
    

    void load(); // load all

    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    unsigned int getYear() const;
    unsigned int getTrackNumber() const;

    unsigned long getFileSize() const;
    int getDuration() const;
    int getBitrate() const;
    int getChannels() const;
    int getSampleRate() const;
    std::string getWritingLibrary() const;

    void play();
    void pause();
    void stop();
    void increaseVolume();
    void decreaseVolume();
    void toggleMute(); // Thêm phương thức toggleMute
    bool isMuted() const;
    int getVolume() const;

    bool isPlaying() const;
    bool isPaused() const;

    void displayMetadata() const;
};

#endif // MEDIAFILE_H
