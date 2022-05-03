#include<bits/stdc++.h>
using namespace std;

class Assignment{
    public :
    struct Namenode{
        bool isEnd;
        vector <Namenode*> children;
        string number;

        Namenode(){
            isEnd = false;
            children.resize(26);
            for(auto child : children) child = NULL;
            number = "";
        }
    };

    struct Numbernode{
        bool isEnd;
        vector <Numbernode*> children;
        string name;

        Numbernode(){
            isEnd = false;
            children.resize(10);
            for(auto child : children) child = NULL;
            name = "";
        }
    };

    Namenode *nameroot;
    Numbernode *numberroot;

    Assignment(){
        nameroot = new Namenode();
        numberroot = new Numbernode();
    }

    // 1. insert
    void insert(){
        string name;
        string number;

        cout << "Enter Name :- ";
        cin >> name;

        cout << "Enter Number :- ";
        cin >> number;

        Namenode *node = nameroot;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';
            if(!node -> children[idx]){
                node -> children[idx] = new Namenode();
            }
            node = node -> children[idx];
            if(i == name.size() - 1){
                if(node -> isEnd == 1){
                    cout << "The entered name already has previous number saved. Please choose update option if you want to change the number for this name." << endl;
                    return;
                }
            }
        }

        Numbernode *numnode = numberroot;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';
            if(!numnode -> children[idx]){
                numnode -> children[idx] = new Numbernode();
            }
            numnode = numnode -> children[idx];
            if(i == number.size() - 1){
                if(numnode -> isEnd == 1){
                    cout << "The entered number already has previous name saved. Please choose update option if you want to change the name for this number." << endl;
                    return;
                }
                node -> isEnd = 1;
                node -> number = number;
                numnode -> isEnd = 1;
                numnode -> name = name;
            }
        }
    }

    //2. search with number
    void search_number(){
        string number;
        cout << "Enter number :- ";
        cin >> number;

        Numbernode *node = numberroot;

        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';

            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact with entered number." << endl;
                return;
            }
        }

        if(node -> isEnd){
            cout << "Name for the entered number in contact diary is :- " << node -> name << endl;
        }
        else{
            cout << "There is no contact with entered number." << endl;
        }
    }

    //3. Search with name
    void search_name(){
        string name;
        cout << "Enter name :- ";
        cin >> name;

        Namenode *node = nameroot;

        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';

            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact with entered name." << endl;
                return;
            }
        }

        if(node -> isEnd){
            cout << "Number for the entered name in contact diary is :- " << node -> number << endl;
        }
        else{
            cout << "There is no contact with entered name." << endl;
        }
    }

    //support function for 4 dfs_name
    void dfs_name(Namenode *node, string name, vector <pair<string, string>> &ans){
        if(node -> isEnd){
            ans.push_back({name, node -> number});
        }

        for(int i = 0; i < 26; i ++){
            if(node -> children[i]){
                string passname = name + (char)(i + 'a');
                dfs_name(node -> children[i], passname, ans);
            }
        }
    }

    //4. prefix search with name
    void pref_search_name(){
        string name;
        cout << "Enter name prefix :- ";
        cin >> name;

        Namenode *node = nameroot;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';

            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact with entered name." << endl;
                return;
            }
        }

        vector <pair<string, string>> ans;
        dfs_name(node, name, ans);

        if(ans.size() == 0){
            cout << "There is no contact with entered name." << endl;
            return;
        }

        cout << "There is " << ans.size() << " contacts with following entered name prefix" << endl;
        for(int i = 0; i < ans.size(); i ++){
            cout << ans[i].first << " - " << ans[i].second << endl;
        }
    }

    //support function for 5 dfs_number
    void dfs_number(Numbernode *node, string number, vector <pair<string, string>> &ans){
        if(node -> isEnd){
            ans.push_back({node -> name, number});
        }

        for(int i = 0; i < 10; i ++){
            if(node -> children[i]){
                string passnumber = number + (char)(i + '0');
                dfs_number(node -> children[i], passnumber, ans);
            }
        }
    }

    //5. prefix search with number
    void pref_search_number(){
        string number;
        cout << "Enter number prefix :- ";
        cin >> number;

        Numbernode *node = numberroot;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';

            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact with entered number." << endl;
                return;
            }
        }

        vector <pair<string, string>> ans;
        dfs_number(node, number, ans);

        if(ans.size() == 0){
            cout << "There is no contact with entered number." << endl;
            return;
        }

        cout << "There is " << ans.size() << " contacts with following entered number prefix" << endl;
        for(int i = 0; i < ans.size(); i ++){
            cout << ans[i].second << " - " << ans[i].first << endl;
        }
    }

    //6. delete contact with name
    void del_name(){
        string name;
        cout << "Enter name you want to delete contact of :- ";
        cin >> name;

        Namenode *node = nameroot;
        string number;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';
            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact available with entered name." << endl;
                return;
            }
        }

        if(!node -> isEnd){
            cout << "There is no contact available with entered name." << endl;
            return;
        }

        number = node -> number;
        node -> isEnd = 0;
        node -> number = "";

        Numbernode *numnode = numberroot;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';
            numnode = numnode -> children[idx];
        }

        numnode -> isEnd = 0;
        numnode -> name = "";

        cout << "Deleted contact :- " << name << " - " << number << endl;
    }

    //7. delete contact with number
    void del_number(){
        string number;
        cout << "Enter number you want to delete contact of :- ";
        cin >> number;

        Numbernode *node = numberroot;
        string name;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';
            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact available with entered number." << endl;
                return;
            }
        }

        if(!node -> isEnd){
            cout << "There is no contact available with entered number." << endl;
            return;
        }

        name = node -> name;
        node -> isEnd = 0;
        node -> name = "";

        Namenode *namenode = nameroot;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';
            namenode = namenode -> children[idx];
        }

        namenode -> isEnd = 0;
        namenode -> number = "";

        cout << "Deleted contact :- " << name << " - " << number << endl;
    }

    //8. Update with name
    void update_name(){
        string name;
        string number;
        cout << "Enter name to update:- ";
        cin >> name;
        cout << "Enter new number :-";
        cin >> number;

        Namenode *node = nameroot;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';
            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact available with entered name." << endl;
                return;
            }
        }

        if(!node -> isEnd){
            cout << "There is no contact available with entered name." << endl;
            return;
        }

        if(node -> number == number){
            cout << "Entered number is same as previous entered number for this name." << endl;
            return;
        }

        string oldnumber = node -> number;

        Numbernode *numnode = numberroot;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';

            if(!numnode -> children[idx]) numnode -> children[idx] = new Numbernode();
            numnode = numnode -> children[idx];

            if(i == number.size() - 1){
                if(numnode -> isEnd == 1){
                    cout << "Entered number is already present in the dairy." << endl;
                    return; 
                }
                numnode -> isEnd = 1;
                numnode -> name = name;
                node -> number = number;
                cout << "Old contact :- " << name << " - " << oldnumber << endl;
                cout << "Updated contact :- " << name << " - " << node -> number << endl;
            }
        }

        numnode = numberroot;
        for(int i = 0; i < oldnumber.size(); i ++){
            int idx = oldnumber[i] - '0';

            numnode = numnode -> children[idx];
            if(i == oldnumber.size() - 1){
                numnode -> isEnd = 0;
                numnode -> name = "";
            }
        }
    }

    //9.Update with number
    void update_number(){
        string name;
        string number;
        cout << "Enter number to update:- ";
        cin >> number;
        cout << "Enter new name :-";
        cin >> name;

        Numbernode *node = numberroot;
        for(int i = 0; i < number.size(); i ++){
            int idx = number[i] - '0';
            if(node -> children[idx]) node = node -> children[idx];
            else{
                cout << "There is no contact available with entered number." << endl;
                return;
            }
        }

        if(!node -> isEnd){
            cout << "There is no contact available with entered number." << endl;
            return;
        }

        if(node -> name == name){
            cout << "Entered name is same as previous entered name for this number." << endl;
            return;
        }

        string oldname = node -> name;

        Namenode *namenode = nameroot;
        for(int i = 0; i < name.size(); i ++){
            int idx = name[i] - 'a';

            if(!namenode -> children[idx]) namenode -> children[idx] = new Namenode();
            namenode = namenode -> children[idx];

            if(i == name.size() - 1){
                if(namenode -> isEnd == 1){
                    cout << "Entered number is already present in the dairy." << endl;
                    return; 
                }
                namenode -> isEnd = 1;
                namenode -> number = number;
                node -> name = name;
                cout << "Old contact :- " << number << " - " << oldname << endl;
                cout << "Updated contact :- " << number << " - " << node -> name << endl;
            }
        }

        namenode = nameroot;
        for(int i = 0; i < oldname.size(); i ++){
            int idx = oldname[i] - 'a';

            namenode = namenode -> children[idx];
            if(i == oldname.size() - 1){
                namenode -> isEnd = 0;
                namenode -> number = "";
            }
        }
    }

    //10. Print whole diary
    void print_diary(){
        vector <pair<string, string>> ans;
        dfs_name(nameroot, "", ans);

        cout << "Total number of contacts :- " << ans.size() << endl;
        for(int i = 0; i < ans.size(); i ++){
            cout << ans[i].first << " " << ans[i].second << endl;
        }
    }
};

