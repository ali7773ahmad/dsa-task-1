
#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:

    // Constructor
    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Add request according to priority
    void Add(BookRequestNode* request)
    {
        request->next = NULL;

        if (front == NULL)
        {
            front = rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* temp = front;

            while (temp->next != NULL &&
                   temp->next->priority <= request->priority)
            {
                temp = temp->next;
            }

            request->next = temp->next;
            temp->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }

        count++;
    }

    // Remove highest-priority request
    BookRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BookRequestNode* temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        temp->next = NULL;
        count--;

        return temp;
    }

    // Check if empty
    bool IsEmpty()
    {
        return front == NULL;
    }

    // Check if not empty
    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Display all requests
    void PrintQueue()
    {
        if (front == NULL)
        {
            cout << "No book requests." << endl;
            return;
        }

        BookRequestNode* temp = front;

        while (temp != NULL)
        {
            cout << "\nStudent ID: " << temp->studentID << endl;
            cout << "Student Name: " << temp->studentName << endl;
            cout << "Book ID: " << temp->bookID << endl;
            cout << "Book Title: " << temp->bookTitle << endl;
            cout << "Priority: " << temp->priority << endl;
            cout << "------------------------" << endl;

            temp = temp->next;
        }
    }

    // Copy constructor
    PriorityQueue(const PriorityQueue& other)
    {
        front = NULL;
        rear = NULL;
        count = 0;

        BookRequestNode* temp = other.front;

        while (temp != NULL)
        {
            BookRequestNode* newNode = new BookRequestNode;

            newNode->studentID = temp->studentID;
            newNode->studentName = temp->studentName;
            newNode->bookID = temp->bookID;
            newNode->bookTitle = temp->bookTitle;
            newNode->priority = temp->priority;

            Add(newNode);
            temp = temp->next;
        }
    }

    // Assignment operator
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;

        BookRequestNode* temp = other.front;

        while (temp != NULL)
        {
            BookRequestNode* newNode = new BookRequestNode;

            newNode->studentID = temp->studentID;
            newNode->studentName = temp->studentName;
            newNode->bookID = temp->bookID;
            newNode->bookTitle = temp->bookTitle;
            newNode->priority = temp->priority;

            Add(newNode);
            temp = temp->next;
        }

        return *this;
    }

    // Destructor
    ~PriorityQueue()
    {
        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
    }
};

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====" << endl;
        cout << "1. Add Book Request" << endl;
        cout << "2. Process Highest Priority Request" << endl;
        cout << "3. Display All Requests" << endl;
        cout << "4. Check Queue Status" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            BookRequestNode* request = new BookRequestNode;

            cout << "Enter Student ID: ";
            cin >> request->studentID;

            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, request->studentName);

            cout << "Enter Book ID: ";
            cin >> request->bookID;

            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, request->bookTitle);

            cout << "Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ";
            cin >> request->priority;

            if (request->priority < 1 || request->priority > 3)
            {
                cout << "Invalid priority. Use 1, 2, or 3." << endl;
                delete request;
            }
            else
            {
                requests.Add(request);
                cout << "Request added successfully." << endl;
            }
        }
        else if (choice == 2)
        {
            BookRequestNode* served = requests.Remove();

            if (served == NULL)
            {
                cout << "No requests to process." << endl;
            }
            else
            {
                cout << "\nProcessing Request:" << endl;
                cout << "Student: " << served->studentName << endl;
                cout << "Book: " << served->bookTitle << endl;
                cout << "Priority: " << served->priority << endl;

                delete served;
            }
        }
        else if (choice == 3)
        {
            requests.PrintQueue();
        }
        else if (choice == 4)
        {
            if (requests.IsEmpty())
            {
                cout << "Priority Queue is empty." << endl;
            }
            else if (requests.IsNotEmpty())
            {
                cout << "Priority Queue has pending requests." << endl;
            }
        }
        else if (choice == 5)
        {
            cout << "Program ended." << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}
