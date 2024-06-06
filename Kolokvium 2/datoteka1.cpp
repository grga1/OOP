#include <iostream>
#include <cstring>
#include <fstream>
using namespace  std;

class Post{
protected:
    char username[20];
    char content[200];
    bool photo;
    int likes;
    void copy_post(const Post &other){
        strcpy(this->username,other.username);
        strcpy(this->content,other.content);
        this->photo=other.photo;
        this->likes=other.likes;
    }
public:
    Post(){
        strcpy(this->username,"");
        strcpy(this->content,"");
        this->photo=0;
        this->likes=0;
    }
    Post(char *username,char *content,bool photo,int likes){
        strcpy(this->username,username);
        strcpy(this->content,content);
        this->photo=photo;
        this->likes=likes;
    }
    Post(const Post &other){
        copy_post(other);
    }
    ~Post(){}

    bool operator>=( Post &rhs) {
        return !(this->popularity()< rhs.popularity());
    }

    virtual double popularity()=0;
    virtual void print()=0;
};

class FacebookPost:public Post{
private:
    int number_of_shares;
    void copy_facebook(const FacebookPost &other){
        strcpy(this->username,other.username);
        strcpy(this->content,other.content);
        this->photo=other.photo;
        this->likes=other.likes;

        this->number_of_shares=other.number_of_shares;
    }
public:
    FacebookPost(): Post(){
        this->number_of_shares=0;
    }
    FacebookPost(char *username,char *content,bool photo,int likes,int number_of_shares ):Post(username,content,photo,likes){
        this->number_of_shares=number_of_shares;
    }
    FacebookPost(const FacebookPost &other):Post(other){
        copy_facebook(other);
    }
    double popularity(){
        double proizvod=0;
        proizvod=likes*number_of_shares;
        if(photo==true){
            proizvod=proizvod+(proizvod*0.2);
        }
        return proizvod;
    }
    void print(){
        cout<<"Test FacebookPost"<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
        cout<<"Facebook post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(photo)
            cout<<"With photo"<<endl;
        cout<<"Likes: "<<likes<<" "<<"Shares: "<<number_of_shares<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
    ~FacebookPost(){}
};

class TwitterPost:public Post{
private:
    int number_of_retweets;
    int number_of_replies;
    void copy_twitter(const TwitterPost &other){
        strcpy(this->username,other.username);
        strcpy(this->content,other.content);
        this->photo=other.photo;
        this->likes=other.likes;

        this->number_of_replies=other.number_of_replies;
        this->number_of_retweets=other.number_of_retweets;
    }
public:
    TwitterPost():Post(){
        this->number_of_retweets=0;
        this->number_of_replies=0;
    }
    TwitterPost(char *username,char *content,bool photo,int likes,int number_of_retweets, int number_of_replies):Post(username,content,photo,likes){
        this->number_of_retweets=number_of_retweets;
        this->number_of_replies=number_of_replies;
    }
    TwitterPost(const TwitterPost &other):Post(other){
        copy_twitter(other);
    }
    double popularity(){
        double proizvod=0;
        proizvod=likes*number_of_retweets*number_of_replies;
        if(photo==true)
        {
            proizvod=proizvod+(proizvod*0.1);
        }
        bool tmp=0;
        for(int i=0;i<200;i++){
            if(content[i]=='#')
                tmp=1;
        }
        if(tmp){
            proizvod=proizvod+(proizvod*0.2);
        }
        return proizvod;
    }

    void print(){
        cout<<"Test TwitterPost"<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
        cout<<"Twitter post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(photo)
            cout<<"With photo"<<endl;
        cout<<"Likes: "<<likes<<" "<<"Retweets: "<<number_of_retweets<<" Replies:"<<number_of_replies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }

    ~TwitterPost(){}
};

double mostPopularPostWithPhoto(Post **posts,int n){
    int index=-1;
    for(int i=0;i<n;i++)
    {
        if(posts[i]->popularity()>posts[i]->popularity()){
            index=i;
        }
    }
    return posts[index]->popularity();
}

int main(){
    ifstream dat("text.txt");
    int n;
    dat>>n;
    if(n==1){
        char name[20];
        char content[200];
        bool photo;
        int likes, shares;
        dat >> name;
        dat.ignore();
        dat.getline(content, 200);
        dat >> photo;
        dat >> likes;
        dat >> shares;
        FacebookPost fb(name, content, photo, likes, shares);
        fb.print();
    }else
        if(n==2){
            char name[20];
            char content[200];
            bool photo;
            int likes;
            int retweets;
            int replies;
            dat>>name;
            dat.ignore();
            dat.getline(content,200);
            dat>>photo;
            dat>>likes;
            dat>>retweets;
            dat>>replies;
            TwitterPost tw(name,content,photo,likes,retweets,replies);
            tw.print();
        }
    return 0;

}
