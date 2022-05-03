# Contact diary using Trie Data Structure

> ### We have implemented contact diary with information of contact number and contact name with features like
<hr>

- Insert new contact.
- Search contact with particular name.
- Search contact with particular number.
- Search all contacts with particular name prefix.
- Search all contacts with particular number prefix.
- Delete contact with a particular contact name.
- Delete contact with a particular contact number.
- Update particular contact number by using contact name.
- Update particular contact name by using contact number.
- Print the whole contact diary.

> ### How to run
<hr>

1) Make executable

```bash 
$gcc assignment.cpp -o assignment.exe
```
2) Run executable

```bash 
$ assignment.exe
```
or

```bash 
$ g++ -o assignment assignment.cpp
```

> ### Details

- We have implemented all above features with the help of <b>2 trie structures</b> 
1) trie of name
2) trie of number

- We handled the updation of both trie after each operation.

- We have provided the menu of options so user can perform as much operation as he/she wants. 

- We have also handled unexpected behaviour that can happen like trying to delete or update contact that doesn't exist.