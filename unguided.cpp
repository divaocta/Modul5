#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int TABLE_SIZE = 11;

struct Student
{
    string nim;
    int nilai;
};

class HashNode
{
public:
    Student data;
    HashNode *next;

    HashNode(const Student &data) : data(data), next(nullptr) {}

    ~HashNode()
    {
        // Add cleanup code if necessary
    }
};

class HashTable
{
private:
    vector<HashNode *> table;

    int hashFunc(const string &key)
    {
        int hashVal = 0;
        for (char c : key)
        {
            hashVal += c;
        }
        return hashVal % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE, nullptr) {}

    ~HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode *entry = table[i];
            while (entry != nullptr)
            {
                HashNode *prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    void insert(const Student &student)
    {
        int hashVal = hashFunc(student.nim);
        HashNode *prev = nullptr;
        HashNode *entry = table[hashVal];

        while (entry != nullptr && entry->data.nim != student.nim)
        {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr)
        {
            entry = new HashNode(student);

            if (prev == nullptr)
            {
                table[hashVal] = entry;
            }
            else
            {
                prev->next = entry;
            }
        }
        else
        {
            entry->data = student;
        }
    }

    void remove(const string &nim)
    {
        int hashVal = hashFunc(nim);
        HashNode *entry = table[hashVal];
        HashNode *prev = nullptr;

        while (entry != nullptr && entry->data.nim != nim)
        {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr)
        {
            cout << "Tidak ditemukan mahasiswa dengan NIM " << nim << endl;
        }
        else
        {
            if (prev == nullptr)
            {
                table[hashVal] = entry->next;
            }
            else
            {
                prev->next = entry->next;
            }
            delete entry;
            cout << "Mahasiswa dengan NIM " << nim << " telah dihapus." << endl;
        }
    }

    Student *searchByNIM(const string &nim)
    {
        int hashVal = hashFunc(nim);
        HashNode *entry = table[hashVal];

        while (entry != nullptr)
        {
            if (entry->data.nim == nim)
            {
                return &(entry->data);
            }
            entry = entry->next;
        }
        return nullptr;
    }

    vector<Student *> searchByValue(int minValue, int maxValue)
    {
        vector<Student *> results;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode *entry = table[i];
            while (entry != nullptr)
            {
                if (entry->data.nilai >= minValue && entry->data.nilai <= maxValue)
                {
                    results.push_back(&(entry->data));
                }
                entry = entry->next;
            }
        }
        return results;
    }
};

void displayMenu()
{
    cout << "Menu:\n";
    cout << "1. Tambah data mahasiswa\n";
    cout << "2. Hapus data mahasiswa\n";
    cout << "3. Cari data mahasiswa berdasarkan NIM\n";
    cout << "4. Cari data mahasiswa berdasarkan rentang nilai (80-90)\n";
    cout << "5. Keluar\n";
    cout << "Pilihan: ";
}

int main()
{
    HashTable hashTable;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string nim;
            int nilai;
            cout << "Masukkan NIM: ";
            cin >> nim;
            cout << "Masukkan nilai: ";
            cin >> nilai;
            Student student = {nim, nilai};
            hashTable.insert(student);
            break;
        }
        case 2:
        {
            string nim;
            cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
            cin >> nim;
            hashTable.remove(nim);
            break;
        }
        case 3:
        {
            string nim;
            cout << "Masukkan NIM mahasiswa yang akan dicari: ";
            cin >> nim;
            Student *student = hashTable.searchByNIM(nim);
            if (student)
            {
                cout << "NIM: " << student->nim << ", Nilai: " << student->nilai << endl;
            }
            else
            {
                cout << "Mahasiswa tidak ditemukan." << endl;
            }
            break;
        }
        case 4:
        {
            int minValue = 80, maxValue = 90;
            vector<Student *> students = hashTable.searchByValue(minValue, maxValue);
            if (!students.empty())
            {
                cout << "Mahasiswa dengan nilai antara " << minValue << " dan " << maxValue << ":\n";
                for (Student *student : students)
                {
                    cout << "NIM: " << student->nim << ", Nilai: " << student->nilai << endl;
                }
            }
            else
            {
                cout << "Tidak ada mahasiswa dengan nilai tersebut." << endl;
            }
            break;
        }
        case 5:
            cout << "Terima kasih telah menggunakan program ini." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
        cout << endl;
    } while (choice != 5);
    return 0;
}
