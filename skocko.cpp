#include <bits/stdc++.h>
using namespace std;

vector <int> valid_combination;
int total_guesses = 0, unsuccessful_attempts = 0;
void skocko();

void read_stats(int *total_guesses, int *unsuccessful_attempts)
{
    ifstream statsFile("skocko_stats.txt");
    if (statsFile.is_open()) {
        statsFile >> *total_guesses >> *unsuccessful_attempts;
        statsFile.close();
    }
}
void write_stats()
{
    ofstream outputFile("skocko_stats.txt");
    if (outputFile.is_open()) {
        outputFile << total_guesses << " " << unsuccessful_attempts;
        outputFile.close();
    } else {
        cout << "Error: Unable to open the stats file." << endl;
    }
}

void print_stats() {
    cout << "Statistics:\n";
    cout << "Total Guesses: " << total_guesses << endl;
    cout << "Unsuccessful Attempts: " << unsuccessful_attempts << endl;
    cout << "Successful Attempts: " << total_guesses - unsuccessful_attempts << endl;
}

void see_stats()
{
    cout << "Do you want to see your all time statistics? (YES/NO)" << endl;
    string check_stats;
    cin >> check_stats;
    for (int i = 0; i < 3; i++)
        check_stats[i] = toupper(check_stats[i]);
    if (check_stats == "NO") return;
    else if (check_stats != "YES")
    {
        cout << "Please enter \"YES\" or \"NO\"" << endl;
        see_stats();
        return;
    }
    print_stats();
}

void print_Skocko_rules()
{
    cout << "Do you want to read the rules? (YES/NO)" << endl;
    string read_rules;
    cin >> read_rules;
    for (int i = 0; i < 3; i++)
        read_rules[i] = toupper(read_rules[i]);
    if (read_rules == "NO") return;
    else if (read_rules != "YES")
    {
        cout << "Please enter \"YES\" or \"NO\"" << endl;
        print_Skocko_rules();
        return;
    }
    string filename = "skocko_rules.txt";
    ifstream rulesFile(filename);

    if (!rulesFile.is_open()) {
        cout << "Error: Unable to open the rules file.\n";
        return;
    }

    string line;
    while (getline(rulesFile, line)) {
        cout << line << '\n';
    }

    rulesFile.close();
}

void skocko_game_flow()
{
    cout << "Do you want to play again? (YES/NO)" << endl;
    string play_again;
    cin >> play_again;
    for (int i = 0; i < 3; i++)
        play_again[i] = toupper(play_again[i]);
    if (play_again == "NO")
        {see_stats(); return;}
    else if (play_again != "YES")
    {
        cout << "Please enter \"YES\" or \"NO\"" << endl;
        skocko_game_flow();
    } else skocko();
}

void countyellow(vector <int> guess, int *yellow)
{
    vector <int> valid_combination_copy = valid_combination;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (guess[i] == valid_combination_copy[j])
            {
                (*yellow)++;
                valid_combination_copy[j] = 0;
                break;
            }
        }
    }
}

void countred(vector <int> guess, int *red)
{
    for (int i = 0; i < 4; i++)
        if (valid_combination[i] == guess[i]) 
            (*red)++;
}
void skocko()
{
    read_stats(&total_guesses, &unsuccessful_attempts);
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 4; i++)
        valid_combination.push_back(rand() % 6 + 1);
    int i = 0;
    for(; i < 7; i++)
    {
        vector <int> guess(4);
        cout << "Enter the combination" << endl;
        for (int & x: guess) cin >> x;
        int yellow = 0, red = 0;
        countyellow(guess, &yellow);
        countred(guess, &red);
        yellow -=  red;
        if (red == 4) {
            cout << "Correct!" << endl;
            cout << "You got it in " << i + 1 << " tries." << endl;
            cout << "The guessed combination was:" << endl;
            for (int &x : valid_combination) cout << x << " ";
            cout << endl;
            total_guesses++;
            break;
        } else {
            cout << "Red matches: " << red << endl;
            cout << "Yellow matches: " << yellow << endl;
        }
    }
    if (i == 7)
    {
        cout << "You lost!" << endl;
        cout << "The correct combination was:" << endl;
        for (int &x : valid_combination) cout << x << " ";
        unsuccessful_attempts++;
        total_guesses++;
    }
    cout << endl;
    valid_combination.clear();
    write_stats();
    skocko_game_flow();
}

int main()
{
    print_Skocko_rules();
    skocko();
}