int main(){
    Assignment obj;
    while(1){
        cout << "Enter your choice :- " << endl;
        cout << "1. Insert contact" << endl;
        cout << "2. Search with number" << endl;
        cout << "3. Search with name" << endl;
        cout << "4. Prefix name search" << endl;
        cout << "5. Prefix number search" << endl;
        cout << "6. Delete contact with name" << endl;
        cout << "7. Delete contact with number" << endl;
        cout << "8. Update contact with name" << endl;
        cout << "9. Update contact with number" << endl;
        cout << "10. Print whole diary" << endl;
        cout << "11. Exit" << endl;
        cout << "---------------------------------------------" << endl;

        int choice;
        cin >> choice;

        if(choice == 1){
            obj.insert();
        }
        else if(choice == 2){
            obj.search_number();
        }
        else if(choice == 3){
            obj.search_name();
        }
        else if(choice == 4){
            obj.pref_search_name();
        }
        else if(choice == 5){
            obj.pref_search_number();
        }
        else if(choice == 6){
            obj.del_name();
        }
        else if(choice == 7){
            obj.del_number();
        }
        else if(choice == 8){
            obj.update_name();
        }
        else if(choice == 9){
            obj.update_number();
        }
        else if(choice == 10){
            obj.print_diary();
        }
        else if(choice == 11){
            break;
        }
        else{
            cout << "Enter valid choice" << endl;
        }

        cout << endl;
        cout << endl;
    }

    return 0;
}