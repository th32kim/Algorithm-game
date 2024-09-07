// define your classes here...
#include <string>
class MusicPlaylist{
    private:
        std::string* Playlist;
        std::string Blacklistauthor;
        std::string Blacklistsong1;
        std::string Blacklistsong2;
        int PlaylistLength;
    public:
        MusicPlaylist();
        ~MusicPlaylist();
        void PlaylistCreate(int N);
        void AddSong(const std::string& song, const std::string& author);
        void PlaySong(int n);
        void EraseSong(int n);
};