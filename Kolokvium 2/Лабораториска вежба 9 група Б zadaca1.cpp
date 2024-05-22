// Дадени ви се класите User и SocialNetwork. 

// Во класата User се чуваат информации за корисничко име, возраст и број на пријатели во рамки на некоја социјална мрежа.

// Во класата SocialNetwork се чува листа на членови (објекти од класата User) и големина на листата.

// Да се дополни почетниот код со следните работи:

// Да се спречи додавање на корисник со веќепостоечко корисничко име преку фрлање исклучок од тип UserAlreadyExistsException. Справете се со исклучокот на потребното место. 
// Да се додаде променлива за лимитот на дозволени пријатели на еден корисник (цел број). Променливата да важи за сите корисници (објекти од класа User) и истата да може да се менува преку методот setLimit. Иницијално променливата да има вредност 3.
// Да се фрли исклучок од тип UserNotFoundException во методот friendRequest доколку firstUsername или secondUsername не се кориснички имиња на корисници во социјалната мрежа. Справете се со исклучокот на потребното место. 
// Да се спречи зголемување на бројот на пријатели на некој корисник (над дозволениот лимит) со исклучок од тип FriendsLimitExceededException. Справете се со исклучокот на потребното место.

#include <iostream>
#include <cstring>
using namespace std;

class UserAlreadyExistsException {
private:
    char user[100];
public:
    UserAlreadyExistsException(const char *user) {
        strcpy(this->user, user);
    }
    void message() {
        cout << "User with username " << user << " already exists!" << endl;
    }
};

class UserNotFoundException {
private:
    char f[100];
public:
    UserNotFoundException(const char *f) {
        strcpy(this->f, f);
    }
    void message() {
        cout << "User with username " << f << " was not found!" << endl;
    }
};

class FriendsLimitExceededException {
private:
    int n;
public:
    FriendsLimitExceededException(int n) {
        this->n = n;
    }
    void message() {
        cout << "Can't have more than " << n << " friends." << endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;
public:
    User(const char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        if (friends == limit) {
            throw FriendsLimitExceededException(limit);
        }
        ++friends;
        return *this;
    }

    friend class SocialNetwork;

    static void setLimit(int lim) {
        limit = lim;
    }

    const char* getUsername() const {
        return username;
    }
};

int User::limit = 3;

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, u.username) == 0)
                throw UserAlreadyExistsException(users[i].username);
        }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(const char *firstUsername, const char *secondUsername) {
        User *user1 = nullptr;
        User *user2 = nullptr;

        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                user1 = &users[i];
            }
            if (strcmp(users[i].username, secondUsername) == 0) {
                user2 = &users[i];
            }
        }

        if (!user1) {
            throw UserNotFoundException(firstUsername);
        }
        if (!user2) {
            throw UserNotFoundException(secondUsername);
        }

        try {
            ++(*user1);
            ++(*user2);
        } catch (FriendsLimitExceededException &e) {
            e.message();
        }
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i = 0; i < network.n; i++) {
            os << network.users[i] << endl;
        }
        return os;
    }

    ~SocialNetwork() {
        delete[] users;
    }
};

int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char username[50];
        int age;
        cin >> username >> age;
        User u(username, age);
        try {
            sn += u;
        } catch (UserAlreadyExistsException &e) {
            e.message();
        }
    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (UserNotFoundException &e) {
            e.message();
        } catch (FriendsLimitExceededException &e) {
            e.message();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    User::setLimit(maxFriends);
    cin >> friendships;
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (UserNotFoundException &e) {
            e.message();
        } catch (FriendsLimitExceededException &e) {
            e.message();
        }
    }
    cout << sn;
    return 0;
}
