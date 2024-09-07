#include "playlist.h"
#include <string>
#include <iostream>

// implement classes' member functions here...
MusicPlaylist::MusicPlaylist(){
    //Values for Blacklisted songs from being added
    Blacklistauthor = "Justin Bieber";
    Blacklistsong1 = "Baby";
    Blacklistsong2 = "My Heart Will Go On";
}
//Creating Playlist
void MusicPlaylist::PlaylistCreate(int N){
    Playlist = new std::string[N];
    PlaylistLength = N;
    //Play list initialization for future comparison
    for (int i=0; i<N; i++){
        Playlist[i] = "!";
    }
    std::cout<<"success"<<std::endl;
}

void MusicPlaylist::AddSong(const std::string& song, const std::string& author){
    std::string album= song+";"+author;
    //Check for blacklisted songs
    if((song==Blacklistsong1&&author==Blacklistauthor)||(song==Blacklistsong2)){
        std::cout<<"can not insert "<<album<<std::endl;
    }else{
        //check if the list is full
        if(Playlist[PlaylistLength-1]!="!"){
            std::cout<<"can not insert "<<album<<std::endl;
        }else{
            //Check if the song trying to add is not already in the list
            for(int i=0; i<PlaylistLength; i++){
                if(Playlist[i]==album){
                    std::cout<<"can not insert "<<album<<std::endl;
                    break;
                }else if(Playlist[i]=="!"){
                    //Able to put it in the list
                    Playlist[i] = album;
                    std::cout<<"success"<<std::endl;
                    break;
                }
            }
            }
    }
}

void MusicPlaylist::PlaySong(int n){
    //Nothing on the Playlist, or out of bound
    if (n>=PlaylistLength||Playlist[n]=="!"||n<0){
        std::cout<<"can not play "<<n<<std::endl;
    }else{
        //Song located in the playlist
        std::cout<<"played "<<n;
        std::cout<<" "<<Playlist[n]<<std::endl;
    }
}

void MusicPlaylist::EraseSong(int n){
    //Deleting song at position n
    if(n>=PlaylistLength||n<0){
        //Invalid n input
        std::cout<<"can not erase "<<n<<std::endl;
    }else if(Playlist[n]=="!"){
        //Empty on the n
        std::cout<<"can not erase "<<n<<std::endl;
    }else{
        //Delete the song at position n
        Playlist[n]="!";
        std::cout<<"success"<<std::endl;
        //move song after position n by 1
        for(int i=n; i<PlaylistLength-1;i++){
            Playlist[i]=Playlist[i+1];
        }
        Playlist[PlaylistLength-1]="!";
    }
}

MusicPlaylist::~MusicPlaylist(){
    //Deallocate the music playlist array
    delete[] Playlist;
    Playlist = nullptr;
}