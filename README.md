**Nume: Mihaicuta Iulia**
**Grupa: 314CA**

## Tema 1 - Now You See Me

### Descriere:

* Programul efectueaza diferite operatii cu pachete de carti pe baza unor
operatii citite de la tastatura.

* functia validate_command(uint nr_arg, uint *idx1, uint *idx2) verifica daca
numarul argumentelor continute de comanda este corect si face parsarea acesteia.
Returneaza 1 daca comanda este corecta, sau 0 in caz contrar

* add_deck() citeste nr_cards carti valide cu get_card_value() si le adauga in
intr-un nou deck la sfarsitul pachetului.

* del_deck() primeste ca parametru verif. Acesta are valoarea 1 daca functia
este apelata din del_card(), sau 0 daca indexul deck-ului se va citi de la
tastatura; folosim functiile dll_remove_nth_node() si dll_free_list() pentru
eliberare

* del_card() verifica daca deck_index si card_index sunt in intervalul
pachetului; daca deck-ul contine o singura carte acesta este eliminat din
pachet cu del_deck() - in caz contrar, cartea este eliminata din deck

* add_cards() adauga nr_cards carti valide intr-un deck dat; cartile sunt
citite de functia get_card_value() si adaugate de dll_add_nth_node()

* deck_number() si deck_len() apeleaza size din structura pentru lista

* shuffle_deck() inverseaza prima si a doua jumatate a pachetului; functia
dll_get_nth_node() ofera acces la nodul din mijloc si la cel de la finalul
listei

* merge_decks() sterge pachetele initiale din lista cu dll_remove_nth_node()
si adauga cartile acestora la un nou deck la finalul pachetului prin
parcurgerea deck - urilor initiale si cu functia dll_add_nth_node()

* split_deck() adauga noul deck pe pozitia urmatoare si seteaza noile capete
pentru deck - urile obtinute

* reverse_deck() apeleaza functia dll_move_last() pentru a reordona
deck - ul, daca acesta are cel putin 2 carti

* sort_deck() foloseste functia swap_cards() pentru a inversa 2 carti pentru
a le ordona in ordine corespunzatoare; daca acestea au aceeasi valoare, ne vom
folosi de simbol pentru a le ordona

* show_deck() foloseste functia print_symbol() pentru a afisa toate cartile
corespunzatoare fiecarui deck

* show_all afiseaza toate deck - urile salvate in memorie cu ajutorul functiei
show_deck() - unde verif == 1

* Comanda exit apeleaza functia free_pack() ce elibereaza toate resursele
folosite de program

### Comentarii asupra temei

* Se pot adauga anumite verificari folosite in programarea defensiza, pentru a
asigura a buna functionare a programului