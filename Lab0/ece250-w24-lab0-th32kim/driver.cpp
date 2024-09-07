// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "playlist.h"

//Original File
int main(int argc, char *argv[]){
    std::string input="";
    int param_num=0;
    std::string album="";
    std::string author="";
    std::string song="";

    //Object Orientation for new Music Playlist
    MusicPlaylist Playlist;
    do{
        std::cin>>input;
        if(input != "done"){
            if(input=="m"){
                //create playlist
                std::cin>>param_num; //extracting number next to m command
                Playlist.PlaylistCreate(param_num);
            }else if(input=="i"){
                //insert to playlist
                std::cin.ignore();
                std::getline(std::cin,album); //extracting t;a next to i command
                //Separating song with author prior to adding it to the playlist
                size_t loc = album.find(";");
                song = album.substr(0,loc);
                author = album.substr(loc+1);
                Playlist.AddSong(song,author);
                
            }else if(input=="p"){
                //play song
                std::cin>>param_num;//extracting number next to p command
                Playlist.PlaySong(param_num);
            }else if(input=="e"){
                //erase song
                std::cin>>param_num;//extracting number next to e command
                Playlist.EraseSong(param_num);
            }
        }
    }while(input!="done");

}