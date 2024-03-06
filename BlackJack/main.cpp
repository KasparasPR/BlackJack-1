#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Card {
    string suit;
    string rank;
    int value;
};

vector<Card> createDeck() {
    vector<Card> deck;
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (const string &suit : suits) {
        for (int i = 0; i < 13; ++i) {
            Card card;
            card.suit = suit;
            card.rank = ranks[i];
            card.value = values[i];
            deck.push_back(card);
        }
    }
    return deck;
}

void shuffleDeck(vector<Card> &deck) {
    srand(time(0));
    for (int i = 0; i < deck.size(); ++i) {
        int j = rand() % deck.size();
        swap(deck[i], deck[j]);
    }
}

int handTotal(const vector<Card> &hand) {
    int total = 0;
    int numAces = 0;
    for (const Card &card : hand) {
        total += card.value;
        if (card.rank == "Ace") {
            numAces++;
        }
    }
    while (total > 21 && numAces > 0) {
        total -= 10;
        numAces--;
    }
    return total;
}

void displayHand(const vector<Card> &hand) {
    for (const Card &card : hand) {
        cout << card.rank << " of " << card.suit << endl;
    }
}

int main() {
    cout << "Welcome to Blackjack!\n" << endl;
    cout << "If you want to play type yes" << endl<<endl;
    string play;
    cin >> play;
    if (play != "yes") {
        return 0;
    }

    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    vector<Card> playerHand;
    vector<Card> dealerHand;


    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();
    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();

    cout << "Your hand:" << endl;
    displayHand(playerHand);
    cout << "Dealer's hand:" << endl;
    cout << "Hidden" << endl;

    while (handTotal(playerHand) < 21) {
        cout << "Do you want to hit or stand? (h/s): "<<endl<<endl;
        char choice;
        cin >> choice;
        if (choice == 'h') {
            playerHand.push_back(deck.back());
            deck.pop_back();
            cout << "Your hand:" << endl;
            displayHand(playerHand);
            if (handTotal(playerHand) > 21) {
                cout << "You busted! Dealer wins." << endl;
                return 0;
            }
        } else if (choice == 's') {
            break;
        }
    }


    cout << "Dealer's turn:" << endl;
    cout << "Dealer's hand:" << endl;
    displayHand(dealerHand);
    while (handTotal(dealerHand) < 17) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
        cout << "Dealer hits." << endl;
        cout << "Dealer's hand:" << endl;
        displayHand(dealerHand);
    }


    int playerTotal = handTotal(playerHand);
    int dealerTotal = handTotal(dealerHand);
    cout << "Your total: " << playerTotal << endl;
    cout << "Dealer's total: " << dealerTotal << endl;

    if (playerTotal > dealerTotal || dealerTotal > 21) {
        cout << "Congratulations! You win!" << endl;
    } else if (playerTotal < dealerTotal) {
        cout << "Sorry, you lose. Dealer wins." << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
    cout << "Do you want to play again? Type y if yes, n if no" << endl;
    string again;
    cin >> again;
    if (again == "y") {
        return main();
    }else{
    return 0;
}
}
