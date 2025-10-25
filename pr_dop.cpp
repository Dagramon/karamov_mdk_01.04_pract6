#include <iostream>

struct Node
{
    void (*handler)(const std::string&);
    Node* next;
    Node(void(*value)(const std::string&)) : handler(value), next(nullptr) {};
};
struct EventSystem
{
    Node* head;
    Node* tail;
    EventSystem() : head(nullptr), tail(nullptr) {};
};

void RegisterHandler(EventSystem &system, void(*handler)(const std::string&))
{
    Node* newNode = new Node(handler);
    if (system.head != nullptr)
    {
        system.head->next = newNode;
        system.head = newNode;
    }
    else
    {
        system.head = newNode;
        system.tail = newNode;
    }
}

void TriggerEvent(const EventSystem &system, const std::string& args)
{
    if (system.head != nullptr)
    {
        Node* currentNode = system.tail;
        while (currentNode != nullptr)
        {
            currentNode->handler(args);
            currentNode = currentNode->next;
        }
    }
}

void OnUserLogin(const std::string& user)
{
    std::cout << user << " has entered the system" << std::endl;
}
void OnUserLogout(const std::string& user)
{
    std::cout << user << " has left the system" << std::endl;
}
void OnError(const std::string& args)
{
    std::cout << "Error has occured" << std::endl;
}
void Handler(const std::string& message)
{
    std::cout << message << std::endl;
}

int main()
{
    EventSystem system;
    RegisterHandler(system, OnUserLogin);
    RegisterHandler(system, OnUserLogout);
    RegisterHandler(system, OnError);
    RegisterHandler(system, Handler);

    TriggerEvent(system, "useeeer");

    return 0;
}