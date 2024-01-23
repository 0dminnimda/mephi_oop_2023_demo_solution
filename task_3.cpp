#include <bits/stdc++.h>

using DB_ID_t = size_t;

class Message {
public:
    DB_ID_t from_id;
    size_t creation_time_for_server_in_ms;
    bool is_read;

    Message(DB_ID_t from_id, size_t creation_time_for_server_in_ms, bool is_read)
        : from_id(from_id),
          creation_time_for_server_in_ms(creation_time_for_server_in_ms),
          is_read(is_read) {}
    virtual ~Message() = default;

    virtual void print(std::ostream &stream) const = 0;
};

class TextMessage : public Message {
public:
    std::string message;

    TextMessage(
        DB_ID_t from_id, size_t creation_time_for_server_in_ms, bool is_read, std::string message
    )
        : Message(from_id, creation_time_for_server_in_ms, is_read), message(message) {}
    virtual ~TextMessage() = default;

    void print(std::ostream &stream) const override { stream << message << std::endl; }
};

class ImageMessage : public Message {
public:
    DB_ID_t image_id;

    ImageMessage(DB_ID_t from_id, size_t creation_time_for_server_in_ms, bool is_read, DB_ID_t image_id)
        : Message(from_id, creation_time_for_server_in_ms, is_read), image_id(image_id) {}
    virtual ~ImageMessage() = default;

    void print(std::ostream &stream) const override {
        stream << "www.telega.org/img/" << image_id << std::endl;
    }
};

class AudioMessage : public Message {
public:
    DB_ID_t audio_id;
    std::string detected_text;

    AudioMessage(
        DB_ID_t from_id,
        size_t creation_time_for_server_in_ms,
        bool is_read,
        DB_ID_t audio_id,
        std::string detected_text
    )
        : Message(from_id, creation_time_for_server_in_ms, is_read),
          audio_id(audio_id),
          detected_text(detected_text) {}

    virtual ~AudioMessage() = default;

    void print(std::ostream &stream) const override {
        stream << "www.telega.org/audio/" << audio_id << ", " << "Detected text: " << detected_text << std::endl;
    }
};

class PhoneNumeber {
public:
    const size_t phone_body;
    const short locale = 7;

    PhoneNumeber(size_t phone_body) : phone_body(phone_body) {}
    PhoneNumeber(short locale, size_t phone_body) : phone_body(phone_body), locale(locale) {}
};

class Person {
public:
    const DB_ID_t id;
    std::string login;
    PhoneNumeber phone_number;

    Person(DB_ID_t id, std::string login, PhoneNumeber phone_number)
        : id(id), login(login), phone_number(phone_number) {}
};

class Chat {
public:
    Person person;
    std::vector<std::shared_ptr<Message>> messages;

    Chat(Person person) : person(person), messages() {}
    ~Chat() = default;

    std::shared_ptr<Message> add_message(std::shared_ptr<Message> message) {
        messages.push_back(message);
        return message;
    }

    void read_unread_messages(std::ostream &stream) {
        for (auto &it : messages) {
            if (it->is_read) continue;
            std::cout << "new message from " << it->from_id << " (" << it->creation_time_for_server_in_ms << "): ";
            it->print(stream);
            std::cout << std::endl;
            it->is_read = true;
        }
    }
};

class Messanger {
    std::map<std::string, Chat> all_chats;

public:
    void add_chat(Chat &&chat) { all_chats.insert({chat.person.login, chat}); }

    Chat &emplace_chat(Chat &&chat) {
        return (*all_chats.emplace(chat.person.login, chat).first).second;
    }

    Chat &operator[](const std::string &login) {
        return (Chat &)((const Messanger *)this)->operator[](login);
    }
    const Chat &operator[](const std::string &login) const {
        auto pp = all_chats.find(login);
        if (pp != all_chats.end()) {
            return pp->second;
        }
        assert(false && "Ayo, don't aske me nonexisting ppl");
    }

    friend std::ostream &operator<<(std::ostream &stream, const Messanger &app) {
        stream << "{";
        for (const auto &it : app.all_chats) {
            stream << "chat(for " << it.first << "), ";
        }
        stream << "}";
        return stream;
    }
};

int main(void) {
    Messanger app;

    Chat &chat = app.emplace_chat(Chat(Person(2, "urmom", 8005353535)));
    auto message = chat.add_message(std::make_shared<TextMessage>(1, 2000, false, "hi mom!"));
    auto message2 = chat.add_message(std::make_shared<AudioMessage>(2, 2040, false, 0xbaba, "wtf brah!"));

    std::cout << "Hello sailor!" << std::endl;

    message->print(std::cout);
    message2->print(std::cout);
    chat.read_unread_messages(std::cout);

    chat.add_message(std::make_shared<ImageMessage>(3, 2080, false, 0xfefe));
    chat.read_unread_messages(std::cout);

    app.add_chat(Chat(Person(3, "beijing", 3989345)));
    std::cout << app << std::endl;

    std::cout << app["beijing"].person.login << std::endl;
    std::cout << app["urmom"].person.login << std::endl;

    return 0;
}


// для operator[]
// посмотреть https://en.cppreference.com/w/cpp/language/operators
